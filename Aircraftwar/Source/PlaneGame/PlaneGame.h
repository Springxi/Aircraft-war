// PlaneGame.h : PlaneGame Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CPlaneGameApp:
// �йش����ʵ�֣������ PlaneGame.cpp
//

class CPlaneGameApp : public CWinApp
{
public:
	CPlaneGameApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPlaneGameApp theApp;