#include "boss.h"

Boss::Boss()
{
    m_boss.load(BOSS_PATH);

    m_X=GAME_WIDTH*0.5-m_boss.width()*0.5;
    m_Y=-m_boss.height();

    m_Free=true;

    m_blood=BOSS_BLOOD;

    m_speed=ENEMY_SPEED/5;

    m_Rect.setWidth(m_boss.width());
    m_Rect.setHeight(m_boss.height());
    m_Rect.moveTo(m_X,m_Y);
}

void Boss::updatePosition()
{
    if(m_Free)
    {
        return;
    }
    if(m_Y<=0)
    {
        m_Y+=m_speed;
        m_Rect.moveTo(m_X,m_Y);
    }


}
