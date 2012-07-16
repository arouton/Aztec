#include "azFilePath.h"
#include <stdio.h>

//#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
//#else
//#include <unistd.h>
//#define GetCurrentDir getcwd
//#endif


azFilePath::azFilePath(azSz a_szPath)
{
    m_strPath = GetAppPath() + azL("\\") + std::string(a_szPath);
}

std::string azFilePath::GetAppPath()
{
    azChar cCurrentPath[FILENAME_MAX];
    azChar* szResult = GetCurrentDir(cCurrentPath, sizeof(cCurrentPath) / sizeof(azChar));
    azAssert(szResult != NULL, "Couldnt retrieve the app path");
    return std::string(cCurrentPath);
}

