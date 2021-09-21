// PlaneGameView.cpp : CPlaneGameView 类的实现
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()

	ON_WM_DESTROY()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CPlaneGameView 构造/析构

CPlaneGameView::CPlaneGameView():m_pMe(NULL)
{
	// TODO: 在此处添加构造代码
	//CBitmap bmp;
//	bmp.LoadOEMBitmap(IDB_BITMAP2);//加载位图
//	m_brush.CreatePatternBrush(&bmp);
	
	
}

CPlaneGameView::~CPlaneGameView()
{
}

BOOL CPlaneGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	
	return CView::PreCreateWindow(cs);
}

// CPlaneGameView 绘制

void CPlaneGameView::OnDraw(CDC* pDC)
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

}


// CPlaneGameView 打印

BOOL CPlaneGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CPlaneGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CPlaneGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CPlaneGameView 诊断

#ifdef _DEBUG
void CPlaneGameView::AssertValid() const
{
	CView::AssertValid();
}

void CPlaneGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlaneGameDoc* CPlaneGameView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlaneGameDoc)));
	return (CPlaneGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CPlaneGameView 消息处理程序
void CPlaneGameView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// TODO: 在此添加专用代码和/或调用基类
	//初始化游戏
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
	 MessageBox(TEXT("一、键盘操作，上下左右键移动战机，按下空格键发射子弹，炸毁敌机得分，\n\n二、吃掉游戏中掉落物可以增加生命或者技能\n\n三、战机生命值初始为5，血量初始值为100\n\n四、游戏过程中，可是随时按下Esc键退出\n\n五、游戏支持同时按下Z与空格键，发射多个子弹（在掉落物中获得技能）\n\n六、游戏中按下X键，进入无敌模式，按下C键，退出无敌模式\n\n七、游戏中按下V键，进行清屏，清屏不进行分数累积（清屏不含BOSS）\n\n八、本游戏增加了隐形战争模式（敌机隐形，BOSS不隐形）欢迎体验"),
		TEXT("飞机大战——游戏说明"),MB_OK);//开始时弹出对话框介绍游戏说明
	 int t  = MessageBox(TEXT(" 你想体验隐形模式吗？\n  YES进入隐形战争,NO进入正常模式"),TEXT("O(∩_∩)O~"),MB_YESNO);
	 if (t==IDYES)
	 yyyy=1;
		
	//产生随机数种子
	srand( (unsigned)time( NULL ) );

	//建立设备DC
	m_pDC = new CClientDC(this);

	//建立内存DC
	m_pMemDC = new CDC;
	m_pMemDC->CreateCompatibleDC(m_pDC);

	//建立内存位图
	m_pMemBitmap = new CBitmap;
	m_pMemBitmap->CreateCompatibleBitmap(m_pDC,GAME_WIDTH,GAME_HEIGHT);

	//将位图选入内存DC
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

	
	//产生主角(战机)
	m_pMe = new CMyPlane;
	ok = true;
	
	//启动游戏

	SetTimer(1,30,NULL);
	
	return TRUE;
}
void CPlaneGameView::UpdateFrame(CDC* pMemDC)
{
	wchar_t lifeleft[20];
	 wchar_t Score[20];
	wchar_t Level[20];
	int n=0; 

static int imagelocation = 0;//背景图片截取位置初始位置
	CDC memDC;
	memDC.CreateCompatibleDC(pMemDC);
	CBitmap bmpDraw;
	if (RR % 3 == 1)
		bmpDraw.LoadBitmapW(IDB_BITMAP3); //创建位图
	if (RR % 3 == 2)
		bmpDraw.LoadBitmapW(IDB_BITMAP13); //创建位图
	if (RR % 3 == 0)
		bmpDraw.LoadBitmapW(IDB_BITMAP12); //创建位图
	
	CBitmap* pbmpold = memDC.SelectObject(&bmpDraw);	
	pMemDC->BitBlt(0, imagelocation,808, 1213, &memDC, 0, 0, SRCCOPY);//设置动态背景
	pMemDC->BitBlt(0, 0, 808, imagelocation, &memDC, 0,1213- imagelocation, SRCCOPY);//设置动态背景
	imagelocation++;
	if (imagelocation == 1213)
		imagelocation = 0;
	//绘制我方战机
	if(m_pMe!=NULL)
	{
	   m_pMe->Draw(m_pMemDC,FALSE);
	   //绘制记录成
	   if (xxxx==1)
	   {
		   pMemDC->SetBkMode(TRANSPARENT);

	   }
	  
			pMemDC->SetBkMode(TRANSPARENT);//文字背景透明
			if (xxxx==1 )
			{
				wsprintf(lifeleft, L"无敌模式开启", m_pMe->HP );
				pMemDC->SetTextColor( RGB(255, 255,0) );    //字体颜色
				pMemDC->TextOutW(10,105, lifeleft, _tcslen(lifeleft));//字体位置
			}
			wsprintf(lifeleft, L"当前血量:%d", m_pMe->HP );
			pMemDC->SetTextColor( RGB(255, 255,0) );    //字体颜色
			pMemDC->TextOutW(10,10, lifeleft, _tcslen(lifeleft));//字体位置
			wsprintf(lifeleft, L"剩余生命:%d", m_pMe->life );
			pMemDC->SetTextColor( RGB(255, 255,0) );
			pMemDC->TextOutW(10,35, lifeleft, _tcslen(lifeleft));
			wsprintf(Score, L"得分:%d", m_pMe->score );
			pMemDC->SetTextColor( RGB(255, 0, 0) );
			pMemDC->TextOutW(10,60, Score, _tcslen(Score));
			wsprintf(Level, L" 第%d 关", m_pMe->level );
			pMemDC->SetTextColor( RGB(255, 255, 255) );
			pMemDC->TextOutW(10,85, Level, _tcslen(Level));

			wsprintf(lifeleft, L"V清屏（不含BOSS）", m_pMe->HP );
			pMemDC->SetTextColor( RGB(255, 255,0) );    //字体颜色
			pMemDC->TextOutW(620,10, lifeleft, _tcslen(lifeleft));//字体位置

			wsprintf(lifeleft, L"X无敌 C退出无敌  ", m_pMe->life );
			pMemDC->SetTextColor( RGB(255, 255,0) );
			pMemDC->TextOutW(620,35, lifeleft, _tcslen(lifeleft));

			wsprintf(Level, L" 剩余多发子弹（z+空格）:%d", tttt );
			pMemDC->SetTextColor( RGB(255, 255, 255) );
			pMemDC->TextOutW(580,85, Level, _tcslen(Level));

			if (boss1)
			{
				wsprintf(Score, L"BOSS生命值:%d", bosslife );
				pMemDC->SetTextColor( RGB(255, 0, 0) );
				pMemDC->TextOutW(620,60, Score, _tcslen(Score));
			}
			
	   
	}
	else
	{   //Game Over
		if(note==1)
		{
			note=0;
			int t  = MessageBox(TEXT("敌人太过强大，少侠想重整旗鼓重新开始吗 ?"),TEXT("Game Over!"),MB_YESNO);//过关时弹出对话框
			if (t==IDYES)
			{
				tttt=0;
				if (boss1)
				{
					POSITION ePos1=NULL,ePos2=NULL;//用于记录敌我两级位置
					for(ePos1=m_ObjList[enBOSS].GetHeadPosition();(ePos2=ePos1)!=NULL;)
					{
						BOSS* pBOSS = (BOSS*)m_ObjList[enBOSS].GetNext(ePos1);
						CRect mRect = pBOSS->GetRect();
						//删除敌机
						m_ObjList[enBOSS].RemoveAt(ePos2);//从索引中删除
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
				PostQuitMessage(0); //退出

		}

	}
	//绘制 导弹、爆炸、敌机1/2、子弹,奖励、BOSS、生命、BOSS子弹
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
	//复制内存DC到设备DC
	m_pDC->BitBlt(0,0,GAME_WIDTH,GAME_HEIGHT,m_pMemDC,0,0,SRCCOPY);
}
void CPlaneGameView::AI()
{
	static int nCreator = rand() %10+4;
	static int n1Creator = rand() %8+10;
	//随机产生敌机
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
		
			//按下了X建
	if(GetKey('X')==1)	
		xxxx=1;
	if(GetKey('C')==1)
		xxxx=0;
	if(m_pMe==NULL)
		return;


	//清屏
	if(GetKey('V')==1)
		
	{
		POSITION ePos1=NULL,ePos2=NULL;//用于记录敌我两级位置
		for(ePos1=m_ObjList[enEnemy].GetHeadPosition();(ePos2=ePos1)!=NULL;)
		{
			CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos1);
			CRect mRect = pEnemy->GetRect();
			//删除敌机
			m_ObjList[enEnemy].RemoveAt(ePos2);//从索引中删除
			delete pEnemy;
			//添加爆炸效果
			  m_ObjList[enExplosion].AddTail(new CExplosion(mRect.left,mRect.top));	
		}
		for(ePos1=m_ObjList[enEnemy1].GetHeadPosition();(ePos2=ePos1)!=NULL;)
		{
			CEnemy1* pEnemy1 = (CEnemy1*)m_ObjList[enEnemy1].GetNext(ePos1);
			CRect mRect = pEnemy1->GetRect();
			//删除敌机
			m_ObjList[enEnemy1].RemoveAt(ePos2);//从索引中删除
			delete pEnemy1;
			//添加爆炸效果
			  m_ObjList[enExplosion].AddTail(new CExplosion(mRect.left,mRect.top));	
		}
	}

	
	//产生奖励
	if(n1Creator<=0)
	{
		n1Creator = rand()%20+100;
		m_ObjList[enjiang].AddTail(new jiang);
		m_ObjList[enshengming].AddTail(new shengming);

	}
	n1Creator--;




	//检测四个方向键，移动战机
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
	//产生BOSS
		if (m_pMe->score>=25 && !boss)
		{
			m_ObjList[enBOSS].AddTail(new BOSS);
			m_pMe->score++;
			boss = true;
			boss1 = true;
			bosslife=200;
		}
	

	//产生战机导弹
	if(GetKey(VK_SPACE)==1)//按下了空格键
	{
		if(m_pMe!=NULL && m_pMe->Fired())
		{
			CPoint pt = m_pMe->GetPoint();
			m_ObjList[enBomb].AddTail(new CBomb(pt.x+10,pt.y+10,0));
			m_ObjList[enBomb].AddTail(new CBomb(pt.x+40,pt.y+10,0));
			if (GetKey('Z') == 1 && tttt)				//同时按Z和空格键 
			{
					tttt--;
					m_ObjList[enBomb].AddTail(new CBomb(pt.x+12,pt.y+12,1));
					m_ObjList[enBomb].AddTail(new CBomb(pt.x+32,pt.y+12,2));
					m_ObjList[enBomb].AddTail(new CBomb(pt.x+12,pt.y+12,3));
					m_ObjList[enBomb].AddTail(new CBomb(pt.x+32,pt.y+12,4));
			}
		}
	}



	if(GetKey(VK_ESCAPE)==1)//按下了退出键
		PostQuitMessage(0); //退出

	//敌机发射子弹

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

	//BOSS 发射导弹
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
	
	//敌机子弹炸掉战机
	POSITION bPos1=NULL,bPos2=NULL;
	CRect mRect = m_pMe->GetRect();
	for(bPos1=m_ObjList[enBall].GetHeadPosition();( bPos2 = bPos1 ) != NULL;)
	{
		CBall* pBall = (CBall*)m_ObjList[enBall].GetNext(bPos1);
		CRect bRect = pBall->GetRect();
		CRect tmpRect;
		if(tmpRect.IntersectRect(&bRect,mRect))
		{
			//添加爆炸效果
			
			m_ObjList[enExplosion].AddTail(
				new CExplosion(mRect.left,mRect.top)
				);

			//删除子弹
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
				//删除战机
				delete m_pMe;
				ok = false;
				m_pMe=NULL;
				break;
			}
		}
	}

	//BOSS 导弹炸毁战机
		POSITION bPos11=NULL,bPos22=NULL;
	
	for(bPos11=m_ObjList[enboer].GetHeadPosition();( bPos22 = bPos11 ) != NULL;)
	{
		boer* pboer = (boer*)m_ObjList[enboer].GetNext(bPos11);
		CRect bbRect = pboer->GetRect();
		CRect tmpRect;
		if(tmpRect.IntersectRect(&bbRect,mRect))
		{
			//添加爆炸效果
			
			m_ObjList[enExplosion].AddTail(
				new CExplosion(mRect.left,mRect.top)
				);

			//删除子弹
			m_ObjList[enboer].RemoveAt(bPos22);
			delete pboer;
			if (xxxx==0)
			m_pMe->life--;
			if(m_pMe->life < 0 && xxxx==0)
			{
				//删除战机
				delete m_pMe;
				ok = false;
				m_pMe=NULL;
				break;
			}
		}
	}
	    //撞机
	POSITION ePos1=NULL,ePos2=NULL;//用于记录敌我两级位置
	for(ePos1=m_ObjList[enEnemy].GetHeadPosition();(ePos2=ePos1)!=NULL;)
	{
		CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos1);
		CRect eRect = pEnemy->GetRect();
		CRect tmpRect;
		if(tmpRect.IntersectRect(eRect,mRect)) //如果交不为空，则返回非零值；否则，如果交为空则返回
		{
			//删除敌机
			m_ObjList[enEnemy].RemoveAt(ePos2);//从索引中删除
			delete pEnemy;
			//添加爆炸效果
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
			  //删除战机
			delete m_pMe;
			ok = false;
			m_pMe=NULL;
			break;
			}
	}
	}
	   //撞机2
	for(ePos1=m_ObjList[enEnemy1].GetHeadPosition();(ePos2=ePos1)!=NULL;)
	{
		CEnemy1* pEnemy1 = (CEnemy1*)m_ObjList[enEnemy1].GetNext(ePos1);
		CRect eRect = pEnemy1->GetRect();
		CRect tmpRect;
		if(tmpRect.IntersectRect(eRect,mRect)) //如果交不为空，则返回非零值；否则，如果交为空则返回
		{
			//删除敌机
			m_ObjList[enEnemy1].RemoveAt(ePos2);//从索引中删除
			delete pEnemy1;
			//添加爆炸效果
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
			  //删除战机
			delete m_pMe;
			ok = false;
			m_pMe=NULL;
			break;
			}
            //还原子弹
//			m_pMe->Bkind = 1;
		}
	}

	//	吃奖励
	
	for(ePos1=m_ObjList[enjiang].GetHeadPosition();(ePos2=ePos1)!=NULL;)
	{
		jiang* pjiang = (jiang*)m_ObjList[enjiang].GetNext(ePos1);
		CRect eRect = pjiang->GetRect();
		CRect tmpRect;
		if(tmpRect.IntersectRect(eRect,mRect)) //如果交不为空，则返回非零值；否则，如果交为空则返回
		{
			//删除奖励
			m_ObjList[enjiang].RemoveAt(ePos2);//从索引中删除
			delete pjiang;
			//添加效果
			 // m_ObjList[enExplosion].AddTail(new CExplosion(mRect.left,mRect.top));
			tttt += 10;
          break;
		}
	}
	//获得生命
		for(ePos1=m_ObjList[enshengming].GetHeadPosition();(ePos2=ePos1)!=NULL;)
	{
		shengming* pshengming = (shengming*)m_ObjList[enshengming].GetNext(ePos1);
		CRect eRect = pshengming->GetRect();
		CRect tmpRect;
		if(tmpRect.IntersectRect(eRect,mRect)) //如果交不为空，则返回非零值；否则，如果交为空则返回
		{
			//删除奖励
			m_ObjList[enshengming].RemoveAt(ePos2);//从索引中删除
			delete pshengming;
			//添加效果
			 // m_ObjList[enExplosion].AddTail(new CExplosion(mRect.left,mRect.top));
		m_pMe->life ++;;
          break;
		}
	}
		//撞BOSS
		POSITION eeePos1=NULL,eeePos2=NULL;//用于记录敌我两级位置
	for(eeePos1=m_ObjList[enBOSS].GetHeadPosition();(eeePos2=eeePos1)!=NULL;)
	{
		BOSS* pBOSS = (BOSS*)m_ObjList[enBOSS].GetNext(eeePos1);
		CRect eRect = pBOSS->GetRect();
		CRect tmpRect;
		if(tmpRect.IntersectRect(eRect,mRect)) //如果交不为空，则返回非零值；否则，如果交为空则返回
		{
			//添加爆炸效果
			  m_ObjList[enExplosion].AddTail(new CExplosion(mRect.left,mRect.top));
			if (xxxx==0)
				m_pMe->life--;
			if(m_pMe->life < 0 && xxxx==0)
			{
			  //删除战机
				delete m_pMe;
				boss = false;
				boss1 = false;
				ok = false;
				m_pMe=NULL;
				break;
			}
		}
	}

	//战机导弹炸掉BOSS
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
				//添加爆炸效果
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left+210,mRect.top+100)
					);
				//删除导弹
				m_ObjList[enBomb].RemoveAt(mPoos2);
				delete pBomb;

				//删除BOSS
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

	//战机导弹炸掉敌机
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
				//添加爆炸效果
				m_pMe->score ++;
				ok = true;
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left,mRect.top)
					);
				//删除导弹
				m_ObjList[enBomb].RemoveAt(mPos2);
				delete pBomb;

				//删除敌机
				m_ObjList[enEnemy].RemoveAt(ePos2);
				delete pEnemy;
				break;

			}
		}
	
	}

	//战机导弹炸掉敌机2
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
				//添加爆炸效果
				m_pMe->score ++;
				ok = true;
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left,mRect.top)
					);
				//删除导弹
				m_ObjList[enBomb].RemoveAt(mPos2);
				delete pBomb;

				//删除敌机
				m_ObjList[enEnemy1].RemoveAt(ePos2);
				delete pEnemy1;
				break;

			}
		}
	
	}
}

