#include <iostream>
#include <string>
#include <WS2tcpip.h>
#include <iomanip>
#include <sstream>

#pragma comment (lib, "ws2_32.lib") //Winsock Library

using namespace std;

/**********************************************************
* Function Description:
* The following function is responsible of converting an
* ascii string to an hex string
***********************************************************/
string ConvertStringToHex(string str)
{
	std::stringstream stream;

	for (const auto& item : str)
	{
		stream << hex << int(item);
	}

	return (stream.str());
}

/***************************************************************
* Function Description:
* The following function is responsible of converting an
* integer to an hex string without bytes padding (meaning
* if the hex value can be represented in one byte insted of 4
* we will return a string of only one byte
****************************************************************/
string ConverIntToHexWithoutBytesPadding(int num)
{
	std::stringstream stream;
	stream << std::hex << num;

	string integerAsHexStr = stream.str();

	if (integerAsHexStr.size() % 2 == 1)
	{
		integerAsHexStr = "0" + integerAsHexStr;
	}

	return integerAsHexStr;
}

/*********************************************************************
* Function Description:
* The following function is responsible of converting an
* integer to an hex string with bytes padding (meaning
* even if the hex value can be represented in one byte insted of 4
* we will return a string of 4 bytes
**********************************************************************/
string ConverIntToHexWithBytesPadding(int num)
{
	std::stringstream stream;

	stream << std::setfill('0') << std::setw(sizeof(num) * 2) //padding
		   << std::hex << num;

	return stream.str();
}

/*************************************************************************
* Function Description:
* The following function will return true if the given string is composed
* from digits onlym and false otherwise.
*************************************************************************/
bool isGivenStringANumber(string str)
{	
	for (char c : str)
	{
		if (isdigit(c) == 0)
		{
			return false;
		}			
	}
	return true;	
}

/*************************************************************************
* Function Description:
* The following function will return true if the given string is composed
* from a to z or A-Z or white sapce only, and false otherwise.
*************************************************************************/
bool isGivenStringAlphaString(string str)
{
	for (char c : str)
	{
		//checking if current character is a to z or A-Z or white sapce.
		if (isalpha(c) == 0 && c != ' ') 
		{
			return false;
		}
	}
	return true;
}

/*************************************************************************
* Function Description:
* The following function is responsible of getting from the client the 
* student id until a valid input will be received.
*************************************************************************/
string GetStudentIdInput(string studentDescriptionStr = "")
{
	string studentIdStr = "";
	printf("Please enter%s student ID: ", studentDescriptionStr.c_str());
	getline(cin, studentIdStr);

	//input validation - id must be a positive number
	while (!isGivenStringANumber(studentIdStr) ||
		   !(stoi(studentIdStr) >= 1))
	{
		printf("-1 Invalid input. Please enter%s student ID "
			   "(valid input - a positive number only): "
			   , studentDescriptionStr.c_str());
		getline(cin, studentIdStr);
	}

	return studentIdStr;
}

/*************************************************************************
* Function Description:
* The following function is responsible of getting from the client the
* class number until a valid input will be received.
*************************************************************************/
string GetClassNumberInput()
{
	string classNumberStr = "";
	printf("Please enter class number: ");
	getline(cin, classNumberStr);

	//input validation - class number must be a non negative number
	while (!isGivenStringANumber(classNumberStr) ||
		   !(stoi(classNumberStr) >= 0))
	{
		printf("-1 Invalid input. Please enter class number " 
			   "(valid input - a non negative number only): ");
		getline(cin, classNumberStr);
	}

	return classNumberStr;
}

/*************************************************************************
* Function Description:
* The following function is responsible of getting from the client the
* cell phone until a valid input will be received.
*************************************************************************/
string GetCellphoneInput(string personDescriptionStr = "")
{
	string cellphoneStr = "";
	printf("Please enter%s cell phone: ", personDescriptionStr.c_str());
	getline(cin, cellphoneStr);

	//input validation - cell phone must be a non negative number
	while (!isGivenStringANumber(cellphoneStr) || !(stoi(cellphoneStr) >= 0))
	{
		printf("-1 Invalid input. Please enter%s cell phone "
			   "(valid input - a non negative number only): "
			   ,personDescriptionStr.c_str());

		getline(cin, cellphoneStr);
	}

	return cellphoneStr;
}

/*************************************************************************
* Function Description:
* The following function is responsible of getting from the client the
* name until a valid input will be received.
*************************************************************************/
string GetNameInput(string personDescriptionStr = "")
{
	string nameStr = "";
	printf("Please enter%s name: ", personDescriptionStr.c_str());
	getline(cin, nameStr);

	//input validation - cell phone must be a non negative number
	while (!isGivenStringAlphaString(nameStr))
	{
		printf("-1 Invalid input. Please enter%s name "
			   "(valid input - alphabet characters only): "
			   , personDescriptionStr.c_str());

		getline(cin, nameStr);
	}

	return nameStr;
}

