#include <iostream>
#include <cstring>
#include <winsock2.h>

#include "protocol.h"

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080
#define SERVER_IP "127.0.0.1"

void sendChoice(SOCKET clientSocket, Choice clientChoice) {
    // �޽��� ��� ����
    MessageHeader header;
    header.messageType = MessageType::CHOICE_RESPONSE;
    header.messageSize = sizeof(Choice);
    header.option = 0; // ���������� ����

    // �޽��� ��� ����
    send(clientSocket, reinterpret_cast<char*>(&header), sizeof(MessageHeader), 0);

    // �޽��� ���� ����
    send(clientSocket, reinterpret_cast<char*>(&clientChoice), sizeof(Choice), 0);
}

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed." << std::endl;
        return -1;
    }

    SOCKET clientSocket;
    struct sockaddr_in serverAddr;
    //����
    // ���� ����
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Error creating client socket" << std::endl;
        WSACleanup();
        return -1;
    }

    // ���� �ּ� ����
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &serverAddr.sin_addr);

    // ������ ����
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Error connecting to server" << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return -1;
    }

    std::cout << "Connected to server" << std::endl;

    // ����ڿ��� ���������� ���� �ޱ�
    Choice clientChoice;
    std::cout << "Enter your choice (0: Rock, 1: Paper, 2: Scissors): ";
    std::cin >> clientChoice;

    // ���� ����
    sendChoice(clientSocket, clientChoice);

    // ��� ����
    GameData gameResult;
    recv(clientSocket, reinterpret_cast<char*>(&gameResult), sizeof(GameData), 0);

    // ���� ��� ���
    if (gameResult.attack == 0) {
        std::cout << "Server wins!" << std::endl;
    }
    else {
        std::cout << "Client wins!" << std::endl;
    }

    // ���� �ݱ�
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
