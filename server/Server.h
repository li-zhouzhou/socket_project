//
// Created by PC on 2022/9/5.
//

#ifndef PROJECT_SERVER_H
#define PROJECT_SERVER_H

#include <iostream>
#include <sys/socket.h>
#include <cstdio>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include <cstdlib>

using namespace std;

#define PORT 9990   //端口号
#define SIZE 1024   //定义的数组大小

class Server
{
private:
    int client_socket;
    int listen_socket;

public:
    ~Server()
    {
        close(client_socket);
        close(listen_socket);
        cout<<"成功关闭client_socket和listen_socket"<<endl;
    }

    int Creat_socket();
    int wait_client(int listen_sock);

    //信息处理函数,功能是将客户端传过来的小写字母转化为大写字母
    void handle_client(int listen_sock, int client_sock);

};


#endif //PROJECT_SERVER_H
