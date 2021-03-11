#include <iostream>
#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>

#pragma warning(disable: 4996)
SOCKET Connection;

void ServerHandler()
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
			std::cout << "Client disconected" << std::endl;
			std::terminate();
		}
	}
}
/*
void ServerSender()
{
	char message[256];

	while (true)
	{
		std::cin >> message;
		int size = send(Connection, message, sizeof(message), NULL);

		if (size != 0)
		{
			std::cout << "Transfered " << size << " bytes" << std::endl;
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

	SOCKET listener = socket(AF_INET, SOCK_STREAM, 0);

	if(INVALID_SOCKET == listener)
	{
		exit(WSAGetLastError());
	}

	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1234);
	int sizeofAddr = sizeof(addr);


	if (bind(listener, (SOCKADDR*)&addr, sizeof(addr)) != 0)
	{
		exit(WSAGetLastError());
	}
	 
	listen(listener, 10);
	
	Connection = accept(listener, (SOCKADDR*)&addr, &sizeofAddr);

	if (Connection == 0)
	{
		std::cout << "Connection error" << std::endl;
	}
	else
	{
		std::cout << "Client connected" << std::endl;


		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ServerHandler, NULL, NULL, NULL);
	
		char message[256];

		while (true)
		{
			std::cin.getline(message, sizeof(message));
			int size = send(Connection, message, sizeof(message), NULL);

			if (size != 0)
			{
				std::cout << "Transfered packet size " << size << " bytes" << std::endl;
			}
			else 
			{
				std::cout << "Not transfered" << std::endl;
			}
		}
	}

	system("pause");
	return 0;

}
