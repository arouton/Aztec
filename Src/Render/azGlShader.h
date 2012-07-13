#ifndef __azGlShader__
#define __azGlShader__

#include "azCommon.h"
#include "Render/azIShader.h"

class azMatrix4x4;
class azVector3;
class azVector4;

// \class azGlShader
// \brief OpenGL shader
class AZ_API azGlShader : public azIShader
{
public:
	// \brief Virtual destructor
	~azGlShader() {}

	// \brief Initialize
	virtual void Initialize(CGprogram a_pProgram);

	// Set a shader parameter (float)
	virtual void SetParameter(azSz a_szName, azFloat a_fValue);

	// Set a shader parameter (vector 2)
	//virtual void SetParameter(azSz a_szName, azVector2 const& a_rf2Value);

	// Set a shader parameter (vector 3)
	virtual void SetParameter(azSz a_szName, azVector3 const& a_rf3Value);

	// Set a shader parameter (vector 4)
	virtual void SetParameter(azSz a_szName, azVector4 const& a_rf4Value);

	// Set a shader parameter (matrix)
	virtual void SetParameter(azSz a_szName, azMatrix4x4 const& a_rValue);

	// Set a shader parameter (coulor)
	//virtual void SetParameter(azSz a_szName, azColor const& a_rValue);
};




#endif // __azGlShader__