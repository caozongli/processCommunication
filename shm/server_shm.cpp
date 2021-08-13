#include "comm_shm.cpp"

void test()
{
  int shmid = GetShm();
  DestroyShm(shmid);
  int shm_id = CreatShm();

  char *mem = (char*)shmat(shm_id, NULL, 0);
  while(1)
  {
    sleep(1);
    cout << mem << endl;
  }
  shmdt(mem);
  DestroyShm(shm_id);
}

int main()
{
  test();
  return 0;
}
