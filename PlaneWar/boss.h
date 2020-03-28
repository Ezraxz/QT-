#ifndef BOSS_H
#define BOSS_H

#include "config.h"
#include <QPixmap>

class Boss
{
public:
    Boss();
    void updatePosition();//更新位置

public:
    QPixmap m_boss;

    int m_X;
    int m_Y;

    QRect m_Rect;

    int m_speed;

    bool m_Free;

    int m_blood;//血量
};

#endif // BOSS_H
