#ifndef __azStackWalker__
#define __azStackWalker__

#include "azCommon.h"
#include <vector>

// Max name length for found symbols
static const azUInt c_uStackWalkerMaxNameLength = 1024;

class azCallStackDecodedEntry
{
public:
	char m_szMethodName[c_uStackWalkerMaxNameLength];
	char m_szFileName[c_uStackWalkerMaxNameLength];
	azUInt m_uLineNumber;
};

class azCallStackEntry
{
public:
	void Decode(azCallStackDecodedEntry& a_rEntry) const;
	void* m_pInstructionPointer;
};

class azCallStack
{
public:
	azCallStack() {}

	azCallStack(azCallStack const& a_rCallStack)
		: m_vEntries(a_rCallStack.m_vEntries)
	{}

	void PushEntry(azCallStackEntry const& a_rEntry);
	void Dump() const;

protected:
	typedef std::vector<azCallStackEntry> azEntries;
	azEntries m_vEntries;
};

class azStackWalker
{
public:
	// Singleton access
	static azStackWalker& GetInstance() { static azStackWalker oWalker; return oWalker; }

	// Build callStack
	void BuildCallStack(azCallStack& a_rCallStack);

private:
	// Constructor / Destructor
	azStackWalker();
	~azStackWalker();

	void Initialize();
	void Terminate();
		
	void BuildSymbolSearchPath(char* a_szSymbolSearchPath, azUInt a_uMaxSize) const;

	void LoadModules();
	azBool LoadModulesToolHelp32();
	azBool LoadModulesPSAPI();
};

#endif // __azStackWalker__