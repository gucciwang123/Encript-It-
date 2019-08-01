/*
iostream
*/
#include <stdexcept>
#include "headers/pch.h"
int decoder(unsigned char* input, unsigned char*& finalBuf, unsigned int size, int index)
{
	unsigned char* output = new unsigned char[size];
	int dummy;
	for (int a = 0; a < (int)size; a++)
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
	finalBuf = output;
	return 0;
}