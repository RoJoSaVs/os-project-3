#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

int main() {
    int arduino = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);
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
    while (1) {
        memset(buffer, 0, sizeof(buffer));
        read(arduino, buffer, sizeof(buffer));
        if (strlen(buffer) > 0) {
            printf("Arduino: %s\n", buffer);
        }
      
        memset(buffer, 0, sizeof(buffer));
        printf("Mensaje para Arduino: ");
        fgets(buffer, sizeof(buffer), stdin);
        write(arduino, buffer, strlen(buffer));
    }
  
    close(arduino);
    return 0;
}
