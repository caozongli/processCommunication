#include "comm.cpp"

void testSemSet()
{
  int sem_id = CreateSemSet(1); 
  InitSem(sem_id, 0);
  pid_t id = fork();
  if(id<0)
  {
    exit(1);
  }
  else if(id==0) // child，打印AA
  {
    cout << "child is running, pid="<< getpid() << "ppid=" << getppid() << endl;
    while(1)
    {
      P(sem_id, 0); 
      cout << "A" << endl;
      usleep(10031);
      cout << "A" << endl;
      usleep(10021);
      V(sem_id, 0);
    }
  }
  else //father，打印BB
  {
    cout << "father is running, pid=" << getpid() << "ppid=" << getppid() << endl;
    while(1)
    {
      P(sem_id, 0);
      cout << "B";
      cout << "B";
      cout << "B" << endl; 
      usleep(10003);
      V(sem_id, 0);
    }
    wait(NULL);
  }
  DestroySemSet(sem_id);
}

int main()
{
  testSemSet();
  return 0;
}
