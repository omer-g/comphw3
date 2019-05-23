#ifndef _COMMON_DEFS_H
#define _COMMON_DEFS_H


#include <string>






////////////////////////////////////////////////////////////
/////////            Expression Types           ////////////
////////////////////////////////////////////////////////////

typedef enum
{
	EXPRRESSION_TYPE_INT, 
	EXPRRESSION_TYPE_BYTE, 
	EXPRRESSION_TYPE_STRING, 
	EXPRRESSION_TYPE_BOOL, 
	EXPRRESSION_TYPE_INVALID // For error checks etc.
} ExpressionType;



////////////////////////////////////////////////////////////
/////////        Value type definitions         ////////////
////////////////////////////////////////////////////////////

#define YYSTYPE Node*





#define YYLVAL_DEFAULT_VAL 0
#define YYLVAL_DEFAULT_TYPE int



////////////////////////////////
///////   NON-TERMINALS    /////
////////////////////////////////

typedef struct 
{
    std::string* id_string;

} id_tt_st;   
    
typedef struct 
{
    int val;

} num_tt_st;      

typedef struct 
{

    std::string* string;

} string_tt_st;  

typedef struct 
{
    std::string* comment_string;
} comments_tt_st; 



////////////////////////////
///////   TERMINALS    /////
////////////////////////////

typedef struct 
{

    ExpressionType type; 
// Insert fields here

} program_nt_st;
		
typedef struct 
{

    ExpressionType type; 
    // Insert fields here

} funcs_nt_st;
		
typedef struct 
{

    ExpressionType type; 
    // Insert fields here

} funcdecl_nt_st;
		 

typedef struct 
{

    ExpressionType type; 
    // Insert fields here

} rettype_nt_st;
		 
		 
typedef struct 
{

    ExpressionType type; 
    // Insert fields here

} formals_nt_st;
		 
		 
typedef struct 
{

    ExpressionType type; 
    // Insert fields here

} formalslist_nt_st;

typedef struct 
{

    ExpressionType type; 
    // Insert fields here

} formalsdecl_nt_st;

typedef struct 
{

    ExpressionType type; 
    // Insert fields here

} preconditions_nt_st;

typedef struct 
{

    ExpressionType type; 
    // Insert fields here

} precondition_nt_st;

typedef struct 
{

    ExpressionType type; 
    // Insert fields here

} statements_nt_st;

typedef struct 
{

    ExpressionType type; 
    // Insert fields here

} statement_nt_st;
		 
typedef struct 
{

    ExpressionType type; 
    // Insert fields here

} nonifstatement_nt_st;
		 
typedef struct 
{

    ExpressionType type; 
    // Insert fields here

} binop_nt_st;

typedef struct 
{

    ExpressionType type; 
    // Insert fields here

} relop_nt_st;		 
		 
typedef struct 
{

    ExpressionType type; 
    // Insert fields here

} ifstatement_nt_st;
		 
typedef struct 
{

    ExpressionType type; 
    // Insert fields here

} ifelsestatement_nt_st;
		 	 

typedef struct 
{

    ExpressionType type; 
    // Insert fields here

} call_nt_st;

typedef struct 
{

    ExpressionType type; 
    // Insert fields here

} explist_nt_st;

typedef struct 
{

    ExpressionType type; 
    // Insert fields here

} type_nt_st;

typedef struct 
{

    ExpressionType type; 
    // Insert fields here

} exp_nt_st;

typedef union 
{
	/* Default value */
	YYLVAL_DEFAULT_TYPE default_value;
	
	/* NON-TERMINALS */
	id_tt_st   id_tt;
	num_tt_st   num_tt;
	string_tt_st   string_tt;
	comments_tt_st   comments_tt;

	/* TERMINALS */
	program_nt_st   program_nt;
	funcs_nt_st   funcs_nt;
	funcdecl_nt_st   funcdecl_nt;
	rettype_nt_st   rettype_nt;
	formals_nt_st   formals_nt;
	formalslist_nt_st   formalslist_nt;
	formalsdecl_nt_st   formalsdecl_nt;
	preconditions_nt_st   preconditions_nt;
	precondition_nt_st   precondition_nt;
	statements_nt_st   statements_nt;
	statement_nt_st   statement_nt;
	nonifstatement_nt_st   nonifstatement_nt;
	binop_nt_st   binop_nt;
	relop_nt_st   relop_nt;
	ifstatement_nt_st   ifstatement_nt;
	ifelsestatement_nt_st   ifelsestatement_nt;
	call_nt_st   call_nt;
	explist_nt_st   explist_nt;
	type_nt_st   type_nt;
	exp_nt_st   exp_nt;

} STYPE;


////////////////////////////////////////////////////////////
/////////             Debug macros              ////////////
////////////////////////////////////////////////////////////

/* Debug ENABLE/DISABLE */
#define DBUG_PRINT_FLEX 1
#define DBUG_PRINT_SEMANTIC 1


/* Debug prints macros */
#if (DBUG_PRINT_FLEX == 1)
#define FLEX_DEBUG_PRINT(token_str) do {printf(token_str); printf("\n");} while(0);
#else // DBUG_PRINT_FLEX
#define FLEX_DEBUG_PRINT(token_str)
#endif

#if (DBUG_PRINT_SEMANTIC == 1)
#define SEMANTIC_DEBUG_PRINT(token_str) do {printf(token_str); printf("\n");} while(0);
#else // DBUG_PRINT_SEMANTIC
#define SEMANTIC_DEBUG_PRINT(token_str)
#endif
    
#endif /* _COMMON_DEFS_H */
