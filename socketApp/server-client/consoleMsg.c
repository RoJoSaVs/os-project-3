// Add color to text in console
// http://web.theurbanpenguin.com/adding-color-to-your-output-from-c/
// https://stackoverflow.com/questions/3219393/stdlib-and-colored-output-in-c

#include <stdio.h>

void red () {
    printf("\033[0;31m");
}

void bold_red () {
    printf("\033[1;31m");
}

void yellow() {
    printf("\033[0;33m");
}

void green() {
    printf("\033[0;32m");
}

void bold_green() {
    printf("\033[1;32m");
}
void blue() {
    printf("\033[0;34m");
}

void bold_blue() {
    printf("\033[1;34m");
}

void purple(){
    printf("\033[1;35m");
}

void cyan(){
    printf("\033[1;36m");
}

void reset() {
    printf("\033[0m");
}


void printErrorMsg(char *msg)
{
    bold_red();
    printf("---------------------------------------------------------------------\n");
    printf("\t \t \t %s \n", msg);
    printf("---------------------------------------------------------------------\n");
    reset();
}


void printInfoMsg(char *msg)
{
    bold_green();
    printf("---------------------------------------------------------------------\n");
    bold_blue();
    printf("\t \t %s \n", msg);
    bold_green();
    printf("---------------------------------------------------------------------\n");
    reset();
}

void printInfoMsgClient(char *msg)
{
    bold_green();
    printf("---------------------------------------------------------------------\n");
    cyan();
    printf("\t \t %s \n", msg);
    bold_green();
    printf("---------------------------------------------------------------------\n");
    reset();
}

