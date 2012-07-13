#include "azIInputLayout.h"

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
azInputLayoutElement::azInputLayoutElement(azESemanticType::Enum a_eSemanticType,
											azUInt a_uSemanticIndex,
											azEFormatType::Enum a_eFormatType,
											azUInt a_uStride,
											azUInt a_uOffset)
	: m_eSemanticType(a_eSemanticType)
	, m_uSemanticIndex(a_uSemanticIndex)
	, m_eFormatType(a_eFormatType)
	, m_uStride(a_uStride)
	, m_uOffset(a_uOffset)
{
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
azInputLayoutElement::azInputLayoutElement(azInputLayoutElement const& a_rInputLayoutElement)
	: m_eSemanticType(a_rInputLayoutElement.m_eSemanticType)
	, m_uSemanticIndex(a_rInputLayoutElement.m_uSemanticIndex)
	, m_eFormatType(a_rInputLayoutElement.m_eFormatType)
	, m_uStride(a_rInputLayoutElement.m_uStride)
	, m_uOffset(a_rInputLayoutElement.m_uOffset)
{
}