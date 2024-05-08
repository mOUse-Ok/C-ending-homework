#ifndef BULLET_H
#define BULLET_H
#include <QString>
#include <QPixmap>
class Bullet
{
public:
    Bullet();
    QPixmap bullet;						//我方飞机子弹图片
    QPixmap EnemyBullet;			//敌方普通飞机子弹图片
    QPixmap EnemyBullet2;				//敌方Boss飞机子弹图片
    int speed;							//子弹运动速度
    int x;
    int y;
    void updatePosition();				//我方飞机子弹运动函数
    void EnemyUpdatePosition();			//敌方飞机子弹运动函数
    void EnemyUpdatePositionLeft();
    void EnemyUpdatePositionRight();
    bool isFree;						//子弹是否在游戏界面中(空闲)
};

#endif // BULLET_H
