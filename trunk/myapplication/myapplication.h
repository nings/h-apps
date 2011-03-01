
#include <libhaggle/haggle.h>

#include <sstream>
#include <stdio.h>
#include <cstring> 
#include <iostream>

//#include <utils/utils.h>
//#include <utils/base64.h>

#include "databuffer.h"

using namespace std;

char **neighbors = NULL;
unsigned long num_neighbors = 0;

#define ATTRIBUTE_NAME "test"
#define ATTRIBUTE_VALUE "app"

#define TIMEOUT 10
#define APP_NAME "myapplication"
#define MAX_DIR_LEN 512

char hagglefilepath[] = "/test.txt";
static char dirpath[MAX_DIR_LEN];

haggle_handle_t haggleHandle;

void getDirPath()
{
	strncpy(dirpath,getenv("HOME"),MAX_DIR_LEN);
	dirpath[strlen(dirpath)]='/';
	strncpy(dirpath+strlen(dirpath),".Haggle/test.txt",MAX_DIR_LEN-strlen(dirpath));
}

int getTime(char** res)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	
	int hour = (time.tv_sec) % (24*3600) / 3600;
	int min = (time.tv_sec) % (3600) / 60;
	int sec = (time.tv_sec) % (60);
	
	ostringstream timeString;
	timeString << hour << ":" << (min < 10 ? "0" : "") << min << ":" << (sec < 10 ? "0" : "") << sec;
	
	*res = (char*)malloc(strlen(timeString.str().c_str()));
	strcpy(*res, timeString.str().c_str());
	
	return 1;
}

//data_buffer mini_base64_decode(char *data, size_t len)
//{
	//data_buffer						retval;
	//struct base64_decode_context	ctx;
	//size_t							new_len;
	
	//base64_decode_ctx_init(&ctx);
	//if(!base64_decode_alloc(&ctx, data, len, &(retval.data), &new_len))
	//{
		//retval.data = NULL;
		//retval.len = 0;
	//}
	//retval.len = new_len;
	
	//return retval;
//}

//char *getAttributeTest(struct dataobject *dObj, char *name)
//{
	//char		*data, *value;
	//attribute	*attr;
	//data_buffer	buf;
	
	//attr = haggle_dataobject_get_attribute_by_name(dObj, name);
	//if(attr == NULL)
		//return NULL;
	
	//value = (char *) haggle_attribute_get_value(attr);
	//if(value == NULL)
		//return NULL;
	
	//buf =mini_base64_decode(value,strlen(value));
	//if(buf.data != NULL)
	//{
		//data = (char *) realloc(buf.data, buf.len + 1);
		//if(data == NULL)
			//return buf.data;
		
		//data[buf.len] = '\0';
	//}
	//return buf.data;
//}

void createDataObject()
{
	char* strTime;
	getTime(&strTime);

	printf("create DataObject (%s)\n", strTime);

	/* --- create dataobject --- */
	haggle_dobj_t *dObj;
	dObj = haggle_dataobject_new();	

	/* --- add attributes --- */
	haggle_dataobject_add_attribute(dObj, ATTRIBUTE_NAME, ATTRIBUTE_VALUE);
	haggle_dataobject_add_attribute(dObj, "Time0", strTime);
	haggle_dataobject_add_attribute(dObj, "Time1", strTime);
	haggle_dataobject_add_attribute(dObj, "Time2", strTime);
	haggle_dataobject_add_attribute(dObj, "Time3", strTime);
	haggle_dataobject_add_attribute(dObj, "Time4", strTime);
	haggle_dataobject_add_attribute(dObj, "Time5", strTime);
	
	haggle_ipc_publish_dataobject(haggleHandle, dObj);

	if (strTime) free(strTime);
}

/**
	This is called when haggle tells us there's a new data object we might be 
	interested in.
*/
int onDataObject(haggle_event_t *e, void *arg)
{
	printf("Event: Data Object Received\n");

	/* --- get filename --- */
	const char *filename = haggle_dataobject_get_filename(e->dobj);

	if (filename) {
		/* --- do something with file --- */
	}

	/* --- extract attributes --- */
	struct attribute *attr = NULL;
	
	int cnt = 0;
	while ((attr = haggle_dataobject_get_attribute_n(e->dobj, cnt++))) {
		printf("   Attribute: %s=%s\n", haggle_attribute_get_name(attr), haggle_attribute_get_value(attr));
	}

	/* --- cleanup --- */
	haggle_dataobject_free(e->dobj);
}


