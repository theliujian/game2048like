#include "cocos2d.h"
#include <stdio.h>
USING_NS_CC;


class gameover : public cocos2d::CCScene//背景宫图的类,是一个层
{
public:

	virtual bool init(); 

	CREATE_FUNC(gameover);
	//virtual bool ccTouchBegan(cocos2d::CCTouch * touch,cocos2d::CCEvent * event);
	//virtual void onEnter();
	
};
//void gameover::onEnter()
//{
//	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate( this,0,false);  
//    onEnter();   
//}
//bool gameover::ccTouchBegan(cocos2d::CCTouch * touch,cocos2d::CCEvent * event)
//{
//	CCScene *psence=HelloWorld::scene();//切换回原来的场景
//	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.1f,psence));
//}
bool gameover::init()
{
	//CCSprite* pSprite = CCSprite::create("chonglai.png");
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    // position the sprite on the center of the screen
    //pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    //this->addChild(pSprite, 0);//加入精灵

	CCLabelTTF* pLabel = CCLabelTTF::create("GAME OVER", "Arial", 24);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);//加入按钮
	onEnter();
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////
class gezi  :public CCSprite//每个格子的类
{
public:
	gezi();
	~gezi();

	void setpos(float x,float y);
	void setvalue(int v);
	class CCLabelTTF* pLabel;//显示的数值
	int value;//精灵的值
private:
	void eat(gezi *p);
	
	
	//cocos2d::CCSprite *kuang;//格子边框，暂时用精灵类显示，以后改为贴图等更合适的方法
	class cocos2d::CCPoint pos;//格子坐标
	friend class gong;

};

gezi::gezi():value(0)//初始化值，图片，位置
{
	//this->  cocos2d::CCSprite::create("CloseNormal.png");//创建边框
	this->initWithFile("kuang1.png");
	pLabel = CCLabelTTF::create("0", "Arial", 24);

	pos.x=NULL;
	pos.y=NULL;
	return;
}
gezi::~gezi()
{}
void gezi::setpos(float x=0,float y=0)//只规定格子的位置，其中精灵的位置又它自己决定
{
	this->setPosition(ccp(x, y));//设定格子边框的位置
	pLabel->setPosition(ccp(x, y));//设定内部数值的位置
	pos.x=x;
	pos.y=y;//显示的指示当前位置
}
void gezi::setvalue(int v)//只规定格子的位置，其中精灵的位置又它自己决定
{
	value=v;

	//const char* pchar=CCString::createWithFormat("%d",NULL)->getCString();
	//if(v!=0)
	//{

	const char* pchar=CCString::createWithFormat("%d",v)->getCString();
	//pchar->autorelease();自动释放
	pLabel->CCLabelTTF::setString(pchar);
	pLabel->CCLabelTTF::setScale(2.0f);
	//pLabel->CCLabelTTF::setVisible(true);
	//}
	//else
	//{
	//	//pLabel->CCLabelTTF::setVisible(false);

	//}
	
	const char* pchar1=CCString::createWithFormat("%d.png",v)->getCString();
	this->initWithFile(pchar1);

}

/////////////////////////——————————————————————////////////////////////////////////


class gong : public cocos2d::CCLayer//背景宫图的类,是一个层
{
public:
	gong();//背景宫图();
	~gong();//背景宫图();
	bool up();//移动格子
	bool up_lie( gezi  (*p)[4],int n);
	bool down();
	bool down_lie( gezi  (*p)[4],int n);
	bool left();
	bool left_lie( gezi  (*p)[4],int n);
	bool right();
	bool right_lie( gezi  (*p)[4],int n);
	bool changshi(gezi  (*p)[4]);//返回1就是不能走了
	virtual bool init(); 
	void suiji();//随机生成新节点
	CREATE_FUNC(gong);
	virtual bool ccTouchBegan(cocos2d::CCTouch * touch,cocos2d::CCEvent * event);
	virtual void onEnter();
	//virtual void onExit();
	int num;
private:
	class cocos2d::CCPoint origin;//原点坐标
	class cocos2d::CCSize visibleSize;//屏幕大小
	class gezi  arry[4][4];//格子类的矩阵,以后修改为P214中描述的二维数组
	
