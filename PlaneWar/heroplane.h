#ifndef HEROPLANE_H
#define HEROPLANE_H

#include <QPixmap>
#include <QRect>
#include "bullet.h"

class HeroPlane
{
public:
    HeroPlane();

    void shoot();//射击
    void setPosition(int x,int y);//设置飞机位置

public:
    QPixmap m_Plane;//设置飞机资源对象

    //飞机坐标
    int m_X;
    int m_Y;

    //飞机区域
    QRect m_Rect;

    //弹夹
    Bullet m_bullets[BULLET_NUM];

    //发射间隔
    int m_recorder;

};

#endif // HEROPLANE_H
