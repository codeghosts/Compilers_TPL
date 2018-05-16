#include "Lexical_Define.h"

char ch;
int pointer = 0;

//读取下一个字符
void Next_Char()
{
        ch = Program_Len[pointer++];
}
//当下一个字符不是空格也不是换行符或者'\0'就读取它
void next_availble_char()
{
	Next_Char();
	while (is_layout(ch))
	{
		Next_Char();
	}
}

//识别一个完整的整数
void Recognize_Constant()
{
	char digits[10];
	int dsp = 0;
	while (is_digit(ch))
	{
		digits[dsp++] = ch;
		Next_Char();
	}
	digits[dsp] = '\0';  //add the end mark 
	token.No = INTGER;
	strcpy_s(token.seman, digits); 
}

//识别保留字和标识符
void Recognize_IdentifierAndKeyName()
{
	char name[20];
	int dsp = 0;
	name[dsp++] = ch;
	Next_Char();
	while (is_letterORdigit(ch))
	{
		name[dsp++] = ch;
		Next_Char();
	}
	name[dsp] = '\0'; 
	if (!strcmp(name, "begin"))
	{
		token.No = BEGIN;
		strcpy_s(token.seman, name);
	}
	else if (!strcmp(name, "end"))
	{
		token.No = END;
		strcpy_s(token.seman, name);
	}
	else if (!strcmp(name, "if"))
	{
		token.No = IF;
		strcpy_s(token.seman, name);
	}
	else if (!strcmp(name, "then"))
	{
		token.No = THEN;
		strcpy_s(token.seman, name);
	}
	else if (!strcmp(name, "else"))
	{
		token.No = ELSE;
		strcpy_s(token.seman, name);
	}
	else if (!strcmp(name, "while"))
	{
		token.No = WHILE;
		strcpy_s(token.seman, name);
	}
	else if (!strcmp(name, "do"))
	{
		token.No = DO;
		strcpy_s(token.seman, name);
	}
	else if (!strcmp(name, "not"))
	{
		token.No = NOT;
		strcpy_s(token.seman, name);
	}
	else if (!strcmp(name, "and"))
	{
		token.No = AND;
		strcpy_s(token.seman, name);
	}
	else if (!strcmp(name, "or"))
	{
		token.No = OR;
		strcpy_s(token.seman, name);
	}
	else if (!strcmp(name, "true"))
	{
		token.No = TRUE;
		strcpy_s(token.seman, name);
	}
	else if (!strcmp(name, "false"))
	{
		token.No = FALSE;
		strcpy_s(token.seman, name);
	}
	else if (!strcmp(name, "for"))
	{
		token.No = FOR;
		strcpy_s(token.seman, name);
	}
	else if (!strcmp(name, "until"))
	{
		token.No = UNTIL;
		strcpy_s(token.seman, name);
	}
	else if (!strcmp(name, "step"))
	{
		token.No = STEP;
		strcpy_s(token.seman, name);
	}
	else
	{
		token.No = ID;
		strcpy_s(token.seman, name);
	}
}

//错误提示
void Print_Error()
{
	e++;
	printf("有错误的字符\n");
	printf("%d,%s,row = %d,col = %d\n", token.No, token.seman, token.pos.line_number, token.pos.col_number);
}

