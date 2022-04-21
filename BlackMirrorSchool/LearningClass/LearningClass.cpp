#include "LearningClass.h"

LearningClass:: LearningClass(int classNumber) : MAX_STUDENTS_NUM_IN_CLASS(5)
{
	m_ClassNumber = classNumber;

	m_TeacherId = -1;
}

int LearningClass:: GetClassNumber()
{
	return m_ClassNumber;
}

void LearningClass:: SetClassNumber(int newClassNumber)
{
	m_ClassNumber = newClassNumber;
}

int LearningClass:: GetClassTeacherId()
{
	return m_TeacherId;
}

void LearningClass:: SetClassTeacherId(int classTeacherId)
{
	m_TeacherId = classTeacherId;
}

bool LearningClass:: AddStudentToClass(Student &newStudent)
{
	bool studentAddedFlag = false;
	
	int currentAmountOfStudentInClass = m_classStudents.size();

	if (currentAmountOfStudentInClass < MAX_STUDENTS_NUM_IN_CLASS)
	{
		newStudent.EnterClass(m_ClassNumber);
		
		m_classStudents.push_back(newStudent);		
		
		studentAddedFlag = true;
	}

	return studentAddedFlag;
}

bool LearningClass:: ExitStudentFromClass(int studentId)
{
	bool studentExitFromClassFlag = false;	

	//Searching the student in the students vector

	int currentAmountOfStudentInClass = m_classStudents.size();

	for (int i = 0; i < currentAmountOfStudentInClass; ++i)
	{
		if (studentId == m_classStudents[i].GetId())
		{
			//The student has been found in the class

			m_classStudents[i].ExitClass();

			m_classStudents.erase(m_classStudents.begin() + i);			

			studentExitFromClassFlag = true;

			break;
		}
	}

	return studentExitFromClassFlag;
}

string LearningClass:: GetClassPresenceList()
{
	string classPresenceDetailsStr = "Class Number: " + to_string(m_ClassNumber) + "\n";

	int currentAmountOfStudentInClass = m_classStudents.size();

	if (currentAmountOfStudentInClass == 0)
	{
		classPresenceDetailsStr += "No students in class " + to_string(m_ClassNumber) + " at the moment\n";
	}
	else
	{
		classPresenceDetailsStr += "Class Number " + to_string(m_ClassNumber) + " Students: ";

		for (int i = 0; i < currentAmountOfStudentInClass; ++i)
		{
			string studentIdAsString = to_string(m_classStudents[i].GetId());

			char studentEntranceTimeStr[100];			

			time_t currStudentEntranceTime  = m_classStudents[i].GetStudentEntranceTimeToClass();			

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