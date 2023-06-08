#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "consoleMsg.c"
#include "processSync.c"
#include "../Library/serialCommArduino.h"
#include "../Library/armLib.h"

//double stick1 = 7.3;
//double stick2 = 5.25;
//double stick3 = 10;

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

    double baseRotationVertical = 11.5;

    setValues(3);


    int servo1Angle = calcBaseRotationAngle(2.5, baseRotationVertical);
    int servo2Angle = calcServo2RotationAngle(baseRotationVertical, 7.3);
    int servo3Angle = calcServo3RotationAngle(baseRotationVertical, 7.3);
    printf("Servo1 angle server %d\n", servo1Angle);
    printf("Servo2 angle server %d\n", servo2Angle);
    printf("Servo3 angle server %d\n", servo3Angle);


    int valueServo1 = (servo1Angle * 10) + 1;
    char angleServo1String[20]; // Assuming the string won't exceed 20 characters
    sprintf(angleServo1String, "%d\n", valueServo1);


    int angleServo2 = 24 + 90;
    int valueServo2 = (angleServo2 * 10) + 2;
    char angleServo2String[20]; // Assuming the string won't exceed 20 characters
    sprintf(angleServo2String, "%d\n", valueServo2);


    int angleServo3 = 180 - 104;
    int valueServo3 = (angleServo3 * 10) + 3;
    char angleServo3String[20]; // Assuming the string won't exceed 20 characters
    sprintf(angleServo3String, "%d\n", valueServo3);


    sendCommandToArduino(serialPort, angleServo1String);
//    sendCommandToArduino(serialPort, "901\n");
    sleep(1);
//    sendCommandToArduino(serialPort, angleServo1String);
//    sleep(1);
//    sendCommandToArduino(serialPort, angleServo3String);

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