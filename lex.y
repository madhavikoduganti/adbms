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
%type <sl> TABLEATTRIBUTES COLUMNS TUPLE COLUMNNAMES
%%


start: 	E  DELIM								{return 0;}
		;
statement: CREATE DATABASE 	STRING 		{createDb($3);}
		| CREATETABLE 				{;}		
		| CREATEUSER  					{;}
		| GRANTON  					{;}
		| DATATYPE 						{printf("you have entered:%s\n",$1);}
		| INSERTINTO  					{;}
		| CLEAR DATABASE 				{;}
		| USE DATABASE STRING 			{useDb($3);}
		|									{;}
		;
E:	E DELIM statement					{;}
	|statement						{;}
	;
CREATETABLE:	CREATE TABLE STRING'.'STRING '(' TABLEATTRIBUTES ')' 	{createTable($3,$5,$7);}
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
INSERTINTO:	INSERT INTO STRING  COLUMNS VALUES '(' TUPLE ')'							{insert($3,$4,$7);}
			;
QSTRING:	QUOTE STRING QUOTE									{$$=$2;}			
			;
COLUMNS:	'(' COLUMNNAMES ')' 									{$$=$2;}
			|													{$$=NULL;}
			;			
COLUMNNAMES:	STRING ',' COLUMNNAMES							{temp = makeStringNode($1, NULL); makeStringList(temp, $3); $$=temp;}
				| STRING											{$$ = makeStringNode($1, NULL);}
				;
TUPLE:		QSTRING ',' TUPLE										{temp = makeStringNode($1, NULL); makeStringList(temp, $3); $$=temp;}
			| QSTRING											{$$ = makeStringNode($1, NULL);}
			;
%%
void yyerror(char *s) {
    fprintf(stderr, "line %d: %s\n", yylineno, s);
}
int main(void){
	int rootFlag=1;
	int len;
	DIR * dirp;
	struct dirent * dp;
	len = strlen("root");
	dirp = opendir("./");
	while ((dp = readdir(dirp)) != NULL){
			if ( !strcmp(dp->d_name,"root")) {
			(void)closedir(dirp);
			rootFlag=0;
			break;
		}
	}
	if(rootFlag){
		int result = mkdir("root", 0777);
	}
	dbInUse[0]='\0';
	yyparse();
	return 0;
}
