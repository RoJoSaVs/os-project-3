#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#define DEVICE_DRIVER_FILE "/dev/arduino_usb"


int main()
{
    // int arduino = open(DEVICE_DRIVER_FILE, O_RDWR | O_NOCTTY | O_NDELAY);
    char buffer[] = "Hola mundo en SO\n";
    // printf("%d\n", arduino);

    FILE *fptr;

   // use appropriate location if you are using MacOS or Linux
   fptr = fopen(DEVICE_DRIVER_FILE,"w");

   if(fptr == NULL)
   {
      printf("Error!");   
      exit(1);             
   }

   fprintf(fptr,"%s", buffer);
   fclose(fptr);

    // close(arduino);
    return 0;
}