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