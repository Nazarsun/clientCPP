#pragma comment(lib, "ws2_32.lib")

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <ctime>

int wsadata_handler()
{
	WSADATA WsaData;
	int err = WSAStartup(0x0101, &WsaData);
	if (err == SOCKET_ERROR) std::cout << "WSAStartup failed : " << GetLastError();
	return 0;
}

int main()
{
	int err = wsadata_handler();
	int s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN anAddr;
	anAddr.sin_family = AF_INET;
	anAddr.sin_port = htons(80);
	err = inet_pton(AF_INET, "127.0.0.1", &(anAddr.sin_addr));

	std::cout << "inet_pton: " << err <<"\n";


	err = connect(s, (LPSOCKADDR)&anAddr, sizeof(anAddr));
	std::cout << "Connect result: " << err << "\n";
	if (err == -1)
	{
		std::cout << "Error: " << WSAGetLastError() << "\n";
		exit(0);
	}

	

	for (;;)
	{
		//err = recv(s, buf, lenbuf, 0);
		//std::cout << "\Client IP: " << buf << "\n";
		char buf[64] = "asdasda";
		err = send(s, buf, sizeof(buf), 0);
		char cbuf[128] = "bye!!";
		err = recv(s, cbuf, 128, 0);
		std::cout << "Current date & time: " << cbuf << "\n";
		
		while (1)
		{
			std::cout << "Continue? (Y/N): ";
			std::cin >> buf;
			err = send(s, buf, sizeof(buf), 0);

			if (buf[0] == 'Y')
			{
				break;
			}
			else if (buf[0] == 'N')
			{
				shutdown(s, SD_BOTH);
				closesocket(s);
				exit(0);
			}
		}

	}
	
	
	
}