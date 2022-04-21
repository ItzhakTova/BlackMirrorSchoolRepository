#include "Teacher.h"

Teacher:: Teacher(int id, string name, string cellphone, int classNumber):
	Person(id, name, cellphone)
{
	m_ClassNumber = classNumber;
}

/* Get & Set functions*/

int Teacher::GetTeacherClassNumber()
{
	return m_ClassNumber;
}

void Teacher::SetTeacherNewClassNumber(int teacherNewClassNumber)
{
	m_ClassNumber = teacherNewClassNumber;
}