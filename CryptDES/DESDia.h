#pragma once


// DESDia �Ի���

class DESDia : public CDialogEx
{
	DECLARE_DYNAMIC(DESDia)

public:
	DESDia(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DESDia();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
