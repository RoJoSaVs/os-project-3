all: build

build:

server:
	gcc server-client/server.c -o output/server -lm
	./output/server

client:
	gcc server-client/client.c -o output/client -lm
	./output/client 3 3
	./output/client 1 2
	./output/client 2 1
	./output/client 3 0
	./output/client 3 8


test:
	gcc server-client/processSync.c -o output/processSync -lm
	./output/processSync


rsa:
	gcc server-client/rsa.c -o output/rsa -lm
	./output/rsa

reset:
	rm output/*
	clear