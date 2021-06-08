#pragma once
#include <iostream>
#include <string>

class pipe
{
public:
	pipe();
	void createLengthIndicator(char* buffer, unsigned long int len);
	uint64_t getTimestamp();
	unsigned long int writeStringToPipe(int fd, const char* text);
	unsigned long int writeFileToPipe(int fd, const char* path);
	unsigned long int readLengthIndicatorFromPipe(int fd);
	int readStringFromPipe(char* buffer, int fd);
};
