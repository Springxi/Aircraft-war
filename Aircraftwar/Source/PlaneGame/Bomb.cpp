#include "StdAfx.h"
#include "Bomb.h"
#include "resource.h"


CImageList CBomb::m_Images;


CBomb::CBomb(int x,int y,int z):CGameObject(x,y)
, kind(z)
{

}

CBomb::~CBomb(void)
{
}
BOOL CBomb::LoadImage()
{
	return CGameObject::LoadImage(m_Images,IDB_BITMAP6,RGB(0,0,0),15,29,1);
}
BOOL CBomb::Draw(CDC* pDC,BOOL bPause)
{
	if(!bPause)
	{
		if (kind ==1)
			m_ptPos.x = m_ptPos.x - 2;
		if (kind ==3)
			m_ptPos.x = m_ptPos.x - 4;
		if (kind ==2)
			m_ptPos.x = m_ptPos.x + 2;
		if (kind ==4)
			m_ptPos.x = m_ptPos.x + 4;
		if (kind ==0)
			m_ptPos.x = m_ptPos.x ;

		m_ptPos.y = m_ptPos.y - 12;
	}

	if(m_ptPos.y < -BOMB_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC,0,m_ptPos,ILD_TRANSPARENT);

	return TRUE;
}