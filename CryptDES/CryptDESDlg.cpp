// CryptDESDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CryptDES.h"
#include "CryptDESDlg.h"
#include "math.h"
#include < iostream >
#include <string>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define MAX_NUM 20

int Prime[MAX_NUM]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67};//素数

#include<stdio.h>

#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

#define RL(x, y) (((x) << (y)) | ((x) >> (32 - (y))))  //x向左循环移y位

#define PP(x) (x<<24)|((x<<8)&0xff0000)|((x>>8)&0xff00)|(x>>24)  //将x高低位互换,例如PP(aabbccdd)=ddccbbaa

#define FF(a, b, c, d, x, s, ac) a = b + (RL((a + F(b,c,d) + x + ac),s))
#define GG(a, b, c, d, x, s, ac) a = b + (RL((a + G(b,c,d) + x + ac),s))
#define HH(a, b, c, d, x, s, ac) a = b + (RL((a + H(b,c,d) + x + ac),s))
#define II(a, b, c, d, x, s, ac) a = b + (RL((a + I(b,c,d) + x + ac),s))

unsigned A,B,C,D,a,b,c,d,i,len,flen[2],x[16];   //i临时变量,len文件长,flen[2]为64位二进制表示的文件初始长度
FILE *fp;

void md5(){                 //MD5核心算法,供64轮
	
	a=A,b=B,c=C,d=D;
	/**//* Round 1 */
	FF (a, b, c, d, x[ 0],  7, 0xd76aa478); /**//* 1 */
	FF (d, a, b, c, x[ 1], 12, 0xe8c7b756); /**//* 2 */
	FF (c, d, a, b, x[ 2], 17, 0x242070db); /**//* 3 */
	FF (b, c, d, a, x[ 3], 22, 0xc1bdceee); /**//* 4 */
	FF (a, b, c, d, x[ 4],  7, 0xf57c0faf); /**//* 5 */
	FF (d, a, b, c, x[ 5], 12, 0x4787c62a); /**//* 6 */
	FF (c, d, a, b, x[ 6], 17, 0xa8304613); /**//* 7 */
	FF (b, c, d, a, x[ 7], 22, 0xfd469501); /**//* 8 */
	FF (a, b, c, d, x[ 8],  7, 0x698098d8); /**//* 9 */
	FF (d, a, b, c, x[ 9], 12, 0x8b44f7af); /**//* 10 */
	FF (c, d, a, b, x[10], 17, 0xffff5bb1); /**//* 11 */
	FF (b, c, d, a, x[11], 22, 0x895cd7be); /**//* 12 */
	FF (a, b, c, d, x[12],  7, 0x6b901122); /**//* 13 */
	FF (d, a, b, c, x[13], 12, 0xfd987193); /**//* 14 */
	FF (c, d, a, b, x[14], 17, 0xa679438e); /**//* 15 */
	FF (b, c, d, a, x[15], 22, 0x49b40821); /**//* 16 */
	
	/**//* Round 2 */
	GG (a, b, c, d, x[ 1],  5, 0xf61e2562); /**//* 17 */
	GG (d, a, b, c, x[ 6],  9, 0xc040b340); /**//* 18 */
	GG (c, d, a, b, x[11], 14, 0x265e5a51); /**//* 19 */
	GG (b, c, d, a, x[ 0], 20, 0xe9b6c7aa); /**//* 20 */
	GG (a, b, c, d, x[ 5],  5, 0xd62f105d); /**//* 21 */
	GG (d, a, b, c, x[10],  9, 0x02441453); /**//* 22 */
	GG (c, d, a, b, x[15], 14, 0xd8a1e681); /**//* 23 */
	GG (b, c, d, a, x[ 4], 20, 0xe7d3fbc8); /**//* 24 */
	GG (a, b, c, d, x[ 9],  5, 0x21e1cde6); /**//* 25 */
	GG (d, a, b, c, x[14],  9, 0xc33707d6); /**//* 26 */
	GG (c, d, a, b, x[ 3], 14, 0xf4d50d87); /**//* 27 */
	GG (b, c, d, a, x[ 8], 20, 0x455a14ed); /**//* 28 */
	GG (a, b, c, d, x[13],  5, 0xa9e3e905); /**//* 29 */
	GG (d, a, b, c, x[ 2],  9, 0xfcefa3f8); /**//* 30 */
	GG (c, d, a, b, x[ 7], 14, 0x676f02d9); /**//* 31 */
	GG (b, c, d, a, x[12], 20, 0x8d2a4c8a); /**//* 32 */
	
	/**//* Round 3 */
	HH (a, b, c, d, x[ 5],  4, 0xfffa3942); /**//* 33 */
	HH (d, a, b, c, x[ 8], 11, 0x8771f681); /**//* 34 */
	HH (c, d, a, b, x[11], 16, 0x6d9d6122); /**//* 35 */
	HH (b, c, d, a, x[14], 23, 0xfde5380c); /**//* 36 */
	HH (a, b, c, d, x[ 1],  4, 0xa4beea44); /**//* 37 */
	HH (d, a, b, c, x[ 4], 11, 0x4bdecfa9); /**//* 38 */
	HH (c, d, a, b, x[ 7], 16, 0xf6bb4b60); /**//* 39 */
	HH (b, c, d, a, x[10], 23, 0xbebfbc70); /**//* 40 */
	HH (a, b, c, d, x[13],  4, 0x289b7ec6); /**//* 41 */
	HH (d, a, b, c, x[ 0], 11, 0xeaa127fa); /**//* 42 */
	HH (c, d, a, b, x[ 3], 16, 0xd4ef3085); /**//* 43 */
	HH (b, c, d, a, x[ 6], 23, 0x04881d05); /**//* 44 */
	HH (a, b, c, d, x[ 9],  4, 0xd9d4d039); /**//* 45 */
	HH (d, a, b, c, x[12], 11, 0xe6db99e5); /**//* 46 */
	HH (c, d, a, b, x[15], 16, 0x1fa27cf8); /**//* 47 */
	HH (b, c, d, a, x[ 2], 23, 0xc4ac5665); /**//* 48 */
	
	/**//* Round 4 */
	II (a, b, c, d, x[ 0],  6, 0xf4292244); /**//* 49 */
	II (d, a, b, c, x[ 7], 10, 0x432aff97); /**//* 50 */
	II (c, d, a, b, x[14], 15, 0xab9423a7); /**//* 51 */
	II (b, c, d, a, x[ 5], 21, 0xfc93a039); /**//* 52 */
	II (a, b, c, d, x[12],  6, 0x655b59c3); /**//* 53 */
	II (d, a, b, c, x[ 3], 10, 0x8f0ccc92); /**//* 54 */
	II (c, d, a, b, x[10], 15, 0xffeff47d); /**//* 55 */
	II (b, c, d, a, x[ 1], 21, 0x85845dd1); /**//* 56 */
	II (a, b, c, d, x[ 8],  6, 0x6fa87e4f); /**//* 57 */
	II (d, a, b, c, x[15], 10, 0xfe2ce6e0); /**//* 58 */
	II (c, d, a, b, x[ 6], 15, 0xa3014314); /**//* 59 */
	II (b, c, d, a, x[13], 21, 0x4e0811a1); /**//* 60 */
	II (a, b, c, d, x[ 4],  6, 0xf7537e82); /**//* 61 */
	II (d, a, b, c, x[11], 10, 0xbd3af235); /**//* 62 */
	II (c, d, a, b, x[ 2], 15, 0x2ad7d2bb); /**//* 63 */
	II (b, c, d, a, x[ 9], 21, 0xeb86d391); /**//* 64 */
	
	A += a;
	B += b;
	C += c;
	D += d;
	
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCryptDESDlg dialog

CCryptDESDlg::CCryptDESDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCryptDESDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCryptDESDlg)
	m_KeyDecrypt = _T("");
	m_KeyEncrypt = _T("");
	m_FileDecrypt = _T("");
	m_FileEncrypt = _T("");
	m_FileDecryptOut = _T("");
	m_FileEncryptOut = _T("");
	m_Input = _T("");
	m_Keyleft = 0;
	m_Keyright = 0;
	m_Output = _T("");
	m_PRd = 0;
	m_PRn = 0;
	m_PUe = 0;
	//m_PUn = 0;
	m_ka = 0;
	m_kb = 0;
	m_p = 0;
	m_a = 0;
	m_k1 = 0;
	m_aa = 0;
	m_k2 = 0;
	m_bb = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_TOM);
}

void CCryptDESDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCryptDESDlg)
	DDX_Text(pDX, IDC_EDIT_DECRYPT, m_KeyDecrypt);
	DDX_Text(pDX, IDC_EDIT_ENCRYPT, m_KeyEncrypt);
	DDX_Text(pDX, IDC_EDIT_DECRYPTFILE, m_FileDecrypt);
	DDX_Text(pDX, IDC_EDIT_ENCRYPTFILE, m_FileEncrypt);
	DDX_Text(pDX, IDC_EDIT_DECRYPTOUT, m_FileDecryptOut);
	DDX_Text(pDX, IDC_EDIT_ENCRYPTFILEOUT, m_FileEncryptOut);
	DDX_Text(pDX, IDC_INPUT, m_Input);
	DDX_Text(pDX, IDC_KEYLEFT, m_Keyleft);
	DDX_Text(pDX, IDC_KEYRIGHT, m_Keyright);
	DDX_Text(pDX, IDC_OUTPUT, m_Output);
	DDX_Text(pDX, IDC_PRD, m_PRd);
	DDX_Text(pDX, IDC_PRN, m_PRn);
	DDX_Text(pDX, IDC_PUE, m_PUe);
	//DDX_Text(pDX, IDC_PUN, m_PUn);
	DDX_Text(pDX, IDC_EDIT10_KA, m_ka);
	DDX_Text(pDX, IDC_EDIT11_KB, m_kb);
	DDX_Text(pDX, IDC_EDIT2_P, m_p);
	DDX_Text(pDX, IDC_EDIT3_A, m_a);
	DDX_Text(pDX, IDC_EDIT5_K1, m_k1);
	DDX_Text(pDX, IDC_EDIT6_AA, m_aa);
	DDX_Text(pDX, IDC_EDIT7_K2, m_k2);
	DDX_Text(pDX, IDC_EDIT8_BB, m_bb);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_BUTTON_ENCRYPTFILE, m_encrypt_file);
	DDX_Control(pDX, IDC_BUTTON_DECRYPTFILE, m_decrypt_file);
	DDX_Control(pDX, IDC_OPENFILE, m_md5_file);
	DDX_Control(pDX, IDC_BUTTON1, m_DH_g);
	DDX_Control(pDX, IDC_BUTTON3, m_DH_Ya);
	DDX_Control(pDX, IDC_BUTTON5, m_DH_Yb);
	DDX_Control(pDX, IDC_BUTTON2, m_DH_Xa);
	DDX_Control(pDX, IDC_BUTTON4, m_DH_Xb);
	DDX_Control(pDX, IDC_BUTTON6, m_DH_keyA);
	DDX_Control(pDX, IDC_BUTTON7, m_DH_keyB);
	DDX_Control(pDX, IDC_CREATKEY, m_RSA_key);
	DDX_Control(pDX, IDC_BUTTON_ENCRYPT, m_b_encrypt);
	DDX_Control(pDX, IDC_BUTTON_DECRYPT, m_b_decrypt);
}

