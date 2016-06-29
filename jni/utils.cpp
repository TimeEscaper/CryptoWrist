#include "utils.h"
#include <stdlib.h>

namespace utils
{
	std::string ToString(int value)
	{
		std::ostringstream tmp_stream;

		tmp_stream << value;

		return tmp_stream.str();
	}

	std::string ToString(long value)
	{
		std::ostringstream tmp_stream;

		tmp_stream << value;

		return tmp_stream.str();
	}

	long StringToLong(std::string str)
	{
		return atol(str.c_str());
	}

	int StringToInt(std::string str)
	{
		return atoi(str.c_str());
	}
}
