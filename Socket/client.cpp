/*
sockfd = socket();    // 创建一个socket，赋给sockfd
connect(sockfd, ip::port和一些配置);    // 使用socket向指定的ip和port发起连接
scanf("%s", buff);    // 读取用户输入
send(sockfd, buff);    // 发送数据到服务端
recv(sockfd, buff);    // 从服务端接收数据
close(sockfd);        // 与服务器断开连接
*/

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sys/socket.h>
#include <sys/unistd.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
using namespace std;

#define BUFFSIZE 2048
#define SERVER_IP "192.168.125.128"
#define SERVER_PORT 16555

int main()
{
    struct sockaddr_in servaddr;
    char buff[BUFFSIZE];
    int sockfd;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == sockfd)
    {
        cout << "Create socket failed:" << strerror(errno) << endl;
        return -1;
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, SERVER_IP, &servaddr.sin_addr); //将点分十进制的ip地址转换成用于网络传输的数值格式
    //返回值成功则指向结构的指针，失败则为NULL
    servaddr.sin_port = htons(SERVER_PORT);
    if(-1 == connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)))
    {
        cout << "Connect failed:" << strerror(errno) << endl;
        return -1;
    }
    cout << "Please input:" << 
    cin.getline(buff, BUFFSIZE-1);
    send(sockfd, buff, strlen(buff), 0);
    bzero(buff, sizeof(buff));
    recv(sockfd, buff, BUFFSIZE - 1, 0);
    cout << "Recv:" << buff << endl;
    close(sockfd);

    return 0;
}