BEGIN_MESSAGE_MAP(CCryptDESDlg, CDialog)
	//{{AFX_MSG_MAP(CCryptDESDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ENCRYPTFILE, OnButtonEncryptfile)
	ON_BN_CLICKED(IDC_BUTTON_DECRYPTFILE, OnButtonDecryptfile)
	ON_BN_CLICKED(IDC_BUTTON_ENCRYPT, OnButtonEncrypt)
	ON_BN_CLICKED(IDC_BUTTON_DECRYPT, OnButtonDecrypt)
	ON_BN_CLICKED(IDC_BUTTON_DECRYPTFOLDER, OnButtonDecryptfolder)
	ON_BN_CLICKED(IDC_BUTTON_ENCRYPTFOLDER, OnButtonEncryptfolder)
	ON_BN_CLICKED(IDC_OPENFILE, OnOpenfile)
	ON_BN_CLICKED(IDC_CREATKEY, OnCreatkey)
	ON_BN_CLICKED(IDOK2, OnOk2)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_PRD, &CCryptDESDlg::OnEnChangePrd)
	ON_EN_CHANGE(IDC_PUE, &CCryptDESDlg::OnEnChangePue)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCryptDESDlg message handlers

BOOL CCryptDESDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	HICON h_con1;
	h_con1 = AfxGetApp() -> LoadIcon(IDI_ICON_mybag); //图标id 
	m_encrypt_file.SetIcon(h_con1);
	m_decrypt_file.SetIcon(h_con1);
	m_md5_file.SetIcon(h_con1);
	HICON h_con2;
	h_con2 = AfxGetApp() -> LoadIcon(IDI_ICON1_jisuan); //图标id 
	m_DH_g.SetIcon(h_con2);
	m_DH_Ya.SetIcon(h_con2);
	m_DH_Yb.SetIcon(h_con2);
	HICON h_con3;
	h_con3 = AfxGetApp() -> LoadIcon(IDI_ICON_search); //图标id 
	m_DH_Xa.SetIcon(h_con3);
	m_DH_Xb.SetIcon(h_con3);
	HICON h_con4;
	h_con4 = AfxGetApp() -> LoadIcon(IDI_ICON_key); //图标id 
	m_DH_keyA.SetIcon(h_con4);
	m_DH_keyB.SetIcon(h_con4);
	m_RSA_key.SetIcon(h_con4);
	HICON h_con5;
	h_con5 = AfxGetApp() -> LoadIcon(IDI_ICON_encrypt); //图标id 
	m_b_encrypt.SetIcon(h_con5);
	HICON h_con6;
	h_con6 = AfxGetApp() -> LoadIcon(IDI_ICON_decrypt); //图标id 
	m_b_decrypt.SetIcon(h_con6);
	// TODO: Add extra initialization here
	m_FileNameEncrypt = _T("");
	m_FileNameDecrypt = _T("");
	m_FolderEncrypt = _T("");
	m_FolderDecrypt = _T("");
	GetDlgItem( IDC_BUTTON_ENCRYPT )->EnableWindow(false);
	GetDlgItem( IDC_BUTTON_DECRYPT )->EnableWindow(false);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCryptDESDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCryptDESDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCryptDESDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCryptDESDlg::OnButtonEncryptfile() 
{
	// TODO: Add your control notification handler code here

	UpdateData(true);
	char szFilter[] = "all Files(*.*)|*.*||";
	CFileDialog FileDlg( TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter );

	if( FileDlg.DoModal() == IDOK )
	{
		m_FileEncrypt = FileDlg.GetPathName();
		string strpath =CStringA(m_FileEncrypt); 
		m_FileNameEncrypt = FileDlg.GetFileName();
		string strpath1 = CStringA(m_FileNameEncrypt); 
		//m_FileEncryptOut = FileDlg.GetPathName()-".txt"+"jiami.txt";
		strpath = strpath.substr(0, strpath.length()-4)+"_加密.txt";
		strpath1 = strpath1.substr(0, strpath1.length()-4)+"_加密.txt";
		if(m_FolderEncrypt=="")
			m_FileEncryptOut = strpath.c_str();
		else
			m_FileEncryptOut = m_FolderEncrypt+"\\"+strpath1.c_str();
		GetDlgItem( IDC_BUTTON_ENCRYPT )->EnableWindow(true);
		m_FileNameEncrypt=strpath1.c_str();
	}	
	UpdateData(false);
}

