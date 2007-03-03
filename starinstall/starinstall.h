// starinstall.h : main header file for the STARINSTALL application
//

#if !defined(AFX_STARINSTALL_H__493CD6B6_6038_4044_A9B8_AF4D275FD04D__INCLUDED_)
#define AFX_STARINSTALL_H__493CD6B6_6038_4044_A9B8_AF4D275FD04D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CStarinstallApp:
// See starinstall.cpp for the implementation of this class
//

class CStarinstallApp : public CWinApp
{
public:
	CStarinstallApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStarinstallApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CStarinstallApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CStarinstallApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STARINSTALL_H__493CD6B6_6038_4044_A9B8_AF4D275FD04D__INCLUDED_)