//在这里系统地识别一个单词
void Recognize_Lexical()
{
	while ((ch) == '\n' || (ch) == ' ') //吸收空格和换行
	{
		Next_Char();
	}
	if (is_digit(ch))
	{
		Recognize_Constant();
	}
	else if (is_letter(ch))
	{
		Recognize_IdentifierAndKeyName();
	}
	else    //define operater
	{
		switch (ch)
		{
		case '+':
			token.No = ADD;
			strcpy_s(token.seman, &ch);
			break;
		case '-':
			token.No = SUB;
			strcpy_s(token.seman, &ch);
			break;
		case '*':
			token.No = MULI;
			strcpy_s(token.seman, &ch);
			break;
		case '/':
			token.No = DIV;
			strcpy_s(token.seman, &ch);
		case '<':
			token.No = LT;
			strcpy_s(token.seman, &ch);
			Next_Char();
			if (ch == '=')
			{
				token.No = LE;
				token.seman[1] = ch;
			}
			else if (ch == '>')
			{
				token.No = UEQUO;
				token.seman[1] = ch;
			}
			else if (is_digit(ch))
			{
				//;
				ch = Program_Len[pointer--];
			}
			else
			{
				Print_Error();
			}
			break;
		case '>':
			strcpy_s(token.seman, &ch);
			Next_Char();
			if (ch == '=')
			{
				token.No = GE;
				token.seman[1] = ch;
			}
			else if (ch == ' ')
			{
				token.No = GT;
				token.seman[1] = ch;
			}
			else if (is_digit(ch))
			{
				ch = Program_Len[pointer--];
			}
			else
			{
				Print_Error();
			}
			break;
		case ':':
			strcpy_s(token.seman, &ch);
			Next_Char();
			if (ch == '=')
			{
				token.No = ASS;
				token.seman[1] = ch;
			}
			else
			{
				Print_Error();
			}
			break;
		case '=':
			token.No = EQUO;
			strcpy_s(token.seman, &ch);
			break;
		case '(':
			token.No = OPEN;
			strcpy_s(token.seman, &ch);
			break;
		case ')':
			token.No = CLOSE;
			strcpy_s(token.seman, &ch);
			break;
		case '\0':
			token.No = FEOF;
			strcpy_s(token.seman, "1 row end");
			memset(Program_Len, 0, sizeof(Program_Len)); //将数组清零以存储下一行读入的字符
			if (fgets(Program_Len, 100, fp) != NULL) //读取下一行字符
			{
				row++;
				token.pos.line_number = row;
				token.pos.col_number = 0;  //字符所在的列号清零，行号加1
				pointer = 0;  
			}
			break;
		case '\n':
			break;
		}
		Next_Char();
	}
	token.pos.col_number++;
}

void Print_Lexical()
{
	Recognize_Lexical();
	if (token.No == BEGIN)
	{
		printf("%s\n", token.seman);
		Recognize_Lexical();
	}
	else
	{
		Recognize_Lexical();
		printf("找不到程序的入口,或许在%s前添加 'begin' \n", token.seman);
	}
	while (token.No != END) //只要未扫描到终结符，继续扫描
	{
	/*	if (token.No == IF)
		{
			printf("保留字：%s\n", token.seman);
		}
		else if (token.No == ELSE)
		{
			printf("保留字：%s\n", token.seman);
		}
		else if (token.No == THEN)
		{
			printf("保留字：%s\n", token.seman);
		}
		else if (token.No == WHILE)
		{
			printf("保留字：%s\n", token.seman);
		}
		else if (token.No == DO)
		{
			printf("保留字：%s\n", token.seman);

		}
		else if (token.No == NOT)
		{
			printf("保留字：%s\n", token.seman);
		}
		else if (token.No == AND)
		{
			printf("保留字：%s\n", token.seman);
		}
		else if (token.No == OR)
		{
			printf("保留字：%s\n", token.seman);
		}
		else if (token.No == TRUE)
		{
			printf("保留字：%s\n", token.seman);
		}
		else if (token.No == FALSE)
		{
			printf("保留字：%s\n", token.seman);
		}
		else if (token.No == FOR)
		{
			printf("保留字：%s\n", token.seman);
		}*/
		if (token.No == ID)
		{
			printf("变量：%s\n", token.seman);
			Recognize_Lexical();
		}
		else if ((token.No == ASS) || (token.No == ADD) || (token.No == SUB) || (token.No == MULI) || (token.No == DIV) || (token.No == EQUO) || (token.No == GT) || (token.No == LT) || (token.No == UEQUO) || (token.No == LE) || (token.No == GE) || (token.No == OPEN) || (token.No == CLOSE))
		{
			printf("操作符：%s\n", token.seman);
			Recognize_Lexical();
		}
		else if (token.No == INTGER)
		{
			printf("整数：%s\n", token.seman);
			Recognize_Lexical();
		}
		else if (token.No == FEOF)
		{
			printf("编译下一行\n");
			Recognize_Lexical();
		}
		else
		{
			printf("保留字：%s\n", token.seman);
			Recognize_Lexical();
		}
	}

}

