#ifndef __COMM_H__
#define __COMM_H__

#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <iostream>
#include <string.h>
#include <errno.h>
using namespace std;

#define PATHNAME "."
#define PROJID 0x6666

union semun
{
  int val; /*Value for SETVAL*/
  struct semid_ds *buf;
  unsigned short *array;
  struct seminfo *_buf;
};

int CreateSemSet(int num);// 创建信号量
int GetSemSet(); //获取信号量
int InitSem(int sem_id, int which);
int P(int sem_id, int which); //p操作
int V(int sem_id, int which); //v操作
int DestroySemSet(int sem_id); //销毁信号量
#endif
