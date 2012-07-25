#include "azImage.h"
#include <FreeImage/FreeImagePlus.h>
#include "Memory/azMemoryManager.h"

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
azImage::azImage()
: m_abData(NULL)
, m_uWidth(0)
, m_uHeight(0)
, m_uBpp(0)
{}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azImage::Initialize()
{
	azSz szFilePath = azL("F://Dev//Aztec//Bin//Debug//Test.png");

	FreeImage_Initialise();

	fipImage oFreeImage;
#ifdef UNICODE
	azBool bLoaded = (0 != oFreeImage.loadU(szFilePath));
#else // UNICODE
    azBool bLoaded = (0 != oFreeImage.load(szFilePath));
#endif // UNICODE
	azAssert(bLoaded, "Image extension or format not supported");

	azAssert(oFreeImage.getBitsPerPixel() <= 32, "More than 32 BPP images not yet supported, there will be some data loss");

	// Always convert to RGBA 32 bits
	azBool bConverted = (0 != oFreeImage.convertTo32Bits());
	azAssert(bConverted, "Image recognized but we failed to convert it to 32 BPP");

	m_uWidth = oFreeImage.getWidth();
	m_uHeight = oFreeImage.getHeight();
	m_uBpp = oFreeImage.getBitsPerPixel();
	azAssert(m_uBpp == 32, "Convert didn't work properly");

	azUInt uBufferSize = GetBufferSize();
	m_abData = azNewArray(azByte, uBufferSize);

	// There is no C++ wrapping for this method.
    FreeImage_ConvertToRawBits(m_abData,
		oFreeImage,
		oFreeImage.getScanWidth(),
		m_uBpp,
		FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK,
		true);  
	
	oFreeImage.clear();

	FreeImage_DeInitialise();
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azImage::Terminate()
{
    azAssert(m_abData != NULL, "The data are not here...");

    azUInt uBufferSize = GetBufferSize();
    azDeleteArray(m_abData, uBufferSize);
    m_abData = NULL;

    m_uWidth = 0;
    m_uHeight = 0;
    m_uBpp = 0;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
azUInt azImage::GetWidth() const
{
    return m_uWidth;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
azUInt azImage::GetHeight() const
{
    return m_uHeight;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
azEPixelFormat::Enum azImage::GetPixelFormat() const
{
    // Hardcoded for now
    return azEPixelFormat::eA8R8G8B8;
}