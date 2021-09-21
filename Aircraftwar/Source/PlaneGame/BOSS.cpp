#include "StdAfx.h"
#include "BOSS.h"
#include "resource.h"

CImageList BOSS::m_Images;
	bool xx=0;
BOSS::BOSS(void)

{
	//随机确定X位置
	m_ptPos.x = 0;

	//随机确定图像索引
	m_nImgIndex = 0;

	//根据图像索引确定方向
	m_nMotion=1;
	m_ptPos.y=20;

	//随机确定速度
	m_V = 1; 

	m_nWait=0;
}

BOSS::~BOSS(void)
{
}
BOOL BOSS::LoadImage()
{
	
	return CGameObject::LoadImage(m_Images,IDB_BITMAP7,RGB(255,255,255),475,185,1);
	
}
BOOL BOSS::Draw(CDC* pDC,BOOL bPause)
{
	m_nWait++;
	if(m_nWait>20)
		m_nWait=0;

	if(!bPause)
	{ 
		if (m_ptPos.x==350)		xx=1;
		if (m_ptPos.x==0)		xx=0;	
		if (xx==0)
		m_ptPos.x = m_ptPos.x+ m_nMotion * m_V;
		if (xx==1)
		m_ptPos.x = m_ptPos.x- m_nMotion * m_V;
		
		
	}

	if(m_ptPos.y > GAME_HEIGHT+ENEMY_HEIGHT )
		return FALSE;
	if(m_ptPos.y < -ENEMY_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC,m_nImgIndex,m_ptPos,ILD_TRANSPARENT);

	return TRUE;
}
BOOL BOSS::Fired()
{
	if(m_nWait==0)
		return TRUE;
	else
		return FALSE;
}