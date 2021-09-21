#include "StdAfx.h"
#include "Enemy1.h"
#include "resource.h"

CImageList CEnemy1::m_Images;

CEnemy1::CEnemy1(void)
: x(0)
{
	//���ȷ��Xλ��
	m_ptPos.x = rand()%(GAME_WIDTH-ENEMY_HEIGHT)+1;

	//���ȷ��ͼ������
	m_nImgIndex = rand()%2;

	//����ͼ������ȷ������
	m_nMotion=1;
	m_ptPos.y=-ENEMY_HEIGHT;
	if (m_nImgIndex%2!=0)//�����ͼ��������ż��
	{
		//m_nMotion=-1;
		m_ptPos.y = GAME_HEIGHT+ENEMY_HEIGHT;
	}
	//���ȷ���ٶ�
	m_V = rand()%6+4;

	m_nWait=0;
}

CEnemy1::~CEnemy1(void)
{
}
BOOL CEnemy1::LoadImage(int t)
{
	if (t==0)
	return CGameObject::LoadImage(m_Images,IDB_BITMAP11,RGB(0,0,0),57,37,1);
	return CGameObject::LoadImage(m_Images,IDB_BITMAP1,RGB(0,0,0),1,35,1);
}
BOOL CEnemy1::Draw(CDC* pDC,BOOL bPause)
{
	m_nWait++;
	if(m_nWait>20)
		m_nWait=0;

	if(!bPause)
	{
		m_ptPos.y = m_ptPos.y + m_nMotion * m_V;
	}

	if(m_ptPos.y > GAME_HEIGHT+ENEMY_HEIGHT )
		return FALSE;
	if(m_ptPos.y < -ENEMY_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC,m_nImgIndex,m_ptPos,ILD_TRANSPARENT);

	return TRUE;
}
BOOL CEnemy1::Fired()
{
	if(m_nWait==0)
		return TRUE;
	else
		return FALSE;
}