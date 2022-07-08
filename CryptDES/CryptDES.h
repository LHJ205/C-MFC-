// CryptDES.h : main header file for the CRYPTDES application
//

#if !defined(AFX_CRYPTDES_H__72EBD634_122F_4D42_83CB_8370006C392D__INCLUDED_)
#define AFX_CRYPTDES_H__72EBD634_122F_4D42_83CB_8370006C392D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCryptDESApp:
// See CryptDES.cpp for the implementation of this class
//

class CCryptDESApp : public CWinApp
{
public:
	CCryptDESApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCryptDESApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCryptDESApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CRYPTDES_H__72EBD634_122F_4D42_83CB_8370006C392D__INCLUDED_)
