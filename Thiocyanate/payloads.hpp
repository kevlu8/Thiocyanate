#pragma once
#include "include.hpp"

#define fori100 for (int i=0;i<100;i++)
#define forj100 for (int j=0;j<100;j++)
#define fori(x) for (int i=0;i<x;i++)
#define forj(x) for (int j=0;j<x;j++)
#define random(x) rand() % x
#define randomRGB random(255)

void p1(PAYLOADPARAMS p) {
	fori(p.x) {
		forj(p.y) {
			SetPixel(p.hdc, i, j, RGB(randomRGB, randomRGB, randomRGB));
		}
	}
}