#include <windows.h>
#include <tchar.h>
#include "azStackWalker.h"
#include <dbghelp.h>

class azDbgHelpDllWrapper
{
public:
	azDbgHelpDllWrapper();
		
	void Initialize();
	void Terminate();

	static azDbgHelpDllWrapper& GetInstance() { static azDbgHelpDllWrapper oWrapper; return oWrapper; }

	// SymInitialize()
	typedef BOOL (__stdcall *SymInitializeFn)(IN HANDLE, IN PSTR, IN BOOL);
	SymInitializeFn m_pfnSymInitialize;

	// SymCleanup()
	typedef BOOL (__stdcall *SymCleanupFn)(IN HANDLE);
	SymCleanupFn m_pfnSymCleanup;

	// SymLoadModule64()
	typedef DWORD64 (__stdcall *SymLoadModule64Fn)(IN HANDLE, IN HANDLE, IN PSTR, IN PSTR, IN DWORD64, IN DWORD);
	SymLoadModule64Fn m_pfnSymLoadModule64;

	// SymGetOptions()
	typedef DWORD (__stdcall *SymGetOptionsFn)(VOID);
	SymGetOptionsFn m_pfnSymGetOptions;

	// SymSetOptions()
	typedef DWORD (__stdcall *SymSetOptionsFn)(IN DWORD);
	SymSetOptionsFn m_pfnSymSetOptions;

	// SymGetSearchPath()
	typedef BOOL (__stdcall WINAPI *SymGetSearchPathFn)(HANDLE, PSTR, DWORD);
	SymGetSearchPathFn m_pfnSymGetSearchPath;

	// SymGetLineFromAddr64()
	typedef BOOL (__stdcall *SymGetLineFromAddr64Fn)(IN HANDLE, IN DWORD64, OUT PDWORD, OUT PIMAGEHLP_LINE64);
	SymGetLineFromAddr64Fn m_pfnSymGetLineFromAddr64;

