#ifndef __azApplication__
#define __azApplication__

#include <windows.h>
#include "azCommon.h"
#include "Toolkit/azRef.h"

class azIRenderer;
class azIGpuBuffer;
class azIInputLayout;
class azIShader;

// \class azIApplication
// \brief Application run by main
class AZ_API azIApplication
{
public:
	// \brief Initialize application
	virtual void Initialize();

	// \brief Terminate application
	virtual void Terminate();


	// \brief Update application
	virtual void Update();

private:
	// The renderer instance
	azRef<azIRenderer> m_rRenderer;

	// Temp
	azRef<azIGpuBuffer> m_rVertexBuffer;
	azRef<azIInputLayout> m_rInputLayout;
	azRef<azIShader> m_rVertexShader;
	azRef<azIShader> m_rPixelShader;
};

#endif // __azApplication__