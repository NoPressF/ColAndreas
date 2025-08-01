#pragma once

#include <vector>
#include <string>
#include <amx/amx.h>

namespace Utility
{
	std::string convertNativeStringToString(AMX *amx, cell input);
}