#include <iostream>
#include <WS2tcpip.h>

#pragma comment (lib, "ws2_32.lib")

using namespace std;

void main()
{
	//Startup Winsock 
	WSADATA data;
	WORD version = MAKEWORD(2,2);
	int wsOk = WSAStartup(version, &data);
	if (wsOk != 0)
	{
		cout << "Can't start the Winsock! " << wsOk<<endl;
	}
	//Bind Socket to the IP Address and port 
	SOCKET in = socket(AF_INET, SOCK_DGRAM,0);
	sockaddr_in serverHint;
	serverHint.sin_addr.S_un.S_addr = ADDR_ANY;
	serverHint.sin_family = AF_INET;
	serverHint.sin_port = htons(54000); //Convert from littke to big Endian

	if (bind(in, (sockaddr*)&serverHint, sizeof(serverHint)) == SOCKET_ERROR)
	{
		cout << "Can't bind to the socket! " << WSAGetLastError() << endl;
		return;
	}
	sockaddr_in client;
	int clientLength = sizeof(client);
	ZeroMemory(&client, clientLength);

	char buf[1024];
	//Enter a loop
	while (true)
	{
		ZeroMemory(buf, 1024);

		//Inside loop wait for the message 
		int bytesIn = recvfrom(in, buf, 1024, 0,(sockaddr*)&client, &clientLength);
		if (bytesIn == SOCKET_ERROR)
		{
			cout<<" Error receiving  from client" <<WSAGetLastError() <<endl;
			continue;
		}
		//Display the message and client info
		char clientIp[256];
		ZeroMemory(clientIp, 256);

		inet_ntop(AF_INET, &client.sin_addr, clientIp, 256);
		cout<<"Message recv from " << clientIp<< " : "<<buf <<endl;

	}
	
		
	//Close Socket 
	closesocket(in);
	//Shutdown winsock
	WSACleanup();
}