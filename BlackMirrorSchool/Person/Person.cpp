#include "Person.h"


Person::Person(int id, string name, string cellphone)
{
	m_ID = id;
	m_Name = name;
	m_CellPhone = cellphone;
}

/** Get & Set Functions */
int Person::GetId()
{
	return m_ID;
}
string Person::GetName()
{
	return m_Name;
}
string Person::GetCellphone()
{
	return m_CellPhone;
}

void Person::SetId(int newId)
{
	m_ID = newId;
}
void Person::SetName(string newName)
{
	m_Name = newName;
}

void Person::SetCellphone(string newCellphoneNumber)
{
	m_CellPhone = newCellphoneNumber;
}