
#include <fstream>
#include <string>
#include <Windows.h>
#include "Common.h"
using namespace std;

bool ReadFile(std::string fileName, std::string &outFile)
{
	ifstream file(fileName);
	bool result = false;
	if (file.is_open())
	{
		string line;
		while (getline(file,line))
		{
			outFile.append(line);
			outFile.append("\n");
		}
		file.close();
		result = true;
	}
	else
	{
		MSG_FILE_ERROR(fileName);
	}
	return result;
}

void MsgFileError(std::string fileName, uint line, std::string fileError)
{
	char msg[1000];
	_snprintf_s(msg, sizeof(msg), "%s:%d: unable to open file `%s`", fileName.c_str(), line, fileError.c_str());
	MessageBoxA(NULL, msg, NULL, 0);
}