int onDataObjectXml(haggle_event_t *e, void *arg)
{
	printf("Event: Receive New data object Event\n");

	if (e->dobj)
	{
		//store_data_object(e->dobj);
		
		const unsigned char *xml = haggle_dataobject_get_raw(e->dobj);
		
		if (xml)
		{
			LIBHAGGLE_DBG("Received data object:\n%s\n", (const char *)xml);
			printf("Received data object:\n%s\n", (const char *)xml);
		}
		
	}
    
    return 1;
}

//int onDataObjectBbs(haggle_event_t *e, void *arg)
//{
	//char *the_topic;
	
	//char tmp[] = "Time";
	//the_topic = getAttributeTest(e->dobj, tmp);
	//if(the_topic == NULL)
		//goto fail_topic;
	
	//free(the_topic);
        //return 1;
        
//fail_topic:
	//return -1;
//}

int onDataObjectFile(haggle_event_t *e, void *arg)
{
	const char *filepath = haggle_dataobject_get_filepath(e->dobj);

	stringstream ResultString;
	
	if (!filepath || strlen(filepath) == 0) {
		return -1;		
	}
	
	cout << "Filepath is \'" << filepath << "\'" << endl;

	struct attribute *attr = NULL;
	int cnt = 0;

	ResultString << filepath ; 

	while ((attr = haggle_dataobject_get_attribute_n(e->dobj, cnt++))) {
		ResultString << haggle_attribute_get_name(attr) << "=" << haggle_attribute_get_value(attr) << " \r\n";
	}
        
    return 0;
}

//int onNeighborUpdate(haggle_event_t *e, void *arg)
//{
	//printf("Event: Neighbor update\n");
	///* --- extract nodes --- */
	//haggle_nodelist_t *nl;
	
	//nl = haggle_nodelist_new_from_dataobject(e->dobj);

	//if (!nl) {
		//fprintf(stderr, "Could not create nodelist from data object\n");
		//return 0;
	//}
	//list_t *pos;
	//list_for_each(pos, &nl->nodes) {
		//haggle_node_t *node = (haggle_node_t *)pos;

		//printf("   Neighbor: %s\n", haggle_node_get_name(node));
	//}
	///* --- cleanup --- */
	//haggle_nodelist_free(nl);
	//haggle_dataobject_free(e->dobj);
//}

static void neighborListClear()
{
	unsigned long i;

	if (num_neighbors) {
		for (i = 0; i < num_neighbors; i++) {
			free(neighbors[i]);
		}
		free(neighbors);
	}
	num_neighbors = 0;
	neighbors = NULL;
}

int onNeighborUpdate(haggle_event_t *e, void* arg)
{
	printf("Event: Neighbor update\n");
	
	haggle_nodelist_t *nl = e->neighbors;
	unsigned long i;
	
	neighborListClear();

	LIBHAGGLE_DBG("number of neighbors is %lu\n", num_neighbors);
	
	if (num_neighbors > 0) {
		neighbors = (char **)malloc(sizeof(char *) * num_neighbors);
		
		if (!neighbors) {
			num_neighbors = 0;
		} else {
			list_t *pos;
			i = 0;
			list_for_each(pos, &nl->nodes) {
				haggle_node_t *n = (haggle_node_t *)pos;
				neighbors[i] = (char *)malloc(strlen(haggle_node_get_name(n)) + 1);
				
				if (neighbors[i]) {
					strcpy(neighbors[i], haggle_node_get_name(n));
				}
				i++;
			}
		}
	} 
	
	return 1;
}

int onInterestList(haggle_event_t *e, void* arg){
	
	printf("Event: Interest update\n");

        // Loop through and list interests:
        bool not_done = true;
        int i = 0;

        while(not_done)
        {
                struct attribute *a;
		
                a = haggle_attributelist_get_attribute_n(e->interests, i);

                if(a == NULL)
                {
                        not_done = false;
                }else{
                        printf("Interest: %s=%s:%ld\n",
                               haggle_attribute_get_name(a),
                               haggle_attribute_get_value(a),
                               haggle_attribute_get_weight(a));
                        i++;
                }
        }
        return 1;
        
}

