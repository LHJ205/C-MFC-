// Main.cpp : 实现文件
//

#include "stdafx.h"
#include "CryptDES.h"
#include "Main.h"
#include "afxdialogex.h"


// Main 对话框

IMPLEMENT_DYNAMIC(Main, CDialogEx)

Main::Main(CWnd* pParent /*=NULL*/)
	: CDialogEx(Main::IDD, pParent)
{

}

Main::~Main()
{
}

void Main::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Main, CDialogEx)
END_MESSAGE_MAP()


// Main 消息处理程序
