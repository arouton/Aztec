#ifndef __azMain__
#define __azMain__

#include "azCommon.h"

class azIApplication;

// \class azMain
// \brief Abstraction of the main
class AZ_API azMain
{
public:
	// \brief Default constructor
	azMain();

	// \brief Destructor
	~azMain();


	// \brief Run application
	void Run(azIApplication& a_rApplication);

	// \brief Request exit of current application at the end of the loop
	void RequestExit();

	// \brief Get the unique main instance
	static azMain* GetInstance();


	// \brief Get Window handle
	azWinHandle GetWindowHandle() { return m_hWindow; }

    azFloat m_fX;
    azFloat m_fY;
    azFloat m_fZ;

private:
	// \brief Create main window
	void CreateMainWindow();

	// \brief Destroy main window
	void DestroyMainWindow();


	// As exit at the end of the loop been requested
	bool m_bIsExitRequested;

	// Current application
	azIApplication* m_pApplication;

	// Unique main pointer
	static azMain* s_pMainInstance;


	// Application instance
	azWinHandle m_hInstance; // HINSTANCE

	// Window handle
	azWinHandle m_hWindow; // HWND

};

#endif // __azMain__