void CCryptDESDlg::OnButtonEncryptfolder() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	BROWSEINFO	bi; 
	ITEMIDLIST	*pidl; 
    char		Dir[256];

	memset(&bi, 0, sizeof(bi));
	bi.pszDisplayName = Dir; 
	bi.lpszTitle = "请选择目录"; 
	bi.ulFlags = BIF_RETURNONLYFSDIRS; 

	pidl = SHBrowseForFolder(&bi);
	SHGetPathFromIDList(pidl,Dir);
    GlobalFree(pidl);
	m_FolderEncrypt = Dir;	
	if(strlen(Dir)==3)
		m_FileEncryptOut = m_FolderEncrypt+m_FileNameEncrypt;
	else
		m_FileEncryptOut = m_FolderEncrypt+"\\"+m_FileNameEncrypt;
	UpdateData(false);
}

void CCryptDESDlg::OnButtonEncrypt() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	HFILE	fh_out,fh_in;//输入输出文件句柄
	fh_in=_lopen(m_FileEncrypt,OF_READ);
	fh_out=_lcreat(m_FileEncryptOut,0);
	long     len;	
	// 读取明文到缓冲区
	while( (len=_lread(fh_in,databuf,BUFSIZE)) >0 )
	{  
		// 设置子密钥
		if(m_KeyEncrypt.GetLength()>=16)
			m_KeyEncrypt=m_KeyEncrypt.Left(16);
		m_des.SetSubKey(m_KeyEncrypt);
        // 将缓冲区长度变为8的倍数
		len = ((len+7)>>3)<<3;
		// 在缓冲区中加密
		m_des.Encrypt(databuf,databuf,len);
		// 将密文写入输出文件
		_lwrite(fh_out,databuf,len);
	}
	_lclose(fh_in);
	_lclose(fh_out);
	AfxMessageBox("文件加密完毕!",MB_OK);

}

