#include <iostream>
#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>

#pragma warning(disable: 4996)

SOCKET Connection;

void ClientHandler()
{
	char message[256];

	while (true)
	{
		int size = recv(Connection, message, sizeof(message), NULL);
		
		if (size > 0)
		{
			std::cout << "Received " << size << " bytes" << std::endl;
			std::cout << "-> " << message << std::endl;
		}
		else if (size < 0)
		{
			std::cout << "Connection closed" << std::endl;
			std::terminate();
		}
	}
}
/*
void ClientSender()
{	
	char message[256];

	while (true)
	{
		std::cin >> message;
		int size = send(Connection, message, sizeof(message), NULL);

		if (size != 0)
		{
			std::cout << "Transfered " << size << std::endl;
		}
	}
}
*/

int main()
{
	WSAData wsaData;
	WORD DDLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DDLVersion, &wsaData) != 0)
	{
		exit(WSAGetLastError());
	}

	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1234);
	int sizeofAddr = sizeof(addr);

	Connection = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0)
	{
		std::cout << "Error: faild connect to server" << std::endl;
		exit(WSAGetLastError());
	}
	else
	{
		std::cout << "Connected succes" << std::endl << std::endl;
		
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, NULL, NULL, NULL);
		
		char message[256];
		while (true)
		{
			std::cin.getline(message, sizeof(message));
			int size = send(Connection, message, sizeof(message), NULL);

			if (size != 0)
			{
				std::cout << "Transfered " << size << std::endl;
			}
			else 
			{
				std::cout << "Not transferred" << std::endl;
			}
		}
	}

	system("pause");
	return 0;
}