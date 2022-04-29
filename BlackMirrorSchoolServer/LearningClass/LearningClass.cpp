#include "LearningClass.h"

/*************************************************************************
* Function Description:
* Class constructor
*************************************************************************/
LearningClass:: LearningClass(int classNumber) : MAX_STUDENTS_NUM_IN_CLASS(5)
{
	//members initalziation
	m_ClassNumber = classNumber;

	m_TeacherId = -1;
}

/*************************************************************************
* Function Description:
* returning class number
*************************************************************************/
int LearningClass:: GetClassNumber()
{
	return m_ClassNumber;
}

/*************************************************************************
* Function Description:
* setting class number
*************************************************************************/
void LearningClass:: SetClassNumber(int newClassNumber)
{
	m_ClassNumber = newClassNumber;
}

/*************************************************************************
* Function Description:
* returning class teacher id
*************************************************************************/
int LearningClass:: GetClassTeacherId()
{
	return m_TeacherId;
}

/*************************************************************************
* Function Description:
* setting class teacher id value
*************************************************************************/
void LearningClass:: SetClassTeacherId(int classTeacherId)
{
	m_TeacherId = classTeacherId;
}

/*************************************************************************
* Function Description:
* Adding a new student to the class
*************************************************************************/
bool LearningClass:: AddStudentToClass(Student* newStudent)
{
	bool studentAddedFlag = false;
	
	int currentAmountOfStudentInClass = m_classStudents.size();

	//limits check
	if (currentAmountOfStudentInClass < MAX_STUDENTS_NUM_IN_CLASS)
	{
		newStudent->EnterClass(m_ClassNumber);
		
		m_classStudents.push_back(newStudent);		
		
		studentAddedFlag = true;
	}

	return studentAddedFlag;
}

/*************************************************************************
* Function Description:
* Exiting a student from the class
*************************************************************************/
bool LearningClass:: ExitStudentFromClass(int studentId)
{
	bool studentExitFromClassFlag = false;		

	int currentAmountOfStudentInClass = m_classStudents.size();

	//Searching the student in the students vector
	for (int i = 0; i < currentAmountOfStudentInClass; ++i)
	{
		if (studentId == (m_classStudents[i])->GetId())
		{
			/* The student has been found in the class */

			m_classStudents[i]->ExitClass();

			m_classStudents.erase(m_classStudents.begin() + i);			

			studentExitFromClassFlag = true;

			break;
		}
	}

	return studentExitFromClassFlag;
}

/*************************************************************************
* Function Description:
* returning a string of all the class students 
*************************************************************************/
string LearningClass:: GetClassPresenceList()
{
	string classPresenceDetailsStr = "Class Number: " + 
		                        to_string(m_ClassNumber) + "\n";

	int currentAmountOfStudentInClass = m_classStudents.size();

	if (currentAmountOfStudentInClass == 0)
	{
		classPresenceDetailsStr += "No students in class " + 
			                   to_string(m_ClassNumber) + " at the moment\n";
	}
	else
	{
		classPresenceDetailsStr += "Class Number " +
			                       to_string(m_ClassNumber) + " Students: ";

		//going over the class students
		for (int i = 0; i < currentAmountOfStudentInClass; ++i)
		{
			string studentIdAsString = to_string(m_classStudents[i]->GetId());

			char studentEntranceTimeStr[100];			

			time_t currStudentEntranceTime  = m_classStudents[i]->GetStudentEntranceTimeToClass();			

			ctime_s(studentEntranceTimeStr, sizeof studentEntranceTimeStr, &currStudentEntranceTime);
			

			classPresenceDetailsStr += "Student Id - " + studentIdAsString + ", Entrance Time - " 
				+ studentEntranceTimeStr + ",";
		}

		//removing the last ','
		classPresenceDetailsStr.pop_back();

		classPresenceDetailsStr += "\n";
	}	

	return classPresenceDetailsStr;
}