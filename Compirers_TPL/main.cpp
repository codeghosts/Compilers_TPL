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
	printf("输入要编译的源文件\n");
	scanf_s("%s", &filename,20);
	strcpy_s(file.filename, filename);
    int i = fopen_s(&fp,filename, "r");
	while (i != 0)
	{
		printf("文件不存在，请重新输入\n");
		scanf_s("%s", &filename,20);
		strcpy_s(file.filename, filename);
		i = fopen_s(&fp,filename, "r");
	}
	token.pos = file;
	if (fgets(Program_Len, 100, fp) == NULL)
	{
		printf("该文件为空\n");
	}
	row++;
	token.pos.line_number = row;
	token.pos.col_number = 0;

	next_availble_char();
	Print_Lexical();
}