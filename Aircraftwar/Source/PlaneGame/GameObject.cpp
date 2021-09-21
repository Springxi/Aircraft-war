// GameObject.cpp : 实现文件
//

#include "stdafx.h"
#include "GameObject.h"


// CGameObject


CGameObject::CGameObject(int x,int y):m_ptPos(x,y)
{
	
}
CGameObject::~CGameObject()
{
}
BOOL CGameObject::LoadImage(CImageList& imgList,UINT bmpID,COLORREF crMask,int cx,int cy,int nInitial)
{
	CBitmap bmp;
	if(!bmp.LoadBitmap(bmpID))
		return FALSE;

	if(!imgList.Create(cx, cy, ILC_COLOR24|ILC_MASK, nInitial, 0))
		return FALSE;
	

	imgList.Add(&bmp, crMask);

	return TRUE;
}

