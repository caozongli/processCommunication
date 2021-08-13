#include "comm_shm.h"

static int CommShm(int flag)
{
  key_t key = ftok(PATHNAME, PROCID);
  if(-1==key)
  {
    cout << "获取key键值失败" << strerror(errno) << endl;
    exit(0);
  }

  int shmid = shmget(key, SIZE, flag);
  if(-1==shmid)
  {
    cout << "创建共享内存失败" << strerror(errno) << endl;
    exit(1);
  }
  cout << "创建共享内存成功" << shmid << endl;
  return shmid;
}

int CreatShm()
{
  return CommShm(IPC_CREAT|IPC_EXCL|0666);
}

int GetShm()
{
  return CommShm(IPC_CREAT);
}

int DestroyShm(int shm_id)
{
  int ret = shmctl(shm_id, IPC_RMID, NULL);
  if(-1==ret) 
  {
    cout << "删除内存失败" << endl;
    exit(0);
  }
  cout << "删除成功" << endl;
  return 0;
}  
