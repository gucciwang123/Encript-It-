/*
iostream
string
Windows.h
*/
#include "headers\pch.h"
#include <cstring>
#include "headers\FileManager.h"
#include "headers\decoder.h"
#include "headers\encoder.h"

#ifdef BFE_x64
#define bits "x64"
#endif
#ifdef BFE_x86
#define bits "x86"
#endif
int main()
{
	//function variable decloration
	std::string s_index, en_de, fileLoc, fileName;
	int index = 0; //the number that the file will be multiplied by.
	unsigned char mode; //if 0, then encode; if 1, then decode
	const char* cs_string;
	bool back = false;
	unsigned char* finalFileBuf, *interFileBuf; //output file buffer, intermediate file buffer
	unsigned long finalFileLength, interFileLength; //output file buffer length, intermediate file buffer length
	OFSTRUCT fileStruct;

	//startup text
	{	
		std::cout << "Hello World" << std::endl;
		std::cout << "Encode It! "<< bits <<" v1.0" << std::endl;
		std::cout << "Developed by Tyler Wang." << std::endl;
		std::cout << "All rights reserved. This is a free software, reselling is PROHIBITED" << std::endl << std::endl;
	}

	//Input Phase
	{
		std::cout << "Enter file name" << std::endl;
		do
		{
			std::getline(std::cin, fileName);
			fileLoc = "input\\" + fileName;
			if (OpenFile((LPCSTR)fileLoc.c_str(), &fileStruct, OF_EXIST) != HFILE_ERROR)
				break;
			std::cout << "Please enter a valid file name reletive to the input directory" << std::endl;
		} while (true);
		std::cout << "Enter encoding index (between -9 and 99 enclusive)" << std::endl;
	enterIndex:
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
		std::cout << "Enter mode (type \"D\" for decode and \"E\" for encode)" << std::endl;
		do
		{
			std::getline(std::cin, en_de);
			if ((en_de.compare("E") == 0) || (en_de.compare("D") == 0))
				break;
			else
			{
				std::cout << "You must only either type \"E\" or \"D\"" << std::endl;
				std::cout << "Type \"D\" for decode and \"E\" for encode" << std::endl;
			}
		} while (true);
	}

	//Converting phase
	{
		if (en_de.compare("E") == 0)
			mode = 0;
		else if (en_de.compare("D") == 0)
			mode = 1;
	indexConv:
		cs_string = new char[s_index.length() + 1];
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
		//delete[s_index.length() + 1] cs_string;
		back = false;
	}

	//Computing phase (Done in other functions)
	std::string output_t = "output//";
	int dummy = fileExtract(fileLoc.c_str(), interFileBuf, interFileLength);
	if (dummy == -1)
	{
		std::cout << "An error has occured" << std::endl;
		system("pause");
		return -1;
	}
	else if (dummy == 1)
	{
		system("pause");
		return -1;
	}
	switch (mode)
	{
	case 0:
		encoder(interFileBuf, finalFileBuf, interFileLength, index);
		break;
	case 1:
		decoder(interFileBuf, finalFileBuf, interFileLength, index);
		break;
	default:
		std::cout << "The index you have entered has been lost or invalid." << std::endl;
		system("pause");
		return -1;
	}
	fileLoc = output_t + fileName;
	finalFileLength = interFileLength;
	dummy = fileWritter(fileLoc.c_str(), finalFileBuf, finalFileLength);
	if (dummy == 1)
		{
			system("pause");
			return -1;
		}
	else if (dummy == -1)
	{
		std::cout << "An error has occured." << std::endl;
		system("pause");
		return -1;
	}
	std::cout << "100% proccessed. Your new file is in the \"output\" directory which is in the program's directory" << std::endl;
	system("pause");
	return 0;
}