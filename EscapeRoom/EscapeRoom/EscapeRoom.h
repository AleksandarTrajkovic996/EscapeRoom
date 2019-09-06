
// EscapeRoom.h : main header file for the EscapeRoom application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CEscapeRoomApp:
// See EscapeRoom.cpp for the implementation of this class
//

class CEscapeRoomApp : public CWinApp
{
public:
	CEscapeRoomApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEscapeRoomApp theApp;
