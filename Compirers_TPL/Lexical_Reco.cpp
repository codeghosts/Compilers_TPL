#include "Lexical_Define.h"

char ch;
int pointer = 0;

//��ȡ��һ���ַ�
void Next_Char()
{
        ch = Program_Len[pointer++];
}
//����һ���ַ����ǿո�Ҳ���ǻ��з�����'\0'�Ͷ�ȡ��
void next_availble_char()
{
	Next_Char();
	while (is_layout(ch))
	{
		Next_Char();
	}
}

//ʶ��һ������������
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

//ʶ�����ֺͱ�ʶ��
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

//������ʾ
void Print_Error()
{
	e++;
	printf("�д�����ַ�\n");
	printf("%d,%s,row = %d,col = %d\n", token.No, token.seman, token.pos.line_number, token.pos.col_number);
}

//������ϵͳ��ʶ��һ������
void Recognize_Lexical()
{
	while ((ch) == '\n' || (ch) == ' ') //���տո�ͻ���
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
			memset(Program_Len, 0, sizeof(Program_Len)); //�����������Դ洢��һ�ж�����ַ�
			if (fgets(Program_Len, 100, fp) != NULL) //��ȡ��һ���ַ�
			{
				row++;
				token.pos.line_number = row;
				token.pos.col_number = 0;  //�ַ����ڵ��к����㣬�кż�1
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
		printf("�Ҳ�����������,������%sǰ��� 'begin' \n", token.seman);
	}
	while (token.No != END) //ֻҪδɨ�赽�ս��������ɨ��
	{
	/*	if (token.No == IF)
		{
			printf("�����֣�%s\n", token.seman);
		}
		else if (token.No == ELSE)
		{
			printf("�����֣�%s\n", token.seman);
		}
		else if (token.No == THEN)
		{
			printf("�����֣�%s\n", token.seman);
		}
		else if (token.No == WHILE)
		{
			printf("�����֣�%s\n", token.seman);
		}
		else if (token.No == DO)
		{
			printf("�����֣�%s\n", token.seman);

		}
		else if (token.No == NOT)
		{
			printf("�����֣�%s\n", token.seman);
		}
		else if (token.No == AND)
		{
			printf("�����֣�%s\n", token.seman);
		}
		else if (token.No == OR)
		{
			printf("�����֣�%s\n", token.seman);
		}
		else if (token.No == TRUE)
		{
			printf("�����֣�%s\n", token.seman);
		}
		else if (token.No == FALSE)
		{
			printf("�����֣�%s\n", token.seman);
		}
		else if (token.No == FOR)
		{
			printf("�����֣�%s\n", token.seman);
		}*/
		if (token.No == ID)
		{
			printf("������%s\n", token.seman);
			Recognize_Lexical();
		}
		else if ((token.No == ASS) || (token.No == ADD) || (token.No == SUB) || (token.No == MULI) || (token.No == DIV) || (token.No == EQUO) || (token.No == GT) || (token.No == LT) || (token.No == UEQUO) || (token.No == LE) || (token.No == GE) || (token.No == OPEN) || (token.No == CLOSE))
		{
			printf("��������%s\n", token.seman);
			Recognize_Lexical();
		}
		else if (token.No == INTGER)
		{
			printf("������%s\n", token.seman);
			Recognize_Lexical();
		}
		else if (token.No == FEOF)
		{
			printf("������һ��\n");
			Recognize_Lexical();
		}
		else
		{
			printf("�����֣�%s\n", token.seman);
			Recognize_Lexical();
		}
	}

}

