#include "azGlTexture.h"
#include <gl/gl.h>
#include <gl/glext.h>
#include "Render/azGlRenderEnums.h"
#include "Render/azGlRenderer.h"
#include "Render/azImage.h"

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
//azUInt GetMipMapLevelsCount(azUInt a_uWidth, azUInt a_uHeight)
//{
//	azUInt uCount = 0;
//	while ((a_uWidth > 1) || (a_uHeight > 1))
//	{
//		if (a_uWidth > 1) 
//		{
//			a_uWidth  /= 2;
//		}
//		if (a_uHeight > 1)
//		{
//			a_uHeight /= 2;
//		}
//		++uCount;
//	}
//	return uCount;
//}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azGlTexture::Initialize(azUInt a_uWidth, azUInt a_uHeight, azEPixelFormat::Enum a_ePixelFormat)
{
	azITexture::Initialize(a_uWidth, a_uHeight, a_ePixelFormat);

	// Texture generation
	glGenTextures(1, &m_uTextureId);

	// Texture activation
	glBindTexture(GL_TEXTURE_2D, m_uTextureId);

	// Init parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

	// No mipmap for now
	// Set number of mipmap levels
	//azUint uMipmapLevelsCount = a_bNoMipMap ? 0 : GetMipMapLevelsCount(m_uWidth, m_uHeight);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_FALSE); 

	// Convert image

	// Load texture
	if (azGlRenderEnums::IsPixelFormatCompressed(a_ePixelFormat))
	{
		// Compressed format
		azUInt uDataSize = m_uWidth * m_uHeight * azGlRenderEnums::GetNativeBytesPerPixel(a_ePixelFormat);
		azGlRenderer::glCompressedTexImage2DARB(GL_TEXTURE_2D,
			0, //uMipMapLevel
			azGlRenderEnums::GetNativePixelInternalFormat(m_ePixelFormat),
			m_uWidth,
			m_uHeight,
			0,
			(GLsizei)uDataSize,
			m_pImage->GetBuffer());
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D,
			0, //uMipMapLevel
			azGlRenderEnums::GetNativePixelInternalFormat(m_ePixelFormat),
			m_uWidth,
			m_uHeight,
			0,
			azGlRenderEnums::GetNativePixelFormat(m_ePixelFormat),
			azGlRenderEnums::GetNativePixelType(m_ePixelFormat),
			m_pImage->GetBuffer());
	}

	// Deactivate texture
	glBindTexture(GL_TEXTURE_2D, 0);
}