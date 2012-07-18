#define _CRT_SECURE_NO_WARNINGS // temp

#include "azIShader.h"
#include <Cg/cg.h>
#include "Math/azMatrix4x4.h"

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azIShader::Terminate()
{
	// Destroy program
	if (m_pProgram)
	{
		cgDestroyProgram(m_pProgram);
	}
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
CGparameter azIShader::GetParameter(azSz a_szName) const
{
#ifdef UNICODE
    // Temp string conversion
    azCharA szaName[1024];
    wcstombs(szaName, a_szName, 1024);
    return cgGetNamedParameter(m_pProgram, szaName);
#else // UNICODE
    return cgGetNamedParameter(m_pProgram, a_szName);
#endif //UNICODE
}
