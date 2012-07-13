#include "azGlInputLayout.h"

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azGlInputLayout::AddElement(azUInt a_uSlotIndex, azInputLayoutElement& a_rInputLayoutElement)
{
	m_avElements[a_uSlotIndex].push_back(a_rInputLayoutElement);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
azInputLayoutElements const& azGlInputLayout::GetElements(azUInt a_uSlotIndex) const
{
	return m_avElements[a_uSlotIndex];
}