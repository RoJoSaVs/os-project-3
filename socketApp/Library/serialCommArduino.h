//
// Created by jess on 05/06/23.
//

#ifndef SOCKETAPP_SERIALCOMMARDUINO_H
#define SOCKETAPP_SERIALCOMMARDUINO_H


int initSerialComm();
int sendCommandToArduino(int serialPort, const char* command);

#endif //SOCKETAPP_SERIALCOMMARDUINO_H
