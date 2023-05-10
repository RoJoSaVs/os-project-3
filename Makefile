all: build

build:

server:
	gcc server-client/server.c -o output/server -lm
	./output/server

client:
	gcc server-client/client.c -o output/client -lm
	./output/client 3


test:
	gcc server-client/processSync.c -o output/processSync -lm
	./output/processSync

reset:
	rm output/*