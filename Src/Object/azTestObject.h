#ifndef __azTestObject__
#define __azTestObject__

#include "azCommon.h"
#include "azObjectMacros.h"
#include "azIObject.h"

class AZ_API azTestObject : public azIObject
{
    AZ_DECLARE_CLASS(azTestObject)

public:
    azTestObject() {}
};

#endif // __azTestObject__