	friend class gezi;
	
};
void gong::onEnter()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate( this,0,false);  
    CCLayer::onEnter();   
}
bool gong::changshi(gezi  (*p)[4])
{
	int i,k,n;
	bool r=true;
	//横向遍历
	for(n=0;n<4;n++)
	{
		for( i=3;i>=0;)//遍历该竖列, 并合并同类项
		{
			if(p[i][n].value != 0)//当前节点不为0就判断是否有合并的可能
			{
				for(k=i-1;k>=0;)//遍历之后的节点
				{
					if(p[k][n].value)//当前节点不为零
					{
						if(p[i][n].value == p[k][n].value)//如果两个值相同就合并
						{

							r=false;
							return r;
						}
						i--;//原节点位置向前移动
						break;
					}

					else
					{
						k--;//当前节点向前移动
					}
				}
				if( k <0)
				{
						i--;
						break;
				}

			}
			else
				i--;
		}
	}
	//纵向遍历，不能走了就返回true
	for(n=0;n<4;n++)
	{
		for(i=0;i<4;)//遍历该竖列, 并合并同类项
		{
			if(p[n][i].value != 0)//当前节点不为0就判断是否有合并的可能
			{
			 
				for(k=i+1;k<4;)//遍历之后的节点
				{
					if(p[n][k].value)//当前节点不为零
					{
						if(p[n][i].value == p[n][k].value)//如果两个值相同就合并
						{

							r=false;
							return r;
						}
						i++;//原节点位置向前移动
						break;
					}

					else
					{
						k++;//当前节点向前移动
					}
				}
				if( k >=4)
				{
						i++;
						break;
				}

			}
			else
				i++;
		}
	}
	return r;
}
void gong::suiji()//背景宫图()
{
	int s=rand()%5;
	int i=0;
	for(i=0;i<4;i++)
	{
		for(int j=0; j<4;j++)
		{

			if(arry[i][j].value == 0)
			{
				if(s==0) //选择这个点作为新的随机生成的点，放大这个点
				{
					
					arry[i][j].setvalue(2);
					num++;
					arry[i][j].setScale(1.0f);      //setscale(0.1f);//真正设置图片大小

					arry[i][j].runAction(CCScaleTo::create(0.1f,1.4f));//runaction(ccscaleto::create(0.1f,1.4f));//0.1并放大1.3倍
					arry[i][j].setScale(1.4f);//真正设置图片大小
					return;
				}
				else
					s--;
			}
		}
		if(i==3)//一遍没有完成随机递减结果，就从头来
		{
			i=-1;//不判断s为多少，因为只要执行这个函数肯定有空值
		}
	}

}
bool gong::ccTouchBegan(cocos2d::CCTouch * touch,cocos2d::CCEvent * event)
{

	CCPoint pos = touch->getLocation();
	//上下两个精灵的位置
	if((pos.x>(visibleSize.width*0.81 + origin.x) )&& (pos.x<(visibleSize.width*0.91 + origin.x) ))
	{
		if((pos.y> (visibleSize.height*0.65 + origin.y) )&& (pos.y<(visibleSize.height*0.76 + origin.y) ))
		{
			if(right())//其实是上
			{	
				suiji();
				return true;
			}
		}
		if((pos.y> (visibleSize.height*0.25 + origin.y) )&& (pos.y<(visibleSize.height*0.36 + origin.y) ))
		{
			if(left())//其实是下
			{	
				suiji();
				return true;
			}
		}
	}
	//左右两个精灵的位置
	if((pos.y> (visibleSize.height*0.43 + origin.y) )&& (pos.y<(visibleSize.height*0.57 + origin.y) ))
	{
		if((pos.x>(visibleSize.width*0.72 + origin.x) )&& (pos.x<(visibleSize.width*0.85 + origin.x) ))
		{
			if(up())//其实是左边
			{	
				suiji();
				return true;
			}
		}
		if((pos.x>(visibleSize.width*0.87 + origin.x) )&& (pos.x<(visibleSize.width*0.99 + origin.x) ))
		{
			if(down())//其实是右边
			{	
				suiji();
				return true;
			}
		}
	}	
	if(num>=16)//如果满了，而且尝试着不能行了就结束了
	{
		if(changshi(arry))
		{
			gameover *psence=gameover::create();
			CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.1f,psence));
		}
	}
	return true;
}
gong::gong()//背景宫图()
{
	num=0;
}