	// SymGetSymFromAddr64()
	typedef BOOL (__stdcall *SymGetSymFromAddr64Fn)(IN HANDLE, IN DWORD64, OUT PDWORD64, OUT PIMAGEHLP_SYMBOL64);
	SymGetSymFromAddr64Fn m_pfnSymGetSymFromAddr64;

private:
	// Handle to Dll
	HMODULE m_hDbgHelpDll;
};

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
azDbgHelpDllWrapper::azDbgHelpDllWrapper()
{
	Initialize();
}

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
void azDbgHelpDllWrapper::Initialize()
{
	// Load dbghelp.dll and retrieve pointers to procs
	m_hDbgHelpDll = LoadLibrary(azL("dbghelp.dll"));
	azAssert(m_hDbgHelpDll != NULL, "Error loading dbghelp.dll");

	m_pfnSymInitialize = (SymInitializeFn)GetProcAddress(m_hDbgHelpDll, "SymInitialize");
	azAssert(m_pfnSymInitialize != NULL, "Can't find method SymInitialize()");
	m_pfnSymCleanup = (SymCleanupFn) GetProcAddress(m_hDbgHelpDll, "SymCleanup");
	azAssert(m_pfnSymCleanup != NULL, "Can't find method SymCleanup()");

	m_pfnSymGetOptions = (SymGetOptionsFn)GetProcAddress(m_hDbgHelpDll, "SymGetOptions");
	azAssert(m_pfnSymGetOptions != NULL, "Can't find method SymGetOptions()");
	m_pfnSymSetOptions = (SymSetOptionsFn)GetProcAddress(m_hDbgHelpDll, "SymSetOptions");
	azAssert(m_pfnSymSetOptions != NULL, "Can't find method SymSetOptions()");

	m_pfnSymLoadModule64 = (SymLoadModule64Fn)GetProcAddress(m_hDbgHelpDll, "SymLoadModule64");
	azAssert(m_pfnSymLoadModule64 != NULL, "Can't find method SymLoadModule64()");

	m_pfnSymGetSearchPath =(SymGetSearchPathFn)GetProcAddress(m_hDbgHelpDll, "SymGetSearchPath");
	azAssert(m_pfnSymGetSearchPath != NULL, "Can't find method SymGetSearchPath()");

	m_pfnSymGetLineFromAddr64 = (SymGetLineFromAddr64Fn)GetProcAddress(m_hDbgHelpDll, "SymGetLineFromAddr64");
	azAssert(m_pfnSymGetLineFromAddr64 != NULL, "Can't find method SymGetLineFromAddr64()");
	m_pfnSymGetSymFromAddr64 = (SymGetSymFromAddr64Fn)GetProcAddress(m_hDbgHelpDll, "SymGetSymFromAddr64");
	azAssert(m_pfnSymGetSymFromAddr64 != NULL, "Can't find method SymGetSymFromAddr64()");
}

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
void azDbgHelpDllWrapper::Terminate()
{
	FreeLibrary(m_hDbgHelpDll);
}

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
azStackWalker::azStackWalker()
{
	Initialize();
}

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
azStackWalker::~azStackWalker()
{
	Terminate();
}

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
void azStackWalker::Initialize()
{
	// Build the symbol search path
	azCharA szaSymbolSearchPath [4096];
	szaSymbolSearchPath[0] = 0;
	BuildSymbolSearchPath(szaSymbolSearchPath, 4096);

	// SymInitialize
	BOOL bRes = azDbgHelpDllWrapper::GetInstance().m_pfnSymInitialize(GetCurrentProcess(), szaSymbolSearchPath, false);
	azAssert(bRes == TRUE, "SymInitialize failed : error code %d", GetLastError());

	// SymSetOptions
	DWORD dwSymOptions = azDbgHelpDllWrapper::GetInstance().m_pfnSymGetOptions();
	dwSymOptions |= SYMOPT_LOAD_LINES;
	dwSymOptions |= SYMOPT_FAIL_CRITICAL_ERRORS;
	//dwSymOptions |= SYMOPT_NO_PROMPTS;
	dwSymOptions &= ~SYMOPT_UNDNAME;
	dwSymOptions &= ~SYMOPT_DEFERRED_LOADS;
	dwSymOptions = azDbgHelpDllWrapper::GetInstance().m_pfnSymSetOptions(dwSymOptions);

	// SymGetSearchPath
	azCharA szaBuffer[c_uStackWalkerMaxNameLength];
	szaBuffer[0] = 0;
	bRes = azDbgHelpDllWrapper::GetInstance().m_pfnSymGetSearchPath(GetCurrentProcess(), szaBuffer, c_uStackWalkerMaxNameLength);
	azAssert(bRes == TRUE, "SymGetSearchPath failed : error code %d", GetLastError());
	azPrint("CallStack Walker Symbol Search Path: '%s'", szaBuffer);

	LoadModules();
}

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
void azStackWalker::Terminate()
{
	azDbgHelpDllWrapper::GetInstance().m_pfnSymCleanup(GetCurrentProcess());
	azDbgHelpDllWrapper::GetInstance().Terminate();
}

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
void azStackWalker::LoadModules()
{
	// First try toolhelp32
	if (LoadModulesToolHelp32())
	{
		return;
	}
	// Then try psapi
	azBool bRes = LoadModulesPSAPI();
	azAssert(bRes == true, "Can't load symbols");
}

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
azBool azStackWalker::LoadModulesToolHelp32()
{
	// Redefinition from psapi.h tlhelp32.h
#	pragma pack(push, 8)
	struct MODULEENTRY32
	{
		DWORD dwSize;
		DWORD th32ModuleID;			// This module
		DWORD th32ProcessID;		// owning process
		DWORD GlblcntUsage;			// Global usage count on the module
		DWORD ProccntUsage;			// oModuleInfo usage count in th32ProcessID's a_pContext
		BYTE* modBaseAddr;			// Base address of module in th32ProcessID's a_pContext
		DWORD modBaseSize;			// Size in bytes of module starting at modBaseAddr
		HMODULE hModule;			// The hModule of this module in th32ProcessID's a_pContext
		TCHAR szModule[256];		// (MAX_MODULE_NAME32+1, MAX_MODULE_NAME32=255 from Tlhelp32.h)
		TCHAR szExePath[MAX_PATH];
	};
#	pragma pack(pop)

	// CreateToolhelp32Snapshot()
	typedef HANDLE (__stdcall *CreateToolhelp32SnapshotFn)(DWORD, DWORD);
	CreateToolhelp32SnapshotFn pfnCreateToolhelp32Snapshot = NULL;

	// Module32First()
	typedef BOOL (__stdcall *Module32FirstFn)(HANDLE, MODULEENTRY32*);
	Module32FirstFn pfnModule32First = NULL;

	// Module32Next()
	typedef BOOL (__stdcall *Module32NextFn)(HANDLE, MODULEENTRY32*);
	Module32NextFn pfnModule32Next = NULL;

	// Try both kernel32.dll and tlhelp32.dll to find the function
	HINSTANCE hToolhelpDll = NULL;
	azChar* szDllName[] = { azL("kernel32.dll"), azL("tlhelp32.dll") };
	for (azUInt uDllIndex = 0; 2; uDllIndex++)
	{
		hToolhelpDll = LoadLibrary(szDllName[uDllIndex]);
		if (hToolhelpDll == NULL)
		{
			continue;
		}
		pfnCreateToolhelp32Snapshot = (CreateToolhelp32SnapshotFn)GetProcAddress(hToolhelpDll, "CreateToolhelp32Snapshot");
		pfnModule32First = (Module32FirstFn)GetProcAddress(hToolhelpDll, "Module32First");
		pfnModule32Next = (Module32NextFn)GetProcAddress(hToolhelpDll, "Module32Next");
		if ((pfnCreateToolhelp32Snapshot != NULL) && (pfnModule32First != NULL) && (pfnModule32Next != NULL))
		{
			// Found the functions!
			break; 
		}
		else
		{
			FreeLibrary(hToolhelpDll);
			hToolhelpDll = NULL;
		}
	}
	if (hToolhelpDll == NULL)
	{
		azAssert(false, "Cant find ToolHelp32 methods in either kernel32.dll or tlhelp32.dll");
		return false;
	}

	DWORD TH32CS_SNAPMODULE = 0x00000008;
	HANDLE hSnapshot = pfnCreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetCurrentProcessId());
	if (hSnapshot == (HANDLE) -1)
	{
		return false;
	}

	MODULEENTRY32 oModuleEntry;
	memset(&oModuleEntry, 0, sizeof(MODULEENTRY32));
	oModuleEntry.dwSize = sizeof(oModuleEntry);

	BOOL bKeepGoing = pfnModule32First(hSnapshot, &oModuleEntry);
	azUInt uModuleCount = 0;
	while (bKeepGoing == TRUE)
	{
		azDbgHelpDllWrapper::GetInstance().m_pfnSymLoadModule64(GetCurrentProcess(), 0, oModuleEntry.szExePath,
			oModuleEntry.szModule, (DWORD64)oModuleEntry.modBaseAddr, oModuleEntry.modBaseSize);
		uModuleCount++;
		bKeepGoing = pfnModule32Next(hSnapshot, &oModuleEntry);
	}

	CloseHandle(hSnapshot);
	FreeLibrary(hToolhelpDll);
		
	return(uModuleCount != 0);
}

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
bool azStackWalker::LoadModulesPSAPI()
{
	HINSTANCE hPsapiDll = LoadLibrary(azL("psapi.dll"));
	if (hPsapiDll == NULL)
	{
		return false;
	}

	// Redefinition from psapi.h header
	struct MODULEINFO
	{
		LPVOID lpBaseOfDll;
		DWORD SizeOfImage;
		LPVOID EntryPoint;
	};

	// EnumProcessModules()
	typedef BOOL (__stdcall *EnumProcessModulesFn)(HANDLE, HMODULE*, DWORD, LPDWORD);
	EnumProcessModulesFn pfnEnumProcessModules = (EnumProcessModulesFn) GetProcAddress(hPsapiDll, "EnumProcessModules");
	azAssert(pfnEnumProcessModules != NULL, "Can't find method EnumProcessModules()");

	// GetModuleFileNameEx()
	typedef DWORD (__stdcall *GetModuleFileNameExFn)(HANDLE, HMODULE, LPSTR, DWORD);
	GetModuleFileNameExFn pfnGetModuleFileNameEx = (GetModuleFileNameExFn) GetProcAddress(hPsapiDll, "GetModuleFileNameExA");
	azAssert(pfnGetModuleFileNameEx != NULL, "Can't find method GetModuleFileNameEx()");

	// GetModuleBaseName()
	typedef DWORD (__stdcall *GetModuleBaseNameFn)(HANDLE, HMODULE, LPSTR, DWORD);
	GetModuleBaseNameFn pfnGetModuleBaseName = (GetModuleFileNameExFn) GetProcAddress(hPsapiDll, "GetModuleBaseNameA");
	azAssert(pfnGetModuleBaseName != NULL, "Can't find method GetModuleBaseName()");

	// GetModuleInformation()
	typedef BOOL (__stdcall *GetModuleInformationFn)(HANDLE, HMODULE, MODULEINFO*, DWORD);
	GetModuleInformationFn pfnGetModuleInformation = (GetModuleInformationFn) GetProcAddress(hPsapiDll, "GetModuleInformation");
	azAssert(pfnGetModuleInformation != NULL, "Can't find method GetModuleInformation()");

	const DWORD c_dwSizeMax = 8096;
	HMODULE* ahModules = (HMODULE*) alloca(sizeof(HMODULE) * (c_dwSizeMax / sizeof(HMODULE)));
	azCharA* szaImageFileName = (azCharA*) alloca(sizeof(azCharA) * c_dwSizeMax);
	azCharA* szaModuleName = (azCharA*) alloca(sizeof(azCharA) * c_dwSizeMax);

	HANDLE hProcess = GetCurrentProcess();

	azUInt uModuleCount = 0;
	DWORD dwSize;
	if (pfnEnumProcessModules(hProcess, ahModules, c_dwSizeMax, &dwSize) == TRUE)
	{
		if (dwSize <= c_dwSizeMax)
		{
			for (DWORD dwModuleIndex = 0; dwModuleIndex < dwSize / sizeof ahModules[0]; dwModuleIndex++)
			{
				MODULEINFO oModuleInfo;

				// Base address, a_uSize
				pfnGetModuleInformation(hProcess, ahModules[dwModuleIndex], &oModuleInfo, sizeof oModuleInfo);
				// Image file name
				szaImageFileName[0] = 0;
				pfnGetModuleFileNameEx(hProcess, ahModules[dwModuleIndex], szaImageFileName, c_dwSizeMax);
				// Module name
				szaModuleName[0] = 0;
				pfnGetModuleBaseName(hProcess, ahModules[dwModuleIndex], szaModuleName, c_dwSizeMax);

				azDbgHelpDllWrapper::GetInstance().m_pfnSymLoadModule64(hProcess, 0,
					szaImageFileName, szaModuleName, (DWORD64)oModuleInfo.lpBaseOfDll, oModuleInfo.SizeOfImage);

				uModuleCount++;
			}
		}
	}

	if (hPsapiDll)
	{
		FreeLibrary(hPsapiDll);
	}

	return (uModuleCount != 0);
}

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
void azStackWalker::BuildSymbolSearchPath(azCharA* a_szaSymbolSearchPath, azUInt a_uMaxSize) const
{
	strcat_s(a_szaSymbolSearchPath, a_uMaxSize, ".;");

	const size_t nTempLen = 1024;
	azCharA szaTemp[nTempLen];
	// Now add the current directory:
	if (GetCurrentDirectoryA(nTempLen, szaTemp) > 0)
	{
		strcat_s(a_szaSymbolSearchPath, a_uMaxSize, szaTemp);
		strcat_s(a_szaSymbolSearchPath, a_uMaxSize, ";");
	}

	// Now add the path for the main-module:
	if (GetModuleFileNameA(NULL, szaTemp, nTempLen) > 0)
	{
		for (azCharA *p = (szaTemp + strlen(szaTemp)-1); p >= szaTemp; --p)
		{
			// locate the rightmost path separator
			if ((*p == '\\') || (*p == '/') || (*p == ':'))
			{
				*p = 0;
				break;
			}
		}  // for (search for path separator...)
		if (strlen(szaTemp) > 0)
		{
			strcat_s(a_szaSymbolSearchPath, a_uMaxSize, szaTemp);
			strcat_s(a_szaSymbolSearchPath, a_uMaxSize, ";");
		}
	}
	if (GetEnvironmentVariableA("_NT_SYMBOL_PATH", szaTemp, nTempLen) > 0)
	{
		strcat_s(a_szaSymbolSearchPath, a_uMaxSize, szaTemp);
		strcat_s(a_szaSymbolSearchPath, a_uMaxSize, ";");
	}
	if (GetEnvironmentVariableA("_NT_ALTERNATE_SYMBOL_PATH", szaTemp, nTempLen) > 0)
	{
		strcat_s(a_szaSymbolSearchPath, a_uMaxSize, szaTemp);
		strcat_s(a_szaSymbolSearchPath, a_uMaxSize, ";");
	}
	if (GetEnvironmentVariableA("SYSTEMROOT", szaTemp, nTempLen) > 0)
	{
		strcat_s(a_szaSymbolSearchPath, a_uMaxSize, szaTemp);
		strcat_s(a_szaSymbolSearchPath, a_uMaxSize, ";");
		// also add the "system32"-directory:
		strcat_s(szaTemp, nTempLen, "\\system32");
		strcat_s(a_szaSymbolSearchPath, a_uMaxSize, szaTemp);
        strcat_s(a_szaSymbolSearchPath, a_uMaxSize, ";");
	}

	if (GetEnvironmentVariableA("SYSTEMDRIVE", szaTemp, nTempLen) > 0)
	{
		strcat_s(a_szaSymbolSearchPath, a_uMaxSize, "SRV*");
		strcat_s(a_szaSymbolSearchPath, a_uMaxSize, szaTemp);
		strcat_s(a_szaSymbolSearchPath, a_uMaxSize, "\\websymbols");
		strcat_s(a_szaSymbolSearchPath, a_uMaxSize, "*http://msdl.microsoft.com/download/symbols;");
	}
	else
	{
		strcat_s(a_szaSymbolSearchPath, a_uMaxSize, "SRV*oContext:\\websymbols*http://msdl.microsoft.com/download/symbols;");
	}
}

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
void azStackWalker::BuildCallStack(azCallStack& a_rCallStack)
{
	// 1. Retrieve context
	CONTEXT oContext;
	memset(&oContext, 0, sizeof(CONTEXT));
	oContext.ContextFlags = CONTEXT_CONTROL;
	RtlCaptureContext(&oContext);

	// 2. Fill oStackFrame
	// Small structure defining an entry in the callstack
	struct azCallStackEntryMemoryFootprint
	{
		azCallStackEntryMemoryFootprint* m_pFramePointer;
		void* m_pInstructionPointer;
	};
#ifdef _M_X64
	azCallStackEntryMemoryFootprint* pCallStackWalker = (azCallStackEntryMemoryFootprint*)(void*)oContext.Rsp;
#elif defined(_M_IX86)
	azCallStackEntryMemoryFootprint* pCallStackWalker = (azCallStackEntryMemoryFootprint*)(void*)oContext.Esp;
#endif
	pCallStackWalker--;

	// 3. Retrieve symbol
	for(int uFrameIndex = 0; ; ++uFrameIndex)
	{
		// This can happen when running an extern command
		if (pCallStackWalker <= (void*)(0x01))
		{
			break;
		}

		if((pCallStackWalker->m_pFramePointer == NULL)) // || (a_rCallStack.GetLength() >= a_rCallStack.GetMaxLength()))
		{
			break;
		}

		if ((pCallStackWalker->m_pInstructionPointer != NULL)) // && (uFrameIndex >= a_rOut.GetSkipCount()))
		{
			azCallStackEntry oEntry;
			oEntry.m_pInstructionPointer = pCallStackWalker->m_pInstructionPointer;
			a_rCallStack.PushEntry(oEntry);
		}

		pCallStackWalker = pCallStackWalker->m_pFramePointer;
	}
}

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
void azCallStackEntry::Decode(azCallStackDecodedEntry& a_rEntry) const
{
	DWORD64 dw64ProgramCounter = (DWORD64)m_pInstructionPointer;
	HANDLE hProcess = GetCurrentProcess();

	// a. Get method info (SymGetSymFromAddr64())
	IMAGEHLP_SYMBOL64 *pSymbolInfo = (IMAGEHLP_SYMBOL64 *) alloca(sizeof(IMAGEHLP_SYMBOL64) + c_uStackWalkerMaxNameLength);
	memset(pSymbolInfo, 0, sizeof(IMAGEHLP_SYMBOL64) + c_uStackWalkerMaxNameLength);
	pSymbolInfo->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL64);
	pSymbolInfo->MaxNameLength = c_uStackWalkerMaxNameLength;

	DWORD64 dw64OffsetFromSymbol = 0;
	BOOL bRes = azDbgHelpDllWrapper::GetInstance().m_pfnSymGetSymFromAddr64(hProcess, dw64ProgramCounter, &dw64OffsetFromSymbol, pSymbolInfo);
	if(bRes == TRUE)
	{
		strcpy_s(a_rEntry.m_szMethodName, pSymbolInfo->Name);
	}
	else
	{
		strcpy_s(a_rEntry.m_szMethodName, azL("Symbol not found"));
		//agePrint("SymGetSymFromAddr64 failed : error code %d", GetLastError());
	}

	// b. Get line number info (SymGetLineFromAddr64())
	IMAGEHLP_LINE64 oLine;
	memset(&oLine, 0, sizeof(oLine));
	oLine.SizeOfStruct = sizeof(oLine);

	DWORD dwOffsetFromLine = 0;
	bRes = azDbgHelpDllWrapper::GetInstance().m_pfnSymGetLineFromAddr64(hProcess, dw64ProgramCounter, &dwOffsetFromLine, &oLine);
	if (bRes == TRUE)
	{
		a_rEntry.m_uLineNumber = oLine.LineNumber;
		strcpy_s(a_rEntry.m_szFileName, oLine.FileName);
	}
	else
	{
		a_rEntry.m_uLineNumber = 0;
		strcpy_s(a_rEntry.m_szFileName, azL("Source file not found"));
		//agePrint("SymGetLineFromAddr64 failed : error code %d", GetLastError());
	}
}

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
void azCallStack::PushEntry(azCallStackEntry const& a_rEntry)
{
	m_vEntries.push_back(a_rEntry);
}

//-------------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------------
void azCallStack::Dump() const
{
	for (azEntries::const_iterator it = m_vEntries.begin(); it != m_vEntries.end(); it++)
	{
		azCallStackEntry const& rEntry = (*it);
		azCallStackDecodedEntry oDecodedEntry;
		rEntry.Decode(oDecodedEntry);
		azPrint("%s (%d): %s", oDecodedEntry.m_szFileName, oDecodedEntry.m_uLineNumber, oDecodedEntry.m_szMethodName);
	}
}

