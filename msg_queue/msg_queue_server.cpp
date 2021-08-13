#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <iostream>
#include <unistd.h>
#include <errno.h>
#define BUF_SIZE 256
#define PROJ_ID 32
#define PATH_NAME "/tmp"
#define SERVER_MSG 1
#define CLIENT_MSG 2
using namespace std;

int main()
{
    struct mymsg
    {
        long msgtype;
        char content[256];
    }msgbuf;
    //var define
    int qid; //消息队列标识
    int msglen; //消息队列长度
    key_t msgkey;

    //获取键值
    msgkey = ftok(PATH_NAME, PROJ_ID);
    if(msgkey==-1)
    {
        cout << "sorry key create failed:" << strerror(errno) << endl;
        exit(0);
    }
    cout << "创建键值成功" << '\n';
    qid = msgget(msgkey, IPC_CREAT|0666);
    if(-1==qid)
    {
        cout << "get msg queue failed" << strerror(errno) << endl;
        exit(0);
    }
    cout << "获取消息队列成功" << endl;

    while(1)
    {
        cout << "请输入服务器给客户的消息\n";
        cin >> msgbuf.content;
        if(strncmp(msgbuf.content, "exit", 4)==0)
        {
            msgctl(qid, IPC_RMID, NULL);
            exit(0);
        }
        msgbuf.msgtype = SERVER_MSG;
        if(msgsnd(qid, &msgbuf, strlen(msgbuf.content)+1, 0)==-1)
        {
            cout << "msg send failed" << endl;
            exit(1);
        }
        cout << "正在接受客户端的消息" << endl;
        if(msgrcv(qid, &msgbuf, BUF_SIZE, CLIENT_MSG, 0)==-1)
        {
            cout << "msg rcv failed" << endl;
            exit(0);
        }
        cout << "Client:" << msgbuf.content << endl;
    }
    
    return 0;
}
