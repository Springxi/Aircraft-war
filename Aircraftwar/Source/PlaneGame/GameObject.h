#pragma once

//��Ϸ����ĸ���
class CGameObject : public CObject
{
public:

	CGameObject(int x=0,int y=0);
	virtual ~CGameObject();
	
	//���ƶ���
	virtual BOOL Draw(CDC* pDC,BOOL bPause)=0;

	//��þ�������
	virtual CRect GetRect()=0;

	//������Ͻ�����
	CPoint GetPoint()
	{
		return m_ptPos;
	}

protected:
	//����ͼ��
	static BOOL LoadImage(CImageList& imgList,UINT bmpID,COLORREF crMask,int cx,int cy,int nInitial);
protected:
	//�����λ��
	CPoint  m_ptPos;
};


