#pragma once

#include <GLFW/glfw3.h>
#include <iostream>
#include "CommonTypes.h"

#define MSG_FILE_ERROR(FileError) MsgFileError(__FILE__, __LINE__, FileError);


bool ReadFile(std::string fileName, std::string &outFile);

void MsgFileError(std::string fileName, uint line, std::string fileError);