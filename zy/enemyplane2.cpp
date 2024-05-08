#include "enemyplane2.h"
#include <QPixmap>
#include "bullet.h"
EnemyPlane2::EnemyPlane2()
{
    enemy2.load(":/image/images/boss.png");
    x = 0;
    y = 0;
    isFree = true;
    isDestroyed = false;
    speed = 1;
    life = 10;
    recored1 = 0;
}

void EnemyPlane2::updatePosition(){
    if(isFree)
        return;
    y+=speed;
    if(y>600)
        isDestroyed = true;
}

void EnemyPlane2::shoot(){			//Boss飞机射击函数
    recored1++;
    if(recored1<20)
        return;
    recored1 = 0;
    for(int i=0;i<30;i++){
        if(enemy2Bullet1[i].isFree){
            enemy2Bullet1[i].x = x+30;
            enemy2Bullet1[i].y = y+20;
            enemy2Bullet1[i].isFree = false;
            break;
        }
    }
    for(int i=0;i<30;i++){
        if(enemy2Bullet2[i].isFree){
            enemy2Bullet2[i].x = x+80;
            enemy2Bullet2[i].y = y+20;
            enemy2Bullet2[i].isFree = false;
            break;
        }
    }
    for(int i=0;i<30;i++){
        if(enemy2Bullet3[i].isFree){
            enemy2Bullet3[i].x = x+130;
            enemy2Bullet3[i].y = y+20;
            enemy2Bullet3[i].isFree = false;
            break;
        }
    }
}
