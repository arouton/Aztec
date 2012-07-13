#ifndef __azIShader__
#define __azIShader__

#include "azCommon.h"

struct _CGprogram;
typedef struct _CGprogram *CGprogram;

struct _CGparameter;
typedef struct _CGparameter *CGparameter;

class azMatrix4x4;
class azVector3;
class azVector4;

// \class azIShader
// \brief Shader interface
class AZ_API azIShader
{
public:
	// \brief Virtual destructor
	~azIShader() {}

	// \brief Initialize
	virtual void Initialize() {}

	// \brief Terminate
	virtual void Terminate();

	// \brief Set a shader parameter (float)
	virtual void SetParameter(azSz a_szName, azFloat a_fValue) = 0;

	// \brief Set a shader parameter (vector 2)
	//virtual void SetParameter(azSz a_szName, azVector2 const& a_rf2Value) = 0;

	// \brief Set a shader parameter (vector 3)
	virtual void SetParameter(azSz a_szName, azVector3 const& a_rf3Value) = 0;

	// \brief Set a shader parameter (vector 4)
	virtual void SetParameter(azSz a_szName, azVector4 const& a_rf4Value) = 0;

	// \brief Set a shader parameter (matrix)
	virtual void SetParameter(azSz a_szName, azMatrix4x4 const& a_rValue) = 0;

	// \brief Set a shader parameter (coulor)
	//virtual void SetParameter(azSz a_szName, azColor const& a_rValue) = 0;

	// \brief Get the Cg program
	CGprogram GetCgProgram() { return m_pProgram; }

protected:
	// \brief Get a shader parameter
	CGparameter GetParameter(azSz a_szName) const;

//private:
	// Cg program for the shader
	CGprogram m_pProgram;
};




#endif // __azIShader__