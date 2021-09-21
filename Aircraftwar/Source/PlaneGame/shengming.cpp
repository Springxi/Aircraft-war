#include "StdAfx.h"
#include "shengming.h"
#include "resource.h"

CImageList shengming::m_Images;

shengming::shengming(void)
{
	//���ȷ��Xλ��
	m_ptPos.x = rand()%(GAME_WIDTH-ENEMY_HEIGHT)+1;

	//���ȷ��ͼ������
	m_nImgIndex = 0;

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

shengming::~shengming(void)
{
}
BOOL shengming::LoadImage()
{
	return CGameObject::LoadImage(m_Images,IDB_BITMAP9,RGB(0,0,0),28,18,1);
}
BOOL shengming::Draw(CDC* pDC,BOOL bPause)
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