#pragma once
int fileExtract(const char* location, unsigned char*& fileBuffer, unsigned long long& bufferLength);

int fileWritter(const char* name, unsigned char* fileBuffer, unsigned long long bufferLength);