//
// Created by PC on 2022/9/5.
//

#include "Server.h"
#include "../led/Led.h"

int Server::Creat_socket()   //�����׽��ֺͳ�ʼ���Լ���������
{
    listen_socket = socket(AF_INET, SOCK_STREAM, 0);   //����һ������������׽���
    if(listen_socket == -1)
    {
        perror("socket");
        return -1;
    }
    struct sockaddr_in addr;
    int listendcliaddrlen = sizeof(addr);
    memset(&addr, 0, listendcliaddrlen);

    addr.sin_family = AF_INET;  /* Internet��ַ�� */
    addr.sin_port = htons(PORT);  /* �˿ں� */
    addr.sin_addr.s_addr = htonl(INADDR_ANY);   /* IP��ַ */

    int ret = bind(listen_socket, (struct sockaddr *)&addr, sizeof(addr));  //����
    if(ret == -1)
    {
        perror("bind");
        return -1;
    }

    cout<<"IP��ַ: "<<addr.sin_addr.s_addr<<endl;
    //��ȡ�����ĵ�ַ�Ͷ˿�
    if(getsockname(listen_socket, (struct sockaddr *)&addr, (socklen_t *)(&listendcliaddrlen)) == -1){
        cout<<"getsockname error"<<endl;
        exit(0);
    }
    cout<<"��ȡ�����ĵ�ַ�Ͷ˿� = "<<inet_ntoa(addr.sin_addr)<<":"<<ntohs(addr.sin_port)<<endl;


    cout<<"��ʼ����......."<<endl;
    ret = listen(listen_socket, 5);        //����
    if(ret == -1)
    {
        perror("listen");
        return -1;
    }
    return listen_socket;
}

int Server::wait_client(int listen_sock)
{
    struct sockaddr_in cliaddr,seraddr;//�ֱ��ʾ�ͻ��˵�ַ�ͷ���˵�ַ
    char ipAddr[INET_ADDRSTRLEN];//������ʮ���Ƶĵ�ַ

    int cliaddrlen = sizeof(cliaddr);
    int seraddrlen = sizeof(seraddr);
    cout<<"�ȴ��ͻ������ӡ�������."<<endl;
    client_socket = accept(listen_sock, (struct sockaddr *)&cliaddr, (socklen_t*)&cliaddrlen);   //����һ���Ϳͻ��˽������׽���
    if(client_socket == -1)
    {
        perror("accept");
        return -1;
    }

    //��ʾ�������ϵĶԶ˵�ַ
    if(getpeername(client_socket, (struct sockaddr *)&cliaddr, (socklen_t *)(&cliaddrlen)) == -1){
        cout<<"getpeername error\n";
        exit(0);
    }
    cout<<"�����ϵĿͻ��˵�ַ = "<<inet_ntop(AF_INET, &cliaddr.sin_addr, ipAddr, sizeof(ipAddr))<<":"<<ntohs(cliaddr.sin_port)<<endl;
    //cout << "�ɹ����յ�һ���ͻ��ˣ�" << inet_ntoa(cliaddr.sin_addr)<<endl;


    //��ʾ�������ϵı��ص�ַ
    if(getsockname(client_socket, (struct sockaddr *)&seraddr, (socklen_t *)(&seraddrlen)) == -1){
        cout<<"getpeername error\n";
        exit(0);
    }
    cout<<"�����ϵķ���˵�ַ = "<<inet_ntoa(seraddr.sin_addr)<<":"<<ntohs(seraddr.sin_port)<<endl;

    return client_socket;
}

void Server::handle_client(int listen_sock, int client_sock)   //��Ϣ������,�����ǽ��ͻ��˴�������Сд��ĸת��Ϊ��д��ĸ
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
