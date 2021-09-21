// PlaneGameView.cpp : CPlaneGameView ���ʵ��
//

#include "stdafx.h"
#include "PlaneGame.h"
#include "jiang.h"
#include "BOSS.h"
#include "PlaneGameDoc.h"
#include "PlaneGameView.h"
#include "MyPlane.h"
#include "Enemy.h"
#include "Enemy1.h"
#include "Bomb.h"
#include "boer.h"
#include "Ball.h"
#include "shengming.h"
#include "Explosion.h"

#include <atlimage.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

bool ok;
int xxxx=0;
int yyyy=0;
int note=1;
int tttt=0;
int bosslife=200;
bool boss = false;
bool boss1 = false;
int RR =1;
// CPlaneGameView

IMPLEMENT_DYNCREATE(CPlaneGameView, CView)

BEGIN_MESSAGE_MAP(CPlaneGameView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()

	ON_WM_DESTROY()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CPlaneGameView ����/����

CPlaneGameView::CPlaneGameView():m_pMe(NULL)
{
	// TODO: �ڴ˴���ӹ������
	//CBitmap bmp;
//	bmp.LoadOEMBitmap(IDB_BITMAP2);//����λͼ
//	m_brush.CreatePatternBrush(&bmp);
	
	
}

CPlaneGameView::~CPlaneGameView()
{
}

BOOL CPlaneGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	
	return CView::PreCreateWindow(cs);
}

// CPlaneGameView ����

void CPlaneGameView::OnDraw(CDC* pDC)
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

}


// CPlaneGameView ��ӡ

BOOL CPlaneGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CPlaneGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CPlaneGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CPlaneGameView ���

#ifdef _DEBUG
void CPlaneGameView::AssertValid() const
{
	CView::AssertValid();
}

void CPlaneGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlaneGameDoc* CPlaneGameView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlaneGameDoc)));
	return (CPlaneGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CPlaneGameView ��Ϣ�������
void CPlaneGameView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// TODO: �ڴ����ר�ô����/����û���
	//��ʼ����Ϸ
	InitGame();
}
void CPlaneGameView::StopGame()
{
	delete m_pMe;
	delete m_pMemDC;
	delete m_pDC;
	delete m_pMemBitmap;
}
BOOL CPlaneGameView::InitGame()
{
	CRect rc;
	GetClientRect(rc);
	 MessageBox(TEXT("һ�����̲������������Ҽ��ƶ�ս�������¿ո�������ӵ���ը�ٵл��÷֣�\n\n�����Ե���Ϸ�е�������������������߼���\n\n����ս������ֵ��ʼΪ5��Ѫ����ʼֵΪ100\n\n�ġ���Ϸ�����У�������ʱ����Esc���˳�\n\n�塢��Ϸ֧��ͬʱ����Z��ո�����������ӵ����ڵ������л�ü��ܣ�\n\n������Ϸ�а���X���������޵�ģʽ������C�����˳��޵�ģʽ\n\n�ߡ���Ϸ�а���V�����������������������з����ۻ�����������BOSS��\n\n�ˡ�����Ϸ����������ս��ģʽ���л����Σ�BOSS�����Σ���ӭ����"),
		TEXT("�ɻ���ս������Ϸ˵��"),MB_OK);//��ʼʱ�����Ի��������Ϸ˵��
	 int t  = MessageBox(TEXT(" ������������ģʽ��\n  YES��������ս��,NO��������ģʽ"),TEXT("O(��_��)O~"),MB_YESNO);
	 if (t==IDYES)
	 yyyy=1;
		
	//�������������
	srand( (unsigned)time( NULL ) );

	//�����豸DC
	m_pDC = new CClientDC(this);

	//�����ڴ�DC
	m_pMemDC = new CDC;
	m_pMemDC->CreateCompatibleDC(m_pDC);

	//�����ڴ�λͼ
	m_pMemBitmap = new CBitmap;
	m_pMemBitmap->CreateCompatibleBitmap(m_pDC,GAME_WIDTH,GAME_HEIGHT);

	//��λͼѡ���ڴ�DC
	m_pMemDC->SelectObject(m_pMemBitmap);

	CMyPlane::LoadImage();
	CEnemy::LoadImage(yyyy);
	CEnemy1::LoadImage(yyyy);
	CBomb::LoadImage();
	CBall::LoadImage();
	boer::LoadImage();
	BOSS::LoadImage();
	CExplosion::LoadImage();
	jiang::LoadImage();
	shengming::LoadImage();

	
	//��������(ս��)
	m_pMe = new CMyPlane;
	ok = true;
	
	//������Ϸ

	SetTimer(1,30,NULL);
	
	return TRUE;
}
void CPlaneGameView::UpdateFrame(CDC* pMemDC)
{
	wchar_t lifeleft[20];
	 wchar_t Score[20];
	wchar_t Level[20];
	int n=0; 

static int imagelocation = 0;//����ͼƬ��ȡλ�ó�ʼλ��
	CDC memDC;
	memDC.CreateCompatibleDC(pMemDC);
	CBitmap bmpDraw;
	if (RR % 3 == 1)
		bmpDraw.LoadBitmapW(IDB_BITMAP3); //����λͼ
	if (RR % 3 == 2)
		bmpDraw.LoadBitmapW(IDB_BITMAP13); //����λͼ
	if (RR % 3 == 0)
		bmpDraw.LoadBitmapW(IDB_BITMAP12); //����λͼ
	
	CBitmap* pbmpold = memDC.SelectObject(&bmpDraw);	
	pMemDC->BitBlt(0, imagelocation,808, 1213, &memDC, 0, 0, SRCCOPY);//���ö�̬����
	pMemDC->BitBlt(0, 0, 808, imagelocation, &memDC, 0,1213- imagelocation, SRCCOPY);//���ö�̬����
	imagelocation++;
	if (imagelocation == 1213)
		imagelocation = 0;
	//�����ҷ�ս��
	if(m_pMe!=NULL)
	{
	   m_pMe->Draw(m_pMemDC,FALSE);
	   //���Ƽ�¼��
	   if (xxxx==1)
	   {
		   pMemDC->SetBkMode(TRANSPARENT);

	   }
	  
			pMemDC->SetBkMode(TRANSPARENT);//���ֱ���͸��
			if (xxxx==1 )
			{
				wsprintf(lifeleft, L"�޵�ģʽ����", m_pMe->HP );
				pMemDC->SetTextColor( RGB(255, 255,0) );    //������ɫ
				pMemDC->TextOutW(10,105, lifeleft, _tcslen(lifeleft));//����λ��
			}
			wsprintf(lifeleft, L"��ǰѪ��:%d", m_pMe->HP );
			pMemDC->SetTextColor( RGB(255, 255,0) );    //������ɫ
			pMemDC->TextOutW(10,10, lifeleft, _tcslen(lifeleft));//����λ��
			wsprintf(lifeleft, L"ʣ������:%d", m_pMe->life );
			pMemDC->SetTextColor( RGB(255, 255,0) );
			pMemDC->TextOutW(10,35, lifeleft, _tcslen(lifeleft));
			wsprintf(Score, L"�÷�:%d", m_pMe->score );
			pMemDC->SetTextColor( RGB(255, 0, 0) );
			pMemDC->TextOutW(10,60, Score, _tcslen(Score));
			wsprintf(Level, L" ��%d ��", m_pMe->level );
			pMemDC->SetTextColor( RGB(255, 255, 255) );
			pMemDC->TextOutW(10,85, Level, _tcslen(Level));

			wsprintf(lifeleft, L"V����������BOSS��", m_pMe->HP );
			pMemDC->SetTextColor( RGB(255, 255,0) );    //������ɫ
			pMemDC->TextOutW(620,10, lifeleft, _tcslen(lifeleft));//����λ��

			wsprintf(lifeleft, L"X�޵� C�˳��޵�  ", m_pMe->life );
			pMemDC->SetTextColor( RGB(255, 255,0) );
			pMemDC->TextOutW(620,35, lifeleft, _tcslen(lifeleft));

			wsprintf(Level, L" ʣ��෢�ӵ���z+�ո�:%d", tttt );
			pMemDC->SetTextColor( RGB(255, 255, 255) );
			pMemDC->TextOutW(580,85, Level, _tcslen(Level));

			if (boss1)
			{
				wsprintf(Score, L"BOSS����ֵ:%d", bosslife );
				pMemDC->SetTextColor( RGB(255, 0, 0) );
				pMemDC->TextOutW(620,60, Score, _tcslen(Score));
			}
			
	   
	}
	else
	{   //Game Over
		if(note==1)
		{
			note=0;
			int t  = MessageBox(TEXT("����̫��ǿ������������������¿�ʼ�� ?"),TEXT("Game Over!"),MB_YESNO);//����ʱ�����Ի���
			if (t==IDYES)
			{
				tttt=0;
				if (boss1)
				{
					POSITION ePos1=NULL,ePos2=NULL;//���ڼ�¼��������λ��
					for(ePos1=m_ObjList[enBOSS].GetHeadPosition();(ePos2=ePos1)!=NULL;)
					{
						BOSS* pBOSS = (BOSS*)m_ObjList[enBOSS].GetNext(ePos1);
						CRect mRect = pBOSS->GetRect();
						//ɾ���л�
						m_ObjList[enBOSS].RemoveAt(ePos2);//��������ɾ��
						delete pBOSS;
						boss1 =false;
						boss =false;
			
					}
				}
				m_pMe = new CMyPlane;
				ok = true;
				note=1;
				SetTimer(1,30,NULL);
			}
			if (t == IDNO)
				PostQuitMessage(0); //�˳�

		}

	}
	//���� ��������ը���л�1/2���ӵ�,������BOSS��������BOSS�ӵ�
	for(int i=0;i<9;i++)
	{
		POSITION pos1,pos2;
		for( pos1 = m_ObjList[i].GetHeadPosition(); ( pos2 = pos1 ) != NULL ; )
		{
			CGameObject* pObj = (CGameObject*)m_ObjList[i].GetNext( pos1 );
			if(!pObj->Draw(pMemDC,FALSE))
			{
				m_ObjList[i].RemoveAt(pos2);
				delete pObj;
			}
		}
	}
	//�����ڴ�DC���豸DC
	m_pDC->BitBlt(0,0,GAME_WIDTH,GAME_HEIGHT,m_pMemDC,0,0,SRCCOPY);
}
void CPlaneGameView::AI()
{
	static int nCreator = rand() %10+4;
	static int n1Creator = rand() %8+10;
	//��������л�
	if(nCreator<=0 && m_pMe != NULL)
	{
		nCreator = rand()%10+3;
		if (m_pMe->level==1)
			m_ObjList[enEnemy].AddTail(new CEnemy);
		else if (m_pMe->level==2)
			m_ObjList[enEnemy1].AddTail(new CEnemy1);
		else  
		{
			//n1Creator = rand()%20+40;
			m_ObjList[enEnemy].AddTail(new CEnemy);
			m_ObjList[enEnemy1].AddTail(new CEnemy1);
		}
		
	}
	nCreator--;
		
			//������X��
	if(GetKey('X')==1)	
		xxxx=1;
	if(GetKey('C')==1)
		xxxx=0;
	if(m_pMe==NULL)
		return;


	//����
	if(GetKey('V')==1)
		
	{
		POSITION ePos1=NULL,ePos2=NULL;//���ڼ�¼��������λ��
		for(ePos1=m_ObjList[enEnemy].GetHeadPosition();(ePos2=ePos1)!=NULL;)
		{
			CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos1);
			CRect mRect = pEnemy->GetRect();
			//ɾ���л�
			m_ObjList[enEnemy].RemoveAt(ePos2);//��������ɾ��
			delete pEnemy;
			//��ӱ�ըЧ��
			  m_ObjList[enExplosion].AddTail(new CExplosion(mRect.left,mRect.top));	
		}
		for(ePos1=m_ObjList[enEnemy1].GetHeadPosition();(ePos2=ePos1)!=NULL;)
		{
			CEnemy1* pEnemy1 = (CEnemy1*)m_ObjList[enEnemy1].GetNext(ePos1);
			CRect mRect = pEnemy1->GetRect();
			//ɾ���л�
			m_ObjList[enEnemy1].RemoveAt(ePos2);//��������ɾ��
			delete pEnemy1;
			//��ӱ�ըЧ��
			  m_ObjList[enExplosion].AddTail(new CExplosion(mRect.left,mRect.top));	
		}
	}

	
	//��������
	if(n1Creator<=0)
	{
		n1Creator = rand()%20+100;
		m_ObjList[enjiang].AddTail(new jiang);
		m_ObjList[enshengming].AddTail(new shengming);

	}
	n1Creator--;




	//����ĸ���������ƶ�ս��
	for(int i=0;i<4;i++)
	{
		int nMeMotion=0;
		m_pMe->SetVerMotion(0);
		m_pMe->SetHorMotion(0);

		nMeMotion = GetKey(VK_UP);
		if(nMeMotion==1)
			m_pMe->SetVerMotion(1);
		    
		nMeMotion = GetKey(VK_DOWN);
		if(nMeMotion==1)
			m_pMe->SetVerMotion(-1);

		nMeMotion = GetKey(VK_RIGHT);
		if(nMeMotion==1)
			m_pMe->SetHorMotion(1);

		nMeMotion = GetKey(VK_LEFT);
		if(nMeMotion==1)
			m_pMe->SetHorMotion(-1);
	}
	//����BOSS
		if (m_pMe->score>=25 && !boss)
		{
			m_ObjList[enBOSS].AddTail(new BOSS);
			m_pMe->score++;
			boss = true;
			boss1 = true;
			bosslife=200;
		}
	

	//����ս������
	if(GetKey(VK_SPACE)==1)//�����˿ո��
	{
		if(m_pMe!=NULL && m_pMe->Fired())
		{
			CPoint pt = m_pMe->GetPoint();
			m_ObjList[enBomb].AddTail(new CBomb(pt.x+10,pt.y+10,0));
			m_ObjList[enBomb].AddTail(new CBomb(pt.x+40,pt.y+10,0));
			if (GetKey('Z') == 1 && tttt)				//ͬʱ��Z�Ϳո�� 
			{
					tttt--;
					m_ObjList[enBomb].AddTail(new CBomb(pt.x+12,pt.y+12,1));
					m_ObjList[enBomb].AddTail(new CBomb(pt.x+32,pt.y+12,2));
					m_ObjList[enBomb].AddTail(new CBomb(pt.x+12,pt.y+12,3));
					m_ObjList[enBomb].AddTail(new CBomb(pt.x+32,pt.y+12,4));
			}
		}
	}



	if(GetKey(VK_ESCAPE)==1)//�������˳���
		PostQuitMessage(0); //�˳�

	//�л������ӵ�

	CPoint PlanePt = m_pMe->GetPoint();
	for(POSITION ePos=m_ObjList[enEnemy].GetHeadPosition();ePos!=NULL;)
	{
          CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos);
		  if(!pEnemy->Fired())
			  continue;
		  CPoint  ePt = pEnemy->GetPoint();
		  BOOL by=TRUE;
		  if(by && ePt.x >= PlanePt.x && ePt.x<PlanePt.x+CMyPlane::PLANE_WIDTH)
		  {
              m_ObjList[enBall].AddTail(new CBall(ePt.x,ePt.y+10,pEnemy->GetMontion()));
		  }
	}
	for(POSITION ePos=m_ObjList[enEnemy1].GetHeadPosition();ePos!=NULL;)
	{
          CEnemy1* pEnemy1 = (CEnemy1*)m_ObjList[enEnemy1].GetNext(ePos);
		  if(!pEnemy1->Fired())
			  continue;
		  CPoint  ePt = pEnemy1->GetPoint();
		  BOOL by=TRUE;
		  if(by && ePt.x >= PlanePt.x && ePt.x<PlanePt.x+CMyPlane::PLANE_WIDTH)
		  {
              m_ObjList[enBall].AddTail(new CBall(ePt.x-5,ePt.y+10,pEnemy1->GetMontion()));
			  m_ObjList[enBall].AddTail(new CBall(ePt.x+25,ePt.y+10,pEnemy1->GetMontion()));
		  }
	}

	//BOSS ���䵼��
	CPoint PlanePt1 = m_pMe->GetPoint();
	for(POSITION eePos=m_ObjList[enBOSS].GetHeadPosition();eePos!=NULL;)
	{
          BOSS* pBOSS = (BOSS*)m_ObjList[enBOSS].GetNext(eePos);
		  if(!pBOSS->Fired())
			  continue;
		  CPoint  ePt = pBOSS->GetPoint();
		  BOOL by=TRUE;
          m_ObjList[enboer].AddTail(new boer(ePt.x+100,ePt.y+60,1));
		  m_ObjList[enboer].AddTail(new boer(ePt.x+300,ePt.y+60,1));

	}
	
	//�л��ӵ�ը��ս��
	POSITION bPos1=NULL,bPos2=NULL;
	CRect mRect = m_pMe->GetRect();
	for(bPos1=m_ObjList[enBall].GetHeadPosition();( bPos2 = bPos1 ) != NULL;)
	{
		CBall* pBall = (CBall*)m_ObjList[enBall].GetNext(bPos1);
		CRect bRect = pBall->GetRect();
		CRect tmpRect;
		if(tmpRect.IntersectRect(&bRect,mRect))
		{
			//��ӱ�ըЧ��
			
			m_ObjList[enExplosion].AddTail(
				new CExplosion(mRect.left,mRect.top)
				);

			//ɾ���ӵ�
			m_ObjList[enBall].RemoveAt(bPos2);
			delete pBall;
			if (xxxx==0)
			m_pMe->HP -= 50;
			if(m_pMe->HP <= 0)
			{
			   m_pMe->life--;
			   m_pMe->HP = 100;
			}
			if(m_pMe->life < 0 && xxxx==0)
			{
				//ɾ��ս��
				delete m_pMe;
				ok = false;
				m_pMe=NULL;
				break;
			}
		}
	}

	//BOSS ����ը��ս��
		POSITION bPos11=NULL,bPos22=NULL;
	
	for(bPos11=m_ObjList[enboer].GetHeadPosition();( bPos22 = bPos11 ) != NULL;)
	{
		boer* pboer = (boer*)m_ObjList[enboer].GetNext(bPos11);
		CRect bbRect = pboer->GetRect();
		CRect tmpRect;
		if(tmpRect.IntersectRect(&bbRect,mRect))
		{
			//��ӱ�ըЧ��
			
			m_ObjList[enExplosion].AddTail(
				new CExplosion(mRect.left,mRect.top)
				);

			//ɾ���ӵ�
			m_ObjList[enboer].RemoveAt(bPos22);
			delete pboer;
			if (xxxx==0)
			m_pMe->life--;
			if(m_pMe->life < 0 && xxxx==0)
			{
				//ɾ��ս��
				delete m_pMe;
				ok = false;
				m_pMe=NULL;
				break;
			}
		}
	}
	    //ײ��
	POSITION ePos1=NULL,ePos2=NULL;//���ڼ�¼��������λ��
	for(ePos1=m_ObjList[enEnemy].GetHeadPosition();(ePos2=ePos1)!=NULL;)
	{
		CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos1);
		CRect eRect = pEnemy->GetRect();
		CRect tmpRect;
		if(tmpRect.IntersectRect(eRect,mRect)) //�������Ϊ�գ��򷵻ط���ֵ�����������Ϊ���򷵻�
		{
			//ɾ���л�
			m_ObjList[enEnemy].RemoveAt(ePos2);//��������ɾ��
			delete pEnemy;
			//��ӱ�ըЧ��
			  m_ObjList[enExplosion].AddTail(new CExplosion(mRect.left,mRect.top));
			if (xxxx==0)
			m_pMe->HP -= 50;
			if(m_pMe->HP <= 0)
			{
			   m_pMe->life--;
			   m_pMe->HP = 100;
			}
          if(m_pMe->life < 0)
			{
			  //ɾ��ս��
			delete m_pMe;
			ok = false;
			m_pMe=NULL;
			break;
			}
	}
	}
	   //ײ��2
	for(ePos1=m_ObjList[enEnemy1].GetHeadPosition();(ePos2=ePos1)!=NULL;)
	{
		CEnemy1* pEnemy1 = (CEnemy1*)m_ObjList[enEnemy1].GetNext(ePos1);
		CRect eRect = pEnemy1->GetRect();
		CRect tmpRect;
		if(tmpRect.IntersectRect(eRect,mRect)) //�������Ϊ�գ��򷵻ط���ֵ�����������Ϊ���򷵻�
		{
			//ɾ���л�
			m_ObjList[enEnemy1].RemoveAt(ePos2);//��������ɾ��
			delete pEnemy1;
			//��ӱ�ըЧ��
			  m_ObjList[enExplosion].AddTail(new CExplosion(mRect.left,mRect.top));
			if (xxxx==0)
			m_pMe->HP -= 50;
			if(m_pMe->HP <= 0)
			{
			   m_pMe->life--;
			   m_pMe->HP = 100;
			}
          if(m_pMe->life < 0)
			{
			  //ɾ��ս��
			delete m_pMe;
			ok = false;
			m_pMe=NULL;
			break;
			}
            //��ԭ�ӵ�
//			m_pMe->Bkind = 1;
		}
	}

	//	�Խ���
	
	for(ePos1=m_ObjList[enjiang].GetHeadPosition();(ePos2=ePos1)!=NULL;)
	{
		jiang* pjiang = (jiang*)m_ObjList[enjiang].GetNext(ePos1);
		CRect eRect = pjiang->GetRect();
		CRect tmpRect;
		if(tmpRect.IntersectRect(eRect,mRect)) //�������Ϊ�գ��򷵻ط���ֵ�����������Ϊ���򷵻�
		{
			//ɾ������
			m_ObjList[enjiang].RemoveAt(ePos2);//��������ɾ��
			delete pjiang;
			//���Ч��
			 // m_ObjList[enExplosion].AddTail(new CExplosion(mRect.left,mRect.top));
			tttt += 10;
          break;
		}
	}
	//�������
		for(ePos1=m_ObjList[enshengming].GetHeadPosition();(ePos2=ePos1)!=NULL;)
	{
		shengming* pshengming = (shengming*)m_ObjList[enshengming].GetNext(ePos1);
		CRect eRect = pshengming->GetRect();
		CRect tmpRect;
		if(tmpRect.IntersectRect(eRect,mRect)) //�������Ϊ�գ��򷵻ط���ֵ�����������Ϊ���򷵻�
		{
			//ɾ������
			m_ObjList[enshengming].RemoveAt(ePos2);//��������ɾ��
			delete pshengming;
			//���Ч��
			 // m_ObjList[enExplosion].AddTail(new CExplosion(mRect.left,mRect.top));
		m_pMe->life ++;;
          break;
		}
	}
		//ײBOSS
		POSITION eeePos1=NULL,eeePos2=NULL;//���ڼ�¼��������λ��
	for(eeePos1=m_ObjList[enBOSS].GetHeadPosition();(eeePos2=eeePos1)!=NULL;)
	{
		BOSS* pBOSS = (BOSS*)m_ObjList[enBOSS].GetNext(eeePos1);
		CRect eRect = pBOSS->GetRect();
		CRect tmpRect;
		if(tmpRect.IntersectRect(eRect,mRect)) //�������Ϊ�գ��򷵻ط���ֵ�����������Ϊ���򷵻�
		{
			//��ӱ�ըЧ��
			  m_ObjList[enExplosion].AddTail(new CExplosion(mRect.left,mRect.top));
			if (xxxx==0)
				m_pMe->life--;
			if(m_pMe->life < 0 && xxxx==0)
			{
			  //ɾ��ս��
				delete m_pMe;
				boss = false;
				boss1 = false;
				ok = false;
				m_pMe=NULL;
				break;
			}
		}
	}

	//ս������ը��BOSS
		POSITION mPoos1=NULL,mPoos2=NULL;
	for(mPoos1=m_ObjList[enBomb].GetHeadPosition();(mPoos2=mPoos1)!=NULL;)
	{
		CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(mPoos1);
		CRect bRect = pBomb->GetRect();

		POSITION ePoos1=NULL,ePoos2=NULL;
		for(ePoos1=m_ObjList[enBOSS].GetHeadPosition();(ePoos2=ePoos1)!=NULL;)
		{
			CEnemy* pBOSS = (CEnemy*)m_ObjList[enBOSS].GetNext(ePoos1);
			CRect mRect = pBOSS->GetRect();
			CRect tmpRect;
			if(tmpRect.IntersectRect(&bRect,mRect))
			{
				bosslife--;
				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left+210,mRect.top+100)
					);
				//ɾ������
				m_ObjList[enBomb].RemoveAt(mPoos2);
				delete pBomb;

				//ɾ��BOSS
				if (bosslife<=0)
				{
					boss1=false;
					m_ObjList[enBOSS].RemoveAt(ePoos2);
					delete pBOSS;
					
				//	break;
				}
				

			}
		}
	}

	//ս������ը���л�
	POSITION mPos1=NULL,mPos2=NULL;
	for(mPos1=m_ObjList[enBomb].GetHeadPosition();(mPos2=mPos1)!=NULL;)
	{
		CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(mPos1);
		CRect bRect = pBomb->GetRect();

		POSITION ePos1=NULL,ePos2=NULL;
		for(ePos1=m_ObjList[enEnemy].GetHeadPosition();(ePos2=ePos1)!=NULL;)
		{
			CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos1);
			CRect mRect = pEnemy->GetRect();
			CRect tmpRect;
			if(tmpRect.IntersectRect(&bRect,mRect))
			{
				//��ӱ�ըЧ��
				m_pMe->score ++;
				ok = true;
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left,mRect.top)
					);
				//ɾ������
				m_ObjList[enBomb].RemoveAt(mPos2);
				delete pBomb;

				//ɾ���л�
				m_ObjList[enEnemy].RemoveAt(ePos2);
				delete pEnemy;
				break;

			}
		}
	
	}

	//ս������ը���л�2
	for(mPos1=m_ObjList[enBomb].GetHeadPosition();(mPos2=mPos1)!=NULL;)
	{
		CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(mPos1);
		CRect bRect = pBomb->GetRect();

		POSITION ePos1=NULL,ePos2=NULL;
		for(ePos1=m_ObjList[enEnemy1].GetHeadPosition();(ePos2=ePos1)!=NULL;)
		{
			CEnemy1* pEnemy1 = (CEnemy1*)m_ObjList[enEnemy1].GetNext(ePos1);
			CRect mRect = pEnemy1->GetRect();
			CRect tmpRect;
			if(tmpRect.IntersectRect(&bRect,mRect))
			{
				//��ӱ�ըЧ��
				m_pMe->score ++;
				ok = true;
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left,mRect.top)
					);
				//ɾ������
				m_ObjList[enBomb].RemoveAt(mPos2);
				delete pBomb;

				//ɾ���л�
				m_ObjList[enEnemy1].RemoveAt(ePos2);
				delete pEnemy1;
				break;

			}
		}
	
	}
}

