#include "plane.h"
Plane::Plane()
{
    myplane.load(":/image/images/myplane.png");
    x = (500-myplane.width())*0.5;		//设置飞机初始化位置
    y = 600-myplane.height();
    recored = 0;
    life = 10;
    isPlayed = false;
    skill = 20;
    interval = 30;
}

void Plane::shoot(){			//飞机射击函数
    recored++;
    if(recored<interval)		//如果标记时间小于间隔，直接返回
        return;
    recored = 0;				//否则重置标记时间，并发射一颗子弹
    for(int i = 0;i<30;i++){	//选择空闲子弹进行发射
        if(myBullet[i].isFree){
            myBullet[i].x = x+40;	//设定子弹发射的位置
            myBullet[i].y = y-10;
            myBullet[i].isFree = false;		//改变子弹空闲状态
            break;
        }
    }
}

