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

#define PORT 9990   //�˿ں�
#define SIZE 1024   //����������С

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
        cout<<"�ɹ��ر�client_socket��listen_socket"<<endl;
    }

    int Creat_socket();
    int wait_client(int listen_sock);

    //��Ϣ������,�����ǽ��ͻ��˴�������Сд��ĸת��Ϊ��д��ĸ
    void handle_client(int listen_sock, int client_sock);

};


#endif //PROJECT_SERVER_H
