#include "azImage.h"
#include <FreeImage/FreeImagePlus.h>

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
azImage::azImage()
: m_auData(NULL)
{}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
azImage::~azImage()
{
	if (m_auData)
	{
		delete [](m_auData);
		m_auData = NULL;
	}
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azImage::Load()
{
	azSz szFilePath = azL("F://Dev//Aztec//Bin//Debug//Test.png");

	FreeImage_Initialise();

	fipImage oImage;
	azBool bLoaded = (0 != oImage.load(szFilePath));
	azAssert(bLoaded, "Image extension or format not supported");

	azAssert(oImage.getBitsPerPixel() <= 32, "More than 32 BPP images not yet supported, there will be some data loss");

	// Always convert to RGBA 32 bits
	azBool bConverted = (0 != oImage.convertTo32Bits());
	azAssert(bConverted, "Image recognized but we failed to convert it to 32 BPP");

	m_uWidth = oImage.getWidth();
	m_uHeight = oImage.getHeight();
	m_uBpp = oImage.getBitsPerPixel();
	azAssert(m_uBpp == 32, "Convert didn't work properly");

	azUInt uBufferSize = GetBufferSize();
	m_auData = new azUInt8[uBufferSize];

	// There is no C++ wrapping for this method.
	FreeImage_ConvertToRawBits(m_auData,
		oImage,
		oImage.getScanWidth(),
		m_uBpp,
		FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK,
		true);  
	
	oImage.clear();

	FreeImage_DeInitialise();
}