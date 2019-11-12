/*
iostream
string
Windows.h
*/
#include "headers\pch.h"
#include <cstring>
#include "headers\FileManager.h"
#include "headers\encryptionTech.h"
#ifdef BFE_x64
#define bits "x64"
#endif
#ifdef BFE_x86
#define bits "x86"
#endif

int main()
{
	//variable decloration
	unsigned char mode;
	unsigned char method;
	std::string en_de, fileLoc, fileName, s_mode, s_method;
	unsigned char* finalFileBuf, *interFileBuf; //output file buffer, intermediate file buffer
	unsigned long long finalFileLength, interFileLength; //output file buffer length, intermediate file buffer length
	OFSTRUCT fileStruct;
	bool moveOn;
	unsigned char nameLength;
	const char* outputName;

	//startup text
	{
		std::cout << "Hello World" << std::endl;
		std::cout << "Encode It! " << bits << " v1.1" << std::endl;
		std::cout << "Developed by Tyler Wang." << std::endl;
		std::cout << "All rights reserved. This is a free software, reselling is PROHIBITED" << std::endl << std::endl;
	}

	//Input Phase
	std::cout << "Enter encryption methodod (Please enter number next to encryption methodod's name):" << std::endl << std::endl 
		<< "\tShift Code (1)" << std::endl;
	const char* cs_method;
methododCreation:
	do
	{
		std::getline(std::cin, s_method);
		moveOn = false;
		cs_method = s_method.c_str();
		for (int a = 0; a < s_method.length(); a++)
		{
			switch (cs_method[a])
			{
			case '0':
				break;
			case '1':
				break;
			case '2':
				break;
			case '3':
				break;
			case '4':
				break;
			case '5':
				break;
			case '6':
				break;
			case '7':
				break;
			case '8':
				break;
			case '9':
				break;
			default:
				moveOn = true;
				break;
			}
			if (moveOn)
				break;
		}
		if(moveOn)
			std::cout << "Enter a valid methodod ID" << std::endl;
	} while (moveOn);
	int z = 0;
	int y = 0;
	int x;
	method = 0;
	for (int a = s_method.length() - 1; a >= 0; a--)
	{
		y = 1;
		for (int b = 0; z > b; b++)
			y *= 10;
		switch (cs_method[a])
		{
		case '1':
			x = 1;
			break;
		case '2':
			x = 2;
			break;
		case '3':
			x = 3;
			break;
		case '4':
			x = 4;
		case '5':
			x = 5;
			break;
		case '6':
			x = 6;
			break;
		case '7':
			x = 7;
			break;
		case '8':
			x = 8;
			break;
		case '9':
			x = 9;
			break;
		case '0':
			x = 0;
			break;
		default:
			std::cout << "Enter a valid methodod ID" << std::endl;
			goto methododCreation;
		}
		method += x * y;
		z++;
	}
	if (!(method == 1))
	{
		std::cout << "Enter a valid methodod ID" << std::endl;
		goto methododCreation;
	}
	moveOn = true;
	std::cout << "Enter file name" << std::endl;
	do
	{
		std::getline(std::cin, fileName);
		fileLoc = "input\\" + fileName;
		if (OpenFile((LPCSTR)fileLoc.c_str(), &fileStruct, OF_EXIST) != HFILE_ERROR)
			break;
		std::cout << "Please enter a valid file name reletive to the input directory" << std::endl;
	} while (true);
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
	if (en_de.compare("E") == 0)
		mode = (unsigned char)_ENCODE_;
	else if (en_de.compare("D") == 0)
	{
		char* extention = new char[4];
		const char* cs_fileName = fileName.c_str();
		z = 4;
		mode = (unsigned char)_DECODE_;
		for (int a = 0; a < fileName.length(); a++)
		{
			extention[a] = cs_fileName[fileName.length() - z];
			z--;
		}
		if (!(extention[0] == '.'))
		{
			std::cout << "Your file format does not support the decoding of files. Please restart the program and try again." << std::endl;
			system("pause");
			return -1;
		}
		else if (!(extention[1] == 'b'))
		{
			std::cout << "Your file format does not support the decoding of files. Please restart the program and try again." << std::endl;
			system("pause");
			return -1;
		}
		else if (!(extention[2] == 'f'))
		{
			std::cout << "Your file format does not support the decoding of files. Please restart the program and try again." << std::endl;
			system("pause");
			return -1;
		}
		else if (!(extention[3] == 'e'))
		{
			std::cout << "Your file format does not support the decoding of files. Please restart the program and try again." << std::endl;
			system("pause");
			return -1;
		}
	}
		

	//Computing phase (Done in other functions)
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
	switch (method)
	{
	case 1:
		SC_setup(interFileBuf, interFileLength, mode, finalFileBuf, finalFileLength, fileName.c_str(), fileName.length(), outputName, nameLength);
		break;
	default:
		std::cout << "Your encription methodod has been lost. Please restart your program" << std::endl;
		system("pause");
		return -1;
	}
	delete[] interFileBuf;
	if (mode == _ENCODE_)
	{
		std::cout << "Enter the output file's name" << std::endl;
		std::getline(std::cin, fileName);
		fileLoc = "output//" + fileName + ".bfe";
	}
	else if (mode == _DECODE_)
	{
		std::string output__(outputName, nameLength);
		fileLoc = "output\\" + output__;
	}
	else
	{
		std::cout << "The mode you have entered has been lost. Please restart the program and try again" << std::endl;
		system("pause");
		return -1;
	}
	
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
	delete[] finalFileBuf;
	delete[] outputName;
	std::cout << "100% proccessed. Your new file is in the \"output\" directory which is in the program's directory" << std::endl;
	system("pause");
	return 0;
}