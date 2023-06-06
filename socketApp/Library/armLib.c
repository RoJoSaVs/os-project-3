#include <stdio.h>
#include <math.h>

// Declaration of global variable
int screenDistance;

// Initialization of global variable
int borderToNumpad;
int ballSize;
int gapX;
int gapY;
int midStickLength;
int pointStickLength;
double hypotenuse;
double stick1 = 6.1;
double stick2 = 5.6;
double stick3 = 8.3;

int calcBaseRotationAngle(double sideHorizontal, double sideVertical){

    double angleServo1 = atan(sideHorizontal / sideVertical) * 180 / M_PI;
    printf("acos %.2f\n", angleServo1);
}


// sideHorizontal is the length between the servo and the number in the central line
int calcUpperServosRotationAngle(double sideHorizontal, double sideVertical){

    double sideH_squared = pow(sideHorizontal, 2);
    double sideV_squared = pow(sideVertical, 2);

    double hypotenuse = sqrt(sideH_squared + sideV_squared);
    printf("The length of the hypotenuse is: %.2f\n", hypotenuse);

    double stick2_squared = pow(stick2, 2);
    double stick3_squared = pow(stick3, 2);
    double hypotenuse_squared = pow(stick3, 2);


    double angleServo2 = acos(((stick2_squared) + (hypotenuse_squared) - (stick3_squared)) / (2 * stick2 * hypotenuse)) * 180 / M_PI;
    printf("acos %.2f\n", angleServo2);

    double angleServo3 = acos(((stick3_squared) + (stick2_squared) - (hypotenuse_squared)) / (2 * stick2 * stick3)) * 180 / M_PI;
    printf("acos %.2f\n", angleServo3);
}


int main() {
    calcBaseRotationAngle(3, 11);
    calcUpperServosRotationAngle(11, stick1);
    return 0;
}