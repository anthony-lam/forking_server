#include "pipe_networking.h"


int main() {
	int to_server;
	int from_server;
	from_server = client_handshake( &to_server );
	while(1){
		printf("[client] Enter input:\n");
		char input[1000];
		char recieved[1000];
		fgets(input, 1000, stdin);
		write(to_server,input,1000);
		read(from_server, recieved, 1000);
		strtok(recieved, "\n");
		printf("[client] Recieved: %s\n", recieved);
	}
}
