// DES.h: interface for the CDES class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DES_H__ED5BB782_2525_428A_915F_2E3CDEFC9091__INCLUDED_)
#define AFX_DES_H__ED5BB782_2525_428A_915F_2E3CDEFC9091__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum    {ENCRYPT1,DECRYPT};
typedef bool	(*PSubKey)[16][48];

class CDES  
{
public:
	CDES();
	virtual ~CDES();

public:
	bool	Encrypt(char *Out,char *In,UINT len,const char *KeyStr=0);//����
	bool	Decrypt(char *Out,char *In,UINT len,const char *KeyStr=0);//����
	bool	SetSubKey(const char *KeyStr);//��������Կ����������Կ
	static	char* RandKeyStr(char KeyStr[9]);//���������Կ��
private:

	void	DES(char Out[8],char In[8],const PSubKey pSubKey,bool Type);//��/����

	void	SetSubKey(PSubKey pSubKey,const char Key[8]);//��������Կ����16Ȧ����Կ
	void	F_func(bool In[32],const bool Ki[48]);//f ����
	void	S_func(bool Out[32],const bool In[48]);//S �д���

private:
	bool	SubKey[2][16][48];//16Ȧ����Կ
	bool    Is3DES;//3��DES��־
	char    deskey[17];//��Կ��������


};

#endif // !defined(AFX_DES_H__ED5BB782_2525_428A_915F_2E3CDEFC9091__INCLUDED_)
