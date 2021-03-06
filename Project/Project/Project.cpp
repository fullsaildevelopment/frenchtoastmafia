/************************************************************************
* Filename:  		Project.cpp
* Date:      		02/10/2018
* Mod. Date: 		09/10/2018
* Mod. Initials:	WM
* Author:    		Wichet Manawanitjarern
* Purpose:   		Main entry point of the program and location of Game Loop
*************************************************************************/

// Project.cpp : Defines the entry point for the application.
//
//#include "vld.h"
//#include <Windows.h>
#include "header.h"
#include "Project.h"
#include "Game_Loop.h"
#include "Graphic_Setup.h"
#include "VR_Setup.h"
#include "dopeSoundSystem.h"

#include <stdio.h>
#include <DbgHelp.h>
//#pragma comment (lib, "dbdhelp.lib")

#define MAX_LOADSTRING 100

#ifdef _RELEASE
LONG WINAPI errorFunc(_EXCEPTION_POINTERS *pExceptionInfo)
{
	/*
	This will give you a date/time formatted string for your dump files
	Make sure to include these files:
	#include &lt;stdio.h&gt;
	#include &lt;DbgHelp.h&gt;
	#include &lt;time.h&gt;
	AND this lib:
	dbghelp.lib
	*/
	struct tm newTime;
	time_t ltime;
	wchar_t buff[100] = { 0 };
	ltime = time(&ltime);
	localtime_s(&newTime, &ltime);
	wcsftime(buff, sizeof(buff), L"%A_%b%d_%I%M%p.mdmp", &newTime);
	HANDLE hFile = ::CreateFileW(/*L&quot;dumpfile.mdmp&quot;*/buff, GENERIC_WRITE,
		FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		_MINIDUMP_EXCEPTION_INFORMATION ExInfo;
		ExInfo.ThreadId = ::GetCurrentThreadId();
		ExInfo.ExceptionPointers = pExceptionInfo;
		ExInfo.ClientPointers = NULL;
		MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile,

			MiniDumpNormal, &ExInfo, NULL, NULL);

		//MessageBox(&quot;Dump File Saved look x directory please email to developer at
		//the following email adress crashdmp@gmail.com with the subject Gamename - Version & quot;);

		::CloseHandle(hFile);
	}
	return 0;
}
#endif

// Global Variables:
HWND hWnd;
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

#ifndef NDEBUG
	AllocConsole();
	FILE* new_std_in_out;
	freopen_s(&new_std_in_out, "CONOUT$", "w", stdout);
	freopen_s(&new_std_in_out, "CONIN$", "r", stdin);
	std::cout << "Hello world!\n";
#endif // NDEBUG

	//set up the function to create the dump file
#ifdef _RELEASE	
	SetUnhandledExceptionFilter(errorFunc);
#endif


    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PROJECT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROJECT));
	
    MSG msg;
	cGraphics_Setup cGSetup(hWnd);
	cGSetup.Initialize();

	cVR_Setup cVSetup;
	cVSetup.Initialize();

	cGame_Loop cGame;
	cGame.Initialize(&cGSetup, &cVSetup);

	cGame.Setup();

    // Main message loop:
	while (true)
	{
		
		// Process all messages, stop on WM_QUIT
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// WM_QUIT does not need to be
			// translated or dispatched
			if (msg.message == WM_QUIT)
				break;
			// Translates messages and sends them
			// to WndProc
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// In the future, do per frame/tick updates here...
			cGame.Update();
		}
	}
	cGame.Clean_Up();
    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROJECT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (GetAsyncKeyState(VK_ESCAPE))
		message = WM_DESTROY;

	switch (message)
	{
	case WM_CLOSE:
	case WM_DESTROY:
	{
		//FreeConsole();
		PostQuitMessage(0);
	}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
    return 0;
}