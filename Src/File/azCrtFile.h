#ifndef __azCrtFile__
#define __azCrtFile__

#include "azIFile.h"

struct _iobuf;
typedef struct _iobuf FILE;

// \class azCrtFile
class azCrtFile : public azIFile
{
public:
    azCrtFile() : m_pFile(NULL) {}

    virtual void Open(azFilePath const& a_rPath, azFileOpenParams const& a_rOpenParams);
    virtual void Close();

    virtual azUInt Read(void* a_pBuffer, azUInt a_uSize);
    virtual azUInt Write(const void* a_pBuffer, azUInt a_uSize);

    virtual void Seek(azInt a_iOffset, azEFilePosition::Enum a_eOrigin);
    virtual azUInt Tell();

private:
    FILE* m_pFile;
};

#endif // __azCrtFile__