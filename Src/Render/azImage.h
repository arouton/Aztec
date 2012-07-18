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

	// \brief Initialize
	void Initialize();

    // \brief Terminate
    void Terminate();

	// \brief Get the internal buffer size
	azUInt8 const* GetBuffer() const { return m_abData; }

	// \brief Get the internal buffer size
	azUInt GetBufferSize() const { return m_uWidth * m_uHeight * m_uBpp / 8; }

private:
	// Pixel data
	azBytes m_abData;

	//
	azUInt m_uWidth;
	
	//
	azUInt m_uHeight;
	
	//
	azUInt m_uBpp;
};

#endif // __azImage__