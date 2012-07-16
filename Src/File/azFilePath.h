#ifndef __azFilePath__
#define __azFilePath__

#include "azCommon.h"
#include <string>

// \class azFilePath
class azFilePath
{
public:
    azFilePath(azSz a_szPath);

    static std::string GetAppPath();

    std::string m_strPath;
};

#endif // __azFilePath__