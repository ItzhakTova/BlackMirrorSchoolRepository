#pragma once

#ifndef SCHOOL_H
#define SCHOOL_H

#include <vector>
#include <unordered_map>
#include "../Student/Student.h"
#include "../Teacher/Teacher.h"
#include "../LearningClass/LearningClass.h"

class School
{
	public:

		School();
		virtual ~School() {};

		string AddNewStudent(string name, string cellPhone, int age);
		string AddNewTeacher(string name, string cellPhone, int classNumber);
		string EnterStudentToClass(int studentId, int classNumber);
		string ExitStudentFromClass(int studentId, int classNumber);
		string StudentEat(int studentId);
		string StudentsChat(int student1Id, int student2Id);

		string GetStudents();
		string GetTeachers();
		string GetStudentsWhoAteInTheLast60MinutesList();
		string GetClassesPresenceList();

	private:

		vector <LearningClass> m_LearningClassesVector;
		//students map: key - student id, value - student object
		unordered_map<int, Student> m_StudentsMap; 
		//teachers map: key - teacher id, value - teacher object
		unordered_map<int, Teacher> m_TeachersMap; 

		//Consts
		const unsigned int MAX_CLASSES_NUM_IN_SCHOOL;
};
#endif