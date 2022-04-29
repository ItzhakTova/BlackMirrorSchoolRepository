#pragma once

#ifndef PERSON_H
#define PERSON_H

#include<iostream>
using namespace std;

class Person
{
	public:			
		
		Person(int id, string name, string cellphone);
		virtual ~Person() {};

		int GetId();
		string GetName();
		string GetCellphone();

		void SetId(int newId);
		void SetName(string newName);
		void SetCellphone(string newCellphoneNumber);		

	private:

		int m_ID;
		string m_Name;
		string m_CellPhone;
};
#endif