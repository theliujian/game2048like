#include "cocos2d.h"
#include <stdio.h>
USING_NS_CC;


class gameover : public cocos2d::CCScene//������ͼ����,��һ����
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
//	CCScene *psence=HelloWorld::scene();//�л���ԭ���ĳ���
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
    //this->addChild(pSprite, 0);//���뾫��

	CCLabelTTF* pLabel = CCLabelTTF::create("GAME OVER", "Arial", 24);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);//���밴ť
	onEnter();
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////
class gezi  :public CCSprite//ÿ�����ӵ���
{
public:
	gezi();
	~gezi();

	void setpos(float x,float y);
	void setvalue(int v);
	class CCLabelTTF* pLabel;//��ʾ����ֵ
	int value;//�����ֵ
private:
	void eat(gezi *p);
	
	
	//cocos2d::CCSprite *kuang;//���ӱ߿���ʱ�þ�������ʾ���Ժ��Ϊ��ͼ�ȸ����ʵķ���
	class cocos2d::CCPoint pos;//��������
	friend class gong;

};

gezi::gezi():value(0)//��ʼ��ֵ��ͼƬ��λ��
{
	//this->  cocos2d::CCSprite::create("CloseNormal.png");//�����߿�
	this->initWithFile("kuang1.png");
	pLabel = CCLabelTTF::create("0", "Arial", 24);

	pos.x=NULL;
	pos.y=NULL;
	return;
}
gezi::~gezi()
{}
void gezi::setpos(float x=0,float y=0)//ֻ�涨���ӵ�λ�ã����о����λ�������Լ�����
{
	this->setPosition(ccp(x, y));//�趨���ӱ߿��λ��
	pLabel->setPosition(ccp(x, y));//�趨�ڲ���ֵ��λ��
	pos.x=x;
	pos.y=y;//��ʾ��ָʾ��ǰλ��
}
void gezi::setvalue(int v)//ֻ�涨���ӵ�λ�ã����о����λ�������Լ�����
{
	value=v;

	//const char* pchar=CCString::createWithFormat("%d",NULL)->getCString();
	//if(v!=0)
	//{

	const char* pchar=CCString::createWithFormat("%d",v)->getCString();
	//pchar->autorelease();�Զ��ͷ�
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

/////////////////////////��������������������������������������������////////////////////////////////////


class gong : public cocos2d::CCLayer//������ͼ����,��һ����
{
public:
	gong();//������ͼ();
	~gong();//������ͼ();
	bool up();//�ƶ�����
	bool up_lie( gezi  (*p)[4],int n);
	bool down();
	bool down_lie( gezi  (*p)[4],int n);
	bool left();
	bool left_lie( gezi  (*p)[4],int n);
	bool right();
	bool right_lie( gezi  (*p)[4],int n);
	bool changshi(gezi  (*p)[4]);//����1���ǲ�������
	virtual bool init(); 
	void suiji();//��������½ڵ�
	CREATE_FUNC(gong);
	virtual bool ccTouchBegan(cocos2d::CCTouch * touch,cocos2d::CCEvent * event);
	virtual void onEnter();
	//virtual void onExit();
	int num;
private:
	class cocos2d::CCPoint origin;//ԭ������
	class cocos2d::CCSize visibleSize;//��Ļ��С
	class gezi  arry[4][4];//������ľ���,�Ժ��޸�ΪP214�������Ķ�ά����
	
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
	//�������
	for(n=0;n<4;n++)
	{
		for( i=3;i>=0;)//����������, ���ϲ�ͬ����
		{
			if(p[i][n].value != 0)//��ǰ�ڵ㲻Ϊ0���ж��Ƿ��кϲ��Ŀ���
			{
				for(k=i-1;k>=0;)//����֮��Ľڵ�
				{
					if(p[k][n].value)//��ǰ�ڵ㲻Ϊ��
					{
						if(p[i][n].value == p[k][n].value)//�������ֵ��ͬ�ͺϲ�
						{

							r=false;
							return r;
						}
						i--;//ԭ�ڵ�λ����ǰ�ƶ�
						break;
					}

					else
					{
						k--;//��ǰ�ڵ���ǰ�ƶ�
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
	//����������������˾ͷ���true
	for(n=0;n<4;n++)
	{
		for(i=0;i<4;)//����������, ���ϲ�ͬ����
		{
			if(p[n][i].value != 0)//��ǰ�ڵ㲻Ϊ0���ж��Ƿ��кϲ��Ŀ���
			{
			 
				for(k=i+1;k<4;)//����֮��Ľڵ�
				{
					if(p[n][k].value)//��ǰ�ڵ㲻Ϊ��
					{
						if(p[n][i].value == p[n][k].value)//�������ֵ��ͬ�ͺϲ�
						{

							r=false;
							return r;
						}
						i++;//ԭ�ڵ�λ����ǰ�ƶ�
						break;
					}

					else
					{
						k++;//��ǰ�ڵ���ǰ�ƶ�
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
void gong::suiji()//������ͼ()
{
	int s=rand()%5;
	int i=0;
	for(i=0;i<4;i++)
	{
		for(int j=0; j<4;j++)
		{

			if(arry[i][j].value == 0)
			{
				if(s==0) //ѡ���������Ϊ�µ�������ɵĵ㣬�Ŵ������
				{
					
					arry[i][j].setvalue(2);
					num++;
					arry[i][j].setScale(1.0f);      //setscale(0.1f);//��������ͼƬ��С

					arry[i][j].runAction(CCScaleTo::create(0.1f,1.4f));//runaction(ccscaleto::create(0.1f,1.4f));//0.1���Ŵ�1.3��
					arry[i][j].setScale(1.4f);//��������ͼƬ��С
					return;
				}
				else
					s--;
			}
		}
		if(i==3)//һ��û���������ݼ�������ʹ�ͷ��
		{
			i=-1;//���ж�sΪ���٣���ΪֻҪִ����������϶��п�ֵ
		}
	}

}
bool gong::ccTouchBegan(cocos2d::CCTouch * touch,cocos2d::CCEvent * event)
{

	CCPoint pos = touch->getLocation();
	//�������������λ��
	if((pos.x>(visibleSize.width*0.81 + origin.x) )&& (pos.x<(visibleSize.width*0.91 + origin.x) ))
	{
		if((pos.y> (visibleSize.height*0.65 + origin.y) )&& (pos.y<(visibleSize.height*0.76 + origin.y) ))
		{
			if(right())//��ʵ����
			{	
				suiji();
				return true;
			}
		}
		if((pos.y> (visibleSize.height*0.25 + origin.y) )&& (pos.y<(visibleSize.height*0.36 + origin.y) ))
		{
			if(left())//��ʵ����
			{	
				suiji();
				return true;
			}
		}
	}
	//�������������λ��
	if((pos.y> (visibleSize.height*0.43 + origin.y) )&& (pos.y<(visibleSize.height*0.57 + origin.y) ))
	{
		if((pos.x>(visibleSize.width*0.72 + origin.x) )&& (pos.x<(visibleSize.width*0.85 + origin.x) ))
		{
			if(up())//��ʵ�����
			{	
				suiji();
				return true;
			}
		}
		if((pos.x>(visibleSize.width*0.87 + origin.x) )&& (pos.x<(visibleSize.width*0.99 + origin.x) ))
		{
			if(down())//��ʵ���ұ�
			{	
				suiji();
				return true;
			}
		}
	}	
	if(num>=16)//������ˣ����ҳ����Ų������˾ͽ�����
	{
		if(changshi(arry))
		{
			gameover *psence=gameover::create();
			CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.1f,psence));
		}
	}
	return true;
}
gong::gong()//������ͼ()
{
	num=0;
}

gong::~gong()//������ͼ()
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
			arry[ii][jj].setScale(1.4f);//��������ͼƬ��С
			//��ʼ��ÿ�����ӵ�λ��,ƫ���µ�������������ȥһ��ֵ
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
////////////////////////////////////���������
	//gong G;//����һ��2*2��

	//this->addChild(&G, 0);
	suiji();//ˢ��һ������
	onEnter();
    return true;
}
bool gong::up_lie( gezi  (*p)[4],int n)//ÿһ���е�����
{
	int k;
	bool r=false;
	for(int i=0;i<4;)//����������, ���ϲ�ͬ����
	{
		if(p[i][n].value != 0)//��ǰ�ڵ㲻Ϊ0���ж��Ƿ��кϲ��Ŀ���
		{
			 
			for(k=i+1;k<4;)//����֮��Ľڵ�
			{
				if(p[k][n].value)//��ǰ�ڵ㲻Ϊ��
				{
					if(p[i][n].value == p[k][n].value)//�������ֵ��ͬ�ͺϲ�
					{
						p[i][n].setvalue(p[i][n].value*2);
						p[k][n].setvalue(0);
						num--;
						r=true;
					}
					i++;//ԭ�ڵ�λ����ǰ�ƶ�
					break;
				}

				else
				{
					k++;//��ǰ�ڵ���ǰ�ƶ�
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
	for(int i=0;i<4;)//���������У�������
	{
		if(p[i][n].value == 0 )
		{
			for(k=i+1;k<4;)//���������ڵ㣬��ǰ�ƶ�
			{
				if(p[k][n].value)
				{
					p[i][n].setvalue(p[k][n].value);
					p[k][n].setvalue(0);
					i++;//�ƶ����ǰ��ԭ�ڵ�
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
bool gong::up()//��������
{
	bool r=false;
	for(int i=0;i<4;i++)
		if(up_lie(arry,i))
			r=true;
	return r;
}


bool gong::down_lie( gezi  (*p)[4],int n)//ÿһ���е�����
{
	int k;
	bool r=false;
	for(int i=3;i>=0;)//����������, ���ϲ�ͬ����
	{
		if(p[i][n].value != 0)//��ǰ�ڵ㲻Ϊ0���ж��Ƿ��кϲ��Ŀ���
		{
			for(k=i-1;k>=0;)//����֮��Ľڵ�
			{
				if(p[k][n].value)//��ǰ�ڵ㲻Ϊ��
				{
					if(p[i][n].value == p[k][n].value)//�������ֵ��ͬ�ͺϲ�
					{
						p[i][n].setvalue(p[i][n].value*2);
						p[k][n].setvalue(0);
						num--;
						r=true;
					}
					i--;//ԭ�ڵ�λ����ǰ�ƶ�
					break;
				}

				else
				{
					k--;//��ǰ�ڵ���ǰ�ƶ�
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
	for(int i=3;i>=0;)//���������У�������
	{
		if(p[i][n].value == 0 )
		{
			for(k=i-1;k>=0;)//���������ڵ㣬��ǰ�ƶ�
			{
				if(p[k][n].value)
				{
					p[i][n].setvalue(p[k][n].value);
					p[k][n].setvalue(0);
					i--;//�ƶ����ǰ��ԭ�ڵ�
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
bool gong::down()//��������
{
	bool r=false;
	for(int i=0;i<4;i++)
		if(down_lie(arry,i))
			r=true;
	return r;
}




bool gong::left_lie( gezi  (*p)[4],int n)//ÿһ���е�����
{
	int k;
	bool r=false;
	for(int i=0;i<4;)//����������, ���ϲ�ͬ����
	{
		if(p[n][i].value != 0)//��ǰ�ڵ㲻Ϊ0���ж��Ƿ��кϲ��Ŀ���
		{
			 
			for(k=i+1;k<4;)//����֮��Ľڵ�
			{
				if(p[n][k].value)//��ǰ�ڵ㲻Ϊ��
				{
					if(p[n][i].value == p[n][k].value)//�������ֵ��ͬ�ͺϲ�
					{
						p[n][i].setvalue(p[n][i].value*2);
						p[n][k].setvalue(0);
						num--;
						r=true;
					}
					i++;//ԭ�ڵ�λ����ǰ�ƶ�
					break;
				}

				else
				{
					k++;//��ǰ�ڵ���ǰ�ƶ�
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
	for(int i=0;i<4;)//���������У�������
	{
		if(p[n][i].value == 0 )
		{
			for(k=i+1;k<4;)//���������ڵ㣬��ǰ�ƶ�
			{
				if(p[n][k].value)
				{
					p[n][i].setvalue(p[n][k].value);
					p[n][k].setvalue(0);
					i++;//�ƶ����ǰ��ԭ�ڵ�
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
bool gong::left()//��������
{
	bool r=false;
	for(int i=0;i<4;i++)
		if(left_lie(arry,i))
			r=true;
	return r;
}


bool gong::right_lie( gezi  (*p)[4],int n)//ÿһ���е�����
{
	int k;
	bool r=false;
	for(int i=3;i>=0;)//����������, ���ϲ�ͬ����
	{
		if(p[n][i].value != 0)//��ǰ�ڵ㲻Ϊ0���ж��Ƿ��кϲ��Ŀ���
		{
			 
			for(k=i-1;k>=0;)//����֮��Ľڵ�
			{
				if(p[n][k].value)//��ǰ�ڵ㲻Ϊ��
				{
					if(p[n][i].value == p[n][k].value)//�������ֵ��ͬ�ͺϲ�
					{
						p[n][i].setvalue(p[n][i].value*2);
						p[n][k].setvalue(0);
						num--;
						r=true;
					}
					i--;//ԭ�ڵ�λ����ǰ�ƶ�
					break;
				}

				else
				{
					k--;//��ǰ�ڵ���ǰ�ƶ�
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
	for(int i=3;i>=0;)//���������У�������
	{
		if(p[n][i].value == 0 )
		{
			for(k=i-1;k>=0;)//���������ڵ㣬��ǰ�ƶ�
			{
				if(p[n][k].value)
				{
					p[n][i].setvalue(p[n][k].value);
					p[n][k].setvalue(0);
					i--;//�ƶ����ǰ��ԭ�ڵ�
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
bool gong::right()//��������
{
	bool r=false;
	for(int i=0;i<4;i++)
		if(right_lie(arry,i))
			r=true;
	return r;
}
////////////////////////////////////////////////////////////key��
