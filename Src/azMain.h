#ifndef __azMain__
#define __azMain__

#include "azCommon.h"
#include <windows.h>

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
	HWND GetWindow() { return m_hWindow; }

private:
	// \brief Create main window
	void CreateMainWindow();

	// \brief Destroy main window
	void DestroyMainWindow();

	// \brief Callback handling window messages
	//static LRESULT CALLBACK GlobalWindowProc(HWND a_hWindow, azUInt a_uMessage, WPARAM a_WParam, LPARAM a_LParam);


	// As exit at the end of the loop been requested
	bool m_bIsExitRequested;

	// Current application
	azIApplication* m_pApplication;

	// Unique main pointer
	static azMain* s_pMainInstance;


	// Application instance
	HINSTANCE m_hInstance;

	// Window handle
	HWND m_hWindow;      

};

#endif // __azMain__
