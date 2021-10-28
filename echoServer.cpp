/*
 * echoServer.cpp
 *
 * receive, print and resend.
 *
 * Usage: echoServer
 */


#include <unistd.h>
#include "tcpudp.h"

#define _USE_UDP_

SocketConnector *myServer;

int main (int argc, char *argv[])
{
  int destPort = 22555;

  #ifdef _USE_UDP_
      myServer = new ServerUDP();
  #else
      myServer = new ServerTCP();
  #endif
  myServer->Bind(destPort);
  
  char buffer[280];
  int res;
  do {
      res = myServer->Receive((unsigned char *)buffer,250);
      if ( res>0 ) {
  	  buffer[res] = 0;
  	  printf("Received: '%s'\n", buffer);
  	  myServer->Send(buffer,res);
      }
      else {
	  fprintf(stderr,"Erro\n");
      }
  } while (res>1);
  /*-- Return 0 if exit is successful --*/
  myServer->Close();
  myServer->EndServer();
  delete myServer;
  return 0;
}
