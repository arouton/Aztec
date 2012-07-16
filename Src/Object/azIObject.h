#ifndef __azIObject__
#define __azIObject__

#include "Object/azObjectMacros.h"

class azMetaClass;

// \class azCreateParams
class AZ_API azCreateParams
{
public:
	azCreateParams() {}
};

// IObject
class AZ_API azIObject
{
    AZ_DECLARE_CLASS(azIObject)

public:
	azIObject() {}
	virtual ~azIObject() {}

	virtual void Create(azCreateParams const& /*a_rParams*/) {}
	virtual void Destroy() {}

	virtual void Initialize() {}
	virtual void Terminate() {}
};

#endif // __azIObject__
