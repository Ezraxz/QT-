#include "map.h"
#include "config.h"

Map::Map()
{
    //初始化加载地图对象
    m_map1.load(MAP_PATH);
    m_map2.load(MAP_PATH);

    //设置地图Y坐标
    m_map1_posY=-GAME_HEIGHT;
    m_map1_posY=0;

    //设置滚动速度
    m_scroll_speed=MAP_SCROLL_SPEED;
}

void Map::mapPositon()
{
    //处理第一张图片滚动
    m_map1_posY += m_scroll_speed;
    if(m_map1_posY >= 0)
    {
        m_map1_posY =-GAME_HEIGHT+10;
    }

    //处理第二张图片滚动
    m_map2_posY += m_scroll_speed;
    if(m_map2_posY >= GAME_HEIGHT-10 )
    {
        m_map2_posY = 0;
    }
}
