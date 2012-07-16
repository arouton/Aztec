#include "azCrtFile.h"
#include "azFilePath.h"
#include <cstdio>

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azCrtFile::Open(azFilePath const& a_rPath, azFileOpenParams const& a_rOpenParams)
{
    std::string strMode;
    switch (a_rOpenParams.m_eReadWrite)
    {
        case azEReadWriteMode::eRead :
        {
            switch (a_rOpenParams.m_eCreateMode)
            {
                case azECreateMode::eCreateOrOpen :
                {
                    azAssert(false, "Not done yet");
                } break;
                case azECreateMode::eOpenExisting :
                {
                    strMode = azL("r");
                } break;
                case azECreateMode::eEraseExisting :
                {
                    azAssert(false, "Not done yet");
                } break;
                azNoDefault;
            }
        } break;
        case azEReadWriteMode::eWrite :
        {
            switch (a_rOpenParams.m_eCreateMode)
            {
                case azECreateMode::eCreateOrOpen :
                {
                    strMode = azL("a");
                } break;
                case azECreateMode::eOpenExisting :
                {
                    azAssert(false, "Not done yet");
                } break;
                case azECreateMode::eEraseExisting :
                {
                    strMode = azL("w");
                } break;
                azNoDefault;
            }
        } break;
        azNoDefault;
    }

    switch (a_rOpenParams.m_eTextOrBinaryMode)
    {
        case azETextOrBinaryMode::eBinary :
        {
            strMode += azL("b");
        } break;
        case azETextOrBinaryMode::eText :
        {
            strMode += azL("t");
        } break;
        azNoDefault;
    }

    fopen_s(&m_pFile, a_rPath.m_strPath.c_str(), strMode.c_str());
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azCrtFile::Close()
{
    fclose(m_pFile);
    m_pFile = NULL;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
azUInt azCrtFile::Read(void* a_pBuffer, azUInt a_uSize)
{
    azUInt uReadSize = fread_s(a_pBuffer, a_uSize, a_uSize, 1, m_pFile);
    return uReadSize;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
azUInt azCrtFile::Write(const void* a_pBuffer, azUInt a_uSize)
{
    azUInt uWrittenSize = fwrite(a_pBuffer, a_uSize, 1, m_pFile);
    return uWrittenSize;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azCrtFile::Seek(azInt a_iOffset, azEFilePosition::Enum a_eOrigin)
{
    int iFilePosition;
    switch (a_eOrigin)
    {
        case azEFilePosition::eBeginning :
        {
            iFilePosition = SEEK_SET;
        } break;
        case azEFilePosition::eCurrent :
        {
            iFilePosition = SEEK_CUR;
        } break;
        case azEFilePosition::eEnd :
        {
            iFilePosition = SEEK_END;
        } break;
        azNoDefault;
    }
    fseek(m_pFile, a_iOffset, iFilePosition);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
azUInt azCrtFile::Tell()
{
    return ftell(m_pFile);
}