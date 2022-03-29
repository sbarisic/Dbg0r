#include <stdio.h>
#include <Windows.h>

#define SUBHOOK_STATIC
#include "subhook.h"

#include <winternl.h>

typedef unsigned char uchar;
typedef unsigned int uint;

extern "C" {
	subhook_t LoadLibraryW_Hook;
	HMODULE __stdcall LoadLibraryW_New(LPCWSTR str) {
		subhook_remove(LoadLibraryW_Hook);

		printf("LoadLibraryW - %ls\n", str);
		HMODULE ret = LoadLibraryW(str);

		subhook_install(LoadLibraryW_Hook);
		return ret;
	}


	subhook_t LoadLibraryA_Hook;
	HMODULE __stdcall LoadLibraryA_New(LPCSTR str) {
		subhook_remove(LoadLibraryA_Hook);

		printf("LoadLibraryA - %s\n", str);
		HMODULE ret = LoadLibraryA(str);

		subhook_install(LoadLibraryA_Hook);
		return ret;
	}


	subhook_t FreeLibrary_Hook;
	BOOL __stdcall FreeLibrary_New(HMODULE mod) {
		subhook_remove(FreeLibrary_Hook);

		wchar_t name[256];
		memset(name, 0, 256 * sizeof(wchar_t));
		GetModuleFileNameW(mod, name, 256);

		//printf("FreeLibrary - %ls\n", name);
		BOOL ret = FreeLibrary(mod);

		subhook_install(FreeLibrary_Hook);
		return ret;
	}


	subhook_t GetProcAddress_Hook;
	FARPROC __stdcall GetProcAddress_New(HMODULE mod, LPCSTR str) {
		subhook_remove(GetProcAddress_Hook);

		//printf("GetProcAddress - %s\n", str);
		FARPROC ret = GetProcAddress(mod, str);

		subhook_install(GetProcAddress_Hook);
		return ret;
	}

	subhook_t GetModuleHandleW_Hook;
	HMODULE __stdcall GetModuleHandleW_New(LPCWSTR str) {
		subhook_remove(GetModuleHandleW_Hook);

		//printf("GetModuleHandleW - %ls\n", str);
		HMODULE ret = GetModuleHandleW(str);

		subhook_install(GetModuleHandleW_Hook);
		return ret;
	}

	subhook_t CreateFileA_Hook;
	HANDLE WINAPI CreateFileA_New(_In_ LPCSTR lpFileName, _In_ DWORD dwDesiredAccess, _In_ DWORD dwShareMode,
		_In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes, _In_ DWORD dwCreationDisposition, _In_ DWORD dwFlagsAndAttributes, _In_opt_ HANDLE hTemplateFile) {
		subhook_remove(CreateFileA_Hook);

		printf("CreateFileA - %s\n", lpFileName);
		HANDLE ret = CreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);

		subhook_install(CreateFileA_Hook);
		return ret;
	}

	subhook_t CreateFileW_Hook;
	HANDLE WINAPI CreateFileW_New(
		_In_ LPCWSTR lpFileName,
		_In_ DWORD dwDesiredAccess,
		_In_ DWORD dwShareMode,
		_In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes,
		_In_ DWORD dwCreationDisposition,
		_In_ DWORD dwFlagsAndAttributes,
		_In_opt_ HANDLE hTemplateFile
	) {
		subhook_remove(CreateFileW_Hook);

		printf("CreateFileW - %ls\n", lpFileName);
		HANDLE ret = CreateFileW(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);

		subhook_install(CreateFileW_Hook);
		return ret;
	}

	__declspec(dllexport) void __cdecl do_drugs() {
		LoadLibraryW_Hook = subhook_new(LoadLibraryW, LoadLibraryW_New, (subhook_flags_t)0);
		LoadLibraryA_Hook = subhook_new(LoadLibraryA, LoadLibraryA_New, (subhook_flags_t)0);
		GetProcAddress_Hook = subhook_new(GetProcAddress, GetProcAddress_New, (subhook_flags_t)0);
		GetModuleHandleW_Hook = subhook_new(GetModuleHandleW, GetModuleHandleW_New, (subhook_flags_t)0);
		FreeLibrary_Hook = subhook_new(FreeLibrary, FreeLibrary_New, (subhook_flags_t)0);

		CreateFileA_Hook = subhook_new(CreateFileA, CreateFileA_New, (subhook_flags_t)0);
		CreateFileW_Hook = subhook_new(CreateFileW, CreateFileW_New, (subhook_flags_t)0);

		subhook_install(LoadLibraryW_Hook);
		subhook_install(LoadLibraryA_Hook);
		subhook_install(GetProcAddress_Hook);
		subhook_install(GetModuleHandleW_Hook);
		subhook_install(FreeLibrary_Hook);

		subhook_install(CreateFileA_Hook);
		subhook_install(CreateFileW_Hook);

		printf("OK\n");


		// HMODULE NOPE_vcmssm = LoadLibraryW(L"NOPE_vcmssm.dll");
	}
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		MessageBoxA(NULL, "OK", "DllMain", NULL);
		break;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}


void do_stuff() {
	printf("do_stuff\n");
}

unsigned int __cdecl a41fe5da(char const* A0) {
	do_stuff();
	return 0;
}

unsigned __int64 __cdecl a7d31d10(void) {
	do_stuff();
	return 0;
}

unsigned int __cdecl a8547dd7(void) {
	do_stuff();
	return 0;
}

unsigned char* __cdecl b32fb08c(unsigned char const* A0, unsigned int A1, unsigned char const* A2, unsigned int A3, unsigned int A4, int A5, unsigned int A6, unsigned int A7, unsigned int* A8) {
	do_stuff();
	return NULL;
}

unsigned char* __cdecl bb524f50(int A0, unsigned char const* A1, unsigned int A2, unsigned int* A3, unsigned char** A4, unsigned int* A5) {
	do_stuff();
	return NULL;
}

unsigned char* __cdecl bdc9dd0d(unsigned int* A0) {
	do_stuff();
	return NULL;
}

unsigned char const* __cdecl c504801c(unsigned int A0, unsigned char A1, unsigned char const* A2, unsigned int A3, unsigned int* A4) {
	do_stuff();
	return NULL;
}

unsigned char* __cdecl cc623062(int A0, unsigned char const* A1, unsigned int A2, unsigned int* A3, unsigned char** A4, unsigned int* A5) {
	do_stuff();
	return NULL;
}

unsigned int __cdecl dd4b00b5(void) {
	do_stuff();
	return 0;
}

int __cdecl ee62726b(int A0, int A1, int A2) {
	do_stuff();
	return 0;
}

unsigned char* __cdecl f16c0321(unsigned char const* A0, unsigned int A1, unsigned char const* A2, unsigned int A3, unsigned int A4, unsigned int A5, unsigned int A6, unsigned int* A7) {
	do_stuff();
	return NULL;
}

void __cdecl ff574450(void* A0) {
	do_stuff();
}