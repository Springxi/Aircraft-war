#pragma once
#include "GameObject.h"

class boer :public CGameObject
{
public:
	boer(int x,int y,int nMontion);
	~boer(void);

	BOOL Draw(CDC* pDC,BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos,CPoint(m_ptPos.x+BALL_HEIGHT,m_ptPos.y+BALL_HEIGHT));
	}
private:
	static const int BALL_HEIGHT=115;
	static CImageList m_Images;
	int    m_nMotion;
};
