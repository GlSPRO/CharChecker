#include <windows.h>
#include <cstring>
#include "pch.h"

extern "C" __declspec(dllexport) bool containsAllCharacters(const char* str, const char* chars) {
    while (*chars) {
        if (!strchr(str, *chars++)) {
            return false;
        }
    }
    return true;
}
