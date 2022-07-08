// CryptDESDlg.h : header file
//

#if !defined(AFX_CRYPTDESDLG_H__C2CBC27F_45AE_4C7F_8310_3FC9E09F43AF__INCLUDED_)
#define AFX_CRYPTDESDLG_H__C2CBC27F_45AE_4C7F_8310_3FC9E09F43AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCryptDESDlg dialog
#define BUFSIZE (1024*50)
#include "DES.h"
#include "afxwin.h"
class CCryptDESDlg : public CDialog
{
// Construction
public:
	CCryptDESDlg(CWnd* pParent = NULL);	// standard constructor
	CString m_FolderEncrypt,m_FolderDecrypt;
	CString m_FileNameEncrypt,m_FileNameDecrypt;
	CDES m_des;
	char databuf[BUFSIZE];//Êý¾Ý»º³åÇø
	public:
		int Get_C(int c);
	int Ra(int f, int l);
	int Get_GCD(int ola,int e,int *d);
	int Get_M(int m);
	int Translate();


// Dialog Data
// Dialog Data
	//{{AFX_DATA(CCryptDESDlg)
	enum { IDD = IDD_CRYPTDES_DIALOG };
	CString	m_KeyDecrypt;
	CString	m_KeyEncrypt;
	CString	m_FileDecrypt;
	CString	m_FileEncrypt;
	CString	m_FileDecryptOut;
	CString	m_FileEncryptOut;
	CString	m_Input;
	int		m_Keyleft;
	int		m_Keyright;
	CString	m_Output;
	int		m_PRd;
	int		m_PRn;
	int		m_PUe;
	int		m_PUn;
	long	m_ka;
	long	m_kb;
	long	m_p;
	long	m_a;
	long	m_k1;
	long	m_aa;
	long	m_k2;
	long	m_bb;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCryptDESDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCryptDESDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonEncryptfile();
	afx_msg void OnButtonDecryptfile();
	afx_msg void OnButtonEncrypt();
	afx_msg void OnButtonDecrypt();
	afx_msg void OnButtonDecryptfolder();
	afx_msg void OnButtonEncryptfolder();
	afx_msg void OnChangeEditEncryptfileout();
	afx_msg void OnOpenfile();
	afx_msg void OnCreatkey();
	virtual void OnOK();
	afx_msg void OnOk2();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton7();
	afx_msg void OnButton6();
	afx_msg void OnButton5();
	afx_msg int Primep(long n);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangePrd();
	afx_msg void OnEnChangePue();
	CButton m_encrypt_file;
	CButton m_decrypt_file;
	CButton m_md5_file;
	CButton m_DH_g;
	CButton m_DH_Ya;
	CButton m_DH_Yb;
	CButton m_DH_Xa;
	CButton m_DH_Xb;
	CButton m_DH_keyA;
	CButton m_DH_keyB;
	CButton m_RSA_key;
	CButton m_b_encrypt;
	CButton m_b_decrypt;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CRYPTDESDLG_H__C2CBC27F_45AE_4C7F_8310_3FC9E09F43AF__INCLUDED_)
