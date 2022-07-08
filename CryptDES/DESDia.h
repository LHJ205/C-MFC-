#pragma once


// DESDia 对话框

class DESDia : public CDialogEx
{
	DECLARE_DYNAMIC(DESDia)

public:
	DESDia(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DESDia();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
