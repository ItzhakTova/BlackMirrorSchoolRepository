#include "Teacher.h"

/*************************************************************************
* Function Description:
* Class constructor
*************************************************************************/
Teacher:: Teacher(int id, string name, string cellphone, int classNumber):
	Person(id, name, cellphone)
{
	m_ClassNumber = classNumber;
}

/*************************************************************************
* Function Description:
* Returning teacher class number
*************************************************************************/
int Teacher::GetTeacherClassNumber()
{
	return m_ClassNumber;
}

/*************************************************************************
* Function Description:
* Setting teacher class number
*************************************************************************/
void Teacher::SetTeacherNewClassNumber(int teacherNewClassNumber)
{
	m_ClassNumber = teacherNewClassNumber;
}