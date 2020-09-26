#include <iostream>
#include <WS2tcpip.h>
#include <string>
#pragma comment (lib, "ws2_32.lib")

using namespace std;

void main(int argc, char* argv[]) //we can pass in a command lIne Option!!
{
	//Startup Winsock 
	WSADATA data;
	WORD version = MAKEWORD(2, 2);
	int wsOk = WSAStartup(version, &data);
	if (wsOk != 0)
	{
		cout << "Can't start the Winsock! " << wsOk << endl;
		return;
	}
	//Create a hint Structure for the server
	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(54000);
	inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

	//Socket Creation 
	SOCKET out = socket(AF_INET, SOCK_DGRAM, 0);

	//Write out to that socket
	string s(argv[1]);
	int sendOk = sendto(out,s.c_str(),s.size()+1, 0, (sockaddr*)&server, sizeof(server));
	if (sendOk == SOCKET_ERROR)
	{
		cout<<"That didn't work" <<WSAGetLastError << endl;
	}
	//close the socket
	closesocket(out);

	//Close down the Winsock
	WSACleanup();
}