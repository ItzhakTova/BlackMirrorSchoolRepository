#include "Student.h"
#include <chrono>

Student:: Student(int id, string name, string cellphone, int age):
	Person(id, name, cellphone)
{
	m_StudentAge = age;

	m_IsStudentChatting = false;	

	m_StudentCurrentClassNumber = -1;

	m_StudentEatingTime = 0;
	m_StudentEntranceTimeToClass = 0;
	m_StudentExitTimeFromClass = 0;
}
/* Get & Set functions*/
int Student:: GetStudentAge()
{
	return m_StudentAge;
}

int Student:: GetStudentClassNumber()
{
	return m_StudentCurrentClassNumber;
}

void Student:: SetStudentClassNumber(int newClassNumber)
{
	m_StudentCurrentClassNumber = newClassNumber;
}

time_t Student:: GetStudentEatingTime()
{
	return m_StudentEatingTime;
}

time_t Student::GetStudentEntranceTimeToClass()
{
	return m_StudentEntranceTimeToClass;
}

bool Student:: GetBoolValueIsStudentChatting()
{
	return m_IsStudentChatting;
}

void Student:: SetStudentAge(int age)
{
	m_StudentAge = age;
}

void Student:: SetStudentEatingTimeToNow()
{
	m_StudentEatingTime = chrono::system_clock::to_time_t(chrono::system_clock::now());
}

void Student:: SetStudentEntranceTimeToClassToNow()
{
	m_StudentEntranceTimeToClass = chrono::system_clock::to_time_t(chrono::system_clock::now());
}

void Student:: SetStudentExitTimeFromClassToNow()
{
	m_StudentExitTimeFromClass = chrono::system_clock::to_time_t(chrono::system_clock::now());
}

void Student:: SetBoolValueIsStudentChatting(bool isStudentChatting)
{
	m_IsStudentChatting = isStudentChatting;
}

//function responsability to check if student ate in the last 60 minutes
bool Student:: HasStudentAteInTheLast60Minutes()
{
	time_t currentTime = chrono::system_clock::to_time_t(chrono::system_clock::now());	

	//calculating the time differences
	double diffTimeInSeconds = difftime(currentTime, m_StudentEatingTime);

	return (diffTimeInSeconds <= 3600);
}

//function responsability to update student details after entring a class
void Student:: EnterClass(int classNumber)
{	
	SetStudentEntranceTimeToClassToNow();

	SetStudentClassNumber(classNumber);
}

//function responsability to update student details after exiting a class
void Student:: ExitClass()
{	
	SetStudentExitTimeFromClassToNow();

	SetStudentClassNumber(-1);
}