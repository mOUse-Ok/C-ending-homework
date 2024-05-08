#ifndef ENEMYPLANE1_H
#define ENEMYPLANE1_H
#include <QPixmap>
#include "bullet.h"
#include "bomb.h"
class EnemyPlane1
{
public:
    Bomb bomb;					//飞机爆炸效果
    EnemyPlane1();
    int x;
    int y;
    double speed;					//飞机运动速度
    bool isFree;				//飞机是否在游戏界面中（空闲）
    bool isDestroyed;			//飞机是否被摧毁
    QPixmap enemy1;				//普通飞机图片
    int recored;				//射击时间间隔标志
    Bullet enemy1Bullet[30]; 	//子弹数组
    void shoot();				//射击函数
    void updatePosition();		//位置更新函数
};

#endif // ENEMYPLANE1_H
