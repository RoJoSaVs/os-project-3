#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Declaration of global variable
int screenDistance;

// Initialization of global variable

double stick1 = 8;
double stick2 = 9.4;
double stick3 = 10;

double baseDistance = 7.6;


struct number {
    int value;
    int row;
    int column;
    float distance;
};

struct number num;
int numpad[4][3] = {
        {1, 2, 3},  // row 0
        {4, 5, 6},  // row 1
        {7, 8, 9},  // row 2
        {0, 90, 90}   // row 3 (empty)
};

int setRowsCols(){
    // Accessing the elements
    int row, col;
    for (row = 0; row < 4; row++) {
        for (col = 0; col < 3; col++) {
            if(num.value == numpad[row][col]){
                num.row = row;
                num.column = col;
                num.distance = (baseDistance + (2.1 * (3 - row)));
            }
        }
    }
}

int calcBaseRotationAngle(double sideHorizontal){

    double angleServo1 = (atan(sideHorizontal / num.distance) * 180 / M_PI);

    if(num.column == 1){
        angleServo1 = 90;
    }

    if(num.column == 0){
        angleServo1 += 90;
    }

    if(num.column == 2){
        angleServo1 = abs(angleServo1 - 90);
    }

    return angleServo1;
}


// sideHorizontal is the length between the servo and the number in the central line
int calcServo2RotationAngle(double sideVertical){

    double sideH_squared = pow(num.distance, 2);
    double sideV_squared = pow(sideVertical, 2);

    double hypotenuse = sqrt(sideH_squared + sideV_squared);

    double stick2_squared = pow(stick2, 2);
    double stick3_squared = pow(stick3, 2);
    double hypotenuse_squared = pow(hypotenuse, 2);

    double angleServo2 = (acos(((stick2_squared) + (hypotenuse_squared) - (stick3_squared)) / (2 * stick2 * hypotenuse))) * 180 / M_PI;

    return angleServo2;
}

// sideHorizontal is the length between the servo and the number in the central line
int calcServo3RotationAngle(double sideVertical){

    double sideH_squared = pow(num.distance, 2);
    double sideV_squared = pow(sideVertical, 2);

    double hypotenuse = sqrt(sideH_squared + sideV_squared);

    double stick2_squared = pow(stick2, 2);
    double stick3_squared = pow(stick3, 2);
    double hypotenuse_squared = pow(hypotenuse, 2);

    double angleServo3 = (acos(((stick3_squared) + (stick2_squared) - (hypotenuse_squared)) / (2 * stick2 * stick3))) * 180 / M_PI;
    return angleServo3;
}

// sideHorizontal is the length between the servo and the number in the central line
int calcServo2OffsetAngle(double sideVertical){

    double sideH_squared = pow(num.distance, 2);
    double sideV_squared = pow(sideVertical, 2);

    double hypotenuse = sqrt(sideH_squared + sideV_squared);


    double angleOffsetServo2 = (90 - (atan(stick1/num.distance) * 180 / M_PI));

    return angleOffsetServo2;
}

int setValues(int numVal) {
    num.value = numVal;
    setRowsCols();
}