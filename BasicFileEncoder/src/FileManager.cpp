/*
iostream
Windows.h
*/
#include "headers/pch.h"

int fileExtract(const char* location, unsigned char*& fileBuffer, unsigned long long& bufferLength)
{
	//variable decoration
	unsigned char* fileContents;
	HANDLE hFile;
	unsigned long long size;
	unsigned long readBytes;
	LARGE_INTEGER L_size;

	hFile = CreateFile(location, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return -1;
	if ((GetFileSizeEx(hFile, &L_size)) == false)
		return -1;
	size = L_size.QuadPart;
	fileContents = new unsigned char[size];
	ReadFile(hFile, fileContents, size, &readBytes, NULL);
	fileBuffer = fileContents;
	bufferLength = size;
	if (CloseHandle(hFile) == FALSE)
	{
		std::cout << "Your file failed to close." << std::endl;
		return 1;
	}
	return 0;
}

int fileWritter(const char* name, unsigned char* fileBuffer, unsigned long long bufferLength)
{
	//variable decoration
	HANDLE hFile;
	unsigned long writeBytes;

	hFile = CreateFile(name, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return -1;
	WriteFile(hFile, fileBuffer, bufferLength, &writeBytes, NULL);
	if (CloseHandle(hFile) == FALSE)
	{
		std::cout << "Your output file failed to close." << std::endl;
		return 1;
	}
	return 0;
}