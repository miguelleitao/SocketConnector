/*
 * echoClient.cpp
 *
 * Send,  receive, print.
 *
 * Usage: echoClient
 */


#include <unistd.h> 
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "tcpudp.h"


SocketConnector *myClient;


#define _USE_UDP_

int main (int argc, char *argv[])
{
  const char *destAddr = "127.0.0.1";
  int destPort = 22555;

  #ifdef _USE_UDP_
  myClient = new ClientUDP();
  #else
  myClient = new ClientTCP();
  #endif
  myClient->Connect(destAddr, destPort);
  
  int res = 0;
  do { 
        char *line = readline("Line to transmite: ");
        myClient->Send(line, strlen(line) );
        printf("Enviou\n");
  
        char buffer[280];
        res = myClient->Receive((unsigned char *)buffer,250);
  
        if ( res>0 ) {
  	    buffer[res] = 0;
  	    printf("Received: '%s'\n", buffer);
        }
        else {
	     fprintf(stderr,"Erro\n");
        }
        free(line);
  } while (res>1);
  /*-- Return 0 if exit is successful --*/
  delete myClient;
  return 0;
}
