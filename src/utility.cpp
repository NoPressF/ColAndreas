#include "utility.h"

std::string Utility::convertNativeStringToString(AMX *amx, cell input)
{
    cell* addr = nullptr;
    if (amx_GetAddr(amx, input, &addr) != AMX_ERR_NONE || addr == nullptr)
    {
        return "";
    }

    int length = 0;
    if (amx_StrLen(addr, &length) != AMX_ERR_NONE || length <= 0)
    {
        return "";
    }

    std::vector<char> buffer(length + 1);
    if (amx_GetString(buffer.data(), addr, 0, length + 1) != AMX_ERR_NONE)
    {
        return "";
    }

    return std::string(buffer.data(), length);
}