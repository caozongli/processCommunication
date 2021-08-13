#include "comm_shm.cpp"

void testclient()
{
  int shm_id = GetShm();
  char *mem = (char*)shmat(shm_id, NULL, 0);
  int index = 0;
  while(1)
  {
    sleep(1);
    mem[index++] = 'B';
    if(index == (10)) return;
    mem[index] = '\0';
  }
  shmdt(mem);
  DestroyShm(shm_id);
}

int main()
{
  testclient();
  return 0;
}