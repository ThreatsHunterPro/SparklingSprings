#include "NetworkManager.h"
#include <iostream>

NetworkManager::NetworkManager()
{
	networkManagerPrefix = "NetworkManager";
	type = NONE;
	serverIP = "127.0.0.1";
	serverPort = 42000;
	client = nullptr;
	server = nullptr;
	clients = vector<TcpSocket*>();
	consoleInfoType = ALL;
}

NetworkManager::~NetworkManager()
{
	if (client)
	{
		delete client;
	}

	if (server)
	{
		delete server;
	}
}


#pragma region Display

void NetworkManager::DisplayInfo(const string& _info)
{
	if (consoleInfoType == INFOS || consoleInfoType == ALL)
	{
		string _prefix = "\x1B[38;5;106m[\x1B[38;5;82m";
		_prefix += networkManagerPrefix;
		_prefix += "\x1B[38;5;106m]\x1B[38;5;82m ";
		cout << _prefix << _info << "\033[0m" << endl;
	}
}

void NetworkManager::DisplayError(const string& _error)
{
	if (consoleInfoType == ERRORS || consoleInfoType == ALL)
	{
		string _prefix = "\x1B[38;5;124m[\x1B[38;5;196m";
		_prefix += networkManagerPrefix;
		_prefix += "\x1B[38;5;124m]\x1B[38;5;196m ";
		cout << _prefix << _error << "\033[0m" << endl;
	}
}

#pragma endregion

void NetworkManager::PrepareHost()
{
	if (IsNetworkPrepared())
	{
		DisplayError("Network has alreaby been prepared!");
		return;
	}

	type = HOST;
	server = new TcpListener();

	if (server->listen(serverPort) != Socket::Done)
	{
		DisplayError("An error occured while opening server!");
		DisplayError("Please check that the port and the IP address are correct!");
		return;
	}
}

void NetworkManager::PrepareClient()
{
	if (IsNetworkPrepared())
	{
		DisplayError("Network has alreaby been prepared!");
		return;
	}

	type = CLIENT;
	client = new TcpSocket();
}

void NetworkManager::UpdateNetwork()
{
	if (type == HOST)
	{
		DisplayError("Server should not update network (at least for now)!");
		return;
	}

	CheckForBroadcastMessage();
}

#pragma region ServersOnly

void NetworkManager::WaitForClient()
{
	if (type != HOST)
	{
		DisplayError("Network is not a server! Cannot listen for client!");
		return;
	}

	DisplayInfo("Server is now listening! Waiting for client connection...");
	TcpSocket* _waitingForClient = new TcpSocket();

	if (server->accept(*_waitingForClient) != Socket::Done)
	{
		DisplayError("An error occured while a client tried to join the server!");
		return;
	}

	DisplayInfo("A client is now connected to the server! Stopped server listening!");
	clients.push_back(_waitingForClient);
}

void NetworkManager::BroadcastMessage(const string& _message)
{
	for (TcpSocket* _client : clients)
	{
		Packet _packet;
		_packet << _message;
		_client->send(_packet);
	}
}

#pragma endregion

#pragma region ClientsOnly

void NetworkManager::CheckForBroadcastMessage()
{
	string _message;
	Packet _packet;

	if (client->receive(_packet) == Socket::Done)
	{
		_packet >> _message;
		cout << "\x1B[38;5;199m[\x1B[38;5;219mBroadcast\x1B[38;5;199m]\x1B[38;5;219m " << _message << "\033[0m" << endl;
	}
}

bool NetworkManager::JoinServer()
{
	if (type != CLIENT)
	{
		DisplayError("Network is not a client! Cannot connect to server!");
		return false;
	}

	if (client->connect(serverIP, serverPort) != Socket::Done)
	{
		DisplayError("An error occured while trying to connect to server!");
		DisplayError("Please check that the port and the IP address are correct!");
		return false;
	}

	DisplayInfo("Succesfully connected to server!");
	return true;
}

#pragma endregion