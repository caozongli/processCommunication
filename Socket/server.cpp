/*sockfd = socket();    // 创建一个socket，赋给sockfd
bind(sockfd, ip::port和一些配置);    // 让socket绑定端口，同时配置连接类型之类的
listen(sockfd);        // 让socket监听之前绑定的端口
while(true)
{
    connfd = accept(sockfd);    // 等待客户端连接，直到连接成功，之后将客户端的套接字返回出来
    recv(connfd, buff); // 接收到从客户端发来的数据，并放入buff中
    send(connfd, buff); // 将buff的数据发回客户端
    close(connfd);      // 与客户端断开连接
}*/
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sys/socket.h>
#include <sys/unistd.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <signal.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
using namespace std;

#define BUFFSIZE 2048
#define DEFAULT_PORT 16555 //指定端口为16555
#define MAXLINK 2048

int sockfd, connfd; //定义服务端的套接字和客户端套接字

void stopServerRunning(int p)
{
    close(sockfd);
    cout << "close server\n";
    exit(0);
}

int main()
{
    struct sockaddr_in servaddr; //用于存放ip和端口的结构
    char buff[BUFFSIZE]; //用于收发数据

    //对应于sockfd=socket()
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == sockfd)
    {
        cout << "Create socket error:" << strerror(errno) << endl;
        return -1;
    }
    // END

    // 对应伪代码中的bind(sockfd, ip::port和一些配置)
    bzero(&servaddr, sizeof(servaddr)); // 将字符串前n个字符串清零
    servaddr.sin_family = AF_INET; // 协议族
    // sin_addr代表的是ip地址
    // servaddr.sin_addr.s_addr = inet_addr("192.168.125.135");
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // 将主机字节顺序转换为网络字节顺序
    // htonl()--"Host to Network Long"
    // ntohl()--"Network to Host Long"
    // htons()--"Host to Network Short"
    // ntohs()--"Network to Host Short"
    servaddr.sin_port = htons(DEFAULT_PORT);
    if(-1 == bind(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr)))
    {
        cout << "Bind error:" << strerror(errno) << endl;
        return -1;
    }
    // END

    //对应伪代码中的listen(sockfd)
    if(-1 == listen(sockfd, MAXLINK))
    {
        cout << "Listen error:" << strerror(errno) << endl;
        return -1;
    }
    //END

    cout << "Listening...\n";

    // 对应于伪代码中的connfd=accept(sockfd);
    connfd = accept(sockfd, NULL, NULL);
    if(-1 == connfd)
    {
        cout << "Accept error:" << strerror(errno) << endl;
        return -1;
    }
    else
    {
        cout << "Accept successed!" << endl;
    }
    //END

    while(true)
    {
        signal(SIGINT, stopServerRunning); //对应于ctrl+c的时候关闭服务器

        

        bzero(buff, BUFFSIZE);

        //对应伪代码中的recv(connfd, buff);
        recv(connfd, buff, BUFFSIZE-1, 0);
        //END  

        cout << "Recv:" << buff << endl;

    }

    //对应伪代码中的close(connfd);
    close(connfd);
    return 0;

}

    