void CCryptDESDlg::OnButtonDecryptfile() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	char szFilter[] = "all Files(*.*)|*.*||";
	CFileDialog FileDlg( TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter );

	if( FileDlg.DoModal() == IDOK )
	{
		m_FileDecrypt = FileDlg.GetPathName();
		m_FileNameDecrypt = FileDlg.GetFileName();
		string strpath =CStringA(m_FileDecrypt); 
		strpath = strpath.substr(0, strpath.length()-4)+"_解密.txt";
		

		string strpath1 =CStringA(m_FileNameDecrypt); 
		strpath1 = strpath1.substr(0, strpath1.length()-4)+"_解密.txt";
		m_FileNameDecrypt = strpath1.c_str();
		if(m_FolderDecrypt=="")
			m_FileDecryptOut = strpath.c_str();
		else
			m_FileDecryptOut = m_FolderDecrypt+"\\"+m_FileNameDecrypt;
		GetDlgItem( IDC_BUTTON_DECRYPT )->EnableWindow(true);
		
	}	
	UpdateData(false);	
}


void CCryptDESDlg::OnButtonDecrypt() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	HFILE	fh_out,fh_in;//输入输出文件句柄
	fh_in=_lopen(m_FileDecrypt,OF_READ);
	fh_out=_lcreat(m_FileDecryptOut,0);
	long     len;	
	// 读取明文到缓冲区
	while( (len=_lread(fh_in,databuf,BUFSIZE)) >0 )
	{  
		// 设置子密钥
		if(m_KeyDecrypt.GetLength()>=16)
			m_KeyDecrypt=m_KeyEncrypt.Left(16);
		m_des.SetSubKey(m_KeyDecrypt);
        // 将缓冲区长度变为8的倍数
		len = ((len+7)>>3)<<3;
		// 在缓冲区中加密
		m_des.Decrypt(databuf,databuf,len);
		// 将密文写入输出文件
		_lwrite(fh_out,databuf,len);
	}
	_lclose(fh_in);
	_lclose(fh_out);
	AfxMessageBox("文件解密完毕!",MB_OK);
	
}

