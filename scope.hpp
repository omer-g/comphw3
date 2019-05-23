#ifndef _SCOPE_H_
#define _SCOPE_H_

#include "common_defs.hpp"
#include "table.hpp"

typedef enum
{
	SCOPE_TYPE_DEFAULT, 
	SCOPE_TYPE_FUNCTION, 
	SCOPE_TYPE_LOOP, 
	SCOPE_TYPE_INVALID 
} scope_type_e;

#define TYPE_CONST_SIZE 1

class Scope
{
public:
	/* Members */
	
	// Pointer to the parent scope (NULL for global scope) 
	Scope* m_parent_p; 
	
	// Symbol Table 
	TypeTable m_table; 
	
	// Current memory offset of THIS scope 
	int m_offset; 
	
	// Functions only - used for counting the offset of function argument by going backwards from 0 
	int m_reverse_offset; 
	
	// Used to define special scope types (i.e. SCOPE_TYPE_FUNCTION)
	scope_type_e m_scope_type; 
	
	
	/* Functions */
	/*
	// Empty constructor, USE FOR GLOBAL SCOPE
	Scope() :
		m_parent_p(NULL),
		m_table(), //TODO init
		m_offset(0), 
		m_reverse_offset(0), 
		m_scope_type(SCOPE_TYPE_DEFAULT)
	{}	
	*/
	
	/* 
		Second constructor, USE FOR SON SCOPE
	*/
	Scope(Scope* parent_p = NULL, scope_type_e scope_type = SCOPE_TYPE_DEFAULT) :
		m_parent_p(parent_p),
		m_table(), //TODO init
		m_offset(0), 
		m_reverse_offset(-TYPE_CONST_SIZE), // This is since the first value should be at -TYPE_CONST_SIZE offset from fp
		m_scope_type(scope_type)
	{	
		/* Update offset to match parent */
		if (m_parent_p)
		{
			m_offset = m_parent_p->m_offset;
		}
	}
	
	//////////////////////////////////////
	///   Functions: CURRENT scope   /////
	//////////////////////////////////////
	
	
	/* 
		Add type to CURRENT symbol table, calculates offset automatically
	*/
	void AddTypeIdentifier (EntryType type, std::string name)
	{
		int offset; 
		if (m_scope_type == SCOPE_TYPE_FUNCTION)
		{
			// Offset is calulated backwards. 
			offset = m_reverse_offset;
			m_reverse_offset -= TYPE_CONST_SIZE;
		}
		else
		{
			offset = m_offset;
			m_offset += TYPE_CONST_SIZE;
		}
		// init
		TableEntry new_entry = TableEntry(type, name, offset);
		
		// Add to table
		m_table.AddEntry (new_entry);
	}
	
	// Add type to CURRENT symbol table
	void AddTypeIdentifier (EntryType type, std::string name, int offset)
	{
		// init
		TableEntry new_entry = TableEntry(type, name, offset);
		
		// Add to table
		m_table.AddEntry (new_entry);
	}
	
	void AddTypeFunction (EntryType type, std::string name, int offset, FuncArgs function_args)
	{
		// init
		TableEntry new_entry = TableEntry(type, name, offset, function_args);
		
		// Add to table
		m_table.AddEntry (new_entry);
	}
	
	/* 
		Find type in symbol table of CURRENT scope
	*/
	TableEntry GetType (std::string name)
	{
		if (m_table.EntryExists(name))
			return m_table.GetEntry(name);
		SEMANTIC_DEBUG_PRINT ("ERROR: Scope::GetType  Entry doesn't exist!");
	}
	
	/* 
		Checks if type exists at CURRENT scope
	*/
	bool TypeExists (std::string name)
	{
		return m_table.EntryExists(name);
	}
	
	////////////////////////////////////////////////
	///   Functions: CURRENT & PARENTS scope   /////
	////////////////////////////////////////////////
	
	/* 
		Find type in symbol table of CURRENT or PARENTS scopes
	*/
	TableEntry GetTypeRecursive (std::string name)
	{
		Scope* current_p = this;
		while (current_p)
		{
			// Search in current scope, if found return
			if (current_p->m_table.EntryExists(name))
				return current_p->m_table.GetEntry(name);
			
			// Advance to parent scope
			current_p = current_p->m_parent_p;
		}
		//TODO return something for invalid
	}
	
	/* 
		Checks if type exists at CURRENT or any PARENTS scopes
	*/
	bool TypeExistsRecursive (std::string name)
	{
		Scope* current_p = this;
		while (current_p)
		{
			// Search in current scope, if found return TRUE
			if (current_p->m_table.EntryExists(name))
				return true;
			
			// Advance to parent scope
			current_p = current_p->m_parent_p;
		}
		return false;
	}
	
};

    
#endif /* _SCOPE_H_ */
