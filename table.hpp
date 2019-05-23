#ifndef _TABLE_H_
#define _TABLE_H_

#include <string>
#include <list>
#include <cstdio>
#include <stdio.h>
#include "common_defs.hpp"
#include "node.hpp"

// Changed entry type to be the enum from node.hpp
typedef nodes::BasicType EntryType;
typedef std::string EntryName;

///////////////////////////////////////////////////////////////////////////////////
/////////            AUXILIARY CLASSES: TableEntry, FuncArgs           ////////////
///////////////////////////////////////////////////////////////////////////////////


/*
	Added to the TableEntry for functions, used for checking correctness of signatures
*/
class FuncArgs
{
public:
	/* Members */
	std::list<ExpressionType> m_args_list; // A list of all args types of the function, for example int func (int a, char b) will have [int, int]
	
	/* Methods */
	
	/* Check equal */
	bool IsEqual (FuncArgs rhs)
	{
		// Check the sizes match
		if (m_args_list.size() != rhs.m_args_list.size())
			return false;
	
		// Handle empty case
		if (m_args_list.size() == 0)
			return true;
		
		// iterate over both lists, make sure every 2 corresponding types are equal
		std::list<ExpressionType>::iterator lhs_i = m_args_list.begin();
		std::list<ExpressionType>::iterator rhs_i = rhs.m_args_list.begin();
		
		while ((lhs_i != m_args_list.end()) && (rhs_i != rhs.m_args_list.end()))
		{
			// Check not equal
			if (*lhs_i != *rhs_i)
			{
				return false;
			}
			
			// advance iterators
			lhs_i++;
			rhs_i++;
		}
		return true;
	}
	
	
	/* operator+= */
	FuncArgs& operator+= (const ExpressionType arg)
	{
		// Assert a valid type
		if (arg >= EXPRRESSION_TYPE_INVALID)
		{
			SEMANTIC_DEBUG_PRINT("ERROR: FuncArgs::operator+=:  Type invalid!");
			return *this;
		}
		
		// add to end of the list
		m_args_list.push_back(arg);
		
		return *this;
	}
	/* operator= */
	FuncArgs& operator= (const FuncArgs& rhs)
	{
		// Copy args list
		m_args_list = std::list<ExpressionType> (rhs.m_args_list);

		
		
		return *this;
	}
	
};
	static bool operator== (const FuncArgs& lhs, const FuncArgs& rhs)
	{
		FuncArgs c_lhs = lhs;
		FuncArgs c_rhs = rhs;
		return c_lhs.IsEqual(c_rhs);
	}

	//operator!=
	static bool operator!= (const FuncArgs& lhs, const FuncArgs& rhs)
	{
		return !(lhs == rhs);
	}





/*
	Used for representing a single entry to be inserted into the TypeTable
*/
class TableEntry
{
public:
	/* Members */
	
	EntryType m_type;   // TODO set the right type
	EntryName m_name;   // Identifiers name
	int m_offset;       // Memory offset
	FuncArgs m_function_args; // Object representing the arguments of the function. This should be left empty for non-Function. 
	
	/* Methods */
	
	TableEntry (EntryType type, std::string name, int offset)
	{
		m_type = type;
		m_name = name;
		m_offset = offset;
	}	
	
	TableEntry (EntryType type, std::string name, int offset, FuncArgs function_args)
	{
		m_type = type;
		m_name = name;
		m_offset = offset;
		m_function_args = function_args;
	}	
};
	static bool operator == (const TableEntry lhs, const TableEntry rhs)
	{
		return ((rhs.m_type == lhs.m_type) && (rhs.m_name == lhs.m_name) && (rhs.m_offset == lhs.m_offset)
				&& (lhs.m_function_args == rhs.m_function_args) );
	}
	
	
	
	
	
	
	
	
	
	
	
	
///////////////////////////////////////////////////////////////////////////////////
/////////                     MAIN CLASS: TypeTable                    ////////////
///////////////////////////////////////////////////////////////////////////////////

class TypeTable
{
public:
	/* Members */
	std::list<TableEntry> m_type_container;
	
	
	/* Methods */
	
	// Add entry to table
	void AddEntry (TableEntry entry)
	{
		/* Check if type exists */
		if (EntryExists (entry))
		{
			SEMANTIC_DEBUG_PRINT("ERROR: TypeTable::AddEntry type already exists!");
			return;
		}
		
		/* Add to table */
		m_type_container.push_back(entry);
				
	}	
	
	// Get entry in table
	TableEntry GetEntry (TableEntry entry)
	{
		
		for (std::list<TableEntry>::iterator it = m_type_container.begin(); it != m_type_container.end(); it++)
		{
			if (*it == entry)
			{
				return *it;
			}
		}
		SEMANTIC_DEBUG_PRINT("ERROR: TypeTable::GetEntry returned an empty result!");
		//return *it;
	}
	

	// Get entry in table by name
	TableEntry GetEntry (EntryName name)
	{
		for (std::list<TableEntry>::iterator it = m_type_container.begin(); it != m_type_container.end(); it++)
		{
			if ((*it).m_name == name)
			{
				return *it;
			}
		}	
		SEMANTIC_DEBUG_PRINT("ERROR: TypeTable::GetEntry returned an empty result!");
		//return *it;
	}

	
	// Checks if type exists
	bool EntryExists (TableEntry entry)
	{
		for (std::list<TableEntry>::iterator it = m_type_container.begin(); it != m_type_container.end(); it++)
		{
			if (*it == entry)
			{
				return 1;
			}
		}
		return 0;
	}
	
	// Checks if type exists by name
	bool EntryExists (EntryName name)
	{
		for (std::list<TableEntry>::iterator it = m_type_container.begin(); it != m_type_container.end(); it++)
		{
			if ((*it).m_name == name)
			{
			//std::cout << "EQUAL: " << "m_name: " << (*it).m_name << "   name: " << name << std::endl;
				return 1;
			}
			//std::cout << "NOT EQUAL: " << "m_name: " << (*it).m_name << "   name: " << name << std::endl;
		}
		return 0;
	}
	
	// Debug print
	void PrintItems()
	{
		for (std::list<TableEntry>::iterator it = m_type_container.begin(); it != m_type_container.end(); it++)
		{
			std::cout << "Item_name: " << (*it).m_name << "   Item_offset: " << (*it).m_offset << "   Item_type: " << (*it).m_type << std::endl;
		}
	}
	
	
};



    
#endif /* _TABLE_H_ */
