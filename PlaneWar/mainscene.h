#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QWidget>
#include "map.h"
#include "heroplane.h"
#include "enemyplane.h"
#include "bomb.h"
#include "boss.h"
#include <QTimer>

class Mainscene : public QWidget
{
    Q_OBJECT

public:
    Mainscene(QWidget *parent = 0);
    ~Mainscene();
    void InitScene();

    //启动游戏  用于启动定时器对象
    void playGame();
    //更新坐标
    void updatePosition();
    //绘图事件
    void paintEvent(QPaintEvent *event);
    //鼠标移动事件
    void mouseMoveEvent(QMouseEvent *event);
    //敌机出场
    void enemyToScene();
    //碰撞检测
    void collisionDetection();


public:
    QTimer m_Timer;
    Map m_map;//地图
    HeroPlane m_hero;//战机
    EnemyPlane m_enemys[ENEMY_NUM];//敌机
    int m_recorder;//敌机出场间隔
    Bomb m_bombs[BOMB_NUM];//爆炸数组
    int m_beat;//消灭数量
    Boss m_bossplane;//boss

};

#endif // MAINSCENE_H
