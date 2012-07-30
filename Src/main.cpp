#include <windows.h>
#include "azMain.h"
#include "azIApplication.h"

// \class azMyApplication
// \brief An application
class azMyApplication : public azIApplication
{
public:
	// \brief Initialize application
	virtual void Initialize()
	{
		azIApplication::Initialize();
	}

	// \brief Update application
	virtual void Update()
	{
		azIApplication::Update();
	}

	// \brief Terminate application
	virtual void Terminate()
	{
		azIApplication::Terminate();
	}
};

// \brief Main
INT WINAPI WinMain(HINSTANCE Instance, HINSTANCE PrevInst, LPSTR CmdLine, INT NbCmd)
{
	azMain oMain;

	azMyApplication oApplication;
	oMain.Run(oApplication);

	return 0;
}
