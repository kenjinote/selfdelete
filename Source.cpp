#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <windows.h>

#define ID_BUTTON1 1000

WCHAR szClassName[] = L"Window";

BOOL SelfDelete() {
	WCHAR szFile[MAX_PATH];
	WCHAR szCommand[MAX_PATH];
	if (GetModuleFileNameW(0, szFile, MAX_PATH) &&
		GetShortPathNameW(szFile, szFile, MAX_PATH))
	{
		lstrcpyW(szCommand, L"/c del ");
		lstrcatW(szCommand, szFile);
		lstrcatW(szCommand, L" >> NUL");

		if (GetEnvironmentVariableW(
			L"ComSpec",
			szFile, MAX_PATH) &&
			(INT)ShellExecute(
				0,
				0,
				szFile,
				szCommand,
				0,
				SW_HIDE) > 32)
			return TRUE;
	}
	return FALSE;
}

LRESULT CALLBACK WndProc(
	HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam) {
	switch (msg)
	{
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			TextOutW(hdc, 0, 0, L"なお、このプログラムは", 11);
			TextOutW(hdc, 0, 20, L"自動的に消滅する。成功を祈る", 14);
			EndPaint(hWnd, &ps);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd
) {
	MSG msg;
	WNDCLASS wndclass = {
		CS_HREDRAW | CS_VREDRAW,
		WndProc,
		0,
		0,
		hInstance,
		0,
		LoadCursor(0,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		0,
		szClassName
	};
	RegisterClass(&wndclass);
	HWND hWnd = CreateWindowW(
		szClassName,
		L"Window",
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
		CW_USEDEFAULT,
		0,
		CW_USEDEFAULT,
		0,
		0,
		0,
		hInstance,
		0
	);
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	SelfDelete();
	return (int)msg.wParam;
}
