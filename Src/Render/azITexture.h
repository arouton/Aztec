#ifndef __azITexture__
#define __azITexture__

#include "azCommon.h"
#include "Render/azGlRenderEnums.h"

class azImage;

// \class azITexture
// \brief Texture interface
class AZ_API azITexture
{
public:
	// \brief Default constructor
	azITexture();

	// \brief Destructor
	virtual ~azITexture() {}

	// \brief Initialize
	virtual void Initialize(azImage const& a_rImage);

	// \brief Terminate
	virtual void Terminate() {}

protected:
	// Pixel format
	azEPixelFormat::Enum m_ePixelFormat;

	// Texture width
	azUInt m_uWidth;

	// Texture height
	azUInt m_uHeight;

	// Mipmap infos
	//azBool m_bHasMipmaps;
	//azvBool m_bAutoMipmaps;
};

#endif // __azITexture__