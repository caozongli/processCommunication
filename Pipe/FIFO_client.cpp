#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
using namespace std;

void testclient()
{
  int fd = open("./mypipe", O_RDWR);
  if(-1==fd)
  {
    cout << "打开管道失败" << strerror(errno) << endl;
    exit(0);
  }

  char buff[1024];
  while(1)
  {
    size_t s = read(fd, buff, sizeof(buff)-1);
    if(s>0) cout << "client:" << buff << endl;
    else cout << "shibai" << endl;
  }
  close(fd);
}

int main()
{
  pid_t pid = fork();
  
  testclient();
  return 0;
}