void CCryptDESDlg::OnButtonDecryptfolder() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	BROWSEINFO	bi; 
	ITEMIDLIST	*pidl; 
    char		Dir[256];

	memset(&bi, 0, sizeof(bi));
	bi.pszDisplayName = Dir; 
	bi.lpszTitle = "请选择目录"; 
	bi.ulFlags = BIF_RETURNONLYFSDIRS; 

	pidl = SHBrowseForFolder(&bi);
	SHGetPathFromIDList(pidl,Dir);
    GlobalFree(pidl);
	m_FolderDecrypt = Dir;	
	if(strlen(Dir)==3)
		m_FileDecryptOut = m_FolderDecrypt+m_FileNameDecrypt;
	else
		m_FileDecryptOut = m_FolderDecrypt+"\\"+m_FileNameDecrypt;
	UpdateData(false);	
}



void CCryptDESDlg::OnOpenfile() 
{
	// TODO: Add your control notification handler code here
		CString  FilePathName;
    //static char BASED_CODE szFilter[] = "Chart Files (*.xlc)|*.xlc|Worksheet Files (*.xls)|*.xls|Data Files (*.xlc;*.xls)|*.xlc; *.xls|All Files (*.*)|*.*||";
    static char BASED_CODE szFilter[] = "Files (*.*)|*.*||";
	CFileDialog fdlg(true,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,BASED_CODE szFilter);
	if(fdlg.DoModal()==IDOK)
	{
		FilePathName=fdlg.GetPathName();
		SetDlgItemText(IDC_EDIT1,FilePathName);
	}     
	if(FilePathName.IsEmpty())return;	 
	
	
	FILE *fp;
	
	if (!(fp=fopen(FilePathName,"rb"))) 
	{
		SetDlgItemText(IDC_EDIT2,"不能打开这个文件！");		
	}  //以二进制打开文件
	fseek(fp, 0, SEEK_END);  //文件指针转到文件末尾
	if((len=ftell(fp))==-1) 
	{
		SetDlgItemText(IDC_EDIT2,"不能打开超过2G的文件！");		
		fclose(fp);		
	}  //ftell函数返回long,最大为2GB,超出返回-1
	rewind(fp);  //文件指针复位到文件头
	A=0x67452301,B=0xefcdab89,C=0x98badcfe,D=0x10325476; //初始化链接变量
	flen[1]=len/0x20000000;     //flen单位是bit
	flen[0]=(len%0x20000000)*8;
	
	
	memset(x,0,64);   //初始化x数组为0
	fread(&x,4,16,fp);  //以4字节为一组,读取16组数据
	for(i=0;i<len/64;i++){    //循环运算直至文件结束
		md5();
		memset(x,0,64);
		fread(&x,4,16,fp);
	}
	((char*)x)[len%64]=128;  //文件结束补1,补0操作,128二进制即10000000
	if(len%64>55) md5(),memset(x,0,64);
	memcpy(x+14,flen,8);    //文件末尾加入原文件的bit长度
	md5();
	fclose(fp);
	CString cstri1,cstri2,cstri3,cstri4,cstri;
	cstri1.Format("%08x",PP(A));
	cstri2.Format("%08x",PP(B));
	cstri3.Format("%08x",PP(C));
	cstri4.Format("%08x",PP(D));
	cstri = cstri1 + cstri2 + cstri3 + cstri4;//按高低位输出：
	SetDlgItemText(IDC_EDIT2,cstri);
}


