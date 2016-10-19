#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
//using namespace std;
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

void skipLine(std::ifstream &f1)
{
	while(f1.get() != '\n');
}

void getLine(std::ifstream &f1,char str[])
{
	int i = 0;
	char c;
	while(!isNewLine(c = f1.get()))
		str[i++] = c;
	str[i] = '\n';
}
void putLine(std::ofstream &f2,char str[])
{
	int i = 0;
	while(!isNewLine(str[i]))
		f2.put(str[i++]);
	f2.put('\n');
}
void skipComma(std::ifstream &f1)
{
	while(!isComma(f1.get()));
}
std::string** dynamic2DString(int row,int column)
{
	std::string** array = new std::string*[row];
	int i;
	for(i = 0;i < column;i++)
		array[i] = new std::string[column];
	return array;
}