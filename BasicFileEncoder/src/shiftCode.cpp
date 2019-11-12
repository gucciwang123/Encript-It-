/*
iostream
*/
#include <stdexcept>
#include "headers/pch.h"

int e_shiftCode(unsigned char* input, unsigned char*& finalBuf, unsigned long long& finalLength, unsigned long long size, int index , const char* originalName, unsigned char nameLength);
int d_shiftCode(unsigned char* input, unsigned char*& finalBuf, unsigned long long& finalLength, unsigned long long size, int index, const char*& outputName, unsigned char& nameLength);

int SC_setup(unsigned char* inputBuf, unsigned long long inputLength, unsigned char mode, unsigned char*& outputBuf, unsigned long long& outputLength, const char* name, unsigned char nameLength, const char*& outputName, unsigned char& lengthOfName)
{
	std::string s_index;
	int index = 0; //the number that the file will be multiplied by.
	bool back = false; 
	unsigned char* finalBuf;
	unsigned long long finalLength;
	

	{
	enterIndex:
		std::cout << "Enter a index between -9 and 99" << std::endl;
		do
		{
			std::getline(std::cin, s_index);
			if ((s_index.length() < 3))
				break;
			else
				std::cout << "Must be a number between -9 and 99 enclusive" << std::endl;
		} while (true);
		if (back)
			goto indexConv;
		

	}

	//Converting phase
	{

	indexConv:
		const char* cs_string;
		cs_string = new char[s_index.length()];
		cs_string = s_index.c_str();

		/*
		switches from the 100's digit to the ones digit
		*/

		//first digit switch
		if (s_index.length() == 2)
		{
			switch (s_index[1])
			{
			case '1':
				index = 1;
				break;
			case '2':
				index = 2;
				break;
			case '3':
				index = 3;
				break;
			case '4':
				index = 4;
				break;
			case '5':
				index = 5;
				break;
			case '6':
				index = 6;
				break;
			case '7':
				index = 7;
				break;
			case '8':
				index = 8;
				break;
			case '9':
				index = 9;
				break;
			case '0':
				index = 0;
				break;
			default:
				back = true;
				std::cout << "The index you enter must be a NUMBER. Please retry" << std::endl;
				goto enterIndex;
			}
			switch (s_index[0])
			{
			case '-':
				index *= -1;
				break;
			case '1':
				index += 10;
				break;
			case '2':
				index += 20;
				break;
			case '3':
				index += 30;
				break;
			case '4':
				index += 40;
				break;
			case '5':
				index += 50;
				break;
			case '6':
				index += 60;
				break;
			case '7':
				index += 70;
				break;
			case '8':
				index += 80;
				break;
			case '9':
				index += 90;
				break;
			case '0':
				break;
			default:
				back = true;
				std::cout << "Must enter a NUMBER as index. Please reenter an index." << std::endl;
				goto enterIndex;
			}
		}

		//second digit switch
		if (s_index.length() == 1)
		{
			switch (s_index[0])
			{
			case '-':
				index *= -1;
				break;
			case '1':
				index += 1;
				break;
			case '2':
				index += 2;
				break;
			case '3':
				index += 3;
				break;
			case '4':
				index += 4;
				break;
			case '5':
				index += 5;
				break;
			case '6':
				index += 6;
				break;
			case '7':
				index += 7;
				break;
			case '8':
				index += 8;
				break;
			case '9':
				index += 9;
				break;
			case '0':
				break;
			default:
				back = true;
				std::cout << "Must enter a NUMBER as index. Please reenter an index." << std::endl;
				goto enterIndex;
			}
		}
		//delete cs_string;
		back = false;
	}

	//Computing
	switch (mode)
	{
	case 0:
		if ((e_shiftCode(inputBuf, finalBuf, finalLength, inputLength, index, name, nameLength)) == -1)
			return -1;
		outputName = nullptr;
		break;
	case 1:
		const char* interName;
		if ((d_shiftCode(inputBuf, finalBuf, finalLength, inputLength, index, outputName, nameLength)) == -1)
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

int d_shiftCode(unsigned char* input, unsigned char*& finalBuf, unsigned long long& finalLength, unsigned long long size, int index, const char*& outputName, unsigned char& nameLength)
{
	unsigned char* interFileBuf;
	unsigned char* output = new unsigned char[size];
	int dummy;
	unsigned char* name;
	
	
	for (unsigned long long a = 0; a < size + (unsigned long long)nameLength + 1; a++)
	{
		try
		{
			dummy = (int)input[a] - index;
			if (dummy < 0)
				output[a] = (unsigned char)256 + dummy;
			else if (dummy > 0)
				output[a] = (unsigned char)dummy;
		}
		catch (std::range_error exp)
		{
			std::cout << "An range \"error\"exception has been thrown. Please check your file size and try again" << std::endl;
			return -1;
		}
		catch (...)
		{
			std::cout << "An exception has been thrown. Please restart and try again" << std::endl;
			return -1;
		}
	}
	
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

int e_shiftCode(unsigned char* input, unsigned char*& finalBuf, unsigned long long& finalLength, unsigned long long size, int index, const char* originalName, unsigned char nameLength)
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

	for (unsigned long long a = 0; a < size + (unsigned long long)nameLength + 1; a++)
	{
		try
		{
			dummy = (int)preProccesedBuf[a] + index;
			if (dummy > 256)
				output[a] = (unsigned char)dummy - 256;
			else if (dummy < 256)
				output[a] = (unsigned char)dummy;
		}
		catch (std::range_error exp)
		{
			std::cout << "An range error exception has been thrown. Please check your file size and try again" << std::endl;
			return -1;
		}
		catch (...)
		{
			std::cout << "An exception has been thrown. Please restart and try again" << std::endl;
			return -1;
		}
	}

	finalBuf = output;
	finalLength = size + nameLength + 1;
	return 0;
}