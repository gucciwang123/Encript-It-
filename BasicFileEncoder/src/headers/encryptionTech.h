#pragma once

int SC_setup(unsigned char* inputBuf,
	unsigned long long inputLength,
	unsigned char mode,
	unsigned char*& outputBuf,
	unsigned long long& outputLength,
	const char* name,
	unsigned char nameLength,
	const char*& outputName,
	unsigned char& lengthOfName);
//name is original name, outputName is the name taken from the file


int PE_setup(unsigned char* inputBuf,
	unsigned long long inputLength,
	unsigned char mode,
	unsigned char*& outputBuf,
	unsigned long long& outputLength,
	const char* name,
	unsigned char nameLength,
	const char*& outputName,
	unsigned char& lengthOfName);