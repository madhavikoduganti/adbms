%{
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
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
}
%token NUM OP PLUS PDT NL UMINUS CREATE TABLE DATABASE USER DATE TIMESTAMP STRING DELIM GRANT ALL PRIVILEGES ON TO IDENTIFIED BY ADDRESS QUOTE DATATYPE
%left PLUS
%left PDT
%nonassoc UMINUS CREATE TABLE SELECT FROM WHERE DATABASE USER DATE TIMESTAMP STRING DELIM GRANT ALL PRIVILEGES ON TO IDENTIFIED BY QUOTE DATATYPE
%type <n> NUM E 
%type <ch> STRING ADDRESS QSTRING TIMESTAMP DATATYPE
%%


start: 	E  DELIM								{return 0;}
		;
E: 		CREATE DATABASE	QSTRING DELIM E		{;}
		| CREATETABLE DELIM E 				{;}		
		| CREATEUSER DELIM E					{;}
		| GRANTON DELIM E					{;}
		| DATATYPE DELIM									{printf("you have entered:%s\n",$1);}
		|									{;}
		;
	
CREATETABLE:	CREATE TABLE STRING '(' TABLEATTRIBUTES ')' 			{printf("%s-created\n",$3);}
		;

TABLEATTRIBUTES	:	STRING DATATYPE ',' TABLEATTRIBUTES	{printf("%s - type %s\n",$1,$2);}
					| STRING DATATYPE					{printf("%s - type %s\n",$1,$2);}
					;


			
CREATEUSER:	CREATE USER QSTRING '@' QSTRING IDENTIFIED BY QSTRING					{;}
			| CREATE USER QSTRING '@' QSTRING										{;}
			| TIMESTAMP															{;}
			| DATE																{;}
			;
GRANTON:	GRANT ALL PRIVILEGES ON QSTRING '.' QSTRING TO QSTRING '@' QSTRING		{;}
			;
QSTRING:	QUOTE STRING QUOTE													{$$=$2;}			
			;

%%
void yyerror(char *s) {
    fprintf(stderr, "line %d: %s\n", yylineno, s);
}
int main(void){
	yyparse();
	return 0;
}
