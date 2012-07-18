#include "azFilePath.h"
#include <stdio.h>

//#ifdef WINDOWS
#include <direct.h>
#ifdef _UNICODE
#define GetCurrentDir _wgetcwd
#else // _UNICODE
#define GetCurrentDir _getcwd
#endif // _UNICODE
//#else
//#include <unistd.h>
//#define GetCurrentDir getcwd
//#endif


azFilePath::azFilePath(azSz a_szPath)
{
    m_strPath = GetAppPath() + azL("\\") + azString(a_szPath);
}

azString azFilePath::GetAppPath()
{
    azChar cCurrentPath[FILENAME_MAX];
    azChar* szResult = GetCurrentDir(cCurrentPath, sizeof(cCurrentPath) / sizeof(azChar));
    azAssert(szResult != NULL, "Couldnt retrieve the app path");
    return azString(cCurrentPath);
}

