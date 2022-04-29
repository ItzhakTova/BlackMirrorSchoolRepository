#include "Person.h"

/*************************************************************************
* Function Description:
* Class constructor
*************************************************************************/
Person::Person(int id, string name, string cellphone)
{
	/* members initalization */

	m_ID = id;
	m_Name = name;
	m_CellPhone = cellphone;
}

/*************************************************************************
* Function Description:
* Returning person ID
*************************************************************************/
int Person::GetId()
{
	return m_ID;
}

/*************************************************************************
* Function Description:
* Returning person name
*************************************************************************/
string Person::GetName()
{
	return m_Name;
}

/*************************************************************************
* Function Description:
* Returning person cell phone
*************************************************************************/
string Person::GetCellphone()
{
	return m_CellPhone;
}

/*************************************************************************
* Function Description:
* Setting person ID
*************************************************************************/
void Person::SetId(int newId)
{
	m_ID = newId;
}

/*************************************************************************
* Function Description:
* Setting person name
*************************************************************************/
void Person::SetName(string newName)
{
	m_Name = newName;
}


/*************************************************************************
* Function Description:
* Setting person cell phone
*************************************************************************/
void Person::SetCellphone(string newCellphoneNumber)
{
	m_CellPhone = newCellphoneNumber;
}