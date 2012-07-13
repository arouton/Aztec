#include "azGlShader.h"
#include <Cg/cgGL.h>
#include "Math/azMatrix4x4.h"

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azGlShader::Initialize(CGprogram a_pProgram)
{
	azIShader::Initialize();
	m_pProgram = a_pProgram;
	cgGLLoadProgram(m_pProgram);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azGlShader::SetParameter(azSz a_szName, azFloat a_fValue)
{
	cgGLSetParameter1f(GetParameter(a_szName), a_fValue);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azGlShader::SetParameter(azSz a_szName, azVector3 const& a_rf3Value)
{
	cgGLSetParameter3fv(GetParameter(a_szName), (const azFloat *)a_rf3Value);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azGlShader::SetParameter(azSz a_szName, azVector4 const& a_rf4Value)
{
	cgGLSetParameter4fv(GetParameter(a_szName), (const azFloat *)a_rf4Value);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azGlShader::SetParameter(azSz a_szName, azMatrix4x4 const& a_rValue)
{
	cgGLSetMatrixParameterfc(GetParameter(a_szName), (const azFloat *)a_rValue);
}
