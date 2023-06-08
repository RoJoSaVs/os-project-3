#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <stdbool.h>

#include "controlStruct.c"
#include "rsa.c"
#include "../Library/armLib.h"



sem_t *indexControlSem;
sem_t *runningProcessSem;

struct controlStruct *control;

void hardwareFunction(int numpadSize, int decryptedNumber)
{
    moveArm(decryptedNumber);
    sleep(5);
}



void setSemaphores()
{
    char semControlName[] = "control";
    char semRunningName[] = "running";
    indexControlSem = sem_open(semControlName, O_CREAT | O_RDWR, 0666, 1);
    runningProcessSem = sem_open(semRunningName, O_CREAT | O_RDWR, 0666, 1);

    // Reset semaphores to original values
    while (1)
    {
        if((sem_trywait(indexControlSem) == -1) && (sem_trywait(runningProcessSem) == -1)){
            break;
        }

    }
    sem_post(indexControlSem); // Let the indexControlSem on 1
    sem_post(runningProcessSem); // Let the runningProcessSem on 1
}

void setSharedMemory()
{
    // Shared memory for control
    int shm_control;
    
    shm_control = shm_open("processControl", O_CREAT | O_RDWR, 0666); // Shared memory for process control

    ftruncate(shm_control, sizeof(struct controlStruct));

    control = mmap(0, sizeof(struct controlStruct), PROT_READ | PROT_WRITE, MAP_SHARED, shm_control, 0);
    control->assignedIndex = 0;
    control->indexBeingProcessed = 0;
}


int getIndexForProcess()
{
    int localIndex;
    sem_wait(indexControlSem);
    localIndex = control->assignedIndex;
    control->assignedIndex++;
    sem_post(indexControlSem);
    return localIndex;
}

void processControl(int numpadSize, int number, int key, int mod)
{
    int localIndex = getIndexForProcess();
    
    while (1)
    {
        sem_wait(indexControlSem);
        if(localIndex == control->indexBeingProcessed)
        {
            sem_wait(runningProcessSem);
            sem_post(indexControlSem);
            
            int decryptedNumber = rsa(number, key, mod); // Call RSA
            char infoMsg[1024];
            sprintf(infoMsg, "Value readed %d, value decrypted %d", number, decryptedNumber);
            printInfoMsg(infoMsg);
            
            // Process number on hardware
            hardwareFunction(numpadSize, decryptedNumber);

            sem_wait(indexControlSem);
            control->indexBeingProcessed++;
            sem_post(indexControlSem);

            sem_post(runningProcessSem);
            break;
        }
        else
        {
            sem_post(indexControlSem);
        }
    }
}



// int main()
// {
//     setSemaphores();
//     setSharedMemory();
//     return 0;
// }