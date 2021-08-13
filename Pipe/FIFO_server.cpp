#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
using namespace std;



void testserver()
{
  int namepipe = mkfifo("mypipe", S_IFIFO|0666);
  if(-1==namepipe)
  {
    cout << "创建管道失败" << strerror(errno) << endl;
    exit(0);
  }

  int fd = open("./mypipe", O_RDWR);
  if(-1==fd)
  {
    cout << "打开命名管道失败" << strerror(errno) << endl;
    exit(0);
  }

  char buff[1024];
  while(1)
  {
    cout << "往管道中写入数据:" << endl;
    string s;
    cin >> s;
    strncpy(buff, s.c_str(), s.size()+1);
    cout << "\n";
    if(-1==write(fd, buff, sizeof(buff)+1))
    {
      cout << "写入失败" << strerror(errno) << endl;
      exit(0);
    }
  }
  close(fd);
}

int main()
{
  testserver();
  return 0;
}
