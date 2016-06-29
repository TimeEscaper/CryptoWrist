#pragma once

#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <sstream>

namespace utils
{
	std::string ToString(int value);

	std::string ToString(long value);

	long StringToLong(std::string str);

	int StringToInt(std::string str);
}

#endif