/*************************************************************************
* Function Description:
* The following function is responsible of getting from the client the
* age until a valid input will be received.
*************************************************************************/
string GetAgeInput(string personDescriptionStr = "")
{
	string ageStr = "";
	printf("Please enter%s age: ", personDescriptionStr.c_str());
	getline(cin, ageStr);

	//input validation - cell phone must be a non negative number
	while (!isGivenStringANumber(ageStr) ||
		   !((stoi(ageStr) >= 1) && (stoi(ageStr) <= 120)))
	{
		printf("-1 Invalid input. Please enter%s age (valid input: 1-120): "
			, personDescriptionStr.c_str());

		getline(cin, ageStr);
	}

	return ageStr;
}

/*************************************************************************
* Function Description:
* The following function is responsible of getting from the client all the
* required input for the "add new student" operation.
* The returned value will be a string representing the input in it's 
* hex value
*************************************************************************/
string GetAddNewStudentOperationInputAsHexString()
{
	string nameStr = GetNameInput(" student");
	string cellphoneStr = GetCellphoneInput(" student");
	string ageStr = GetAgeInput(" student");

	string givenInputHexString =
		ConvertStringToHex(nameStr) + ConvertStringToHex(",") +
		ConvertStringToHex(cellphoneStr) + ConvertStringToHex(",") +
		ConverIntToHexWithoutBytesPadding(stoi(ageStr));

	return givenInputHexString;
}

/*************************************************************************
* Function Description:
* The following function is responsible of getting from the client all the
* required input for the "add new teacher" operation.
* The returned value will be a string representing the input in it's
* hex value
*************************************************************************/
string GetAddNewTeacherOperationInputAsHexString()
{
	string nameStr = GetNameInput(" teacher");
	string cellphoneStr = GetCellphoneInput(" teacher");
	string classNumberStr = GetClassNumberInput();

	string givenInputHexString =
		ConvertStringToHex(nameStr) + ConvertStringToHex(",") +
		ConvertStringToHex(cellphoneStr) + ConvertStringToHex(",") +
   	    ConverIntToHexWithoutBytesPadding(stoi(classNumberStr));

	return givenInputHexString;		
}

/*************************************************************************
* Function Description:
* The following function is responsible of getting from the client all the
* required input for the "Student entrance to class documention" operation
* or for the Student exiting from class documention operation.
* The returned value will be a string representing the input in it's
* hex value
*************************************************************************/
string GetClassEnteringOrExistingOperationInputAsHexString()
{
	string studentIdStr = GetStudentIdInput();

	string classNumberStr = GetClassNumberInput();

	string givenInputHexString = 
		ConverIntToHexWithoutBytesPadding(stoi(studentIdStr)) +
		ConvertStringToHex(",") +
		ConverIntToHexWithoutBytesPadding(stoi(classNumberStr));

	return givenInputHexString;
}

/*************************************************************************
* Function Description:
* The following function is responsible of getting from the client all the
* required input for the "Student eating documention" operation.
* The returned value will be a string representing the input in it's
* hex value
*************************************************************************/
string GetEatingDocumentionOperationInputAsHexString()
{
	string studentIdStr = GetStudentIdInput();

	string givenInputHexString = 
		   ConverIntToHexWithoutBytesPadding(stoi(studentIdStr));

	return givenInputHexString;
}

/*************************************************************************
* Function Description:
* The following function is responsible of getting from the client all the
* required input for the "Two students chatting documention" operation.
* The returned value will be a string representing the input in it's
* hex value
*************************************************************************/
string GetChattingDocumentionOperationInputAsHexString()
{
	string firstStudentIdStr = GetStudentIdInput(" first");	

	string secondStudentIdStr = GetStudentIdInput(" second");

	string givenInputHexString =
		ConverIntToHexWithoutBytesPadding(stoi(firstStudentIdStr)) +
		ConvertStringToHex(",") +
		ConverIntToHexWithoutBytesPadding(stoi(secondStudentIdStr));

	return givenInputHexString;
}

