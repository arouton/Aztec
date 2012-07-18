#ifndef __azFilePath__
#define __azFilePath__

#include "azCommon.h"
#include <string>

// \class azFilePath
class azFilePath
{
public:
    azFilePath(azSz a_szPath);

    static azString GetAppPath();

    azString m_strPath;
};

#endif // __azFilePath__