int CCryptDESDlg::Translate()//加密函数
{
	UpdateData(TRUE);
	CString str=m_Input;
	int length=str.GetLength();
	CString str2;
	int k1,k2,k3,k4,M;
	unsigned char ch,m1,m2,m3;
	for(int i=0;i<length;i++)//思路：将一个字节转化为3个字节的密文
	{
		ch=str.GetAt(i);
        M=Get_M((int)ch);//M为加密或解密处理后的值（int型）
		k1=M/58;   //k1有可能大于64
		k2=M%58;   //0<=k2<64
		k3=k1/58;  //k3不大可能大于64,故0<=k3<64
		k4=k1%58;  //0<=k4<64
		//M=k3*58*58+k4*58+k2
        k2+=65;//目的是将k2的ASCII的值限制在65~65+57之间,下同
		k3+=65;
		k4+=65;
		m1=(unsigned char)k2;
		m2=(unsigned char)k4;
		m3=(unsigned char)k3;
		str2.Insert(i*3,m1);
		str2.Insert(i*3+1,m2);
		str2.Insert(i*3+2,m3);
		
	}
	
	SetDlgItemText(IDC_OUTPUT,str2);
	return 0;

}
int CCryptDESDlg::Get_M(int m)//计算：(m的e次方)%n
{
	int d=m_PRd;
	int n=m_PRn;
	int f=1;
	for(int i=0;i<d;i++)
	{
		f=(m*f)%n;
	}

	return f;

}
void CCryptDESDlg::OnCreatkey() 
{
	// TODO: Add your control notification handler code here
		int primeA,primeB;
	int n;         //primeA*primeB;

	while(TRUE)
	{
		primeA=Prime[Ra(0,MAX_NUM/2)];
	    primeB=Prime[Ra(0,MAX_NUM-1)];
		n=primeA*primeB;
		if(primeA!=primeB&&n>256) break;
	}

	int ola=(primeA-1)*(primeB-1);
	int e,d;
	int t[1];

	e=Ra(0,ola/10);
    while(TRUE)
	{
		if(Get_GCD(ola,e,t))
		{
			d=t[0];
			break;
		}
		e++;
	}
	//m_PUn=n;
	m_PRn=n;

	m_PUe=e;
	m_PRd=d;

	m_Keyleft=primeA;
    m_Keyright=primeB;

	UpdateData(FALSE);

}

void CCryptDESDlg::OnOK() 
{
	// TODO: Add extra validation here
	Translate();

	
	//CDialog::OnOK();
	//CDialog::OnOK();
}
int CCryptDESDlg::Get_GCD(int ola, int e, int *d)//扩展欧拉算法，计算最大公约数和乘法逆元
{
	int A[3]={1,0,ola};
	int B[3]={0,1,e};
	int T[3];
	int q;
	while(TRUE)
	{
		if(B[2]==0||(B[2]==1&&d[0]<0))
			return 0;
		if(B[2]==1&&d[0]>0)
			return 1;
		q=A[2]/B[2];
		T[0]=A[0]-q*B[0]; T[1]=A[1]-q*B[1]; T[2]=A[2]-q*B[2];
		A[0]=B[0]; A[1]=B[1]; A[2]=B[2];
		B[0]=T[0]; B[1]=T[1]; B[2]=T[2];
		d[0]=B[1];

	}

}

int CCryptDESDlg::Ra(int f, int l)//返回从f到l(f要比l小)之间的随机数
{
	srand((unsigned)time(NULL));
	int n;
	if(f<=l)
	{
		n=rand()%(l-f);
		return (n+f);
	}
	return 0;
}


void CCryptDESDlg::OnOk2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	/////////////////////////////////////////////////////以下更改
	CString str=m_Input;
	int length=str.GetLength();
	CString str2;
	int k2,k3,k4,M;
	unsigned char ch,m1,m2,m3;
	for(int i=0;i<length/3;i++)
	{
		m1=str.GetAt(i*3);
		m2=str.GetAt(i*3+1);
		m3=str.GetAt(i*3+2);
		k2=(int)m1-65;
		k4=(int)m2-65;
		k3=(int)m3-65;
		M=k2+k4*58+k3*58*58;
		ch=(unsigned char)Get_C(M);
		str2.Insert(i,ch);
	
	}
	
	SetDlgItemText(IDC_OUTPUT,str2);
}

