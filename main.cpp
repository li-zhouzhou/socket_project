#include "server/Server.h"

using namespace std;

int main()
{
    cout<<"aaaaaaaaaaaaaaaa"<<endl;
    cout<<"bbbbbbbbbbbbbbbb"<<endl;

    Server server;//�ͻ��˵ĺ�����

    int listen_fd = server.Creat_socket();
    int client_fd = server.wait_client(listen_fd);
    server.handle_client(listen_fd, client_fd);

    cout<<"lizhoulihzou"<<endl;

    return 0;
}

