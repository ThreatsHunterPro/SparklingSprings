#pragma once

#include <SFML/Network.hpp>

#include "IManager.h"
#include "Singleton.h"

using namespace std;
using namespace sf;

enum ConsoleInfo
{
	NOTHING,
	INFOS,
	ERRORS,
	ALL,
};

enum NetworkType
{
	NONE,
	HOST,
	CLIENT,
};

class NetworkManager : public Singleton<NetworkManager>, public IManager<string, string>
{
	vector<TcpSocket*> clients;
	NetworkType type;
	string serverIP;
	int serverPort;
	TcpSocket* client;
	TcpListener* server;
	ConsoleInfo consoleInfoType;
	string networkManagerPrefix;

public:
	void SetConsoleInfoType(const ConsoleInfo _type = ALL)
	{
		consoleInfoType = _type;
	}
	void SetTargetIP(const string& _ip = "127.0.0.1")
	{
		serverIP = _ip;
	}
	void SetTargetPort(const int _port = 42000)
	{
		serverPort = _port;
	}
private:
	bool IsNetworkPrepared() const
	{
		return type != NONE;
	}

public:
	NetworkManager();
	~NetworkManager();

private:
	void DisplayInfo(const string& _info);
	void DisplayError(const string& _error);

public:
	void PrepareHost();
	void PrepareClient();
	void UpdateNetwork();

	#pragma region ServersOnly

private:

public:
	void WaitForClient();
	void BroadcastMessage(const string& _message);

	#pragma endregion

	#pragma region ClientsOnly

private:
	void CheckForBroadcastMessage();
public:
	bool JoinServer();

	#pragma endregion
};