#pragma once

#ifndef TEACHER_H
#define TEACHER_H

#include "../Person/Person.h"

class Teacher : public Person
{
	public:		
		
		Teacher(int id, string name, string cellphone, int classNumber);
		virtual ~Teacher() {};

		int GetTeacherClassNumber();
		void SetTeacherNewClassNumber(int teacherNewClassNumber);

	private:

		int m_ClassNumber;
};
#endif