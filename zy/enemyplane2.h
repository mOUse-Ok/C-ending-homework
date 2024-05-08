#ifndef ENEMYPLANE2_H
#define ENEMYPLANE2_H
#include <QPixmap>
#include "bullet.h"
#include "bomb.h"
class EnemyPlane2
{
public:
    EnemyPlane2();
    Bomb bomb;
    int x;
    int y;
    int speed;
    bool isDestroyed;
    bool isFree;
    int life;						//Boss类飞机的生命值
    QPixmap enemy2;					//Boss类飞机图片
    int recored1;				   //射击时间间隔
    Bullet enemy2Bullet1[30];
    Bullet enemy2Bullet2[30];
    Bullet enemy2Bullet3[30];		//Boss类飞机弹匣
    void shoot();					//射击函数
    void updatePosition();			//位置更新函数
};
#endif // ENEMYPLANE2_H
