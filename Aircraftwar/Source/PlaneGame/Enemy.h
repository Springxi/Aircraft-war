#pragma once
#include "gameobject.h"

class CEnemy :public CGameObject
{
public:
	CEnemy(void);
	~CEnemy(void);

	BOOL Draw(CDC* pDC,BOOL bPause);

	static BOOL LoadImage(int t);

	CRect GetRect()
	{
		return CRect(m_ptPos,CPoint(m_ptPos.x+ENEMY_HEIGHT,m_ptPos.y+ENEMY_HEIGHT));
	}

	int GetMontion() const
	{
		return m_nMotion;
	}
	//�Ƿ���Կ������ӵ�
	BOOL Fired();
private:
	static const int ENEMY_HEIGHT = 35;
	static CImageList m_Images;
	int    m_nMotion;//���� 1->���� 0->ֹͣ -1->����
	//ͼ������
	int m_nImgIndex;
	//�ٶ�
	int m_V;
	int    m_nWait;//������ʱ
public:
	int x;
};
