#ifndef __azFactory__
#define __azFactory__

#include "azCommon.h"
#include "Toolkit/azRef.h"
#include <list>

class azIObject;
class azMetaClass;
class azCreateParams;
class azClassId;

// \class azFactory
class AZ_API azFactory
{
public:
	// Singleton management
	static azFactory& GrabInstance();

	static azFactory const& GetInstance();
		

	// Allocate / Construct / Create / Initialize
	azIObject& CreateObject(azClassId const& a_rClassId);

	azIObject& CreateObject(azClassId const& a_rClassId, azCreateParams const& a_rCreateParams);

	template<class t_Class>
	t_Class& CreateObject();

	template<class t_Class>
	t_Class& CreateObject(azCreateParams const& a_rCreateParams);


	// Terminate / Destroy / Destruct / Free
	void DestroyObject(azIObject& a_rObject);

private:
    // Create an object from a metaclass
	azIObject& _CreateObject(azMetaClass const& a_rMetaClass, azCreateParams const& a_rCreateParams);
};

#include "azFactory.inl"

#endif // __azFactory__
