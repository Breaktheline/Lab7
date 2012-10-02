#include "Common.h"

const char* ErrorMessages::MEMORY_ERROR = "Can't allocate memory";
const char* ErrorMessages::FILE_OPEN_ERROR = "Can't open file";
const char* ErrorMessages::WRONG_INPUT_ERROR = "Wrong input format.";
const char* ErrorMessages::ERROR = "Error";

int Max( int a, int b )
{
	return a > b ? a : b;
}

AppException::AppException( const char* message )
{
	_message = message;
}

const char* AppException::GetMessage()
{
	return _message;
}
