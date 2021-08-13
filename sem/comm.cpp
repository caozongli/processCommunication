#include "comm.h"

static int commSemSet(int num, int flag)
{
  key_t key = ftok(PATHNAME, PROJID);
  if( key==-1 ) 
  {
    cout << "key创建失败" << strerror(errno);
    exit(1);
  }

  int sem_id = semget(key, num, flag);
  if(sem_id==-1)
  {
    cout << "信号创建失败" << strerror(errno) << endl;
    exit(2);
  }
  return sem_id;
}

int CreateSemSet(int num)
{
  return commSemSet(num, IPC_CREAT|0666);
}

int InitSem(int sem_id, int which)
{
  union semun un;
  un.val = 1;
  int ret = semctl(sem_id, which, SETVAL, un);
  if(ret<0)
  {
    return -1;
  }
  return 0;
}

int GetSemSet()
{
  return commSemSet(0, IPC_CREAT);
}

static int SemOp(int sem_id, int which, int op)
{
  struct sembuf buf;
  buf.sem_num = which;
  buf.sem_op = op;
  buf.sem_flg = 0;
  int ret = semop(sem_id, &buf, 1);
  if(ret<0)
  {
    return -1;
  }
  return 0;
}

int P(int sem_id, int which)
{
  return SemOp(sem_id, which, -1);
}

int V(int sem_id, int which)
{
  return SemOp(sem_id, which, 1);
}

int DestroySemSet(int sem_id)
{
  int ret = semctl(sem_id, 0, IPC_RMID);
  if(ret<0)
  {
    return -1;
  }
  return 0;
}

