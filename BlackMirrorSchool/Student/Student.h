#pragma once

#ifndef STUDENT_H
#define STUDENT_H

#include "../Person/Person.h"
#include <ctime>

class Student : public Person
{
	public:
		
		Student(int id, string name, string cellphone, int age);
		virtual ~Student() {};

		bool HasStudentAteInTheLast60Minutes();
		void EnterClass(int classNumber);
		void ExitClass();
		
		int GetStudentAge();
		int GetStudentClassNumber();
		bool GetBoolValueIsStudentChatting();
		time_t GetStudentEntranceTimeToClass();
		time_t GetStudentEatingTime();

		void SetStudentClassNumber(int newClassNumber);

		void SetStudentEatingTimeToNow();
		
		void SetBoolValueIsStudentChatting(bool isStudentChatting);
		
		void SetStudentAge(int age);		
		
		void SetStudentEntranceTimeToClassToNow();

		void SetStudentExitTimeFromClassToNow();
		

	private:

		int m_StudentAge;
		bool m_IsStudentChatting;
		time_t m_StudentEatingTime;
		time_t m_StudentEntranceTimeToClass;
		time_t m_StudentExitTimeFromClass;		
		int m_StudentCurrentClassNumber;
};
#endif