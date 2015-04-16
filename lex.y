%{
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <unistd.h>
     #include <dirent.h>
	#include "decls.h"
	#include "func.h"
	void yyerror(char *);
	extern int yylineno;
%}
%union{
struct node * nd;
int n;
char c;
char * ch;
struct StringList * sl;
}
%token  UMINUS CREATE TABLE DATABASE USER DATE TIMESTAMP STRING DELIM GRANT ALL PRIVILEGES ON TO IDENTIFIED BY ADDRESS QUOTE DATATYPE INSERT INTO VALUES CLEAR USE
%left PLUS
%left PDT
%nonassoc  CREATE TABLE SELECT FROM WHERE DATABASE USER DATE TIMESTAMP STRING DELIM GRANT ALL PRIVILEGES ON TO IDENTIFIED BY QUOTE DATATYPE INSERT INTO VALUES CLEAR USE
%type <n> E 
%type <ch> STRING ADDRESS QSTRING TIMESTAMP DATATYPE
%type <sl> TABLEATTRIBUTES
%%


start: 	E  DELIM								{return 0;}
		;
E: 		CREATE DATABASE	STRING DELIM E		{createDb($3);}
		| CREATETABLE DELIM E 				{;}		
		| CREATEUSER DELIM E					{;}
		| GRANTON DELIM E					{;}
		| DATATYPE DELIM						{printf("you have entered:%s\n",$1);}
		| INSERTINTO 	DELIM E					{;}
		| CLEAR DATABASE DELIM				{;}
		| USE DATABASE STRING DELIM			{useDb($3);}
		|									{;}
		;
	
CREATETABLE:	CREATE TABLE STRING'.'STRING '(' TABLEATTRIBUTES ')' 	{printf("%s.%s-created\n",$3,$5);}
				| CREATE TABLE STRING '(' TABLEATTRIBUTES ')'			{createTable(NULL,$3, $5);}
		;

TABLEATTRIBUTES	:	STRING DATATYPE ',' TABLEATTRIBUTES	{temp = makeStringNode($1, $2); makeStringList(temp, $4); $$=temp;}
					| STRING DATATYPE					{$$ = makeStringNode($1, $2); }
					;


CREATEUSER:	CREATE USER QSTRING '@' QSTRING IDENTIFIED BY QSTRING					{;}
			| CREATE USER QSTRING '@' QSTRING										{;}
			
			| TIMESTAMP															{;}
			| DATE																{;}
			;
GRANTON:	GRANT ALL PRIVILEGES ON QSTRING '.' QSTRING TO QSTRING '@' QSTRING		{;}
			;
INSERTINTO:	INSERT INTO STRING  COLUMNS VALUES '(' TUPLE ')'							{;}
			;
QSTRING:	QUOTE STRING QUOTE													{$$=$2;}			
			;
COLUMNS:	'(' COLUMNNAMES ')' 													{;}
			|																	{;}
			;			
COLUMNNAMES:	STRING ',' COLUMNNAMES											{;}
				| STRING															{;}
				;
TUPLE:		QSTRING ',' TUPLE														{;}
			| QSTRING															{;}
			;
%%
void yyerror(char *s) {
    fprintf(stderr, "line %d: %s\n", yylineno, s);
}
int main(void){
	yyparse();
	return 0;
}
