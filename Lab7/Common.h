#ifndef H_COMMON
#define H_COMMON

#include <stdlib.h>

struct ErrorMessages
{
	static const char* ERROR;
	static const char* MEMORY_ERROR;
	static const char* FILE_OPEN_ERROR;
	static const char* WRONG_INPUT_ERROR;
};

class AppException 
{
public:
	AppException(const char* message);
	const char* GetMessage();
private:
	const char* _message;
};

#endif

