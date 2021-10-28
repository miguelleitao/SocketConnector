
-include .config

DEST_ADDR?=127.0.0.1
DEST_PORT?=22333

TARGET=socket-connector
SRC=tcpudp.h

CFLAGS=-Wall -Wno-unused-local-typedefs -fPIC

default: ${TARGET}.so

all: default echoClient echoServer

${TARGET}.so: ${TARGET}.o
	g++ -o $@ $^ `wx-config --libs` -l wxsvg -shared

${TARGET}.o: tcpudp.h config.h
	g++ -o $@ -c ${CFLAGS} -g -D_ALLOW_OLD_PAINEL_PROTOCOL_ `wx-config --cxxflags` $<

echoServer: echoServer.cpp tcpudp.h
	g++ -Wall -o $@ $<

echoClient: echoClient.cpp tcpudp.h
	g++ -Wall -o $@ $< -l readline

clean:
	rm -f ${TARGET}.so ${TARGET}.o echoServer echoClient

push:
	git add .
	git commit -m "auto update"
	git push
