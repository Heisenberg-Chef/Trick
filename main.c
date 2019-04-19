#include <windows.h>
#define NUM 1000

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static int pattern[NUM][4];
	int x, z, y, cxClient, cyClient, x1, y1;
	HWND hwnd;
	HDC hdcMem, hdcSRC;
	cxClient = GetSystemMetrics(SM_CXSCREEN)/10;
	cyClient = GetSystemMetrics(SM_CYSCREEN)/10;
	LockWindowUpdate(hwnd = GetDesktopWindow());
	hdcSRC = GetDCEx(hwnd, NULL, DCX_CACHE | DCX_LOCKWINDOWUPDATE);
	srand(GetCurrentTime());
	hdcMem = CreateCompatibleDC(hdcSRC);
	HBITMAP hBitmap = CreateCompatibleBitmap(hdcSRC, cxClient, cyClient);
	for (z = 0; z < NUM; z++)
	{
		x = cxClient * (rand() % 10);
		y = cyClient * (rand() % 10);
		x1 = cxClient * (rand() % 10);
		y1 = cyClient * (rand() % 10);
		BitBlt(hdcMem, 0, 0, cxClient, cyClient,
			hdcSRC, x,y , SRCCOPY);
		BitBlt(hdcSRC, x, y, cxClient, cyClient, hdcSRC, x1, y1, SRCCOPY);
		BitBlt(hdcSRC, x1, y1, cxClient, cyClient, hdcMem, 0, 0, SRCCOPY);

	}
	DeleteDC(hdcMem);
	ReleaseDC(hwnd,hdcSRC);
	DeleteObject(hBitmap);
	LockWindowUpdate(NULL);
	return 0;
}
