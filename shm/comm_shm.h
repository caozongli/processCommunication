#ifndef __COMM__
#define __COMM__
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <iostream>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
using namespace std;
    
#define PATHNAME "."
#define PROCID 0x6666
#define SIZE 4096*1
int CreatShm();
int GetShm();

int DestoryShm(int shm_id);
#endif
