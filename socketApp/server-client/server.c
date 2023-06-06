#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "consoleMsg.c"
#include "processSync.c"
#include "../Library/serialCommArduino.h"


void runServer(int port, int key, int mod, pid_t mainPid)
{
    int server_fd;
    int new_socket;
    int valread;
    struct sockaddr_in address;

    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = { 0 };

    while (1)
    {
        // Creating socket file descriptor
        if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            printErrorMsg("socket failed");
            exit(EXIT_FAILURE);
        }

        // Forcefully attaching socket to the port
        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
            printErrorMsg("setsockopt");
            exit(EXIT_FAILURE);
        }

        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port);

        // Forcefully attaching socket to the port
        if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
            printErrorMsg("bind failed");
            exit(EXIT_FAILURE);
        }

        if (listen(server_fd, 3) < 0) {
            printErrorMsg("listen");
            exit(EXIT_FAILURE);
        }


        if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
            printErrorMsg("accept");
            exit(EXIT_FAILURE);
        }

        valread = read(new_socket, buffer, 1024);

        fork();
        if(mainPid != getpid())
        {
            processControl(atoi(buffer), key, mod);
            close(new_socket); // closing the connected socket
            shutdown(server_fd, SHUT_RDWR); // closing the listening socket
            exit(0);
        }

        close(new_socket); // closing the connected socket
        shutdown(server_fd, SHUT_RDWR); // closing the listening socket
    }
}


int main(int argc, char const* argv[])
{
    //-------------------Temporary arduino comms init-----------------------------------
    int serialPort = initSerialComm();

    // Send commands to the Arduino
    sendCommandToArduino(serialPort, "100\n");
    sendCommandToArduino(serialPort, "10\n");

    close(serialPort);


    //-------------------Temporary arduino comms end-----------------------------------

	int port;
	if (argc < 2)
    {
        port = 25565;
    }
    else
    {
		port = atoi(argv[1]);
	}

	int key = 11;
	int mod = 14;

    setSemaphores();
    setSharedMemory();

    pid_t mainPid = getpid();
	//runServer(port, key, mod, mainPid);

	
	return 0;
}