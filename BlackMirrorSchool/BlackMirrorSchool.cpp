
#include <iostream>
#include <WS2tcpip.h>

#pragma comment (lib, "ws2_32.lib") //Winsock Library

using namespace std;

#include "School/School.h"

string HandleGivenRequest(char op_code, vector<string> argumentsVector, School &blackMirrorSchool)
{
	string result = "";
	
	//Add new student operation
	if (op_code == '1')
	{
		if (argumentsVector.size() == 3)
		{
			result = blackMirrorSchool.AddNewStudent(argumentsVector[0], argumentsVector[1], stoi(argumentsVector[2]));
		}
		else
		{
			result = "Invalid payload num of arguments";
		}
	}
	//Add new teacher operation
	else if (op_code == '2')
	{
		if (argumentsVector.size() == 3)
		{
			result = blackMirrorSchool.AddNewTeacher(argumentsVector[0], argumentsVector[1], stoi(argumentsVector[2]));
		}
		else
		{
			result = "Invalid payload num of arguments";
		}
	}
	//Enter class operation
	else if (op_code == '3')
	{
		if (argumentsVector.size() == 2)
		{
			result = blackMirrorSchool.EnterStudentToClass(stoi(argumentsVector[0]), stoi(argumentsVector[1]));
		}
		else
		{
			result = "Invalid payload num of arguments";
		}
	}
	//Exit class operation
	else if (op_code == '4')
	{
		if (argumentsVector.size() == 2)
		{
			result = blackMirrorSchool.ExitStudentFromClass(stoi(argumentsVector[0]), stoi(argumentsVector[1]));
		}
		else
		{
			result = "Invalid payload num of arguments";
		}
	}
	//Eat operation
	else if (op_code == '5')
	{
		if (argumentsVector.size() == 1)
		{
			result = blackMirrorSchool.StudentEat(stoi(argumentsVector[0]));
		}
		else
		{
			result = "Invalid payload num of arguments";
		}
	}
	//chat operation
	else if (op_code == '6')
	{
		if (argumentsVector.size() == 2)
		{
			result = blackMirrorSchool.StudentsChat(stoi(argumentsVector[0]), stoi(argumentsVector[1]));
		}
		else
		{
			result = "Invalid payload num of arguments";
		}
	}
	//Get students operation
	else if (op_code == '7')
	{		
		result = blackMirrorSchool.GetStudents();		
	}
	//Get teachers operation
	else if (op_code == '8')
	{
		result = blackMirrorSchool.GetTeachers();
	}
	//Get list of student who ate operation
	else if (op_code == '9')
	{
		result = blackMirrorSchool.GetStudentsWhoAteInTheLast60MinutesList();
	}
	//Get presence list operation
	else if (op_code == '0')
	{
		result = blackMirrorSchool.GetClassesPresenceList();
	}

	return result;
}

int main()
{
	School blackMirrorSchool;
	
	//Initialize winsoc
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsok = WSAStartup(ver, &wsData);

	if (wsok != 0)
	{
		printf("-1 Error: Winsock initializing has failed. Exiting the system");
		return 0;
	}

	//Creating a socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
	{
		printf("-1 Error: Socket creation has failed. Exiting the system");
		return 0;
	}

	//Bind the ip address and port to a socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(listening, (sockaddr*)&hint, sizeof(hint));

	//Tell winsock the socket is for listening
	listen(listening, SOMAXCONN);

	//Wait for a connection
	sockaddr_in client;
	int clientSize = sizeof(client);

	SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
	if (clientSocket == INVALID_SOCKET)
	{
		printf("-1 Error: Client Socket creation has failed. Exiting the system\n");
		return 0;
	}

	closesocket(listening);

	// while loop: get system request and answer properly
	char buf[4096];

	while (true)
	{
		ZeroMemory(buf, 4096);

		int bytesReceived = recv(clientSocket, buf, 4096, 0);

		if (bytesReceived == SOCKET_ERROR)
		{
			printf("-1 Error in data receiving. Exiting the system\n");
			break;
		}
		if (bytesReceived == 0)
		{
			printf("Client disconnected\n");
			break;
		}

		int systemRequestRunningIndex = 0;		

		//request number reading
		char reqNumberStr[8];   

		memset(reqNumberStr, '\0', sizeof(reqNumberStr));

		strncpy_s(reqNumberStr, buf + systemRequestRunningIndex, 4);

		systemRequestRunningIndex += 4; //promoting the index


		//operation code reading
		char op_code = buf[systemRequestRunningIndex];		

		++systemRequestRunningIndex; //promoting the index


		//size reading
		char payloadSizeStr[5] = "\0";

		memset(payloadSizeStr, '\0', sizeof(payloadSizeStr));

		strncpy_s(payloadSizeStr, buf + systemRequestRunningIndex, 4);		

		systemRequestRunningIndex += 4; //promoting the index

		payloadSizeStr[4] = '\0';

		string tmpStr = payloadSizeStr;	
		
		int payloadSize = stoi(tmpStr);



		//payload reading
		string payloadStr = "";

		memset(&payloadStr, '\0', payloadSize);

		memcpy(&payloadStr[0], buf + systemRequestRunningIndex, payloadSize);

		//arguments vector
		vector<string> argumentsVector;

		char* token = strtok(const_cast<char*>(payloadStr.c_str()), ",");
		while (token != nullptr)
		{
			argumentsVector.push_back(std::string(token));
			token = strtok(nullptr, ",");
		}		

		string serverResult = HandleGivenRequest(op_code, argumentsVector, blackMirrorSchool);

		send(clientSocket, serverResult.c_str(), serverResult.size() + 1, 0);				
	}

	//Closing the socket
	closesocket(clientSocket);

	//Shutdown winsock
	WSACleanup();

	return 0;
}
