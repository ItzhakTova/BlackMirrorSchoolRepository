
#include <iostream>
#include <WS2tcpip.h>

#pragma comment (lib, "ws2_32.lib") //Winsock Library

using namespace std;

#include "School/School.h"

// Defining black mirror school possible operations enum 
enum blackMirrorOperationsEnum {
	AddNewStudent = 1,
	AddNewTeacher = 2,
	StudentEntranceToClassDocumention = 3,
	StudentExitingFromClassDocumention = 4,
	StudentEatingDocumention = 5,
	TwoStudentsChattingDocumention = 6,
	GetStudentsList = 160,
	GetTeachersList = 161,
	GetAListOfAllTheStudentsWhoAteInTheLast60Minutes = 162,
	GetAPresenceListForEachClass = 163
};

/*************************************************************************
* Function Description:
* The following function is responsible of converting hex string to an 
* ascii string
*************************************************************************/
string  ConvertHexStringToAsciiString(string hexStr)
{
	int len = hexStr.length();
	string asciiString;

	for (int i = 0; i < len; i += 2)
	{
		string byte = hexStr.substr(i, 2);
		char chr = (char)(int)strtol(byte.c_str(), NULL, 16);		

		asciiString.push_back(chr);
	}

	return asciiString;
}

/*************************************************************************
* Function Description:
* The following function is responsible of converting hex string to an 
* integer number
*************************************************************************/
int ConvertHexStringToInt(string hexStr)
{
	int number = (int)strtol(hexStr.c_str(), NULL, 16);

	return number;
}

/*****************************************************************************
* Function Description:
* The following function is responsible of parsing the reeived payload string
* In order to get all the required arguments in order to perform the client's
* desired operation - we will parse the received payload string (that holds all
* the arguments) in the following manner:
* since all the argumnets are separted by "," (hex value 2c) - we will get all
* the arguments and save them in the given vector by spliting the payload 
* string by "," (hex value 2c)
******************************************************************************/
void ParseReceivedPayloadString(string str,
	                            vector<string>& receivedPacketArgumentsVector)
{	
	string subStr = "2c";
	string argument = "";

	int startIndex = 0;
	int endIndex = str.find(subStr);	

	while (endIndex != -1)
	{
		argument = str.substr(startIndex, endIndex - startIndex);

		//inserting the found sub string to the arguments vector
		receivedPacketArgumentsVector.push_back(argument);

		startIndex = endIndex + subStr.size();

		endIndex = str.find(subStr, startIndex);
	}

	argument = str.substr(startIndex, endIndex - startIndex);

	//inserting the found sub string to the arguments vector
	receivedPacketArgumentsVector.push_back(argument);	
}

