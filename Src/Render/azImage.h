#ifndef __azImage__
#define __azImage__

#include "azCommon.h"

class AZ_API azImage
{
public:
	// \brief Default constructor
	azImage();

	// \brief Destructor
	~azImage();

	// \brief Load
	void Load();

	// \brief Get the internal buffer size
	azUInt8 const* GetBuffer() const { return m_auData; }

	// \brief Get the internal buffer size
	azUInt GetBufferSize() const { return m_uWidth * m_uHeight * m_uBpp / 8; }

private:
	// Pixel data
	azUInt8* m_auData;

	//
	azUInt m_uWidth;
	
	//
	azUInt m_uHeight;
	
	//
	azUInt m_uBpp;
};

#endif // __azImage__