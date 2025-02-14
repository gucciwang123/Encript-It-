/*
iostream
*/
#include <stdexcept>
#include "headers/pch.h"

int encrypt(unsigned char* input, unsigned char*& finalBuf, unsigned long long& finalLength, unsigned long long size, int index, const char* originalName, unsigned char nameLength);
int decrypt(unsigned char* input, unsigned char*& finalBuf, unsigned long long& finalLength, unsigned long long size, int index, char*& outputName, unsigned char& nameLength);

int PE_setup(unsigned char* inputBuf, unsigned long long inputLength, unsigned char mode, unsigned char*& outputBuf, unsigned long long& outputLength, const char* name, unsigned char nameLength, char*& outputName, unsigned char& lengthOfName)
{
	std::string s_index;
	int index = 0; //the number that the file will be multiplied by.
	bool back = false;
	unsigned char* finalBuf;
	unsigned long long finalLength;

	//Input Phase
	{
		
	}

	//Converting phase
	{

	}

	//Computing
	switch (mode)
	{
	case 0:
		if ((encrypt(inputBuf, finalBuf, finalLength, inputLength, index, name, nameLength)) == -1)
			return -1;
		outputName = nullptr;
		break;
	case 1:
		char* interName;
		if ((decrypt(inputBuf, finalBuf, finalLength, inputLength, index, interName, nameLength)) == -1)
			return -1;
		outputName = interName;
		break;
	default:
		return -1;
	}
	outputBuf = finalBuf;
	outputLength = finalLength;
	lengthOfName = nameLength;
	return 0;
}

int decrypt(unsigned char* input, unsigned char*& finalBuf, unsigned long long& finalLength, unsigned long long size, int index, char*& outputName, unsigned char& nameLength)
{
	unsigned char* interFileBuf;
	unsigned char* output = new unsigned char[size];
	int dummy;
	unsigned char* name;


	//decryption start

	//decryption end

	nameLength = output[0];
	console(output[0]);
	name = new unsigned char[nameLength];
	interFileBuf = new unsigned char[size - output[0] - 1];
	for (int a = 0; a < output[0]; a++)
		name[a] = output[a + 1];
	std::string s_name(reinterpret_cast<char*>(name), nameLength);
	for (int a = 0; a < size - output[0] - 1; a++)
		interFileBuf[a] = output[a + output[0] + 1];
	outputName = new char[nameLength];
	const char* cs_name = s_name.c_str();
	for (int a = 0; a < nameLength; a++)
		outputName[a] = cs_name[a];
	finalBuf = interFileBuf;
	finalLength = size - nameLength - 1;
	return 0;
}

int encrypt(unsigned char* input, unsigned char*& finalBuf, unsigned long long& finalLength, unsigned long long size, int index, const char* originalName, unsigned char nameLength)
{
	unsigned char* output = new unsigned char[size + nameLength + sizeof(unsigned int)];
	unsigned char* preProccesedBuf = new unsigned char[size + nameLength + 1];
	int dummy;
	console(size + (unsigned int)nameLength + 1);
	console((unsigned int)nameLength);
	//File Concatenation
	preProccesedBuf[0] = nameLength;
	for (int a = 0; a < nameLength; a++)
		preProccesedBuf[a + 1] = originalName[a];
	for (int a = 0; a < size; a++)
		preProccesedBuf[a + nameLength + 1] = input[a];

	//encryption starts

	//encryption ends

	finalBuf = output;
	finalLength = size + nameLength + 1;
	return 0;
}