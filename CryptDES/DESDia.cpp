// DESDia.cpp : 实现文件
//

#include "stdafx.h"
#include "CryptDES.h"
#include "DESDia.h"
#include "afxdialogex.h"


// DESDia 对话框

IMPLEMENT_DYNAMIC(DESDia, CDialogEx)

DESDia::DESDia(CWnd* pParent /*=NULL*/)
	: CDialogEx(DESDia::IDD, pParent)
{

}

DESDia::~DESDia()
{
}

void DESDia::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DESDia, CDialogEx)
END_MESSAGE_MAP()


// DESDia 消息处理程序
