// AdeethyiaShankarEXELibrary.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "AdeethyiaShankarEXELibrary.h"
#include <string>
#include <shellapi.h>
#include <Windows.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
HINSTANCE hInstSettings;						// Settings instance
HINSTANCE hCC{}, hCTC{}, hGTN{}, hRPS{}, hTE{};	// Button instances								
HWND hWCC, hWCTC, hWGTN, hWRPS, hWTE;			// Button handles
HWND hCheckmark1;								// Settings checkmark button handle
HWND hSettings;									// "Settings"
HWND hMsgTxt;									// "Message"
HWND hTitleTxt;									// "Title"
HWND hIconTxt;									// "Icon"
HWND hButtonsTxt;								// "Buttons"
HWND hWA;										// "Adeethyia Shankar's EXE Library" handle
HWND hInfo;										// Edit control under EXE buttons
HWND hTitle;									// MessageBox Title Edit handle
HWND hMsg;										// MessageBox Message Edit handle
HWND hIcon;										// MessageBox Icon ComboBox handle
HWND hButton;									// MessageBox Button ComboBox handle
HBITMAP hBitmap;								// "Adeethyia" bitmap
HBITMAP hCheckmark;								// Checkmark bitmap
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
std::wstring title = L"";						// Title for MessageBox
std::wstring msg = L"";							// Message for MessageBox
UINT icon = MB_OK;								// Icon for MessageBox
UINT button = MB_OK;							// Buttons for MessageBox
LRESULT geticon = 0;							// Gets selected ComboBox index
LRESULT getbutton = 0;							// Gets selected ComboBox index
bool settings = false;							// Whether settings is open

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
ATOM				SettingsRegisterClass(HINSTANCE);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    SettingsWndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ADEETHYIASHANKAREXELIBRARY, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ADEETHYIASHANKAREXELIBRARY));

	SettingsRegisterClass(hInstance);

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ADEETHYIA));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_ADEETHYIASHANKAREXELIBRARY);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ADEETHYIA));

    return RegisterClassExW(&wcex);
}