void CPlaneGameView::OnTimer(UINT_PTR nIDEvent)
{
	//ˢ����Ϸ֡����: ���ڴ�DC�ϻ�ͼ
	UpdateFrame(m_pMemDC);
	AI();
	if (ok)
	if (m_pMe->score >= 100  && !boss1)
	{
		ok = false;
		KillTimer(1);
		int t  = MessageBox(TEXT("��ϲ����ͻ����Χ���������һ���� ?"),TEXT("Congratulation��"),MB_YESNO);//����ʱ�����Ի���
		if (t == IDYES){
			RR++;
			boss = false;
			m_pMe->score=0;
			m_pMe->level++;
			POSITION ePos1=NULL,ePos2=NULL;//���ڼ�¼��������λ��
	for(ePos1=m_ObjList[enEnemy].GetHeadPosition();(ePos2=ePos1)!=NULL;)
	{
		CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos1);
		CRect mRect = pEnemy->GetRect();
			//ɾ���л�
			m_ObjList[enEnemy].RemoveAt(ePos2);//��������ɾ��
			delete pEnemy;
			
	}



		for(ePos1=m_ObjList[enEnemy1].GetHeadPosition();(ePos2=ePos1)!=NULL;)
	{
		CEnemy1* pEnemy1 = (CEnemy1*)m_ObjList[enEnemy1].GetNext(ePos1);
		CRect mRect = pEnemy1->GetRect();
			//ɾ���л�
			m_ObjList[enEnemy1].RemoveAt(ePos2);//��������ɾ��
			delete pEnemy1;
			
	}
			SetTimer(1,30,NULL);
		}
		else 
		PostQuitMessage(0);
	}

	CView::OnTimer(nIDEvent);
}



void CPlaneGameView::OnDestroy()
{
	CView::OnDestroy();
	this->StopGame();
	// TODO: �ڴ˴������Ϣ����������
}

void CPlaneGameView::OnPaint()
{
	CPaintDC dc(this);
	 // device context for painting
	// TODO: �ڴ˴������Ϣ����������

	// ��Ϊ��ͼ��Ϣ���� CView::OnPaint()
	
	}
