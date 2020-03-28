#ifndef ENEMYPLANE_H
#define ENEMYPLANE_H

#include "config.h"
#include <QPixmap>


class EnemyPlane
{
public:
    EnemyPlane();

    //更新坐标
    void updatePosition();

public:
    //资源
    QPixmap m_enemy;
    //位置
    int m_X;
    int m_Y;
    //矩型框
    QRect m_Rect;
    //状态
    bool m_Free;
    //速度
    int m_Speed;
};

#endif // ENEMYPLANE_H
