#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
bool isComma(char c)
{
	if(c == ',')
		return true;
	else
		return false;
}

bool isNewLine(char c)
{
	if(c == '\n')
		return true;
	else
		return false;
}

void endString(char str[],int index)
{
	str[index] = '\0';
}

void truncate(int &x)
{
	x = 0;
}

void skipLine(ifstream &f1)
{
	while(f1.get() != '\n');
}

void getLine(ifstream &f1,char str[])
{
	int i = 0;
	char c;
	while((c = f1.get()) != '\n')
		str[i++] = c;
	str[i] = '\n';
}
string** dynamic2DString(int row,int column)
{
	string** array = new string*[row];
	int i;
	for(i = 0;i < column;i++)
		array[i] = new string[column];
	return array;
}