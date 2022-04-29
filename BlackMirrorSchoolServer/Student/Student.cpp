#include "Student.h"
#include <chrono>

/*************************************************************************
* Function Description:
* Class constructor
*************************************************************************/
Student:: Student(int id, string name, string cellphone, int age):
	Person(id, name, cellphone)
{
	/* members initalization */
	
	m_StudentAge = age;

	m_IsStudentChatting = false;	

	m_StudentCurrentClassNumber = -1;

	m_StudentEatingTime = 0;
	m_StudentEntranceTimeToClass = 0;
	m_StudentExitTimeFromClass = 0;
}

/*************************************************************************
* Function Description:
* Returning student age
*************************************************************************/
int Student:: GetStudentAge()
{
	return m_StudentAge;
}

/*************************************************************************
* Function Description:
* Returning student class number
*************************************************************************/
int Student:: GetStudentClassNumber()
{
	return m_StudentCurrentClassNumber;
}

/*************************************************************************
* Function Description:
* Setting student class number
*************************************************************************/
void Student:: SetStudentClassNumber(int newClassNumber)
{
	m_StudentCurrentClassNumber = newClassNumber;
}

/*************************************************************************
* Function Description:
* Returning student eating time
*************************************************************************/
time_t Student:: GetStudentEatingTime()
{
	return m_StudentEatingTime;
}

/*************************************************************************
* Function Description:
* Returning student enterance to class time
*************************************************************************/
time_t Student::GetStudentEntranceTimeToClass()
{
	return m_StudentEntranceTimeToClass;
}

/*************************************************************************
* Function Description:
* Returning if the student is chatting
*************************************************************************/
bool Student:: GetBoolValueIsStudentChatting()
{
	return m_IsStudentChatting;
}

/*************************************************************************
* Function Description:
* Setting student age
*************************************************************************/
void Student:: SetStudentAge(int age)
{
	m_StudentAge = age;
}

/*************************************************************************
* Function Description:
* Setting student eating time to now
*************************************************************************/
void Student:: SetStudentEatingTimeToNow()
{
	m_StudentEatingTime = chrono::system_clock::to_time_t(chrono::system_clock::now());
}

/*************************************************************************
* Function Description:
* Setting student entracne to class time to now
*************************************************************************/
void Student:: SetStudentEntranceTimeToClassToNow()
{
	m_StudentEntranceTimeToClass = chrono::system_clock::to_time_t(chrono::system_clock::now());
}

/*************************************************************************
* Function Description:
* Setting student exiting from class time to now
*************************************************************************/
void Student:: SetStudentExitTimeFromClassToNow()
{
	m_StudentExitTimeFromClass = chrono::system_clock::to_time_t(chrono::system_clock::now());
}

/*************************************************************************
* Function Description:
* Setting student chatting boolean value
*************************************************************************/
void Student:: SetBoolValueIsStudentChatting(bool isStudentChatting)
{
	m_IsStudentChatting = isStudentChatting;
}

/*************************************************************************
* Function Description:
* returning true if the student ate in the last 60 minutes
* and false otherwise.
*************************************************************************/
bool Student:: HasStudentAteInTheLast60Minutes()
{
	time_t currentTime = chrono::system_clock::to_time_t(chrono::system_clock::now());	

	//calculating the time differences
	double diffTimeInSeconds = difftime(currentTime, m_StudentEatingTime);

	return (diffTimeInSeconds <= 3600);
}

/*************************************************************************
* Function Description:
* Updating the required data when a student enter a class
*************************************************************************/
void Student:: EnterClass(int classNumber)
{	
	SetStudentEntranceTimeToClassToNow();

	SetStudentClassNumber(classNumber);
}

/*************************************************************************
* Function Description:
* Updating the required data when a student exiting a class
*************************************************************************/
void Student:: ExitClass()
{	
	SetStudentExitTimeFromClassToNow();

	SetStudentClassNumber(-1);
}