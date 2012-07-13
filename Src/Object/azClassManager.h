#ifndef __azClassManager__
#define __azClassManager__

#include "azCommon.h"
#include "Toolkit/azRef.h"
#include "Object/azObjectMacros.h"
#include <list>

class azMetaClass;
class azClassId;

// \class azClassManager
class AZ_API azClassManager
{
    AZ_DECLARE_CLASS(azClassManager)

public:
    // Singleton management
    static azClassManager& GrabInstance();

    static azClassManager const& GetInstance();


    // Initialize
    void Initialize();

    // Terminate
    void Terminate();


    // Register a meta class
    void RegisterMetaClass(azMetaClass& a_rMetaClass);

    void UnregisterMetaClass(azMetaClass& a_rMetaClass);


    azMetaClass const& FindMetaClass(azClassId const& a_rClassId) const;

    azMetaClass const* TryFindMetaClass(azClassId const& a_rClassId) const;


private:
    // This should be a map<azClassId, azMetaClass>
    typedef std::list< azRef<azMetaClass> > azMetaClasses;
    azMetaClasses m_lMetaClasses;

    azMetaClass* TryFindMetaClass(azClassId const& a_rClassId);
};

#endif // __azClassManager__