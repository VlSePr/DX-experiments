#include "DXUtilities.h"


namespace
{
	DXUAppUtilities* g_pDXU = nullptr;
}

LRESULT CALLBACK MainMsgProc (HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	if (g_pDXU)
	{
		return g_pDXU->MsgProc (hwnd, msg, wparam, lparam);
	}
	else
	{
		return DefWindowProc (hwnd, msg, wparam, lparam);
	}
}

DXUAppUtilities::DXUtilities (HINSTANCE hInstance)
{
	m_HWND = nullptr;
	m_hAppInstance = hInstance;
	m_ClientHeight = 768;
	m_ClientWidth = 1024;
	m_AppTitle = "DirectXApp";
	m_WinStyle = WS_OVERLAPPEDWINDOW;
	//g_pDXU = this;
}

DXUAppUtilities::~DXUtilities ()
{}

int DXUAppUtilities::Run ()
{
	MSG windowsMessage = { 0 };
	while (WM_QUIT != windowsMessage.message)
	{
		if (PeekMessage (&windowsMessage, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage (&windowsMessage);
			DispatchMessage (&windowsMessage);
		}
		else
		{
			Update (0);
			Render (0);
		}
	}

	return static_cast<int>(windowsMessage.wParam);
}

bool DXUAppUtilities::Init ()
{
	if (!InitWindow ())
	{
		return false;
	}

	return true;
}

LRESULT DXUAppUtilities::MsgProc (HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage (EXIT_SUCCESS);
	default:
		DefWindowProc (hwnd, msg, wparam, lparam);
	}
	return 0;
}

bool DXUAppUtilities::InitWindow ()
{
	WNDCLASSEX wndClsEx;
	memset (&wndClsEx, 0, sizeof (WNDCLASSEX));

	wndClsEx.cbClsExtra = 0;
	wndClsEx.cbSize = sizeof (WNDCLASSEX);
	wndClsEx.cbWndExtra = 0;
	wndClsEx.style = CS_VREDRAW | CS_HREDRAW;
	wndClsEx.lpfnWndProc = MainMsgProc;
	wndClsEx.hIcon = LoadIcon (NULL, IDI_APPLICATION);
	wndClsEx.hInstance = m_hAppInstance;
	wndClsEx.lpszMenuName = NULL;
	wndClsEx.lpszClassName = "DX_WINDOW";

	if (!RegisterClassEx (&wndClsEx))
	{
		OutputDebugString ("Failed to register WNDCLASSEX");
		return false;
	}

	RECT rect = { 0, 0, m_ClientWidth, m_ClientHeight };
	AdjustWindowRect (&rect, m_WinStyle, false);
	UINT width = rect.right - rect.left;
	UINT height = rect.bottom - rect.top;
	UINT x = GetSystemMetrics (SM_CXSCREEN) / 2 - width / 2;
	UINT y = GetSystemMetrics (SM_CYSCREEN) / 2 - height / 2;

	m_HWND = CreateWindow (wndClsEx.lpszClassName, m_AppTitle.c_str (), m_WinStyle, x, y, width, height, NULL, NULL, m_hAppInstance, NULL);
	
	if (!m_HWND)
	{
		OutputDebugString ("Failed to crete window");
		return false;
	}

	g_pDXU = this;
	ShowWindow (m_HWND, SW_SHOW);
	return true;
}


