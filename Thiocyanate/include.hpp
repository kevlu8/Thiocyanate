#pragma once
#include <Windows.h>
#include <math.h>
#include <vector>

typedef struct PAYLOADPARAMS {
	HDC hdc;
	int x;
	int y;
} PAYLOADPARAMS;

uint32_t sd = 0xe8386aef;

uint32_t random(uint32_t x) {
	sd += 0x9e3779b97f4a7c15;
	uint32_t z = sd;
	z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
	z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
	z ^= (z >> 31);
	z &= (1 << (uint32_t)ceil(log2(x))) - 1;
	if (z > x)
		return random(x);
	return z;
}

void send_indir_msgbox(LPCSTR txt, LPCSTR capt, DWORD type) {
	MSGBOXPARAMS msg = { 0 };
	msg.hwndOwner = NULL;
	msg.hInstance = GetModuleHandle(NULL);
	msg.lpszText = txt;
	msg.lpszCaption = capt;
	msg.dwStyle = type;

	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MessageBoxIndirect, &msg, NULL, NULL);
}