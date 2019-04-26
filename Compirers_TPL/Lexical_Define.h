#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>


#define Token_Len 20 
/*
The following content defines macro 
name and number 
*/

#define HEAD 0
#define BEGIN 1
#define END 2
#define IF 3
#define THEN 4
#define ELSE 5
#define WHILE 6
#define DO 7
#define NOT 8
#define AND 9
#define OR 10
#define TRUE 11
#define FALSE 12
#define FOR 13
#define UNTIL 14
#define ADD 15
#define SUB 16
#define MULI 17
#define DIV 18
#define EQUO 19
#define ASS 20
#define GT 21   
#define LT 22
#define UEQUO 23
#define LE 24
#define GE 25
#define OPEN 26
#define CLOSE 27
#define INTGER 28
#define ID 29
#define FEOF 30
#define STEP 31



/*
character recognition
*/

//

#define is_endofinput(ch) ((ch) == '\0')

#define is_lcletter(ch) ('a' <= (ch) && (ch) <= 'z')
#define is_ucletter(ch) ('A' <= (ch) && (ch) <= 'Z')
#define is_letter(ch) (('a' <= (ch) && (ch) <= 'z') || ('A' <= (ch) && (ch) <= 'Z'))
#define is_digit(ch) ('0' <= (ch) && (ch) <= '9')
#define is_letterORdigit(ch) (is_letter(ch) || is_digit(ch))
#define is_operater(ch) ((ch) == '+' || (ch) == '*' || (ch) == '-' || (ch) == '/' || (ch) == '<' (ch) == '>' || (ch) == '=' )
#define is_layout(ch) (!is_endofinput(ch) && (ch) <= ' ' && (ch) != '\n')


typedef struct  position{
	char filename[20];
	int line_number;
	int col_number;
}Position;

typedef struct Token {
	int No;
	char seman[Token_Len]; //semantic of the token
	Position pos;
}Token_Type;

extern char ch;
extern FILE *fp;

extern Token_Type token;
extern int e;
extern int row;
extern char Program_Len[100]; //store  characters  


void Next_Char();
void next_availble_char();
void Recognize_Constant();
void Recognize_IdentifierAndKeyName();
void Print_Error();
void Recognize_Lexical();
void Print_Lexical();