//send contacts
struct dataobject* haggle_publish_contacts_info(haggle_handle_t hh,char *file_name)
{
	struct dataobject *dObj;
	char* strTime;
	getTime(&strTime);
	
	// New data object:
	if(file_name == NULL)
		dObj = haggle_dataobject_new();
	else
		dObj = haggle_dataobject_new_from_file(file_name);
	
	printf("DataObject Created (%s)\n", strTime);
	
	if(dObj != NULL)
	{
		// Set create time to "now":
		haggle_dataobject_set_createtime(dObj, NULL);
		
		// Add attribute:
		haggle_dataobject_add_attribute(dObj, ATTRIBUTE_NAME, ATTRIBUTE_VALUE);
		
		printf("   %s=%s\n", ATTRIBUTE_NAME, ATTRIBUTE_VALUE);
		//haggle_dataobject_add_attribute(dObj, "Time", strTime);
		// Make sure the data object is permanent:
		haggle_dataobject_set_flags(dObj, DATAOBJECT_FLAG_PERSISTENT);
		
		// Publish:
		haggle_ipc_publish_dataobject(hh, dObj);
	}

	if (strTime) free(strTime);
	
	return dObj;
}

//receive contacts
void haggle_express_contacts_interests(haggle_handle_t hh)
{
	
	struct attribute *attr;
	haggle_attrlist_t *al;
	 //= haggle_attributelist_new_from_string(str);

	attr = haggle_attribute_new_weighted(ATTRIBUTE_NAME, ATTRIBUTE_VALUE, 1);
	
   	haggle_attributelist_add_attribute(al, attr);
                
	if (!al)
		return;

	haggle_ipc_add_application_interests(hh,al);

	haggle_attributelist_free(al);
}

void sendEventLoop() {
	
	fd_set readfds;
	int result = 0;
	struct timeval timeout;
	static volatile int StopNow = 0;
	
	struct dataobject *dobj;

	while (!StopNow) {
		unsigned int nfds = 0;
		timeout.tv_sec = TIMEOUT;
		timeout.tv_usec = 0;

		FD_ZERO(&readfds);

		result = select(nfds, &readfds, NULL, NULL, &timeout);
		
			if (result < 0)
			{
				StopNow = 1;
			}else
			{
				dobj=haggle_publish_contacts_info(haggleHandle,dirpath);
			}
				
	}
}

void recvEventLoop() {
	
	fd_set readfds;
	int result = 0;
	struct timeval timeout;
	static volatile int StopNow = 0;
	
	struct dataobject *dobj;

	while (!StopNow) {
		unsigned int nfds = 0;
		timeout.tv_sec = TIMEOUT;
		timeout.tv_usec = 0;

		FD_ZERO(&readfds);

		result = select(nfds, &readfds, NULL, NULL, &timeout);
		

			if (result < 0) {
				// error
				StopNow = 1;
			} else {
				// timeout
				haggle_ipc_add_application_interest_weighted(
				haggleHandle, 
				ATTRIBUTE_NAME, 
				ATTRIBUTE_VALUE,
				1);
				
				const unsigned char *xml = haggle_dataobject_get_raw(dobj);
				if (xml)
				{
					LIBHAGGLE_DBG("Sending data object:\n%s\n", (const char *)xml);
					printf("Sending data object:\n%s\n", (const char *)xml);
				}
			}
		
	}
}

void sendAndReceive() {
	
	fd_set readfds;
	int result = 0;
	struct timeval timeout;
	static volatile int StopNow = 0;
	
	struct dataobject *dobj;

	while (!StopNow) {
		unsigned int nfds = 0;
		timeout.tv_sec = TIMEOUT;
		timeout.tv_usec = 0;

		FD_ZERO(&readfds);

		result = select(nfds, &readfds, NULL, NULL, &timeout);

			if (result < 0)
			{
				StopNow = 1;
			}else
			{
				dobj=haggle_publish_contacts_info(haggleHandle,dirpath);
				
				// timeout
				haggle_ipc_add_application_interest_weighted(
				haggleHandle, 
				ATTRIBUTE_NAME, 
				ATTRIBUTE_VALUE,
				1);	
				
				const unsigned char *xml = haggle_dataobject_get_raw(dobj);
				if (xml)
				{
					LIBHAGGLE_DBG("Sending data object:\n%s\n", (const char *)xml);
					printf("Sending data object:\n%s\n", (const char *)xml);
				}
			}
		
	}
}
