#include "School.h"

//Constructor
School:: School(): MAX_CLASSES_NUM_IN_SCHOOL(8)
{
	for (int i = 0; i < MAX_CLASSES_NUM_IN_SCHOOL; ++i)
	{
		m_LearningClassesVector.push_back(LearningClass(i));
	}
}


string School:: AddNewTeacher(string name, string cellPhone, int classNumber)
{
	string result = "";
	
	int currentAmountOfTeacherInSchool = m_TeachersMap.size();
	
	/* Input validation */

	if (classNumber < 0 || classNumber >= MAX_CLASSES_NUM_IN_SCHOOL)
	{
		result = "-1 Error: Class number input is not valid\n";
	}		
	
	else if (m_LearningClassesVector[classNumber].GetClassTeacherId() != -1)
	{
		result = "-1 Error: Class number input is not valid. There is already another techer in this class.\n";
	}	
	
	else if (currentAmountOfTeacherInSchool >= MAX_CLASSES_NUM_IN_SCHOOL)
	{
		result = "-1 Error: New teacher cannot be added since amount of teachers reached the maximum.\n";
	}
	else
	{
		/* Adding the new teacher */
		int newTeacherId = currentAmountOfTeacherInSchool + 1;		

		m_TeachersMap.insert({ newTeacherId , Teacher(newTeacherId, name, cellPhone, classNumber) });

		m_LearningClassesVector[classNumber].SetClassTeacherId(newTeacherId);

		result = to_string(newTeacherId) + "\n";
	}

	return result;
}

string School:: AddNewStudent(string name, string cellPhone, int age)
{
	string result = "";
	
	int newStudentId = MAX_CLASSES_NUM_IN_SCHOOL + m_StudentsMap.size() + 1;  //so teacherId 1-8 and student from 9 and above

	m_StudentsMap.insert({ newStudentId , Student(newStudentId, name, cellPhone, age) });

	result = to_string(newStudentId) + "\n";

	return result;
}

string School:: EnterStudentToClass(int studentId, int classNumber)
{
	string result = "";
	
	int studentCurrentClassNumber = m_StudentsMap.at(studentId).GetStudentClassNumber();
	
	/* Input validation */

	if (classNumber < 0 || classNumber >= MAX_CLASSES_NUM_IN_SCHOOL)
	{
		result = "-1 Error: Class number input is not valid\n";
	}
	else if (m_StudentsMap.size() > 0 && m_StudentsMap.find(studentId) == m_StudentsMap.end())
	{
		result = "-1 Error: Student Id was not found in the system. Please check your input\n";
	}
	else if (studentCurrentClassNumber != -1)
	{
		result = "-1 Error: The Student is already in class number: %d. "
			+ to_string(studentCurrentClassNumber) + 
			"He can enter a new class only after exiting from current class\n";
	}
	else
	{
		/* Commiting the desired actions to enter the student to the class */
		if (m_LearningClassesVector[classNumber].AddStudentToClass((m_StudentsMap.at(studentId))))
		{
			result = "OK\n";
		}
		else
		{
			result = "-1 Error: Student can not enter the class since it is full \n";
		}		
	}

	return result;
}

string School:: ExitStudentFromClass(int studentId, int classNumber)
{
	string result = "";

	/* Input validation */

	if (classNumber < 0 || classNumber >= MAX_CLASSES_NUM_IN_SCHOOL)
	{
		result = "-1 Error: Class number input is not valid\n";
	}
	else if (m_StudentsMap.size() > 0 && m_StudentsMap.find(studentId) == m_StudentsMap.end())
	{
		result = "-1 Error: Student Id was not found in the system. Please check your input\n";
	}	
	else
	{
		/* Commiting the desired actions to exit the student from the class */
		if (m_LearningClassesVector[classNumber].ExitStudentFromClass(studentId))
		{
			result = "OK\n";
		}
		else
		{
			result = "-1 Error: The Student is not in the given class. Please check your input\n";
		}		
	}

	return result;
}

