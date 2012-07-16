#ifndef __azIFile__
#define __azIFile__

#include "azCommon.h"
#include "azFilePath.h"
#include <string>

class azFilePath;

// \class azEReadWriteMode
class azEReadWriteMode
{
public:
    enum Enum
    {
        eRead,
        eWrite,
        eReadWrite
    };
};

// \class azECreateMode
class azECreateMode
{
public:
    enum Enum
    {
        eCreateOrOpen,
        eOpenExisting,
        eEraseExisting
    };
};

// \class azETextOrBinaryMode
class azETextOrBinaryMode
{
public:
    enum Enum
    {
        eBinary,
        eText
    };
};

// \class azFileOpenParams
class azFileOpenParams
{
public:
    azFileOpenParams(azEReadWriteMode::Enum a_eReadWrite = azEReadWriteMode::eReadWrite,
        azECreateMode::Enum a_eCreateMode = azECreateMode::eCreateOrOpen,
        azETextOrBinaryMode::Enum a_eTextOrBinaryMode =azETextOrBinaryMode::eBinary)
        : m_eReadWrite(a_eReadWrite)
        , m_eCreateMode(a_eCreateMode)
        , m_eTextOrBinaryMode(a_eTextOrBinaryMode)
    {}

    azEReadWriteMode::Enum m_eReadWrite;
    azECreateMode::Enum m_eCreateMode;
    azETextOrBinaryMode::Enum m_eTextOrBinaryMode;
};

// \class azEFilePosition
// \brief File position for seek
class azEFilePosition
{
public:
    enum Enum
    {
        eBeginning,
        eCurrent,
        eEnd
    };
};

// \class azIFile
class azIFile
{
public:
    virtual void Open(azFilePath const& a_rPath, azFileOpenParams const& a_rOpenParams) = 0;
    virtual void Close() = 0;

    virtual azUInt Read(void* a_pBuffer, azUInt a_uSize) = 0;
    virtual azUInt Write(const void* a_pBuffer, azUInt a_uSize) = 0;

    virtual void Seek(azInt a_iOffset, azEFilePosition::Enum a_eOrigin) = 0;
    virtual azUInt Tell() = 0;
};


#endif // __azIFile__