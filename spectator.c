#include "defs.h"

/*
  Function:  viewEscape
  Purpose:   initializes a client socket and sends a connection request to the server at given IP address, 
             loops and waits for data that it prints out until quit message is received, at which point it closes the server
       in:   the address of the ip address to connect to the server with
*/

void viewEscape(char *ip){
  int clientSocket;
  char buffer[MAX_BUFF];
  int bytes;
  setupClientSocket(&clientSocket, ip);
  
  while(1){
    
    bytes = rcvData(clientSocket, buffer);
    buffer[bytes] = '\0';
    
    if(strcmp(buffer, "quit")==0){
      break;
    }
    
    if(strstr(buffer, "-")){
      system("clear");
    }
    
    printf("%s",buffer);
    usleep(OUTPUT_INTERVAL);
  }
  
  close(clientSocket);
}