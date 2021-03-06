#include "azMain.h"
#include "azIApplication.h"
#include <windows.h>

azMain* azMain::s_pMainInstance = NULL;

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
LRESULT CALLBACK azGlobalWindowProc(HWND a_hWindow, UINT a_uMessage, WPARAM a_WParam, LPARAM a_LParam)
{
	switch (a_uMessage)
	{
		// Window destruction : exit
		case WM_DESTROY:
		{
			azMain* pMainInstance = azMain::GetInstance();
			azAssert(pMainInstance != NULL, "Main has no instance");
			pMainInstance->RequestExit();
			return 0;
		}

        // Window resize
        case WM_SIZE:
        {
            //
        }

		// Key stroke
		case WM_KEYDOWN:
		{
            switch (LOWORD(a_WParam))
            {
                // Escape : exit
            case VK_ESCAPE:
                {
                    azMain* pMainInstance = azMain::GetInstance();
                    azAssert(pMainInstance != NULL, "Main has no instance");
                    pMainInstance->RequestExit();
                    break;
                }
            case VK_F1 :
                {
                    break;
                }
            case VK_UP :
                {
                    azMain::GetInstance()->m_fX += 0.1f;
                    break;
                }
            case VK_DOWN :
                {
                    azMain::GetInstance()->m_fX -= 0.1f;
                    break;
                }
            case VK_LEFT :
                {
                    azMain::GetInstance()->m_fY += 0.1f;
                    break;
                }
            case VK_RIGHT :
                {
                    azMain::GetInstance()->m_fY -= 0.1f;
                    break;
                }
            case VK_HOME :
                {
                    azMain::GetInstance()->m_fZ += 0.1f;
                    break;
                }
            case VK_END :
                {
                    azMain::GetInstance()->m_fZ -= 0.1f;
                    break;
                }
            }
			return 0;
		}

		// Character
		case WM_CHAR :
		{
			//Console.SendChar(static_cast<char>(LOWORD(a_WParam)));
			return 0;
		}
	}

	return DefWindowProc(a_hWindow, a_uMessage, a_WParam, a_LParam);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
azMain::azMain()
	: m_bIsExitRequested(false)
	, m_pApplication(NULL)
	, m_hInstance(NULL)
	, m_hWindow(NULL)
    , m_fX(0.f)
    , m_fY(0.f)
    , m_fZ(0.f)
{
	azAssert(s_pMainInstance == NULL, "Main has already an instance");
	s_pMainInstance = this;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
azMain::~azMain()
{
	azAssert(s_pMainInstance != NULL, "Main instance was already deleted");
	s_pMainInstance = NULL;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
azMain* azMain::GetInstance()
{
	return s_pMainInstance;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azMain::Run(azIApplication& a_rApplication)
{
	azAssert(s_pMainInstance != NULL, "Static Main instance is not properly set");

	CreateMainWindow();

	a_rApplication.Initialize();
	m_bIsExitRequested = false;

    MSG oMessage;
    while (!m_bIsExitRequested)
    {
        if (PeekMessage(&oMessage, NULL, 0, 0, PM_REMOVE))
        {
            // Handling Windows messages
            TranslateMessage(&oMessage);
            DispatchMessage(&oMessage);
        }
        else
        {
            // Update scene
            a_rApplication.Update();
        }
    }

	a_rApplication.Terminate();

	DestroyMainWindow();
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azMain::RequestExit()
{
    m_bIsExitRequested = true;
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azMain::CreateMainWindow()
{
	azAssert(m_hWindow == NULL, "Main window already created");

	// Make sure the window is centered
	const azInt iWidth = 800;
	const azInt iHeight = 600;
	const azInt iLeft = (GetDeviceCaps(GetDC(NULL), HORZRES) - iWidth)  / 2;
	const azInt iTop = (GetDeviceCaps(GetDC(NULL), VERTRES) - iHeight) / 2;

	// Window definition
	WNDCLASSEX oWindowClass;
	oWindowClass.cbSize = sizeof(WNDCLASSEX);
	oWindowClass.style = 0;
	oWindowClass.lpfnWndProc = azGlobalWindowProc;
	oWindowClass.cbClsExtra = 0;
	oWindowClass.cbWndExtra = 0;
	oWindowClass.hInstance = (HINSTANCE)m_hInstance;
	oWindowClass.hIcon = NULL;
	oWindowClass.hCursor = 0;
	oWindowClass.hbrBackground = 0;
	oWindowClass.lpszMenuName = NULL;
	oWindowClass.lpszClassName = azL("Aztec");
	oWindowClass.hIconSm = NULL;

	RegisterClassEx(&oWindowClass);

	// Window creation
	m_hWindow = CreateWindow(azL("Aztec"), azL("Prototype"), WS_OVERLAPPEDWINDOW , iLeft, iTop, iWidth, iHeight, NULL, NULL, (HINSTANCE)m_hInstance, NULL);
	azAssert(m_hWindow != NULL, "Couldn't create window");
	ShowWindow((HWND)m_hWindow, SW_NORMAL);
}

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
void azMain::DestroyMainWindow()
{
    if (m_hWindow != NULL)
    {
        DestroyWindow((HWND)m_hWindow);
        UnregisterClass(azL("Aztec"), (HINSTANCE)m_hInstance);
    }
}