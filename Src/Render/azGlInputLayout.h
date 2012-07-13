#ifndef __azGlInputLayout__
#define __azGlInputLayout__

#include "azCommon.h"
#include <vector>
#include "Render/azIInputLayout.h"

typedef std::vector<azInputLayoutElement> azInputLayoutElements;

// \class azGlInputLayout
// \brief OpenGL declaration
class AZ_API azGlInputLayout : public azIInputLayout
{
public:
	// \brief Default constructor
	azGlInputLayout() {}

	// \brief Add a new element on given slot
	virtual void AddElement(azUInt a_uSlotIndex, azInputLayoutElement& a_rInputLayoutElement);

	// \brief Get elements for one stream
	azInputLayoutElements const& GetElements(azUInt a_uSlotIndex) const;

private:
	// Elements (16 streams max)
	azInputLayoutElements m_avElements[16];
};



#endif // __azGlInputLayout__