string School:: StudentEat(int studentId)
{
	string result = "";
	
	/* Input validation */

	if (m_StudentsMap.size() > 0 && m_StudentsMap.find(studentId) == m_StudentsMap.end())
	{
		result = "-1 Error: Student Id was not found in the system. Please check your input\n";
	}
	else
	{
		/* Commiting the desired actions when a student eat */
		m_StudentsMap.at(studentId).SetStudentEatingTimeToNow();
		result = "OK\n";
	}

	return result;
}

string School:: StudentsChat(int student1Id, int student2Id)
{
	string result = "";
	
	/* Input validation */
	if (m_StudentsMap.size() > 0 && m_StudentsMap.find(student1Id) == m_StudentsMap.end())
	{
		result = "-1 Error: Student 1 Id was not found in the system. Please check your input\n";
	}
	else if (m_StudentsMap.size() > 0 && m_StudentsMap.find(student2Id) == m_StudentsMap.end())
	{
		result = "-1 Error: Student 2 Id was not found in the system. Please check your input\n";
	}
	else
	{
		/* Commiting the desired actions when students chat */

		m_StudentsMap.at(student1Id).SetBoolValueIsStudentChatting(true);
		m_StudentsMap.at(student2Id).SetBoolValueIsStudentChatting(true);
		result = "OK\n";
	}
	
	return result;
}

//Getting the list of all the school students
string School:: GetStudents()
{	
	string studentsDetailsStr = " ";
	int studentsAmount = m_StudentsMap.size();

	if (studentsAmount == 0)
	{
		studentsDetailsStr = "\nThere are not any students in the school.\n";
	}
	else
	{
		studentsDetailsStr = "\nStudents List:\n";
		
		for (auto& it : m_StudentsMap)
		{
			studentsDetailsStr += "Student Id: " + to_string(it.second.GetId()) +
				", Student Name: " + it.second.GetName() + ", Student Age: " +
				to_string(it.second.GetStudentAge()) + "\n";
		}		
	}

	return studentsDetailsStr;
}

//Getting the list of all the school teachers
string School:: GetTeachers()
{	
	string teachersDetailsStr = " ";
	int teachersAmount = m_TeachersMap.size();

	if (teachersAmount == 0)
	{
		teachersDetailsStr = "\nThere are not any teachers in the school.\n";
	}
	else
	{
		teachersDetailsStr = "\nTeachers List:\n";

		for (auto& it : m_TeachersMap)
		{
			teachersDetailsStr += "Teacher Id: " + to_string(it.second.GetId()) +
				", Teacher Name: " + it.second.GetName() + ", Teacher Class Number: " +
				to_string(it.second.GetTeacherClassNumber()) + "\n";
		}
	}

	return teachersDetailsStr;
}

//Getting the list of student who ate in the last 60 minutes
string School:: GetStudentsWhoAteInTheLast60MinutesList()
{	
	bool thereAreNotAnyStudentsWhoAte = true;
	string studentsDetailsStr = " ";
	int studentsAmount = m_StudentsMap.size();

	if (studentsAmount == 0)
	{
		studentsDetailsStr = "\nThere are not any students in the school.\n";
	}
	else
	{
		studentsDetailsStr = "\nStudents Who Ate In The Last 60 Minutes:\n";

		for (auto& it : m_StudentsMap)
		{
			if (it.second.HasStudentAteInTheLast60Minutes())
			{
				studentsDetailsStr += "Student Id: " + to_string(it.second.GetId()) +
					", Student Name: " + it.second.GetName() + "\n";

				thereAreNotAnyStudentsWhoAte = false;
			}
		}

		if (thereAreNotAnyStudentsWhoAte)
		{
			studentsDetailsStr += "None\n";
		}
	}

	return studentsDetailsStr;
}

//printing each class presence list
string School:: GetClassesPresenceList()
{	
	string presenceListStr = "\nPresence List:\n";

	for (int i = 0; i < MAX_CLASSES_NUM_IN_SCHOOL; ++i)
	{
		presenceListStr += m_LearningClassesVector[i].GetClassPresenceList();
	}

	return presenceListStr;
}