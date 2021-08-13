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
    struct mymsg{
        long msgtype;
        char content[256];
    }msgbuf;
    int qid; //消息队列标识
    int msglen;// 消息长度
    key_t msgkey;

    //获取键值
    msgkey = ftok(PATH_NAME, PROJ_ID);
    if(-1==msgkey)
    {
        cout << "sorry key create failed:" << strerror(errno) << endl;
        exit(0);
    }
    cout << "获取键值成功" << endl;

    //获取消息队列
    qid = msgget(msgkey, IPC_CREAT|0666);
    if(-1==qid)
    {
        cout << "get msg queue failed" << strerror(errno) << endl;
        exit(0);
    }
    cout << "获取消息队列成功" << qid << endl;

    while(1)
    {
        //正在接收服务器给客户端的消息
        if(-1==msgrcv(qid, &msgbuf, BUF_SIZE, SERVER_MSG, 0))
        {
            cout << "msg rcv failed" << endl;
            exit(0);
        }
        cout << "Server:" << msgbuf.content << endl;

        msgbuf.msgtype = CLIENT_MSG;
        cout << "Client:" ;
        cin >> msgbuf.content;
        if(0==strncmp(msgbuf.content, "exit", 4))
        {
            msgctl(qid, IPC_RMID, NULL);
            exit(0);
        }

        if(-1==msgsnd(qid, &msgbuf, strlen(msgbuf.content)+1, 0))
        {
            cout << "msg send failed" << endl;
            exit(1);
        }
    }

    return 0;
}
