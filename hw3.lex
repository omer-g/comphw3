%{
    #include "common_defs.hpp"
    #include "hw3.tab.hpp"
	//YYSTYPE yylval;
%}


%option noyywrap
%option yylineno



/* Regular expresion macros */
VOID_TOKEN        "void"
INT_TOKEN         "int"
BYTE_TOKEN        "byte"
B_TOKEN           "b"
BOOL_TOKEN        "bool"
AND_TOKEN         "and"
OR_TOKEN          "or"
NOT_TOKEN         "not"
TRUE_TOKEN        "true"
FALSE_TOKEN       "false"
RETURN_TOKEN      "return"
IF_TOKEN          "if"
ELSE_TOKEN        "else"
WHILE_TOKEN       "while"
BREAK_TOKEN       "break"
CONTINUE_TOKEN    "continue"
PRECOND_TOKEN     "@pre"
SC_TOKEN          ;
COMMA_TOKEN       ,
LPAREN_TOKEN      \(
RPAREN_TOKEN      \)
LBRACE_TOKEN      \{
RBRACE_TOKEN      \}
ASSIGN_TOKEN      =

REL_TOKEN         <=|<|>=|>|!=
EQ_TOKEN          ==


MULDIV_TOKEN      \*|\/
PLUSMINUS_TOKEN   \+|\-


ID_TOKEN          [a-zA-Z][a-zA-Z0-9]* 
NUM_TOKEN         0|[1-9][0-9]*
WHITESPACE_TOKEN  [\r\n\t ]+
STRING_TOKEN      "([^\n\r\"\\]|\\[rnt\"\\])+"
COMMENTS_TOKEN    \/\/[^\r\n]*(\r|\n|\r\n)?






%%

{VOID_TOKEN}    {DBUG_PRINT("VOID");  return (VOID); }      
{INT_TOKEN}    { DBUG_PRINT("INT");  return (INT); }       
{BYTE_TOKEN}    { DBUG_PRINT("BYTE"); return (BYTE); }      
{B_TOKEN}    { DBUG_PRINT("B");   return (B); }         
{BOOL_TOKEN}    { DBUG_PRINT("BOOL");   return (BOOL); }      
{AND_TOKEN}    { DBUG_PRINT("AND");    return (AND); }       
{OR_TOKEN}    { DBUG_PRINT("OR");   return (OR); }        
{NOT_TOKEN}    { DBUG_PRINT("NOT");   return (NOT); }       
{TRUE_TOKEN}    { DBUG_PRINT("TRUE");   yylval = new nodes::True();    return (TRUE); }      
{FALSE_TOKEN}    { DBUG_PRINT("FALSE");   yylval = new nodes::False();    return (FALSE); }     
{RETURN_TOKEN}    { DBUG_PRINT("RETURN");  return (RETURN); }    
{IF_TOKEN}    { DBUG_PRINT("IF");   return (IF); }        
{ELSE_TOKEN}    { DBUG_PRINT("ELSE");    return (ELSE); }      
{WHILE_TOKEN}    { DBUG_PRINT("WHILE");    return (WHILE); }     
{BREAK_TOKEN}    { DBUG_PRINT("BREAK");   return (BREAK); }     
{CONTINUE_TOKEN}    { DBUG_PRINT("CONTINUE");    return (CONTINUE); }  
{PRECOND_TOKEN}    { DBUG_PRINT("PRECOND");   return (PRECOND); }   
{SC_TOKEN}    { DBUG_PRINT("SC");    return (SC); }        
{COMMA_TOKEN}    { DBUG_PRINT("COMMA");   return (COMMA); }     
{LPAREN_TOKEN}    { DBUG_PRINT("LPAREN");   return (LPAREN); }    
{RPAREN_TOKEN}    { DBUG_PRINT("RPAREN");   return (RPAREN); }    
{LBRACE_TOKEN}    { DBUG_PRINT("LBRACE");   return (LBRACE); }    
{RBRACE_TOKEN}    { DBUG_PRINT("RBRACE");   return (RBRACE); }    
{ASSIGN_TOKEN}    { DBUG_PRINT("ASSIGN");   return (ASSIGN); }    


{MULDIV_TOKEN}     { DBUG_PRINT("MULDIV");      return (MULDIV); }
{PLUSMINUS_TOKEN}   { DBUG_PRINT("PLUSMINUS");  return (PLUSMINUS); }
{REL_TOKEN}    { DBUG_PRINT("REL_TOKEN");       return (RELOP_REL); }
{EQ_TOKEN}    { DBUG_PRINT("EQ_TOKEN");         return (RELOP_EQ); }

{ID_TOKEN}    { DBUG_PRINT("ID");   yylval = new nodes::IDNode(yytext);    return (ID); }        
{NUM_TOKEN}    { DBUG_PRINT("NUM");   yylval = new nodes::Num(atoi(yytext));    return (NUM); }       
{STRING_TOKEN}    { DBUG_PRINT("STRING");   yylval = new nodes::String(yytext);    return (STRING); }    
{WHITESPACE_TOKEN}    { DBUG_PRINT("WHITESPACE");  }
{COMMENTS_TOKEN}    { DBUG_PRINT("COMMENTS");  }  
.    { DBUG_PRINT("INVALID LEXEME"); output::errorLex(yylineno)); exit(0); }  

%%