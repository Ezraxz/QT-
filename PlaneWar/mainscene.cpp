#include "mainscene.h"
#include "config.h"
#include <QIcon>
#include <QPainter>
#include <QMouseEvent>
#include <ctime>

Mainscene::Mainscene(QWidget *parent)
    : QWidget(parent)
{
    InitScene();
    playGame();
}

Mainscene::~Mainscene()
{

}

void Mainscene::InitScene()
{
    //设置窗口
    setFixedSize(GAME_WIDTH,GAME_HEIGHT);
    setWindowTitle(GAME_TITLE);
    setWindowIcon(QIcon(GAME_ICON));
    //初始化定时器
    m_Timer.setInterval(GAME_RATE);

    m_recorder=0;//敌机初始化

    srand((unsigned int)time(NULL));//随机种子

    m_beat=0;//消灭数量初始化


}

void Mainscene::playGame()
{
    m_Timer.start();  //启动定时器

    //监听定时器
    connect(&m_Timer,&QTimer::timeout,[=](){
        enemyToScene();//敌机出场
        updatePosition();
        update();
        collisionDetection();//碰撞检测
    });
}

void Mainscene::updatePosition()
{
    m_map.mapPositon();
    m_hero.shoot();
    //计算子弹坐标
    for(int i = 0 ;i < BULLET_NUM;i++)
    {
        //如果子弹状态为非空闲，计算发射位置
        if(!m_hero.m_bullets[i].m_Free)
        {
            m_hero.m_bullets[i].updatePosition();
        }
    }
    //计算敌机坐标
    for(int i = 0 ; i< ENEMY_NUM;i++)
    {
        //非空闲敌机 更新坐标
        if(m_enemys[i].m_Free == false)
        {
            m_enemys[i].updatePosition();
        }
    }

    //计算爆炸播放的图片
    for(int i = 0 ; i < BOMB_NUM;i++)
    {
        if(m_bombs[i].m_Free == false)
        {
            m_bombs[i].updateInfo();
        }
    }

    //计算boss坐标
    if(m_bossplane.m_Free == false)
    {
        m_bossplane.updatePosition();
    }
}

void Mainscene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    //绘制地图
    painter.drawPixmap(0,m_map.m_map1_posY , m_map.m_map1);
    painter.drawPixmap(0,m_map.m_map2_posY , m_map.m_map2);

    //绘制飞机
    painter.drawPixmap(m_hero.m_X,m_hero.m_Y,m_hero.m_Plane);

    //绘制子弹
    for(int i=0;i<BULLET_NUM;i++)
    {
        if(!m_hero.m_bullets[i].m_Free)
        {
            painter.drawPixmap(m_hero.m_bullets[i].m_X,m_hero.m_bullets[i].m_Y,m_hero.m_bullets[i].m_Bullet);
        }
    }

    //绘制敌机
    for(int i=0;i<ENEMY_NUM;i++)
    {
        if(!m_enemys[i].m_Free)
        {
            painter.drawPixmap(m_enemys[i].m_X,m_enemys[i].m_Y,m_enemys[i].m_enemy);
        }
    }

    //绘制爆炸图片
    for(int i = 0 ; i < BOMB_NUM;i++)
    {
        if(m_bombs[i].m_Free == false)
        {
            painter.drawPixmap(m_bombs[i].m_X,m_bombs[i].m_Y,m_bombs[i].m_pixArr[m_bombs[i].m_index]);
        }
    }

    //绘制boss
    if(!m_bossplane.m_Free)
    {
        painter.drawPixmap(m_bossplane.m_X,m_bossplane.m_Y,m_bossplane.m_boss);
    }
}

void Mainscene::mouseMoveEvent(QMouseEvent *event)
{
    int x = event->x() - m_hero.m_Rect.width()*0.5; //鼠标位置 - 飞机矩形的一半
    int y = event->y() - m_hero.m_Rect.height()*0.5;

    if(x<=0)
    {
        x=0;
    }
    if(x>=GAME_WIDTH-m_hero.m_Rect.width())
    {
        x=GAME_WIDTH-m_hero.m_Rect.width();
    }
    if(y<=0)
    {
        y=0;
    }
    if(y>=GAME_HEIGHT-m_hero.m_Rect.height())
    {
        y=GAME_HEIGHT-m_hero.m_Rect.height();
    }
     m_hero.setPosition(x,y);
}

void Mainscene::enemyToScene()
{
    if(!m_bossplane.m_Free)
    {
        return;
    }
    m_recorder++;
    if(m_recorder<ENEMY_INTERVAL)
    {
        return;
    }

    m_recorder=0;

    for(int i=0;i<ENEMY_NUM;i++)
    {
        if(m_enemys[i].m_Free)
        {
            m_enemys[i].m_Free=false;

            m_enemys[i].m_X=rand()%(GAME_WIDTH-m_enemys[i].m_Rect.width());
            m_enemys[i].m_Y=-m_enemys[i].m_Rect.height();
            break;
        }
    }
}

void Mainscene::collisionDetection()
{
    //boss碰撞
    if(!m_bossplane.m_Free)
    {
        for(int i=0;i<BULLET_NUM;i++)
        {
            if(m_hero.m_bullets[i].m_Free)
            {
                continue;
            }
            if(m_bossplane.m_Rect.intersects(m_hero.m_bullets[i].m_Rect))
            {
                m_hero.m_bullets[i].m_Free=true;
                m_bossplane.m_blood--;
                if(m_bossplane.m_blood==0)
                {
                    m_bossplane.m_blood=BOSS_BLOOD;

                    //播放爆炸效果
                    for(int k = 0 ; k < BOMB_NUM;k++)
                    {
                        if(m_bombs[k].m_Free)
                        {
                            //爆炸状态设置为非空闲
                            m_bombs[k].m_Free = false;

                            //更新坐标
                            m_bombs[k].m_X = m_bossplane.m_X;
                            m_bombs[k].m_Y = m_bossplane.m_Y;
                            break;
                        }
                    }

                    m_bossplane.m_Free=true;
                }
            }
        }
    }

    //小兵碰撞
    for(int i=0;i<ENEMY_NUM;i++)
    {
        if(m_enemys[i].m_Free)
        {
            continue;
        }

        for(int j=0;j<BULLET_NUM;j++)
        {
            if(m_hero.m_bullets[j].m_Free)
            {
                continue;
            }

            if(m_enemys[i].m_Rect.intersects(m_hero.m_bullets[j].m_Rect))
            {
                m_enemys[i].m_Free=true;
                m_hero.m_bullets[j].m_Free=true;
                //计算消灭数量
                m_beat++;
                if(m_beat==30)
                {
                    m_bossplane.m_Free=false;
                    m_beat=0;
                }

                //播放爆炸效果
                for(int k = 0 ; k < BOMB_NUM;k++)
                {
                    if(m_bombs[k].m_Free)
                    {
                        //爆炸状态设置为非空闲
                        m_bombs[k].m_Free = false;

                        //更新坐标
                        m_bombs[k].m_X = m_enemys[i].m_X;
                        m_bombs[k].m_Y = m_enemys[i].m_Y;
                        break;
                    }
                }
            }
        }
    }
}