/*************************************************************************
* Function Description:
* The following function is the main() function.
* Creating a socket to talk with the server
*************************************************************************/
int main()
{
	string ipAddress = "127.0.0.1"; //Server IP address (local)
	int port = 54000;	           //Listening port on the server

	//Initialize WinSock
	WSADATA data;
	WORD ver = MAKEWORD(2, 2);

	int wsResult = WSAStartup(ver, &data);

	if (wsResult != 0)
	{
		printf("-1 Error: Winsock initializing has failed. "
			   "Exiting the system\n");
		return 0;
	}

	//Create socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		printf("-1 Error: Socket creation has failed. "
			   "Exiting the system\n");
		WSACleanup();
		return 0;
	}

	//Fill in a hint structure
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

	//Connect to server
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		printf("-1 Error: Connection to server has failed. "
			   "Exiting the system\n");

		closesocket(sock);
		WSACleanup();
		return 0;
	}

	//Do-while loop to send and receive data
	char buf[4096];
	string userInput;

	//Prompt the user with the following text
	printf("Hello! Welcome to the Black Mirror School System\n\n");
	printf("There are a variety of operations you can perform: \n\n");
	printf("  1. Add new student\n  2. Add new Teacher\n"
		"  3. Student entrance to class documention\n"
		"  4. Student exiting from class documention\n"
		"  5. Student eating documention\n"
		"  6. Two students chatting documention\n  7. Get students list\n"
		"  8. Get teachers list\n"
		"  9. Get a list of all the students who ate in the last 60 minutes\n"
		"  10.Get a presence list for each class\n");

	int requestNumber = 999; //according to the task requirements

	do
	{		

		printf("\nPlease choose the operation to perform: ");

		getline(cin, userInput);

		if (userInput.size() > 0)  //Make sure the user has typed in something
		{
			
			//checking if the given operation code input is a number
			while (!isGivenStringANumber(userInput) ||
				   !(stoi(userInput) >= 1 && stoi(userInput) <= 10))
			{
				printf("-1 Invalid input. "
					   "Please choose the operation to perform (valid input: 1-10): ");
				getline(cin, userInput);
			}
			
			/** At this point we are certian the given input is a valid operation code **/

			int operationIdToPerform = stoi(userInput);			
			
			++requestNumber;

			string payloadFieldAsHexString = "";
			string sizeFieldValueAsHexString = "";
			string operationCodeFieldAsHexString = "";
			string requestNumberHexString = ConverIntToHexWithBytesPadding(requestNumber);

			if (operationIdToPerform >= 7 && operationIdToPerform <= 10)
			{
				//building the packet to send to the server with the proper data
				
				//7: A0, 8: A1, 9: A2, 10: A3
				operationCodeFieldAsHexString = "A" + to_string(operationIdToPerform - 7);

				sizeFieldValueAsHexString = ConverIntToHexWithBytesPadding(0);
			}
			else
			{
				/* At this point we know operationIdToPerform >= 1 &&
				                         operationIdToPerform <= 6 */

				operationCodeFieldAsHexString = "0" + userInput;				 
				
				//Client operation choice: "Add new student"
				if (operationIdToPerform == 1) 
				{
					payloadFieldAsHexString = GetAddNewStudentOperationInputAsHexString();
				}
				//Client operation choice: "Add new Teacher"
				else if (operationIdToPerform == 2) 
				{
					payloadFieldAsHexString = GetAddNewTeacherOperationInputAsHexString();
				}
				//Client operation choice: Student entrance to / exiting from class documention  
				else if (operationIdToPerform == 3 || operationIdToPerform == 4)
				{
					payloadFieldAsHexString = GetClassEnteringOrExistingOperationInputAsHexString();
				}
				//Client operation choice: "Student eating documention"
				else if (operationIdToPerform == 5) 
				{
					payloadFieldAsHexString = GetEatingDocumentionOperationInputAsHexString();
				}
				//Client operation choice: "Two students chatting documention"
				else if (operationIdToPerform == 6)  
				{
					payloadFieldAsHexString = GetChattingDocumentionOperationInputAsHexString();
				}

				//calculating the size field to send //("xxxx" - 4 characters, 2 bytes)
				int sizeFieldIntegerValue = payloadFieldAsHexString.size() / 2; 

				sizeFieldValueAsHexString = ConverIntToHexWithBytesPadding(sizeFieldIntegerValue);
			}

			//building the packet to send to the server
			string packetToSend = requestNumberHexString + operationCodeFieldAsHexString + 
				                  sizeFieldValueAsHexString + payloadFieldAsHexString;


			//Send the text
			int sendResult = send(sock, packetToSend.c_str(), packetToSend.size() + 1, 0);
			
			if (sendResult != SOCKET_ERROR)
			{
				//Wait for response 
				ZeroMemory(buf, 4096);
				int bytesReceived = recv(sock, buf, 4096, 0);
				if (bytesReceived > 0)
				{
					//Echo response to console
					string serverResponseStr = string(buf, 0, bytesReceived);
					printf("%s\n", serverResponseStr.c_str());
				}
			}
		}

	} while (userInput.size() > 0);

	//Gracefully close down everything
	closesocket(sock);
	WSACleanup();

	return 0;
}

