#include "StdAfx.h"
#include "Ball.h"
#include "resource.h"
#include "MyPlane.h"

CImageList CBall::m_Images;

CBall::CBall(int x,int y,int nMontion):CGameObject(x,y),m_nMotion(nMontion)
{

}

CBall::~CBall(void)
{
}
BOOL CBall::Draw(CDC* pDC,BOOL bPause)
{
	if(!bPause)
	{
		m_ptPos.y = m_ptPos.y + m_nMotion * 12;
		//m_ptPos.x = m_ptPos.x + m_nMotion * 12;
		
	}

	if(m_ptPos.y > GAME_HEIGHT+BALL_HEIGHT )
		return FALSE;
	if(m_ptPos.y < -BALL_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC,0,m_ptPos,ILD_TRANSPARENT);

	return TRUE;
}

BOOL CBall::LoadImage()
{
	return CGameObject::LoadImage(m_Images,IDB_BITMAP2,RGB(0,0,0),29,37,1);
}