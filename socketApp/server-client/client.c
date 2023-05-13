#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#include "consoleMsg.c"
#include "rsa.c"



void clientExecution(int port, int number, int key, int mod)
{
    int status;
    int valread;
    int client_fd;

    struct sockaddr_in serv_addr;
    
    char msg[6];
    int encryptedNumber = rsa(number, key, mod);
    sprintf(msg, "%d", encryptedNumber);

    char buffer[1024] = { 0 };

    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printErrorMsg("Socket creation error");
        return;
    }
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
  
    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printErrorMsg("Invalid address/ Address not supported ");
        return;
    }
  
    if ((status = connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
        printErrorMsg("Connection Failed");
        return;
    }

    send(client_fd, msg, strlen(msg), 0);
    char infoMsg[1024];
    sprintf(infoMsg, "Seed number: %d, encrypted value: %d", number, encryptedNumber);
    printInfoMsgClient(infoMsg);
  
    // closing the connected socket
    close(client_fd);
}


int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printErrorMsg("Missing arguments");
    }
    else
    {
        int port;
        int number = atoi(argv[1]);
        if(argc == 2)
        {
            port = 25565; // Default port
        }
        else
        {
            port = atoi(argv[2]);
        }
        // Values for RSA
        int key = 5;
        int mod = 14;
        clientExecution(port, number, key, mod);

    }
    return 0;
}