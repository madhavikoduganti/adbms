%{
	#include<stdio.h>
	#include "y.tab.h"
	#include<stdlib.h>	
%}
datatype		(?i:integer)|(?i:varchar)|(?i:float)|(?i:timestamp)|(?i:date)|(?i:boolean)

timestamp	[0-9]{1,4}\-[0-9]{1,2}\-[0-9]{1,2},[0-9]{1,2}:[0-9][0-9]:[0-9][0-9]
date		[0-9]{1,4}\-[0-9]{1,2}\-[0-9]{1,2}



create		(?i:create)
table		(?i:table)
database		(?i:database)
user			(?i:user)
grant 		(?i:grant)
all			(?i:all)
privileges	(?i:privileges)
on			(?i:on)
to			(?i:to)
identified		(?i:identified)
by			(?i:by)
insert		(?i:insert)
into			(?i:into)
values		(?i:values)
clear		(?i:clear)
address		\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}


string		[a-zA-Z]+[0-9_]*[a-zA-z]*
quote		[\' \"]

space		[\n \t]+
number 		[0-9]+
plus 		\+
pdt			\*
minus		\-

%%
{space}			;

{create}			{return CREATE;}
{table}			{return TABLE;}
{database}		{return DATABASE;}
{user}			{return USER;}
{grant}			{return GRANT;}
{all}			{return ALL;}
{privileges}		{return PRIVILEGES;}
{on}			{return ON;}
{to}			{return TO;}
{identified}		{return IDENTIFIED;}
{by}			{return BY;}
{insert}			{return INSERT;}
{into}			{return INTO;}
{values}			{return VALUES;}
{clear}			{return CLEAR;}

 	
{datatype}		{yylval.ch=strdup(yytext);return DATATYPE;}
{string}			{yylval.ch=strdup(yytext);return STRING;}
{address}		{yylval.ch=strdup(yytext);return ADDRESS;}

{timestamp}		{return TIMESTAMP;}
{date}			{return DATE;}
[(),@\.]			return *yytext;
;				return DELIM;
{quote}			return QUOTE;

%%

