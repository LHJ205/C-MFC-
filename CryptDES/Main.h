#pragma once


// Main �Ի���

class Main : public CDialogEx
{
	DECLARE_DYNAMIC(Main)

public:
	Main(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Main();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
