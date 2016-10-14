#include "auxiliary_functions.h"
#define READ 1
#define WRITE 2
#define APPEND 4
#define ERROR -1
#define NOT_CALCULATED -2
class CSVParser
{
private:
	string filehandle;
	int records;
	int mode;
	int noOfAttributes;
	int noOfRecords;
public:
	CSVParser(){
	//	filehandle = NULL;
		noOfAttributes = NOT_CALCULATED;
		noOfRecords = NOT_CALCULATED;
	}
	CSVParser(string filename,int mode)
	{
		this->filehandle = filename + ".csv";
		this->mode = mode;
		noOfAttributes = NOT_CALCULATED;
		noOfRecords = NOT_CALCULATED;
		/*everytime check if the mode allows the function to be executed or not
i.e, if user wants to add or delete record, check if mode is write or append, otherwise return false
*/
	}

	int countRecords()
	{
		if(noOfRecords == NOT_CALCULATED)
		{
			noOfRecords = 0;
			ifstream f1(filehandle,ios::in);
			while(!f1.eof())
			{
				if(f1.get() == '\n')
					noOfRecords++;
			}
			noOfRecords--;
			f1.close();
		}
		return noOfRecords;
	}
	int countAttributes()
	{
		if(noOfAttributes == NOT_CALCULATED)
		{
			noOfAttributes = 0;
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
	string** getRecords()
	{
		ifstream f1(filehandle,ios::in);
		string** records = dynamic2DString(countRecords(),countAttributes());
		int recordsIndex = 0;
		skipLine(f1);
		while(!f1.eof())
		{
			if(f1.peek() == EOF)
				break;
			char row[1000];
			getLine(f1,row);
			records[recordsIndex++] = parseRecord(row);
		}
		f1.close();
		return records;
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
	string* getRecord(string recordId)
	{
		ifstream f1(filehandle,ios::in);
		string *record = new string[countAttributes()];
		skipLine(f1);
		bool found = false;
		while(!f1.eof())
		{
			if(f1.peek() == EOF)
				break;
			char row[1000];
			getLine(f1,row);
			record = parseRecord(row);
			if(record[0] == recordId)
			{
				found = true;
				break;
			}
		}
		
		if(found)
			return record;
		else
			return NULL;
	}
	string* getAttributes()
	{
		ifstream f1(filehandle,ios::in);
		string *attributes = new string[countAttributes()];
		char row[1000];
		getLine(f1,row);
		attributes = parseRecord(row);
		return attributes;
	}
	bool deleteRecord(string recordID)
	{
		ifstream f1(filehandle,ios::in);
		ofstream f2("temp.csv",ios::out);
		char row[1000];
		getLine(f1,row);
		putLine(f2,row);
		bool found = false;
		string *record = new string[countAttributes()];
		while(!f1.eof())
		{
			if(f1.peek() == EOF)
				break;
			getLine(f1,row);
			record = parseRecord(row);
			if(record[0] == recordID)
			{
				found = true;
				continue;
			}
			putLine(f2,row);
		}
		f1.close();
		f2.close();
		remove(filehandle.c_str());
		rename("temp.csv",filehandle.c_str());
		return found;
	}
};