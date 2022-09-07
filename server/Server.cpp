//
// Created by PC on 2022/9/5.
//

#include "Server.h"
#include "../led/Led.h"

int Server::Creat_socket()   //创建套接字和初始化以及监听函数
{
    listen_socket = socket(AF_INET, SOCK_STREAM, 0);   //创建一个负责监听的套接字
    if(listen_socket == -1)
    {
        perror("socket");
        return -1;
    }
    struct sockaddr_in addr;
    int listendcliaddrlen = sizeof(addr);
    memset(&addr, 0, listendcliaddrlen);

    addr.sin_family = AF_INET;  /* Internet地址族 */
    addr.sin_port = htons(PORT);  /* 端口号 */
    addr.sin_addr.s_addr = htonl(INADDR_ANY);   /* IP地址 */

    int ret = bind(listen_socket, (struct sockaddr *)&addr, sizeof(addr));  //连接
    if(ret == -1)
    {
        perror("bind");
        return -1;
    }

    cout<<"IP地址: "<<addr.sin_addr.s_addr<<endl;
    //获取监听的地址和端口
    if(getsockname(listen_socket, (struct sockaddr *)&addr, (socklen_t *)(&listendcliaddrlen)) == -1){
        cout<<"getsockname error"<<endl;
        exit(0);
    }
    cout<<"获取监听的地址和端口 = "<<inet_ntoa(addr.sin_addr)<<":"<<ntohs(addr.sin_port)<<endl;


    cout<<"开始监听......."<<endl;
    ret = listen(listen_socket, 5);        //监听
    if(ret == -1)
    {
        perror("listen");
        return -1;
    }
    return listen_socket;
}

int Server::wait_client(int listen_sock)
{
    struct sockaddr_in cliaddr,seraddr;//分别表示客户端地址和服务端地址
    char ipAddr[INET_ADDRSTRLEN];//保存点分十进制的地址

    int cliaddrlen = sizeof(cliaddr);
    int seraddrlen = sizeof(seraddr);
    cout<<"等待客户端连接。。。。."<<endl;
    client_socket = accept(listen_sock, (struct sockaddr *)&cliaddr, (socklen_t*)&cliaddrlen);   //创建一个和客户端交流的套接字
    if(client_socket == -1)
    {
        perror("accept");
        return -1;
    }

    //表示的连接上的对端地址
    if(getpeername(client_socket, (struct sockaddr *)&cliaddr, (socklen_t *)(&cliaddrlen)) == -1){
        cout<<"getpeername error\n";
        exit(0);
    }
    cout<<"连接上的客户端地址 = "<<inet_ntop(AF_INET, &cliaddr.sin_addr, ipAddr, sizeof(ipAddr))<<":"<<ntohs(cliaddr.sin_port)<<endl;
    //cout << "成功接收到一个客户端：" << inet_ntoa(cliaddr.sin_addr)<<endl;


    //表示的连接上的本地地址
    if(getsockname(client_socket, (struct sockaddr *)&seraddr, (socklen_t *)(&seraddrlen)) == -1){
        cout<<"getpeername error\n";
        exit(0);
    }
    cout<<"连接上的服务端地址 = "<<inet_ntoa(seraddr.sin_addr)<<":"<<ntohs(seraddr.sin_port)<<endl;

    return client_socket;
}

void Server::handle_client(int listen_sock, int client_sock)   //信息处理函数,功能是将客户端传过来的小写字母转化为大写字母
{
    char buf[SIZE];
    while(1)
    {
        int ret = read(client_socket, buf, SIZE - 1);
        if(ret == -1)
        {
            perror("read");
            break;
        }
        if(ret == 0)
        {
            break;
        }
        buf[ret] = '\0';
        int i;
//        for(i = 0; i < ret; i++)
//        {
//            buf[i] = buf[i] + 'A' - 'a';
//        }


        if(strncmp(buf,"on",2) == 0)
        {
            ledBlink(25,0);
        }
        if(strncmp(buf,"off",3) == 0)
        {
            ledBlink(25,1);
        }

        cout<<"buf: "<<buf<<endl;
        write(client_socket, buf, ret);

        if(strncmp(buf, "end", 3) == 0)
        {
            break;
        }
    }
}
