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
azGlTexture::azGlTexture()
    : m_uTextureId(0)
{}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azGlTexture::Initialize(azImage const& a_rImage)
{
	azITexture::Initialize(a_rImage);

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

	// Load texture
    azEPixelFormat::Enum ePixelFormat = a_rImage.GetPixelFormat();
    if (azGlRenderEnums::IsPixelFormatCompressed(ePixelFormat))
	{
		// Compressed format
		azUInt uDataSize = a_rImage.GetBufferSize();
        azAssert(m_uWidth * m_uHeight * azGlRenderEnums::GetNativeBytesPerPixel(ePixelFormat) == uDataSize, "Sizes mismatch");
		azGlRenderer::glCompressedTexImage2DARB(GL_TEXTURE_2D,
			0, //uMipMapLevel
			azGlRenderEnums::GetNativePixelInternalFormat(m_ePixelFormat),
			m_uWidth,
			m_uHeight,
			0,
			(GLsizei)uDataSize,
			(GLvoid*)a_rImage.GetBuffer());
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
			(GLvoid*)a_rImage.GetBuffer());
	}

	// Deactivate texture
	glBindTexture(GL_TEXTURE_2D, 0);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azGlTexture::Terminate()
{
    glDeleteTextures(1, &m_uTextureId);

    azITexture::Terminate();
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
GLuint azGlTexture::GetTextureId() const
{
    return m_uTextureId;
}