gong::~gong()//背景宫图()
{
}
bool gong::init()
{
    //////////////////////////////
    // 1. super init first
	int a[16]={0,0,0,0,
				0,0,0,0,
				0,0,0,0,
				0,0,0,0};
    if ( !CCLayer::init() )
    {
        return false;
    }
    
     visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    origin = CCDirector::sharedDirector()->getVisibleOrigin();

	int i=4,j=4,k=0;
	for(int ii=0;ii<i;ii++)
		for(int jj=0;jj<j;jj++)
		{
			arry[ii][jj].setvalue(a[k++]);
			arry[ii][jj].setScale(1.4f);//真正设置图片大小
			//初始化每个格子的位置,偏坐下调整，横竖都减去一个值
			arry[ii][jj].setpos((visibleSize.height/j)*(ii) + origin.x+visibleSize.width/(i+1)-(visibleSize.height/i/2), visibleSize.height/(j+1)+(visibleSize.height/j)*(jj) + origin.y-(visibleSize.height/j/4));
			this->addChild(&arry[ii][jj], 1);
			this->addChild(arry[ii][jj].pLabel, 2);
		}
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    //CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
    //
    //// position the label on the center of the screen
    //pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
    //                        origin.y + visibleSize.height - pLabel->getContentSize().height));

    //// add the label as a child to this layer
    //this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("shang.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width*0.86 + origin.x, visibleSize.height*0.7 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 1);
	pSprite = CCSprite::create("xia.png");
	pSprite->setPosition(ccp(visibleSize.width*0.86 + origin.x, visibleSize.height*0.3 + origin.y));
	this->addChild(pSprite, 1);
	pSprite = CCSprite::create("zuo.png");
	pSprite->setPosition(ccp(visibleSize.width*0.79 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(pSprite, 1);
	pSprite = CCSprite::create("you.png");
	pSprite->setPosition(ccp(visibleSize.width*0.94 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(pSprite, 1);
////////////////////////////////////加入格子了
	//gong G;//创建一个2*2宫

	//this->addChild(&G, 0);
	suiji();//刷新一个格子
	onEnter();
    return true;
}
bool gong::up_lie( gezi  (*p)[4],int n)//每一竖列的上移
{
	int k;
	bool r=false;
	for(int i=0;i<4;)//遍历该竖列, 并合并同类项
	{
		if(p[i][n].value != 0)//当前节点不为0就判断是否有合并的可能
		{
			 
			for(k=i+1;k<4;)//遍历之后的节点
			{
				if(p[k][n].value)//当前节点不为零
				{
					if(p[i][n].value == p[k][n].value)//如果两个值相同就合并
					{
						p[i][n].setvalue(p[i][n].value*2);
						p[k][n].setvalue(0);
						num--;
						r=true;
					}
					i++;//原节点位置向前移动
					break;
				}

				else
				{
					k++;//当前节点向前移动
				}
			}
			if( k >=4)
			{
					i++;
					break;
			}

		}
		else
			i++;
	}
	for(int i=0;i<4;)//遍历该竖列，并移向
	{
		if(p[i][n].value == 0 )
		{
			for(k=i+1;k<4;)//遍历后续节点，向前移动
			{
				if(p[k][n].value)
				{
					p[i][n].setvalue(p[k][n].value);
					p[k][n].setvalue(0);
					i++;//移动后就前移原节点
					r=true;
					break;
				}
				else
					k++;
			}
			if(k>=4)
			{
				i++;
				break;
			}
		}
		else
		{
			i++;
		}
	}
	return r;
}
bool gong::up()//整体上移
{
	bool r=false;
	for(int i=0;i<4;i++)
		if(up_lie(arry,i))
			r=true;
	return r;
}


bool gong::down_lie( gezi  (*p)[4],int n)//每一竖列的上移
{
	int k;
	bool r=false;
	for(int i=3;i>=0;)//遍历该竖列, 并合并同类项
	{
		if(p[i][n].value != 0)//当前节点不为0就判断是否有合并的可能
		{
			for(k=i-1;k>=0;)//遍历之后的节点
			{
				if(p[k][n].value)//当前节点不为零
				{
					if(p[i][n].value == p[k][n].value)//如果两个值相同就合并
					{
						p[i][n].setvalue(p[i][n].value*2);
						p[k][n].setvalue(0);
						num--;
						r=true;
					}
					i--;//原节点位置向前移动
					break;
				}

				else
				{
					k--;//当前节点向前移动
				}
			}
			if( k <0)
			{
					i--;
					break;
			}

		}
		else
			i--;
	}
	for(int i=3;i>=0;)//遍历该竖列，并移向
	{
		if(p[i][n].value == 0 )
		{
			for(k=i-1;k>=0;)//遍历后续节点，向前移动
			{
				if(p[k][n].value)
				{
					p[i][n].setvalue(p[k][n].value);
					p[k][n].setvalue(0);
					i--;//移动后就前移原节点
					r=true;
					break;
				}
				else
					k--;
			}
			if(k<0)
			{
				i--;
				break;
			}
		}
		else
		{
			i--;
		}
	}
	return r;
}
bool gong::down()//整体上移
{
	bool r=false;
	for(int i=0;i<4;i++)
		if(down_lie(arry,i))
			r=true;
	return r;
}




bool gong::left_lie( gezi  (*p)[4],int n)//每一竖列的上移
{
	int k;
	bool r=false;
	for(int i=0;i<4;)//遍历该竖列, 并合并同类项
	{
		if(p[n][i].value != 0)//当前节点不为0就判断是否有合并的可能
		{
			 
			for(k=i+1;k<4;)//遍历之后的节点
			{
				if(p[n][k].value)//当前节点不为零
				{
					if(p[n][i].value == p[n][k].value)//如果两个值相同就合并
					{
						p[n][i].setvalue(p[n][i].value*2);
						p[n][k].setvalue(0);
						num--;
						r=true;
					}
					i++;//原节点位置向前移动
					break;
				}

				else
				{
					k++;//当前节点向前移动
				}
			}
			if( k >=4)
			{
					i++;
					break;
			}

		}
		else
			i++;
	}
	for(int i=0;i<4;)//遍历该竖列，并移向
	{
		if(p[n][i].value == 0 )
		{
			for(k=i+1;k<4;)//遍历后续节点，向前移动
			{
				if(p[n][k].value)
				{
					p[n][i].setvalue(p[n][k].value);
					p[n][k].setvalue(0);
					i++;//移动后就前移原节点
					r=true;
					break;
				}
				else
					k++;
			}
			if(k>=4)
			{
				i++;
				break;
			}
		}
		else
		{
			i++;
		}
	}
	return r;
}
bool gong::left()//整体上移
{
	bool r=false;
	for(int i=0;i<4;i++)
		if(left_lie(arry,i))
			r=true;
	return r;
}


bool gong::right_lie( gezi  (*p)[4],int n)//每一竖列的上移
{
	int k;
	bool r=false;
	for(int i=3;i>=0;)//遍历该竖列, 并合并同类项
	{
		if(p[n][i].value != 0)//当前节点不为0就判断是否有合并的可能
		{
			 
			for(k=i-1;k>=0;)//遍历之后的节点
			{
				if(p[n][k].value)//当前节点不为零
				{
					if(p[n][i].value == p[n][k].value)//如果两个值相同就合并
					{
						p[n][i].setvalue(p[n][i].value*2);
						p[n][k].setvalue(0);
						num--;
						r=true;
					}
					i--;//原节点位置向前移动
					break;
				}

				else
				{
					k--;//当前节点向前移动
				}
			}
			if( k<0)
			{
					i--;
					break;
			}

		}
		else
			i--;
	}
	for(int i=3;i>=0;)//遍历该竖列，并移向
	{
		if(p[n][i].value == 0 )
		{
			for(k=i-1;k>=0;)//遍历后续节点，向前移动
			{
				if(p[n][k].value)
				{
					p[n][i].setvalue(p[n][k].value);
					p[n][k].setvalue(0);
					i--;//移动后就前移原节点
					r=true;
					break;
				}
				else
					k--;
			}
			if(k<0)
			{
				i--;
				break;
			}
		}
		else
		{
			i--;
		}
	}
	return r;
}
bool gong::right()//整体上移
{
	bool r=false;
	for(int i=0;i<4;i++)
		if(right_lie(arry,i))
			r=true;
	return r;
}
////////////////////////////////////////////////////////////key类
