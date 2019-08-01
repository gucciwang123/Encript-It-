#pragma once
int fileExtract(const char* location, unsigned char*& fileBuffer, unsigned long& bufferLength);

int fileWritter(const char* name, unsigned char* fileBuffer, unsigned long bufferLength);