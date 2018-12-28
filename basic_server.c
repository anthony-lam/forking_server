#include "pipe_networking.h"
#include <signal.h>



static void sighandler(int n){
	if(n == SIGINT){
		remove("wkp");
		printf("[server] exiting\n");
		exit(0);
	}
}


int main() {
	signal(SIGINT, sighandler);
	int to_client;
	int from_client;
	char recieved[1000];
	int i;
	int pid;
	while(1){
		from_client = server_handshake( &to_client );
		pid = fork();
		if (pid){
			while(read(from_client, recieved, 1000)){
				strtok(recieved, "\n");
				printf("[server %d] Recieved -%s-\n",getpid(), recieved);
				for(i = 0; i < strlen(recieved); i++){
					recieved[i] += 10;
				}
				write(to_client, recieved, 1000);
				printf("[server %d] Sent -%s-\n",getpid(), recieved);
			}
		}
	}
}
