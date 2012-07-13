#include "azCommon.h"
#include <windows.h>

#include <cstdio>
#include <cassert>
#include <cstdarg>

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azAssert(azBool a_bCondition, const azChar* a_szFormat, ...)
{
	if (!a_bCondition)
	{
		va_list oArgs;
		va_start(oArgs, a_szFormat);
		azChar szBuffer[1024];
		vsnprintf_s(szBuffer, 1024, 1204, a_szFormat, oArgs);
		azPrint(szBuffer);
		va_end(oArgs);

		assert(false);
	}
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azPrint(const azChar* a_szFormat, ...)
{
    va_list oArgs;
    va_start(oArgs, a_szFormat);
    azChar szBuffer[1024];
	vsnprintf_s(szBuffer, 1024, 1024, a_szFormat, oArgs);
	OutputDebugString(szBuffer);
    va_end(oArgs);
}

