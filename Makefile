
-include .config

DEST_ADDR?=127.0.0.1
DEST_PORT?=22333

TARGETS=echoServer echoClient

SRC=tcpudp.h

CFLAGS=-Wall -Wno-unused-local-typedefs -fPIC

default: ${TARGETS}

all: default mcast_socket multicastSender multicastReceiver

echoServer: echoServer.cpp tcpudp.h
	g++ -Wall -o $@ $<

echoClient: echoClient.cpp tcpudp.h
	g++ -Wall -o $@ $< -l readline

multicastSender: multicastSender.cpp tcpudp.h
	g++ -Wall -o $@ $< -l readline

multicastReceiver: multicastReceiver.cpp tcpudp.h
	g++ -Wall -o $@ $<

clean:
	rm -f ${TARGETS} multicastSender multicastReceiver

push:
	git add .
	git commit -m "auto update"
	git push
