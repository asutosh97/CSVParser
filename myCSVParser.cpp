#include "auxilary_functions.h"
#define READ 1
#define WRITE 2
#define APPEND 4
#define ERROR -1
#define NOT_CALCULATED -2
using namespace std;
class CSVParser
{
private:
	string filehandle;
	int records;
	int mode;
	int noOfAttributes;
public:
	CSVParser(){
		filehandle = NULL;
		noOfAttributes = NOT_CALCULATED;
	}
	CSVParser(string filename,int mode)
	{
		this->filehandle = filename + ".csv";
		this->mode = mode;
		/*everytime check if the mode allows the function to be executed or not
i.e, if user wants to add or delete record, check if mode is write or append, otherwise return false
*/
	}

	int countRecords()
	{
		int noOfRecords = 0;
		ifstream f1(filehandle,ios::in);
		while(!f1.eof())
		{
			if(f1.get() == '\n')
				noOfRecords++;
		}
		f1.close();
		return noOfRecords;
	}
	int countAttributes()
	{
		if(noOfAttributes == NOT_CALCULATED)
		{
			ifstream f1(filehandle,ios::in);
			char c;
			do{
				c = f1.get();
				if(c == ',')
					noOfAttributes++;
			}while(c != '\n');
			noOfAttributes++;
		}
		return noOfAttributes;
	}
	string* parseRecord(string row)
	{
		string* record = new string[countAttributes()];
		char tempString[1000];
		int rowIndex ,recordIndex,tempIndex;
		rowIndex = recordIndex = tempIndex = 0;
		while(!isNewLine(row[rowIndex]))
		{
			if(isComma(row[rowIndex]))
			{
				endString(tempString,tempIndex);
				record[recordIndex++] = tempString;
				truncate(tempIndex);
			}
			else
			{
				tempString[tempIndex++] = row[rowIndex];
			}
			rowIndex++;
		}
		endString(tempString,tempIndex);
		record[recordIndex]=  tempString;
		return record;
	}
};