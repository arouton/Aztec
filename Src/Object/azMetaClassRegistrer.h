#ifndef __azMetaClassRegistrer__
#define __azMetaClassRegistrer__

#include "azCommon.h"
#include <list>

class azMetaClass;

// \function Fill the meta class
typedef void (*azPfnMetaClassFiller)(azMetaClass& a_rOutMetaClass);

// \class azMetaClassRegistrer
class AZ_API azMetaClassRegistrer
{
public:
    static azMetaClassRegistrer& GrabInstance();

    static azMetaClassRegistrer const& GetInstance();

    azMetaClass* RegisterMetaClassFiller(azPfnMetaClassFiller a_pfnMetaClassFiller);

    void CreateMetaClasses() const;

private:
    // Metaclass fillers
    typedef std::list<azPfnMetaClassFiller> azMetaClassFillers;
    azMetaClassFillers m_lMetaClassFillers;
};

#endif // __azMetaClassRegistrer__

