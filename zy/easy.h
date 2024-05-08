#ifndef EASY_H
#define EASY_H

#include <QWidget>
#include "plane.h"
#include <QPainter>
#include <QPaintEvent>
#include "bullet.h"
#include <QTimer>
#include <QMouseEvent>
#include "enemyplane1.h"
#include "enemyplane2.h"
#include <QLabel>
#define SCORE "Score: %1"		//预定义得分字符串
#define LIFE  "Life:  %1"		//预定义生命值字符串
class Easy : public QWidget
{
    Q_OBJECT
public:
    QLabel life;
    QLabel score;
    int Score;
    Plane MyPlane;
    EnemyPlane1 Enemy1[10];						//敌机数组
    EnemyPlane2 Enemy2[2];						//Boss敌机数组
    int EnemyRecored1;							//敌机出场间隔
    int EnemyRecored2;							//Boss出场间隔
    QTimer Timer;								//设置QTimer定时器
    void initial();								//游戏初始化
    void startGame();							//游戏开始
    void updatePositino();						//游戏信息更新函数
    void paintEvent(QPaintEvent *E);			//绘图事件
    void mouseMoveEvent(QMouseEvent *E);		//鼠标移动事件
    void BossShow();							//Boss出场函数
    void EnemyShow();							//敌机出场函数
    void collisionDetection();					//碰撞检测函数
    int getDistanceBAE(Bullet b,EnemyPlane1 E){
        int distance=0;
        return distance;}//子弹与敌机距离
    int getDistanceBAB(Bullet b,EnemyPlane2 B){
        int distance=0;
        return distance;} //子弹与Boss距离
    int getDistanceBAM(Bullet b,Plane M){
        int distance=0;
        return distance;
    }		//子弹与我方飞机距离
    int getDistanceEAM(EnemyPlane1 E,Plane M){
        int distance=0;
        return distance;
    }	//敌机与我方飞机距离
    explicit Easy(QWidget *parent = 0);
    ~Easy(){};
};
#endif // EASY_H