/*************************************************************************
* Function Description:
* The following function is responsible the received packet proccessing 
* and returns the server answer for the required operation
*************************************************************************/
string HandleReceivedPacket(string receivedOperationCodeStr,
	             string receivedPayloadFieldStr, School& blackMirrorSchool)
{
	string serverResponseToReceivedPacket = "";
	
	int operationCode = ConvertHexStringToInt(receivedOperationCodeStr);	

	blackMirrorOperationsEnum operationToPerform =
		                     (blackMirrorOperationsEnum)operationCode;

	
	//checking if the operation is one of the Get operations
	if (operationCode >= 160 && operationCode <= 163)
	{
		if (operationToPerform == GetStudentsList)
		{
			serverResponseToReceivedPacket = blackMirrorSchool.GetStudents();
		}
		else if (operationToPerform == GetTeachersList)
		{
			serverResponseToReceivedPacket = blackMirrorSchool.GetTeachers();
		}
		else if (operationToPerform == GetAListOfAllTheStudentsWhoAteInTheLast60Minutes)
		{
			serverResponseToReceivedPacket = blackMirrorSchool.GetStudentsWhoAteInTheLast60MinutesList();
		}
		else if (operationToPerform == GetAPresenceListForEachClass)
		{
			serverResponseToReceivedPacket = blackMirrorSchool.GetClassesPresenceList();
		}
	}
	else if (operationCode >= 1 && operationCode <= 6)
	{
		vector<string> OperationArgumentsVector;

		//getting all the argumnets for the desired operation fron the recived payload string
		ParseReceivedPayloadString(receivedPayloadFieldStr, OperationArgumentsVector);

		if (operationToPerform == AddNewStudent)
		{
			//for this operation there should be 3 arguments
			if (OperationArgumentsVector.size() == 3)
			{
				string newStudentName = ConvertHexStringToAsciiString(OperationArgumentsVector[0]);
				string newStudentCellPhone = ConvertHexStringToAsciiString(OperationArgumentsVector[1]);
				int newStudentAge = ConvertHexStringToInt(OperationArgumentsVector[2]);

				serverResponseToReceivedPacket = blackMirrorSchool.AddNewStudent(newStudentName,
					newStudentCellPhone, newStudentAge);
			}
			else
			{
				serverResponseToReceivedPacket = "-1 Incorrect arguments input";
			}			
		}
		else if (operationToPerform == AddNewTeacher)
		{
			//for this operation there should be 3 arguments
			if (OperationArgumentsVector.size() == 3)
			{
				string newTeacerName = ConvertHexStringToAsciiString(OperationArgumentsVector[0]);
				string newTeacherCellPhone = ConvertHexStringToAsciiString(OperationArgumentsVector[1]);
				int newTeacherClassNumber = ConvertHexStringToInt(OperationArgumentsVector[2]);

				serverResponseToReceivedPacket = blackMirrorSchool.AddNewTeacher(newTeacerName,
					newTeacherCellPhone, newTeacherClassNumber);
			}
			else
			{
				serverResponseToReceivedPacket = "-1 Incorrect arguments input";
			}
		}
		else if (operationToPerform == StudentEntranceToClassDocumention ||
			     operationToPerform == StudentExitingFromClassDocumention)
		{
			//for these operations there should be 2 arguments
			if (OperationArgumentsVector.size() == 2)
			{
				int studentId = ConvertHexStringToInt(OperationArgumentsVector[0]);
				int classNumber = ConvertHexStringToInt(OperationArgumentsVector[1]);

				if (operationToPerform == StudentEntranceToClassDocumention)
				{
					serverResponseToReceivedPacket = blackMirrorSchool.EnterStudentToClass(studentId, classNumber);	
				}
				else if (operationToPerform == StudentExitingFromClassDocumention)
				{
					serverResponseToReceivedPacket = blackMirrorSchool.ExitStudentFromClass(studentId, classNumber);
				}
			}
			else
			{
				serverResponseToReceivedPacket = "-1 Incorrect arguments input";
			}
		}
		else if (operationToPerform == StudentEatingDocumention)
		{
			//for this operation there should be 1 argument
			if (OperationArgumentsVector.size() == 1)
			{				
				int studentId = ConvertHexStringToInt(OperationArgumentsVector[0]);

				serverResponseToReceivedPacket = blackMirrorSchool.StudentEat(studentId);
			}
			else
			{
				serverResponseToReceivedPacket = "-1 Incorrect arguments input";
			}
		}
		else if (operationToPerform == TwoStudentsChattingDocumention)
		{
			//for this operation there should be 2 arguments
			if (OperationArgumentsVector.size() == 2)
			{
				int firstStudentId = ConvertHexStringToInt(OperationArgumentsVector[0]);
				int secondStudentId = ConvertHexStringToInt(OperationArgumentsVector[1]);

				serverResponseToReceivedPacket = blackMirrorSchool.StudentsChat(firstStudentId, secondStudentId);
			}
			else
			{
				serverResponseToReceivedPacket = "-1 Incorrect arguments input";
			}
		}
	}
	else
	{
		serverResponseToReceivedPacket = "-1 Invalid operation code";
	}

	return serverResponseToReceivedPacket;
}

/*************************************************************************
* Function Description:
* The following function is the main() function.
* Creating a TCP server.
*************************************************************************/
int main()
{
	School blackMirrorSchool;

	//Initialize WinSock
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsok = WSAStartup(ver, &wsData);

	if (wsok != 0)
	{
		printf("-1 Error: Winsock initializing has failed. "
			   "Exiting the system");
		return 0;
	}

	//Creating a socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
	{
		printf("-1 Error: Socket creation has failed. "
			   "Exiting the system");
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

		//wait for client to send data
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
				
		/*
		* The received packet is in the following structure
		* REQ_NUMBER - 4 bytes
		* OP_CODE - 1 byte
		* SIZE - 4 bytes
		* PAYLOAD - the value of size represent the amount of bytes of this field
		*/
		string receivedPacket = string(buf, 0, bytesReceived);

		string receivedReqNumberStr = string(receivedPacket.begin(), receivedPacket.begin() + 8); //4 first bytes
		string receivedOperationCodeStr = string(receivedPacket.begin() + 8, receivedPacket.begin() + 10); //byte
		string receivedSizeFieldStr = string(receivedPacket.begin() + 10, receivedPacket.begin() + 18); //4 first bytes
		string receivedPayloadFieldStr = string(receivedPacket.begin() + 18, receivedPacket.end()); //4 first bytes

		//Getting the server response for the received packet
		string serverResponseToReceivedClientPacket = 
			HandleReceivedPacket(receivedOperationCodeStr, receivedPayloadFieldStr, blackMirrorSchool);

		//Answering the client
		send(clientSocket, serverResponseToReceivedClientPacket.c_str(),
			 serverResponseToReceivedClientPacket.size() + 1, 0);
	}

	//Closing the socket
	closesocket(clientSocket);

	//Cleanup winsock
	WSACleanup();

	return 0;
}