void CPlaneGameView::OnTimer(UINT_PTR nIDEvent)
{
	//刷新游戏帧画面: 在内存DC上绘图
	UpdateFrame(m_pMemDC);
	AI();
	if (ok)
	if (m_pMe->score >= 100  && !boss1)
	{
		ok = false;
		KillTimer(1);
		int t  = MessageBox(TEXT("恭喜少侠突破重围，想进入下一关吗 ?"),TEXT("Congratulation！"),MB_YESNO);//过关时弹出对话框
		if (t == IDYES){
			RR++;
			boss = false;
			m_pMe->score=0;
			m_pMe->level++;
			POSITION ePos1=NULL,ePos2=NULL;//用于记录敌我两级位置
	for(ePos1=m_ObjList[enEnemy].GetHeadPosition();(ePos2=ePos1)!=NULL;)
	{
		CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos1);
		CRect mRect = pEnemy->GetRect();
			//删除敌机
			m_ObjList[enEnemy].RemoveAt(ePos2);//从索引中删除
			delete pEnemy;
			
	}



		for(ePos1=m_ObjList[enEnemy1].GetHeadPosition();(ePos2=ePos1)!=NULL;)
	{
		CEnemy1* pEnemy1 = (CEnemy1*)m_ObjList[enEnemy1].GetNext(ePos1);
		CRect mRect = pEnemy1->GetRect();
			//删除敌机
			m_ObjList[enEnemy1].RemoveAt(ePos2);//从索引中删除
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
	// TODO: 在此处添加消息处理程序代码
}

void CPlaneGameView::OnPaint()
{
	CPaintDC dc(this);
	 // device context for painting
	// TODO: 在此处添加消息处理程序代码

	// 不为绘图消息调用 CView::OnPaint()
	
	}
