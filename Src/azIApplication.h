#ifndef __azApplication__
#define __azApplication__

#include <windows.h>
#include "azCommon.h"

class azIRenderer;
class azIGpuBuffer;
class azIInputLayout;
class azIShader;

// \class azIApplication
// \brief Application run by main
class AZ_API azIApplication
{
public:
	// \brief Default constructor
	azIApplication();

	// \brief Destructor
	virtual ~azIApplication() {}


	// \brief Initialize application
	virtual void Initialize();

	// \brief Terminate application
	virtual void Terminate();


	// \brief Update application
	virtual void Update();

private:
	// The renderer instance
	azIRenderer* m_pRenderer;

	// Temp
	azIGpuBuffer* m_pVertexBuffer;
	azIInputLayout* m_pInputLayout;
	azIShader* m_pVertexShader;
	azIShader* m_pPixelShader;
};

#endif // __azApplication__