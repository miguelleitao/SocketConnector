/*
 * multicastSender.cpp
 *
 * Multicast sender example
 *
 * Usage: multicastSender [ - | message ]
 */


#include <unistd.h> 
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "tcpudp.h"

SocketConnector *myClient;

int main (int argc, char *argv[])
{
  printf("\nMulticast Sender\n\n");
  const char *destAddr = "224.224.224.224";
  int destPort = 22555;

  myClient = new ClientUDP();
  myClient->Connect(destAddr, destPort);
  
  char *line = NULL;
  if ( argc>1 ) {
        if ( argv[1][0]=='-' ) 
            line = readline("Line to transmite: ");
        else 
            line = strdup(argv[1]);
  }
  else line = strdup("");
  char *mesg = (char *)malloc(10+strlen(line));
  int cnt;
  for( cnt=0 ; cnt<3600 ; cnt++ ) {
  	sprintf(mesg, "%d: %s", cnt, line); 	
        myClient->Send(mesg, strlen(mesg) );
        printf("Sent %d\n", cnt);
        sleep(1);
  }  
  printf("\n%d messages sent.\n", cnt);
  free(line);
  free(mesg);
  // Send an empty message to signal end of session.
  myClient->Send(NULL, 0 );
  /*-- Return 0 if exit is successful --*/
  delete myClient;
  return 0;
}

