#include <libhaggle/haggle.h>

#include <sstream>
#include <stdio.h>
#include <cstring> 
#include <signal.h>
#include <iostream>

#include <pthread.h>
#include <libgen.h>

typedef pthread_mutex_t mutex_t;

#define APP_NAME "MoLu"

haggle_handle_t	haggle_;
dataobject* dObject;


char *snd_attributes = NULL;
char *recv_attributes = NULL;

char *file_path = NULL;

//char hagglefilepath[] = "~/.Haggle/test.txt";

static enum {
	Snd_node,
	Recv_node,
	node_NONE
} which_node;
	

static void cleanup(int signal)
{
	switch(signal) {
	case SIGKILL:
	case SIGHUP:
	case SIGINT:
	case SIGTERM:
		haggle_handle_free(haggle_);
		haggle_dataobject_free(dObject);
		printf("Cleaned up\n");
		exit(EXIT_SUCCESS);
		break;
	default:
		break;
	}
}

static void print_usage()
{
	
	printf(
		"%s \n"
		"\n"
		"\t-s\tCauses this program to behave as sender.\n"
		"\t-i\tInterest.\n"
		"\t-f\tFilePath.\n"
		"\n",
		APP_NAME);
}

static void parse_commandline(int argc, char **argv)
// Parses our command line arguments into the global variables 
// listed above.
{
	int ch;
	
	which_node = node_NONE;
	
	// Parse command line options using getopt.
	
	do {
		ch = getopt(argc, argv,"s:r:f:");
		if (ch != -1) {
			switch (ch) {
				case 'r':
					//which_node = Recv_node;
					recv_attributes = optarg;
					break;
				case 'f':
					file_path = optarg;
					break;
				case 's':
					snd_attributes = optarg;
					which_node = Snd_node;
					break;
				default:
					print_usage();
					exit(1);
					break;
			}
		}
	} while (ch != -1);
	
	// Check for any left over command line arguments.
	
	if (optind != argc) {
		print_usage();
		fprintf(stderr, "%s: Unexpected argument '%s'\n", argv[0], argv[optind]);
		exit(1);
	}
	
}

void haggle_receive_file()
{
	
	if (recv_attributes!=NULL)
	{
			haggle_ipc_add_application_interest(haggle_, APP_NAME, recv_attributes);
			sleep(10);
		
	}
}

dataobject* haggle_send_file(haggle_handle_t hh,char *file_name)
{
	struct dataobject *dObj;
	
	if(file_name == NULL)
		dObj = haggle_dataobject_new();
		
	else
	
		dObj = haggle_dataobject_new_from_file(file_name);
	
	if(dObj != NULL)
	{
		haggle_dataobject_set_createtime(dObj, NULL);
		haggle_dataobject_add_attribute(dObj, APP_NAME, snd_attributes);
		haggle_dataobject_set_flags(dObj, DATAOBJECT_FLAG_PERSISTENT);
		while (1)
		{
			sleep(150);
			haggle_receive_file();		
			sleep(150);
			haggle_ipc_publish_dataobject(hh, dObj);
			sleep(50);
			
		}
		
	}
	//haggle_dataobject_free(dObj);
	//return dObj;
}



void create_interest(char* interest) 
{
	struct attributelist *al;
	if (! haggle_attributelist_new())
	{
		LIBHAGGLE_DBG("Fail to create interest list");
	}
	
	struct attribute *attr = haggle_attribute_new_weighted(APP_NAME, interest, 1);
	
	haggle_attributelist_add_attribute(al, attr);

	haggle_ipc_add_application_interests(haggle_, al);
	
	haggle_attributelist_free(al);

}

int on_interests(haggle_event_t *e, void* nix)
{
	LIBHAGGLE_DBG("Received application interests event\n");

	if (haggle_attributelist_get_attribute_by_name(e->interests, APP_NAME) != NULL) {
	
		list_t *pos;

		LIBHAGGLE_DBG("Checking existing interests\n");

		list_for_each(pos, &e->interests->attributes) {
			struct attribute *attr = (struct attribute *)pos;
			LIBHAGGLE_DBG("interest: %s=%s:%lu\n", 
			       haggle_attribute_get_name(attr), 
			       haggle_attribute_get_value(attr), 
			       haggle_attribute_get_weight(attr));
		}

	} else {
		LIBHAGGLE_DBG("No existing interests, generating new ones\n");
		
		if (recv_attributes != NULL)
		{
			create_interest(recv_attributes);
		}
				

	}
	
	return 0;
}

int main(int argc, char *argv[])
{
	
	int				retval = 1;
	
	struct sigaction sigact;
	memset(&sigact, 0, sizeof(struct sigaction));
	sigact.sa_handler = &cleanup;
	sigaction(SIGHUP, &sigact, NULL);
	sigaction(SIGINT, &sigact, NULL);
	sigaction(SIGKILL, &sigact, NULL);
	
	parse_commandline(argc,argv);

	if(which_node == node_NONE)
	{
		which_node = Recv_node;		

	}
	
	if(	haggle_handle_get(APP_NAME, &haggle_) != 
			HAGGLE_NO_ERROR)
	{
		LIBHAGGLE_ERR("ERROR: Haggle test application already running!\n");
		goto fail_err;
	}
	
	if (haggle_ipc_register_event_interest(haggle_, LIBHAGGLE_EVENT_INTEREST_LIST, on_interests) != 
			HAGGLE_NO_ERROR)
	{
			LIBHAGGLE_ERR("ERROR: Haggle event interest register fail!\n");
			goto fail_err;
	}
	
	
	switch(which_node)
	{
		case Snd_node:
			dObject=haggle_send_file(haggle_,file_path);
			break;
		case Recv_node:
			haggle_receive_file();
			break;
		default:
			printf("CODING ERROR: SHOULD NOT HAVE GOTTEN HERE!\n");
			goto fail_err;
		break;
	}
	
	// Make sure to return success:
	retval = 0;
	
fail_err:
	haggle_handle_free(haggle_);
	haggle_dataobject_free(dObject);

}
