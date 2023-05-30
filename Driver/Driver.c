#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include "Driver.h"

//int main(){
//    driver(1);
//    driver(2);
//    driver(3);
//    driver(4);
//}

int driver(int a) {
    int arduino = open("/dev/ttyUSB1", O_RDWR | O_NOCTTY | O_NDELAY);
    if (arduino == -1) {
        perror("Error al abrir el puerto serie");
        return 1;
    }
  
    struct termios options;
    tcgetattr(arduino, &options);
    cfsetispeed(&options, B9600);
    cfsetospeed(&options, B9600);
    options.c_cflag |= (CLOCAL | CREAD);
    tcsetattr(arduino, TCSANOW, &options);
  
    char buffer[255];
    //while (1) {
    memset(buffer, 0, sizeof(buffer));
    read(arduino, buffer, sizeof(buffer));
    if (strlen(buffer) > 0) {
        printf("Arduino: %s\n", buffer);
    }
      
    memset(buffer, 0, sizeof(buffer));
    //printf("Mensaje para Arduino: ");
    //fgets(buffer, sizeof(buffer), stdin);
    sprintf(buffer, "%d", a);
    //printf(buffer);
    write(arduino, buffer, strlen(buffer));
    //}
    sleep(5);//cambiar por esperar la respuesta del arduino
    close(arduino);
    return 0;
}
