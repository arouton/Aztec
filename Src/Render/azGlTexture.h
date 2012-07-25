#ifndef __azGlTexture__
#define __azGlTexture__

#include "azCommon.h"
#include "Render/azITexture.h"

// \class azGlTexture
// \brief OpenGL texture
class AZ_API azGlTexture : public azITexture
{
public :
	// \brief Default constructor
	azGlTexture();

	// \brief Initialize
	virtual void Initialize(azImage const& a_rImage);

	// \brief Terminate
	virtual void Terminate();


    // \brief GetTextureId
    GLuint GetTextureId() const;

private:
	// Texture id
	GLuint m_uTextureId;
};

#endif // __azGlTexture__