#include "Lexical_Define.h"


int row = 0;
int e = 0;
FILE *fp;
Token_Type token;
Position file;
char Program_Len[100];


int main()
{
	char filename[20];
	printf("����Ҫ�����Դ�ļ�\n");
	scanf_s("%s", &filename,20);
	strcpy_s(file.filename, filename);
    int i = fopen_s(&fp,filename, "r");
	while (i != 0)
	{
		printf("�ļ������ڣ�����������\n");
		scanf_s("%s", &filename,20);
		strcpy_s(file.filename, filename);
		i = fopen_s(&fp,filename, "r");
	}
	token.pos = file;
	if (fgets(Program_Len, 100, fp) == NULL)
	{
		printf("���ļ�Ϊ��\n");
	}
	row++;
	token.pos.line_number = row;
	token.pos.col_number = 0;

	next_availble_char();
	Print_Lexical();
}