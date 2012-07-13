#ifndef __azClassId__
#define __azClassId__

#include "azCommon.h"

// \function Hash function
azUInt azHashFunction(azSz a_pStr);

// \class azClassId
class AZ_API azClassId
{
public:
    azClassId();
    azClassId(azUInt a_uId);
    azClassId(azSz a_szName);
    azClassId(azClassId const& a_rSource);
    azClassId const& operator =(azClassId const& a_rSource);
    bool operator ==(azClassId const& a_rSource) const;
    bool operator !=(azClassId const& a_rSource) const;
    bool IsNullType() const;
    azUInt GetId() const { return m_uId; }

private:
    azUInt m_uId;
    azSz m_szName; // for debug purposes only
};

#endif // __azClassId__