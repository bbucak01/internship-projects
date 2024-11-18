#pragma once
#pragma comment(lib, "ws2_32.lib")

#include<chrono>
#include<thread>
#include<WS2tcpip.h>
#include<windows.h>
#include<ctime>
#include<iostream>
#include<fstream>
#include<string>



#define ITERETION (10000000)
#define TIME_ENABLED (0)
#define DEBUG_ENABLED (1)
using namespace std;

class Task
{
public:

	virtual void run() = 0;
};


#if DEBUG_ENABLED
// aciksa
#else
// kapaliysa
#endif


class TaskOne : public Task{
public:
	virtual void run() {
		// Winsock baþlatma
		WSADATA data;
		WORD version = MAKEWORD(2, 2);
		int wsOK = WSAStartup(version, &data);
		if (wsOK != 0) {
			cout << "Can't start Winsock, Error #" << wsOK << endl;
			return;
		}

		// Sunucu yapýlandýrmasý
		sockaddr_in server;
		server.sin_family = AF_INET;
		server.sin_port = htons(54000);
		inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

		// Soket oluþturma
		SOCKET out = socket(AF_INET, SOCK_DGRAM, 0);
		if (out == INVALID_SOCKET) {
			cout << "Can't create socket, Error #" << WSAGetLastError() << endl;
			WSACleanup();
			return;
		}
		int hscounterone = 0;
		// handshake loop
		clock_t startOneHandshake = clock(), finishOneHandshake;
		for (int i = 0; i < ITERETION; i++) {
			if (hscounterone != 134324)
				hscounterone++;
			else
				continue;
		}

		finishOneHandshake = clock();
		//controlling is function interrupted between handshake loop and pinging loop
#if DEBUG_ENABLED
		float TaskOneHandshakeTime = finishOneHandshake - startOneHandshake;
		std::this_thread::sleep_for(std::chrono::microseconds(150));  //manual interrupt
		clock_t controlOneHandshake = clock();
		if (hscounterone != ITERETION)
			sendToServer(out, server, "TaskOne HandshakeLoop ÝNTERRUPTED");
		
		if (controlOneHandshake - finishOneHandshake != 0) {
			sendToServer(out, server, "TaskOne INTERRUPTED between handshake and pinging loop");
		}
#endif


#if TIME_ENABLED
		sendToServer(out, server, "handshake loop for TaskOne " + std::to_string((float)(finishOneHandshake - startOneHandshake) * 1000) + " microseconds");
#endif 

		while (1) {
			std::this_thread::sleep_for(std::chrono::microseconds(150));

			// pinging loop
			int pingCounterOne = 0;
			clock_t startOnePing = clock(), finishOnePing;
			for (int i = 0; i < ITERETION; i++) {
				if (pingCounterOne != 134324)
					pingCounterOne++;
				else
					continue;
			}
			finishOnePing = clock();
			//controlling is function interrupted at pinging loop
#if DEBUG_ENABLED
			float TaskonePingTime = finishOnePing - startOnePing;
			clock_t controlOnePing = clock();
			if (controlOnePing - finishOnePing != 0) {
				sendToServer(out, server, "Taskone  INTERRUPTED after PingLoop");
			}
			if (pingCounterOne != ITERETION)
				sendToServer(out, server, "TaskOne PingLoop INTERRUPTED");
#endif

#if TIME_ENABLED
			sendToServer(out, server, "ping loop for TaskOne " + std::to_string((float)(finishOnePing - startOnePing) * 1000) + " microseconds");
#endif
		}

		// Soketi kapat
		closesocket(out);

		// Winsock kapatma
		WSACleanup();
	}

private:
	void sendToServer(SOCKET & out, sockaddr_in & server, const std::string & message) {
		int sendOk = sendto(out, message.c_str(), message.size() + 1, 0, (sockaddr*)&server, sizeof(server));
		if (sendOk == SOCKET_ERROR) {
			cout << "That didn't work! Error #" << WSAGetLastError() << endl;
		}
	}
};
class TaskTwo : public Task
{
public:
	virtual void run() {
		// Winsock baþlatma
		WSADATA data;
		WORD version = MAKEWORD(2, 2);
		int wsOK = WSAStartup(version, &data);
		if (wsOK != 0) {
			cout << "Can't start Winsock, Error #" << wsOK << endl;
			return;
		}

		// Sunucu yapýlandýrmasý
		sockaddr_in server;
		server.sin_family = AF_INET;
		server.sin_port = htons(54000);
		inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

		// Soket oluþturma
		SOCKET out = socket(AF_INET, SOCK_DGRAM, 0);
		if (out == INVALID_SOCKET) {
			cout << "Can't create socket, Error #" << WSAGetLastError() << endl;
			WSACleanup();
			return;
		}

		// handshake loop
		clock_t startTwoHandshake = clock(), finishTwoHandshake;
		for (int i = 0; i < 10000000; i++) {
			continue;
		}
		finishTwoHandshake = clock();
		//controlling is function interrupted at handshake loop
#if DEBUG_ENABLED
		float TaskTwoHandshakeTime = finishTwoHandshake - startTwoHandshake;
		clock_t controlTwoHandshake = clock();
		if (controlTwoHandshake - finishTwoHandshake != 0) {
			sendToServer(out, server, "TaskTwo HandshakeLoop ÝNTERRUPTED");
		}
#endif

#if TIME_ENABLED
		sendToServer(out, server, "handshake loop for TaskTwo " + std::to_string((float)(finishTwoHandshake - startTwoHandshake) * 1000) + " microseconds");
#endif 

		while (1) {
			std::this_thread::sleep_for(std::chrono::microseconds(150));

			// pinging loop
			clock_t startTwoPing = clock(), finishTwoPing;
			for (int i = 0; i < 10000000; i++) {
				continue;
			}
			finishTwoPing = clock();
			//controlling is function interrupted at pinging loop
#if DEBUG_ENABLED
			float TaskTwoPingTime = finishTwoPing - startTwoPing;
			clock_t controlTwoPing = clock();
			if (controlTwoPing - finishTwoPing != 0) {
				sendToServer(out, server, "TaskTwo PingLoop ÝNTERRUPTED");
			}
#endif

#if TIME_ENABLED
			sendToServer(out, server, "ping loop for TaskTwo " + std::to_string((float)(finishTwoPing - startTwoPing) * 1000) + " microseconds");
#endif
		}

		// Soketi kapat
		closesocket(out);

		// Winsock kapatma
		WSACleanup();
	}

private:
	void sendToServer(SOCKET& out, sockaddr_in& server, const std::string& message) {
		int sendOk = sendto(out, message.c_str(), message.size() + 1, 0, (sockaddr*)&server, sizeof(server));
		if (sendOk == SOCKET_ERROR) {
			cout << "That didn't work! Error #" << WSAGetLastError() << endl;
		}
	}
};
class TaskThree : public Task
{
public:
	virtual void run() {
		// Winsock baþlatma
		WSADATA data;
		WORD version = MAKEWORD(2, 2);
		int wsOK = WSAStartup(version, &data);
		if (wsOK != 0) {
			cout << "Can't start Winsock, Error #" << wsOK << endl;
			return;
		}

		// Sunucu yapýlandýrmasý
		sockaddr_in server;
		server.sin_family = AF_INET;
		server.sin_port = htons(54000);
		inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

		// Soket oluþturma
		SOCKET out = socket(AF_INET, SOCK_DGRAM, 0);
		if (out == INVALID_SOCKET) {
			cout << "Can't create socket, Error #" << WSAGetLastError() << endl;
			WSACleanup();
			return;
		}

		// handshake loop
		clock_t startThreeHandshake = clock(), finishThreeHandshake;
		for (int i = 0; i < 10000000; i++) {
			continue;
		}
		finishThreeHandshake = clock();
		//controlling is function interrupted at handshake loop
#if DEBUG_ENABLED
		float TaskThreeHandshakeTime = finishThreeHandshake - startThreeHandshake;
		clock_t controlThreeHandshake = clock();
		if (controlThreeHandshake - finishThreeHandshake != 0) {
			sendToServer(out, server, "TaskThree HandshakeLoop ÝNTERRUPTED");
		}
#endif

#if TIME_ENABLED
		sendToServer(out, server, "handshake loop for TaskThree " + std::to_string((float)(finishThreeHandshake - startThreeHandshake) * 1000) + " microseconds");
#endif 

		while (1) {
			std::this_thread::sleep_for(std::chrono::microseconds(150));

			// pinging loop
			clock_t startThreePing = clock(), finishThreePing;
			for (int i = 0; i < 10000000; i++) {
				continue;
			}
			finishThreePing = clock();
			//controlling is function interrupted at pinging loop
#if DEBUG_ENABLED
			float TaskThreePingTime = finishThreePing - startThreePing;
			clock_t controlThreePing = clock();
			if (controlThreePing - finishThreePing != 0) {
				sendToServer(out, server, "TaskThree PingLoop ÝNTERRUPTED");
			}
#endif

#if TIME_ENABLED
			sendToServer(out, server, "ping loop for TaskThree " + std::to_string((float)(finishThreePing - startThreePing) * 1000) + " microseconds");
#endif
		}

		// Soketi kapat
		closesocket(out);

		// Winsock kapatma
		WSACleanup();
	}

private:
	void sendToServer(SOCKET& out, sockaddr_in& server, const std::string& message) {
		int sendOk = sendto(out, message.c_str(), message.size() + 1, 0, (sockaddr*)&server, sizeof(server));
		if (sendOk == SOCKET_ERROR) {
			cout << "That didn't work! Error #" << WSAGetLastError() << endl;
		}
	}
};
class TaskFour : public Task
{
public:
	virtual void run() {
		// Winsock baþlatma
		WSADATA data;
		WORD version = MAKEWORD(2, 2);
		int wsOK = WSAStartup(version, &data);
		if (wsOK != 0) {
			cout << "Can't start Winsock, Error #" << wsOK << endl;
			return;
		}

		// Sunucu yapýlandýrmasý
		sockaddr_in server;
		server.sin_family = AF_INET;
		server.sin_port = htons(54000);
		inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

		// Soket oluþturma
		SOCKET out = socket(AF_INET, SOCK_DGRAM, 0);
		if (out == INVALID_SOCKET) {
			cout << "Can't create socket, Error #" << WSAGetLastError() << endl;
			WSACleanup();
			return;
		}

		// handshake loop
		clock_t startFourHandshake = clock(), finishFourHandshake;
		for (int i = 0; i < 10000000; i++) {
			continue;
		}
		finishFourHandshake = clock();
		//controlling is function interrupted at handshake loop
#if DEBUG_ENABLED
		float TaskFourHandshakeTime = finishFourHandshake - startFourHandshake;
		clock_t controlFourHandshake = clock();
		if (controlFourHandshake - finishFourHandshake != 0) {
			sendToServer(out, server, "TaskFour HandshakeLoop ÝNTERRUPTED");
		}
#endif

#if TIME_ENABLED
		sendToServer(out, server, "handshake loop for TaskFour " + std::to_string((float)(finishFourHandshake - startFourHandshake) * 1000) + " microseconds");
#endif 

		while (1) {
			std::this_thread::sleep_for(std::chrono::microseconds(150));

			// pinging loop
			clock_t startFourPing = clock(), finishFourPing;
			for (int i = 0; i < 10000000; i++) {
				continue;
			}
			finishFourPing = clock();
			//controlling is function interrupted at pinging loop
#if DEBUG_ENABLED
			float TaskFourPingTime = finishFourPing - startFourPing;
			clock_t controlFourPing = clock();
			if (controlFourPing - finishFourPing != 0) {
				sendToServer(out, server, "TaskFour PingLoop ÝNTERRUPTED");
			}
#endif

#if TIME_ENABLED
			sendToServer(out, server, "ping loop for TaskFour " + std::to_string((float)(finishFourPing - startFourPing) * 1000) + " microseconds");
#endif
		}

		// Soketi kapat
		closesocket(out);

		// Winsock kapatma
		WSACleanup();
	}

private:
	void sendToServer(SOCKET& out, sockaddr_in& server, const std::string& message) {
		int sendOk = sendto(out, message.c_str(), message.size() + 1, 0, (sockaddr*)&server, sizeof(server));
		if (sendOk == SOCKET_ERROR) {
			cout << "That didn't work! Error #" << WSAGetLastError() << endl;
		}
	}
};
class TaskFive : public Task
{
public:
	virtual void run() {
		// Winsock baþlatma
		WSADATA data;
		WORD version = MAKEWORD(2, 2);
		int wsOK = WSAStartup(version, &data);
		if (wsOK != 0) {
			cout << "Can't start Winsock, Error #" << wsOK << endl;
			return;
		}

		// Sunucu yapýlandýrmasý
		sockaddr_in server;
		server.sin_family = AF_INET;
		server.sin_port = htons(54000);
		inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

		// Soket oluþturma
		SOCKET out = socket(AF_INET, SOCK_DGRAM, 0);
		if (out == INVALID_SOCKET) {
			cout << "Can't create socket, Error #" << WSAGetLastError() << endl;
			WSACleanup();
			return;
		}

		// handshake loop
		clock_t startFiveHandshake = clock(), finishFiveHandshake;
		for (int i = 0; i < 10000000; i++) {
			continue;
		}
		finishFiveHandshake = clock();
		//controlling is function interrupted at handshake loop
#if DEBUG_ENABLED
		float TaskFiveHandshakeTime = finishFiveHandshake - startFiveHandshake;
		clock_t controlFiveHandshake = clock();
		if (controlFiveHandshake - finishFiveHandshake != 0) {
			sendToServer(out, server, "TaskFive HandshakeLoop ÝNTERRUPTED");
		}
#endif

#if TIME_ENABLED
		sendToServer(out, server, "handshake loop for TaskFive " + std::to_string((float)(finishFiveHandshake - startFiveHandshake) * 1000) + " microseconds");
#endif 

		while (1) {
			std::this_thread::sleep_for(std::chrono::microseconds(150));

			// pinging loop
			clock_t startFivePing = clock(), finishFivePing;
			for (int i = 0; i < 10000000; i++) {
				continue;
			}
			finishFivePing = clock();
			//controlling is function interrupted at pinging loop
#if DEBUG_ENABLED
			float TaskFivePingTime = finishFivePing - startFivePing;
			clock_t controlFivePing = clock();
			if (controlFivePing - finishFivePing != 0) {
				sendToServer(out, server, "TaskFive PingLoop ÝNTERRUPTED");
			}
#endif

#if TIME_ENABLED
			sendToServer(out, server, "ping loop for TaskFive " + std::to_string((float)(finishFivePing - startFivePing) * 1000) + " microseconds");
#endif
		}

		// Soketi kapat
		closesocket(out);

		// Winsock kapatma
		WSACleanup();
	}

private:
	void sendToServer(SOCKET& out, sockaddr_in& server, const std::string& message) {
		int sendOk = sendto(out, message.c_str(), message.size() + 1, 0, (sockaddr*)&server, sizeof(server));
		if (sendOk == SOCKET_ERROR) {
			cout << "That didn't work! Error #" << WSAGetLastError() << endl;
		}
	}
};
class TaskSix : public Task
{
public:
	virtual void run() {
		// starting winsock
		WSADATA data;
		WORD version = MAKEWORD(2, 2);
		int wsOK = WSAStartup(version, &data);
		if (wsOK != 0) {
			cout << "Can't start Winsock, Error #" << wsOK << endl;
			return;
		}

		// config server
		sockaddr_in server;
		server.sin_family = AF_INET;
		server.sin_port = htons(54000);
		inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

		// creating socket
		SOCKET out = socket(AF_INET, SOCK_DGRAM, 0);
		if (out == INVALID_SOCKET) {
			cout << "Can't create socket, Error #" << WSAGetLastError() << endl;
			WSACleanup();
			return;
		}

		// handshake loop
		clock_t startSixHandshake = clock(), finishSixHandshake;
		for (int i = 0; i < 10000000; i++) {
			continue;
		}
		finishSixHandshake = clock();
		//controlling is function interrupted at handshake loop
#if DEBUG_ENABLED
		float TaskSixHandshakeTime = finishSixHandshake - startSixHandshake;

		clock_t controlSixHandshake = clock();
		if (controlSixHandshake - finishSixHandshake != 0) {
			sendToServer(out, server, "TaskSix HandshakeLoop ÝNTERRUPTED");
		}
#endif

#if TIME_ENABLED
		sendToServer(out, server, "handshake loop for TaskSix " + std::to_string((float)(finishSixHandshake - startSixHandshake) * 1000) + " microseconds");
#endif 

		while (1) {
			std::this_thread::sleep_for(std::chrono::microseconds(150));

			// pinging loop
			clock_t startSixPing = clock(), finishSixPing;
			for (int i = 0; i < 10000000; i++) {
				continue;
			}
			finishSixPing = clock();
			//controlling is function interrupted at pinging loop
#if DEBUG_ENABLED
			float TaskSixPingTime = finishSixPing - startSixPing;
			clock_t controlSixPing = clock();
			if (controlSixPing - finishSixPing != 0) {
				sendToServer(out, server, "TaskSix PingLoop ÝNTERRUPTED");
			}
#endif

#if TIME_ENABLED
			sendToServer(out, server, "ping loop for TaskSix " + std::to_string((float)(finishSixPing - startSixPing) * 1000) + " microseconds");
#endif
		}

		// closing socket
		closesocket(out);

		// closing Winsock
		WSACleanup();
	}

private:
	void sendToServer(SOCKET& out, sockaddr_in& server, const std::string& message) {
		int sendOk = sendto(out, message.c_str(), message.size() + 1, 0, (sockaddr*)&server, sizeof(server));
		if (sendOk == SOCKET_ERROR) {
			cout << "That didn't work! Error #" << WSAGetLastError() << endl;
		}
	}
};

