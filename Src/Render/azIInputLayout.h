#ifndef __azIInputLayout__
#define __azIInputLayout__

#include "azCommon.h"
#include "Render/azRenderEnums.h"

// \class azInputLayoutElement
// \brief Input layout element
class AZ_API azInputLayoutElement
{
public:
	// \brief Value constructor
	azInputLayoutElement(azESemanticType::Enum a_eSemanticType,
							azUInt a_uSemanticIndex,
							azEFormatType::Enum a_eFormatType,
							azUInt a_uStride,
							azUInt a_uOffset);

	// \brief Copy constructor
	azInputLayoutElement(azInputLayoutElement const& a_rInputLayoutElement);

	// Semantic type (ePosition, eNormal, ...)
	azESemanticType::Enum m_eSemanticType;  

	// Semantic index
	azUInt m_uSemanticIndex;

	// Format type (eFloat1, eFloat2, eColor ...)
	azEFormatType::Enum m_eFormatType; 

	// Stride
	azUInt m_uStride;

	// Offset
	azUInt m_uOffset;
};

// \class azIInputLayout
// \brief Input layout interface
class AZ_API azIInputLayout
{
public:
	// \brief Virtual destructor
	virtual ~azIInputLayout() {}

	// \brief Initialize
	virtual void Initialize() {}

	// \brief Terminate
	virtual void Terminate() {}

	// \brief Add a new element on given slot
	virtual void AddElement(azUInt a_uSlotIndex, azInputLayoutElement& a_rInputLayoutElement) = 0;
};



#endif // __azIInputLayout__