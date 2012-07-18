#define _CRT_SECURE_NO_WARNINGS // temp

#include "azCommon.h"
#include <windows.h>

#include <cstdio>
#include <cassert>
#include <cstdarg>

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void _azAssert(azBool a_bCondition, const azCharA* a_szFormat, ...)
{
	if (!a_bCondition)
	{
		va_list oArgs;
		va_start(oArgs, a_szFormat);
		azCharA szBuffer[1024];
		vsnprintf_s(szBuffer, 1024, 1204, a_szFormat, oArgs);
		_azPrint(szBuffer);
		va_end(oArgs);

		assert(false);
	}
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void _azAssert(azBool a_bCondition, const azCharW* a_szFormat, ...)
{
    if (!a_bCondition)
    {
        va_list oArgs;
        va_start(oArgs, a_szFormat);
        azCharW szBuffer[1024];
        _vsnwprintf_s(szBuffer, 1024, 1204, a_szFormat, oArgs);
        _azPrint(szBuffer);
        va_end(oArgs);

        assert(false);
    }
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void _azPrint(const azCharA* a_szaFormat, ...)
{
    va_list oArgs;
    va_start(oArgs, a_szaFormat);
    azChar szBuffer[1024];
#ifdef _UNICODE
    azChar szwFormat[1024];
    mbstowcs(szwFormat, a_szaFormat, 1024);
    _vsnwprintf_s(szBuffer, 1024, 1204, szwFormat, oArgs);
    wcscat_s(szBuffer, 1024, azL("\n"));
#else
    vsnprintf_s(szBuffer, 1024, 1204, a_szaFormat, oArgs);
    strcat_s(szBuffer, 1024, azL("\n"));
#endif
	OutputDebugString(szBuffer);
    va_end(oArgs);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void _azPrint(const azCharW* a_szwFormat, ...)
{
    va_list oArgs;
    va_start(oArgs, a_szwFormat);
    azChar szBuffer[1024];
#ifdef _UNICODE
    _vsnwprintf_s(szBuffer, 1024, 1204, a_szwFormat, oArgs);
    wcscat_s(szBuffer, 1024, azL("\n"));
#else
    azChar szwFormat[1024];
    wcstombs(szwFormat, a_szwFormat, 1024);
    vsnprintf_s(szBuffer, 1024, 1204, szwFormat, oArgs);
    strcat_s(szBuffer, 1024, azL("\n"));
#endif
    OutputDebugString(szBuffer);
    va_end(oArgs);
}


