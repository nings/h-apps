
#include "myapplication.h"

int main (int argc, char *argv[]) 
{
	unsigned long pid;

	getDirPath();
	
	LIBHAGGLE_DBG("HAGGLE_DBG: path %s \n",dirpath);
	
	char hostName[64];
	
	gethostname(hostName, 64);

	if (argc < 0)
	{
		printf ("Please indicate which node in send mode and the others are in receive mode. \n");
		exit(EXIT_FAILURE);
	}
	else
	{
		int retpid = haggle_daemon_pid(&pid);
	
		if (retpid == HAGGLE_ERROR) {
				printf("Could not get Haggle pid\n");
				exit(EXIT_FAILURE);
		}
		if (retpid == 0) {
				printf("Haggle not running, trying to spawn daemon... ");
				
				if (haggle_daemon_spawn(NULL) != 1) {
						printf("failed!\n");
						exit(EXIT_FAILURE);
				}
				printf("success!\n");
		} 
		else if (retpid==1)
		{
			printf("Haggle daemon is running with pid=%lu\n",pid);
		}
		  
		printf("Haggle running trying to get handle\n");
		
		int ret = haggle_handle_get(APP_NAME, &haggleHandle);
		if (ret != HAGGLE_NO_ERROR) {
			fprintf(stderr, "Could not get haggle handle, error: %d\n", ret);
					exit(EXIT_FAILURE);                
		}
		
		haggle_ipc_register_event_interest(haggleHandle, LIBHAGGLE_EVENT_NEW_DATAOBJECT, onDataObject);
		haggle_ipc_register_event_interest(haggleHandle, LIBHAGGLE_EVENT_NEIGHBOR_UPDATE, onNeighborUpdate);
		haggle_ipc_register_event_interest(haggleHandle, LIBHAGGLE_EVENT_INTEREST_LIST, onInterestList);
		
		if (strcmp(argv[1],hostName)==0)
		{
			sendEventLoop();
		}
		
		if (strcmp(argv[1],"-r")==0)
		{
			recvEventLoop();
		}
		
		//if (strcmp(argv[1],"-a")==0)
		//{	

			//if (strcmp(hostName, "node-1")==0)
			//{
				//LIBHAGGLE_DBG("HAGGLE_DBG: Found %s to send \n", hostName);
				//sendEventLoop();
			//}
			
			//if (strcmp(hostName, "node-10")==0)
			//{

				//LIBHAGGLE_DBG("HAGGLE_DBG: Found %s to receive \n", hostName);

				//recvEventLoop();
			//}
		
		//}
		
		//if (strcmp(argv[1],"-o")==0)
		//{
			//sendAndReceive();
		//}
	
		haggle_event_loop_run(haggleHandle);

	}
	
done:
	haggle_handle_free(haggleHandle);
	
	return 1;
}
