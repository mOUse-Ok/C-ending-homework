#include "enemyplane1.h"

EnemyPlane1::EnemyPlane1()
{
    enemy1.load(":/image/images/enemyplane.png");
    x = 0;
    y = 0;
    isFree = true;
    isDestroyed = false;
    speed = 1.5;
    recored = 0;
}

void EnemyPlane1::updatePosition(){ 	//敌方飞机运动函数
    if(isFree)					//如果为空闲飞机直接返回
        return;
    y+=speed;					//否则向下运动
    if(y>600)
        isDestroyed = true;		//超出游戏界面设为摧毁
}

void EnemyPlane1::shoot(){
    recored++;
    if(recored<50)
        return;
    recored = 0;
    for(int i=0;i<30;i++){
        if(enemy1Bullet[i].isFree){
            enemy1Bullet[i].x = x+20;
            enemy1Bullet[i].y = y+40;
            enemy1Bullet[i].isFree = false;
            break;
        }
    }
}