ATOM SettingsRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = SettingsWndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = 0;
	wcex.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ADEETHYIA));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_SETTINGS);
	wcex.lpszClassName = L"Message Box Wizard";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ADEETHYIA));

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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
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
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT window;
	GetClientRect(hWnd, &window);
	PROCESS_INFORMATION processInformation = { 0 };
	STARTUPINFO startupInfo = { 0 };
	startupInfo.cb = sizeof(startupInfo);
	bool startEXE = false;
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBoxW(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
			case IDM_SETTINGS:
				if (!settings)
				{
					HWND hWSettings = CreateWindowW(L"Message Box Wizard", L"Message Box Wizard", WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInst, nullptr);
	
					if (!hWSettings)
					{
						int nResult = GetLastError();
						MessageBox(NULL,
							L"Window class creation failed for window 2",
							L"Window Class Failed",
							MB_ICONERROR);
						break;
					}

					ShowWindow(hWSettings, 1);
					settings = true;
	
					HACCEL hAccelTable = LoadAccelerators(hInst, MAKEINTRESOURCE(IDC_ADEETHYIASHANKAREXELIBRARY));

					MSG msg;

					// Main message loop:
					while (GetMessage(&msg, nullptr, 0, 0) && settings)
					{
						if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
						{
							TranslateMessage(&msg);
							DispatchMessage(&msg);
						}
					}
				}
				else
				{
					MessageBoxW(hWnd, L"Message Box Wizard is already open", L"Message Box Wizard", MB_ICONINFORMATION);
				}
				break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
			case IDM_CAESARCIPHER:
				startEXE = CreateProcess(L"CaesarCipher.exe", NULL, NULL, NULL, false, NORMAL_PRIORITY_CLASS, NULL, NULL, &startupInfo, &processInformation);
				CloseHandle(processInformation.hThread);
				CloseHandle(processInformation.hProcess);
				if (startEXE)
				{
					SetWindowTextW(hInfo, L"Executed Caesar Cipher");
				}
				else
				{
					SetWindowTextW(hInfo, L"Could not execute Caesar Cipher");
				}
				break;
			case IDM_COLLECTTHECOINS:
				startEXE = CreateProcess(L"CollectTheCoins.exe", NULL, NULL, NULL, false, NORMAL_PRIORITY_CLASS, NULL, NULL, &startupInfo, &processInformation);
				CloseHandle(processInformation.hThread);
				CloseHandle(processInformation.hProcess);
				if (startEXE)
				{
					SetWindowTextW(hInfo, L"Executed Collect The Coins");
				}
				else
				{
					SetWindowTextW(hInfo, L"Could not execute Collect The Coins");
				}
				break;
			case IDM_GUESSTHENUMBER:
				startEXE = CreateProcess(L"GuessTheNumber.exe", NULL, NULL, NULL, false, NORMAL_PRIORITY_CLASS, NULL, NULL, &startupInfo, &processInformation);
				CloseHandle(processInformation.hThread);
				CloseHandle(processInformation.hProcess);
				if (startEXE)
				{
					SetWindowTextW(hInfo, L"Executed Guess The Number");
				}
				else
				{
					SetWindowTextW(hInfo, L"Could not execute Guess The Number");
				}
				break;
			case IDM_ROCKPAPERSCISSORS:
				startEXE = CreateProcess(L"RockPaperScissors.exe", NULL, NULL, NULL, false, NORMAL_PRIORITY_CLASS, NULL, NULL, &startupInfo, &processInformation);
				CloseHandle(processInformation.hThread);
				CloseHandle(processInformation.hProcess);
				if (startEXE)
				{
					SetWindowTextW(hInfo, L"Executed Rock Paper Scissors");
				}
				else
				{
					SetWindowTextW(hInfo, L"Could not execute Rock Paper Scissors");
				}
				break;
			case IDM_TEXTEDITOR:
				startEXE = CreateProcess(L"TextEditor.exe", NULL, NULL, NULL, false, NORMAL_PRIORITY_CLASS, NULL, NULL, &startupInfo, &processInformation);
				CloseHandle(processInformation.hThread);
				CloseHandle(processInformation.hProcess);
				if (startEXE)
				{
					SetWindowTextW(hInfo, L"Executed Text Editor");
				}
				else
				{
					SetWindowTextW(hInfo, L"Could not execute Text Editor");
				}
				break;
			case IDM_VISITWEBSITE:
				startEXE = ShellExecute(0, 0, L"https://sites.google.com/view/adeethyiashankarexelibrary", 0, 0, SW_SHOW);
				if (startEXE)
				{
					SetWindowTextW(hInfo, L"Website reached");
				}
				else
				{
					SetWindowTextW(hInfo, L"Could not reach website");
				}
				break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_CREATE:
		hWCC = CreateWindowExW(0L, L"Button", L"Caesar Cipher", WS_VISIBLE | WS_CHILD, (int)4 * window.right / 32, (int)1 * window.bottom / 4, (int)window.right / 8, (int)window.bottom / 20, hWnd, (HMENU)IDM_CAESARCIPHER, hCC, NULL);
		hWCTC = CreateWindowExW(0L, L"Button", L"Collect The Coins", WS_VISIBLE | WS_CHILD, (int)9 * window.right / 32, (int)1 * window.bottom / 4, (int)window.right / 8, (int)window.bottom / 20, hWnd, (HMENU)IDM_COLLECTTHECOINS, hCTC, NULL);
		hWGTN = CreateWindowExW(0L, L"Button", L"Guess The Number", WS_VISIBLE | WS_CHILD, (int)14 * window.right / 32, (int)1 * window.bottom / 4, (int)window.right / 8, (int)window.bottom / 20, hWnd, (HMENU)IDM_GUESSTHENUMBER, hGTN, NULL);
		hWRPS = CreateWindowExW(0L, L"Button", L"Rock Paper Scissors", WS_VISIBLE | WS_CHILD, (int)19 * window.right / 32, (int)1 * window.bottom / 4, (int)window.right / 8, (int)window.bottom / 20, hWnd, (HMENU)IDM_ROCKPAPERSCISSORS, hRPS, NULL);
		hWTE = CreateWindowExW(0L, L"Button", L"Text Editor", WS_VISIBLE | WS_CHILD, (int)24 * window.right / 32, (int)1 * window.bottom / 4, (int)window.right / 8, (int)window.bottom / 20, hWnd, (HMENU)IDM_TEXTEDITOR, hTE, NULL);
		hWA = CreateWindowExW(0L, L"static", L"Adeethyia Shankar's EXE Library", WS_VISIBLE | WS_CHILD | ES_CENTER | ES_AUTOVSCROLL, 0, 0, (int)window.right, (int)1 * window.bottom / 4, hWnd, NULL, NULL, NULL);
		hInfo = CreateWindowExW(0L, L"Edit", L"", WS_VISIBLE | WS_CHILD | ES_CENTER, window.right / 4, 2 * window.bottom / 4, (int)2 * window.right / 4, (int)1 * window.bottom / 4, hWnd, NULL, NULL, NULL);
		//MessageBoxW(hWnd, L"Please press the Help button in each of the applications", L"If you need help", MB_ICONINFORMATION);
		break;
    case WM_PAINT:
        {
			if (window.right < 1000)
			{
				SetWindowTextW(hWCC, L"CC");
				SetWindowTextW(hWCTC, L"CTC");
				SetWindowTextW(hWGTN, L"GTN");
				SetWindowTextW(hWRPS, L"RPS");
				SetWindowTextW(hWTE, L"TE");
			}
			else if (window.right >= 1000)
			{
				SetWindowTextW(hWCC, L"Caesar Cipher");
				SetWindowTextW(hWCTC, L"Collect The Coins");
				SetWindowTextW(hWGTN, L"Guess The Number");
				SetWindowTextW(hWRPS, L"Rock Paper Scissors");
				SetWindowTextW(hWTE, L"Text Editor");
			}
			int length = window.right > window.bottom ? window.bottom : window.right;
			int font = 95 * length / 500;
			if (font > 200)
				font = 200;
			else if (font > 150)
				font = 150;
			else if (font > 100)
				font = 100;
			else if (font > 50)
				font = 50;
			else
				font = 30;
			HFONT hFont = CreateFont(font, 0, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE, UNICODE, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Calibri");
			HFONT hFont1 = CreateFont(font / 3, 0, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE, UNICODE, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Calibri");
			SendMessage(hWA, WM_SETFONT, WPARAM(hFont), TRUE);
			SendMessage(hInfo, WM_SETFONT, WPARAM(hFont1), TRUE);
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			hBitmap = LoadBitmapW(hInst, MAKEINTRESOURCE(IDC_ADEETHYIASHANKAREXELIBRARY));
			// TODO: Add any drawing code that uses hdc here...
			BITMAP                     bm;
			GetObject(hBitmap, sizeof(bm), &bm);
			HDC     hdcFrom = CreateCompatibleDC(hdc);
			HBITMAP bmpTo = CreateCompatibleBitmap(hdc, window.bottom / 10, window.bottom / 10);
			HGDIOBJ hobFrom = SelectObject(hdcFrom, hBitmap);
			HGDIOBJ hobTo = SelectObject(hdc, bmpTo);

			StretchBlt(hdc, 0, 9 * window.bottom / 10, window.bottom / 10, window.bottom / 10,
				hdcFrom, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);

			SelectObject(hdcFrom, hobFrom);
			SelectObject(hdc, hobTo);

			DeleteObject(hBitmap);

			ReleaseDC(hWnd, hdc);
			DeleteDC(hdcFrom);
			DeleteDC(hdc);
			EndPaint(hWnd, &ps);
        }
        break;
	case WM_CTLCOLORSTATIC:
		if ((HWND)lParam == hWA)
		{
			HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
			HDC hdcStatic = (HDC)wParam;
			SetTextColor(hdcStatic, RGB(0, 0, 0));
			SetBkColor(hdcStatic, RGB(255, 255, 255));
			return (INT_PTR)hBrush;
		}
		break;
	case WM_SIZE:
		MoveWindow(hWCC, (int)4 * window.right / 32, (int)1 * window.bottom / 4, (int)window.right / 8, (int)max(window.bottom / 20, 20), true);
		MoveWindow(hWCTC, (int)9 * window.right / 32, (int)1 * window.bottom / 4, (int)window.right / 8, (int)max(window.bottom / 20, 20), true);
		MoveWindow(hWGTN, (int)14 * window.right / 32, (int)1 * window.bottom / 4, (int)window.right / 8, (int)max(window.bottom / 20, 20), true);
		MoveWindow(hWRPS, (int)19 * window.right / 32, (int)1 * window.bottom / 4, (int)window.right / 8, (int)max(window.bottom / 20, 20), true);
		MoveWindow(hWTE, (int)24 * window.right / 32, (int)1 * window.bottom / 4, (int)window.right / 8, (int)max(window.bottom / 20, 20), true);
		MoveWindow(hWA, 0, 0, (int)window.right, (int)1 * window.bottom / 4, true);
		MoveWindow(hInfo, window.right / 4, 2 * window.bottom / 4, (int)2 * window.right / 4, (int)1 * window.bottom / 4, true);
		return DefWindowProc(hWnd, message, wParam, lParam);
    case WM_DESTROY:
		DeleteObject(hBitmap);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK SettingsWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT window;
	GetClientRect(hWnd, &window);
	if (GetActiveWindow() != hWnd)
	{
		settings = false;
	}
	switch (message)
	{
		case WM_COMMAND:
		{
			if (HIWORD(wParam) == CBN_SELCHANGE)
			{
				getbutton = SendMessage((HWND)hButton, (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				switch (getbutton)
				{
				case 0:
					button = MB_OK;
					break;
				case 1:
					button = MB_OKCANCEL;
					break;
				case 2:
					button = MB_YESNO;
					break;
				case 3:
					button = MB_YESNOCANCEL;
					break;
				case 4:
					button = MB_RETRYCANCEL;
					break;
				case 5:
					button = MB_ABORTRETRYIGNORE;
					break;
				case 6:
					button = MB_CANCELTRYCONTINUE;
					break;
				}
				geticon = SendMessage((HWND)hIcon, (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				switch (geticon)
				{
				case 0:
					icon = button | MB_ICONINFORMATION;
					break;
				case 1:
					icon = button | MB_ICONERROR;
					break;
				case 2:
					icon = button | MB_ICONWARNING;
					break;
				case 3:
					icon = button | MB_ICONQUESTION;
					break;
				case 4:
					icon = button;
					break;
				}
				break;
			}
			int wmId = LOWORD(wParam);
			switch (wmId)
			{
				case ID_FILE_EXIT:
					DestroyWindow(hCheckmark1);
					DestroyWindow(hWnd);
					break;
				case ID_MESSAGEBOX_CREATOR:
				{
					getbutton = SendMessage((HWND)hButton, (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					switch (getbutton)
					{
					case 0:
						button = MB_OK;
						break;
					case 1:
						button = MB_OKCANCEL;
						break;
					case 2:
						button = MB_YESNO;
						break;
					case 3:
						button = MB_YESNOCANCEL;
						break;
					case 4:
						button = MB_RETRYCANCEL;
						break;
					case 5:
						button = MB_ABORTRETRYIGNORE;
						break;
					case 6:
						button = MB_CANCELTRYCONTINUE;
						break;
					}
					geticon = SendMessage((HWND)hIcon, (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
					switch (geticon)
					{
					case 0:
						icon = button | MB_ICONINFORMATION;
						break;
					case 1:
						icon = button | MB_ICONERROR;
						break;
					case 2:
						icon = button | MB_ICONWARNING;
						break;
					case 3:
						icon = button | MB_ICONQUESTION;
						break;
					case 4:
						icon = button;
						break;
					}
					wchar_t m[1000];
					wchar_t t[1000];
					GetWindowText(hMsg, m, 1000);
					msg = std::wstring(m);
					GetWindowText(hTitle, t, 1000);
					title = std::wstring(t);
					MessageBoxW(hWnd, msg.c_str(), title.c_str(), icon);
					break;
				}
				case ID_SETTINGS_HELP:
					SetWindowText(hMsg, L"Hello from Adeethyia Shankar's EXE Library");
					SetWindowText(hTitle, L"Hello");
					SendMessage(hWnd, (UINT)WM_COMMAND, (WPARAM)ID_MESSAGEBOX_CREATOR, (LPARAM)0);
					break;
				default:
					return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		}
		case WM_CREATE:
		{
			hCheckmark = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_CHECKMARK));
			hSettings = CreateWindowExW(0L, L"static", L"Message Box Wizard", WS_VISIBLE | WS_CHILD | ES_CENTER | ES_AUTOVSCROLL, 0, 0, window.right, window.bottom / 4, hWnd, NULL, NULL, NULL);
			hMsg = CreateWindowExW(0L, L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE, 0 * window.right / 5, window.bottom / 4, window.bottom / 5, window.bottom / 5, hWnd, NULL, NULL, NULL);
			hTitle = CreateWindowExW(0L, L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE, 1 * window.right / 5, window.bottom / 4, window.bottom / 5, window.bottom / 5, hWnd, NULL, NULL, NULL);
			hMsgTxt = CreateWindowExW(0L, L"static", L"Message", WS_VISIBLE | WS_CHILD | ES_CENTER | ES_AUTOVSCROLL, 0, 2 * window.bottom / 4, window.bottom / 4, window.bottom / 8, hWnd, NULL, NULL, NULL);
			hTitleTxt = CreateWindowExW(0L, L"static", L"Title", WS_VISIBLE | WS_CHILD | ES_CENTER | ES_AUTOVSCROLL, window.right / 4, 2 * window.bottom / 4, window.bottom / 4, window.bottom / 8, hWnd, NULL, NULL, NULL);
			hIconTxt = CreateWindowExW(0L, L"static", L"Icon", WS_VISIBLE | WS_CHILD | ES_CENTER | ES_AUTOVSCROLL, 2 * window.right / 4, 2 * window.bottom / 4, window.bottom / 4, window.bottom / 8, hWnd, NULL, NULL, NULL);
			hButtonsTxt = CreateWindowExW(0L, L"static", L"Buttons", WS_VISIBLE | WS_CHILD | ES_CENTER | ES_AUTOVSCROLL, window.bottom / 4, 2 * window.bottom / 4, window.bottom / 4, window.bottom / 8, hWnd, NULL, NULL, NULL);
			hIcon = CreateWindowExW(0L, L"ComboBox", L"", WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_VSCROLL, 2 * window.right / 5, window.bottom / 4, window.bottom / 5, window.bottom / 5, hWnd, NULL, NULL, NULL);
			hButton = CreateWindowExW(0L, L"ComboBox", L"", WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_VSCROLL, 3 * window.right / 5, window.bottom / 4, window.bottom / 5, window.bottom / 5, hWnd, NULL, NULL, NULL);
			hCheckmark1 = CreateWindowExW(0L, L"Button", L"Create", WS_VISIBLE | WS_CHILD, 4 * window.right / 5, window.bottom / 4, window.bottom / 4, window.bottom / 5, hWnd, (HMENU)ID_MESSAGEBOX_CREATOR, NULL, NULL);
			SendMessage(hIcon, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)L"Information");
			SendMessage(hIcon, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)L"Error");
			SendMessage(hIcon, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)L"Warning");
			SendMessage(hIcon, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)L"Question");
			SendMessage(hIcon, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)L"None");
			SendMessage(hIcon, (UINT)CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
			SendMessage(hButton, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)L"OK");
			SendMessage(hButton, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)L"OK Cancel");
			SendMessage(hButton, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)L"Yes No");
			SendMessage(hButton, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)L"Yes No Cancel");
			SendMessage(hButton, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)L"Retry Cancel");
			SendMessage(hButton, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)L"Abort Retry Ignore");
			SendMessage(hButton, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)L"Cancel Try Continue");
			SendMessage(hButton, (UINT)CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
			break;
		}
		case WM_PAINT:
		{
			int length = window.right > window.bottom ? window.bottom : window.right;
			int font = 95 * length / 500;
			if (font > 200)
				font = 200;
			else if (font > 150)
				font = 150;
			else if (font > 100)
				font = 100;
			else if (font > 50)
				font = 50;
			else
				font = 30;
			HFONT hFont = CreateFont(font, 0, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE, UNICODE, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Calibri");
			SendMessage(hSettings, WM_SETFONT, WPARAM(hFont), TRUE);
			MoveWindow(hMsg, 0 * window.right / 5, window.bottom / 4, window.right / 5, window.bottom / 5, true);
			MoveWindow(hTitle, 1 * window.right / 5, window.bottom / 4, window.right / 5, window.bottom / 5, true);
			MoveWindow(hMsgTxt, 0, 2 * window.bottom / 4, window.right / 5, window.bottom / 8, true);
			MoveWindow(hTitleTxt, window.right / 5, 2 * window.bottom / 4, window.right / 5, window.bottom / 8, true);
			MoveWindow(hIconTxt, 2 * window.right / 5, 2 * window.bottom / 4, window.right / 5, window.bottom / 8, true);
			MoveWindow(hButtonsTxt, 3 * window.right / 5, 2 * window.bottom / 4, window.right / 5, window.bottom / 8, true);
			MoveWindow(hIcon, 2 * window.right / 5, window.bottom / 4, window.right / 5, window.bottom / 5, true);
			MoveWindow(hButton, 3 * window.right / 5, window.bottom / 4, window.right / 5, window.bottom / 5, true);
			MoveWindow(hCheckmark1, 4 * window.right / 5, window.bottom / 4, window.right / 5, window.bottom / 5, true);
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			hBitmap = LoadBitmapW(hInst, MAKEINTRESOURCE(IDC_ADEETHYIASHANKAREXELIBRARY));
			// TODO: Add any drawing code that uses hdc here...
			BITMAP                     bm;
			GetObject(hBitmap, sizeof(bm), &bm);
			HDC     hdcFrom = CreateCompatibleDC(hdc);
			HBITMAP bmpTo = CreateCompatibleBitmap(hdc, window.bottom / 10, window.bottom / 10);
			HGDIOBJ hobFrom = SelectObject(hdcFrom, hBitmap);
			HGDIOBJ hobTo = SelectObject(hdc, bmpTo);

			StretchBlt(hdc, 0, 9 * window.bottom / 10, window.bottom / 10, window.bottom / 10,
				hdcFrom, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);

			SelectObject(hdcFrom, hobFrom);
			SelectObject(hdc, hobTo);

			DeleteObject(hBitmap);
			DeleteDC(hdcFrom);

			BITMAP                     bm1;
			GetObject(hCheckmark, sizeof(bm1), &bm1);
			HDC     hdcFrom1 = CreateCompatibleDC(hdc);
			HBITMAP bmpTo1 = CreateCompatibleBitmap(hdc, window.bottom / 5, window.bottom / 5);
			HGDIOBJ hobFrom1 = SelectObject(hdcFrom1, hCheckmark);
			HGDIOBJ hobTo1 = SelectObject(hdc, bmpTo1);

			BLENDFUNCTION fnc;
			fnc.BlendOp = AC_SRC_OVER;
			fnc.BlendFlags = 0;
			fnc.SourceConstantAlpha = 0xFF;
			fnc.AlphaFormat = AC_SRC_ALPHA;

			SelectObject(hdcFrom1, hobFrom1);

			SelectObject(hdc, hobTo1);

			DeleteDC(hdcFrom1);

			ReleaseDC(hWnd, hdc);
			DeleteDC(hdc);
			EndPaint(hWnd, &ps);
			break;
		}
		case WM_SIZE:
			MoveWindow(hSettings, 0, 0, (int)window.right, (int)window.bottom / 4, true);
			return DefWindowProc(hWnd, message, wParam, lParam);
		case WM_CTLCOLORSTATIC:
		{
			HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
			HDC hdcStatic = (HDC)wParam;
			SetTextColor(hdcStatic, RGB(0, 0, 0));
			SetBkColor(hdcStatic, RGB(255, 255, 255));
			return (INT_PTR)hBrush;
		}
		case WM_DESTROY:
			DestroyWindow(hWnd);
			settings = false;
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
