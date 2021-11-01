/*
 * multicastReceiver.cpp
 *
 * Subscribe multicast group, receive and print.
 *
 * Usage: multicastReceiver
 */


#include <unistd.h>
#include "tcpudp.h"

ServerUDP *myServer;

int main (int argc, char *argv[])
{
  printf("\nMulticast Receiver\n\n");
  int destPort = 22555;

  myServer = new ServerUDP();
  myServer->Bind(destPort);
  
  int res = myServer->AddMulticastGroup("224.224.224.224");
  if ( res ) {
      fprintf(stderr,"Error: MulticastGroup not subscribed.\n");
      exit(1);
  }
  char buffer[280];
  do {
      res = myServer->Receive((unsigned char *)buffer,250);
      if ( res>0 ) {
  	  buffer[res] = 0;
  	  printf("Received: '%s'\n", buffer);
  	  // Do not reply.
  	  // myServer->Send(buffer,res); 
      }
  } while (res>1);
  printf("Terminated.\n");
  /*-- Return 0 if exit is successful --*/
  myServer->Close();
  delete myServer;
  return 0;
}
