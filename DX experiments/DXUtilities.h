#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <string>
#include <stdlib.h>

class DXUAppUtilities
{
public:
	DXUAppUtilities (HINSTANCE hInstance);
	virtual ~DXUAppUtilities ();
	
	int Run ();

	bool Init ();
	virtual void Update (float dx) = 0;
	virtual void Render (float dx) = 0;
	LRESULT MsgProc (HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

protected:

	HINSTANCE m_hAppInstance;
	UINT m_ClientWidth;
	UINT m_ClientHeight;
	HWND m_HWND;
	DWORD m_WinStyle;
	std::string m_AppTitle;

protected:
	bool InitWindow ();
};

