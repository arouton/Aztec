#ifndef __azImage__
#define __azImage__

#include "azCommon.h"
#include "Render/azRenderEnums.h"

class AZ_API azImage
{
public:
	// \brief Default constructor
	azImage();

	// \brief Initialize
	void Initialize();

    // \brief Terminate
    void Terminate();

	// \brief Get the internal buffer size
	azCBytes GetBuffer() const { return m_abData; }

	// \brief Get the internal buffer size
	azUInt GetBufferSize() const { return m_uWidth * m_uHeight * m_uBpp / 8; }

    // \brief Get the image width
    azUInt GetWidth() const;

    // \brief Get the image height
    azUInt GetHeight() const;

    // \brief Get the pixel format
    azEPixelFormat::Enum GetPixelFormat() const;

private:
	// Pixel data
	azBytes m_abData;

	//
	azUInt m_uWidth;
	
	//
	azUInt m_uHeight;
	
	// todo : get rid of this, use pixel format instead
	azUInt m_uBpp;
};

#endif // __azImage__