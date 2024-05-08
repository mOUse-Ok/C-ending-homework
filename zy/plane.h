#ifndef PLANE_H
#define PLANE_H
#include <QPoint>
#include <QPixmap>
#include "bullet.h"
class Plane
{
public:
    Bullet myBullet[30];
    Plane();
    void shoot();				//飞机射击函数
    QPixmap myplane;			//我方飞机图片
    int x;
    int y;
    int recored;				//飞机射击时间标记
    int interval;				//飞机射击间隔
    int life;                   //生命值
    bool isPlayed;
    double skill;				//技能值
};

#endif // PLANE_H

