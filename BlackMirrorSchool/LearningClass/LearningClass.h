#pragma once

#ifndef CLASS_H
#define CLASS_H

#include <string> 
#include <vector>
#include <iostream>
#include "../Student/Student.h"
#include "../Teacher/Teacher.h"

class LearningClass
{
	public:

		LearningClass(int classNumber);
		virtual ~LearningClass() {};

		string GetClassPresenceList();
		bool AddStudentToClass(Student &newStudent);
		bool ExitStudentFromClass(int studentId);
	

		int GetClassNumber();
		void SetClassNumber(int newClassNumber);

		int GetClassTeacherId();
		void SetClassTeacherId(int classTeacherId);

	private:

		int m_ClassNumber;
		int m_TeacherId;
		vector<Student> m_classStudents;

		//Consts
		const unsigned int MAX_STUDENTS_NUM_IN_CLASS;
};
#endif