#include <stdio.h>
#include <math.h>

// Declaration of global variable
int screenDistance;

// Initialization of global variable
int borderToNumpad;
int ballSize;
int gapX;
int gapY;
double stick1 = 6.1;
double stick2 = 5.6;
double stick3 = 8.3;


struct number {
    int value;
    int row;
    int column;
};

struct number num;
int numpad[4][3] = {
        {1, 2, 3},  // row 0
        {4, 5, 6},  // row 1
        {7, 8, 9},  // row 2
        {0, 0, 0}   // row 3 (empty)
};

int setRowsCols(){
    // Accessing the elements
    int row, col;
    for (row = 0; row < 4; row++) {
        for (col = 0; col < 3; col++) {
            if(num.value == numpad[row][col]){
                num.row = row;
                num.column = col;
            }
        }
    }
}

int calcBaseRotationAngle(double sideHorizontal, double sideVertical){

    double angleServo1 = (atan(sideHorizontal / sideVertical) * 180 / M_PI);

    if(num.column == 1){
        angleServo1 = 90;
    }

    if(num.column == 0){
        angleServo1 += 90;
    }

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
    double hypotenuse_squared = pow(hypotenuse, 2);


    double angleServo2 = (acos(((stick2_squared) + (hypotenuse_squared) - (stick3_squared)) / (2 * stick2 * hypotenuse))) * 180 / M_PI;
    printf("angleServo2 %.2f\n", angleServo2);

    double angleServo3 = (acos(((stick3_squared) + (stick2_squared) - (hypotenuse_squared)) / (2 * stick2 * stick3))) * 180 / M_PI;
    printf("angleServo3 %.2f\n", angleServo3);
}


int main() {
    num.value = 3;
    setRowsCols();

    double baseRotationVertical = 8.5;

    calcBaseRotationAngle(3, baseRotationVertical);
    calcUpperServosRotationAngle(baseRotationVertical, stick1);

    return 0;
}