#include "bullet.h"

Bullet::Bullet()
{
    bullet.load(":/image/images/mybullet.png");			//子弹图片加载
    EnemyBullet.load(":/image/images/enemybullet.png");
    EnemyBullet2.load(":/image/images/bossbullet.png");
    speed = 10;											//设置子弹速度
    isFree = true;										//设置状态为空闲
}
void Bullet::updatePosition(){	//我方飞机子弹更新函数
    if(isFree)
        return;			//如果子弹为空闲，直接返回，否则向上运动
    y-=5;
    if(y<0)
        isFree = true;		//子弹超出游戏界面，返回空闲状态
}

void Bullet::EnemyUpdatePosition(){		//敌方飞机子弹更新函数
    if(isFree)
        return;
    y+=5;
}

void Bullet::EnemyUpdatePositionLeft(){ //子弹偏左运动
    if(isFree)
        return;
    x-=2;
    y+=5;
}

void Bullet::EnemyUpdatePositionRight(){	//子弹偏右运动
    if(isFree)
        return;
    x+=2;
    y+=5;
}