int CCryptDESDlg::Get_C(int c)
{
	int e=m_PUe;
	int n=m_PRn;
	int f=1;
	for(int i=0;i<e;i++)
	{
		f=(f*c)%n;
	}
	return f;
}

void CCryptDESDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);	
 if(Primep(m_p))
{
	int a,d,x;
	for(a=2;a<m_p;a++)
	{
		x=1;
		for(d=1;d<m_p;d++)
		{
			x=(x*a)%m_p;
			if(x==1)
				break;
		}
		if(d==m_p-1)
		{
		
		
			m_a=a;
			UpdateData(false);
		}
	}
}
 else
	 MessageBox("请确定输入的数是素数!");
    return;
}

void CCryptDESDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);//用于将屏幕中控件的数据交换到变量中
    if(Primep(m_p))
	{
     
	
	m_k1=rand();
	UpdateData(false);//用于将数据在屏幕中对应空间中显示出来
	}
	else
	{
	 MessageBox("请确定输入的数是素数!");
    return;
	}
}

void CCryptDESDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if(m_k1==0)
		{
			MessageBox("请先选择随机数！");
		}
	else if(m_a==0)
		{
			MessageBox("请选择生成元！");
		}
	else
	{
	int temp=1;
	for(int i=0;i<m_k1;i++)
	{
		temp=temp*m_a;
		temp=temp%m_p;
	
	}
	
	m_aa = temp;
	UpdateData(false);
	}
}

void CCryptDESDlg::OnButton4() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);//用于将屏幕中控件的数据交换到变量中
    if(Primep(m_p))
	{
     
	
	m_k2=rand();
	UpdateData(false);//用于将数据在屏幕中对应空间中显示出来
	}
	else
	{
	 MessageBox("请确定输入的数是素数!");
    return;
	}
}

void CCryptDESDlg::OnButton7() 
{
	// TODO: Add your control notification handler code here
UpdateData(true);
	int temp=1;
	for(int i=0;i<m_k2;i++)
	{
		temp=temp*m_aa;
		temp=temp%m_p;
	
	}
	
	m_kb = temp;
	UpdateData(false);
}
int CCryptDESDlg::Primep(long n)

{ 
    if(n<=0||n==1)
		return false;
    else
	{
    int i;
    int k;
    k=(int)sqrt((double)n);
    for(i = 2; i <= k; i++)
        if(n%i==0) break;
    if(i>k)
             return true;
       else
             return false;
	}
}



void CCryptDESDlg::OnButton6() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if(m_p==0||m_a==0)
	      MessageBox("请确认输入的数的正确性！");
	else if(m_k1==0||m_k2==0||m_aa==0||m_bb==0)
	      MessageBox("请按步骤进行，先生成随机数，再计算数！");   
	else
	{
	int temp=1;
	for(int i=0;i<m_k1;i++)
	{
		temp=temp*m_bb;
		temp=temp%m_p;
	
	}
	
	m_ka = temp;
	UpdateData(false);
	}
}

void CCryptDESDlg::OnButton5() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
		if(m_k2==0)
			{
				MessageBox("请先选择随机数！");
			}
		else if(m_a==0)
			{
				MessageBox("请选择生成元！");
			}
		else
			{
			int temp=1;
			for(int i=0;i<m_k2;i++)
				{
					temp=temp*m_a;
					temp=temp%m_p;
				}
			m_bb = temp;
			UpdateData(false);
			}
}


void CCryptDESDlg::OnEnChangePrd()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。



	// TODO:  在此添加控件通知处理程序代码
}


void CCryptDESDlg::OnEnChangePue()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。



	// TODO:  在此添加控件通知处理程序代码
}
