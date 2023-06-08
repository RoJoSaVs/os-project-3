//
// Created by jess on 08/06/23.
//

#ifndef SOCKETAPP_ARMLIB_H
#define SOCKETAPP_ARMLIB_H

int calcBaseRotationAngle(double sideHorizontal, double sideVertical);
int calcServo2RotationAngle(double sideHorizontal, double sideVertical);
int calcServo3RotationAngle(double sideHorizontal, double sideVertical);
int setValues(int numVal);


#endif //SOCKETAPP_ARMLIB_H
