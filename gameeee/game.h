#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QWidget>
#include <QTimer>
#include "map.h"
#include "heroplane.h"
//#include "bullet.h"
#include "enemyplane.h"
#include "bomb.h"
//#include <QSound>
#include"hp.h"
#include"gameover.h"
#include "socre.h"
class game : public QWidget
{
    Q_OBJECT
public:
    explicit game(QWidget *parent = nullptr);
    //初始化场景
    void initScene();

    GameOver *go=NULL;
    void over();

    //启动游戏  用于启动定时器对象
    void playGame();
    //更新坐标
    void updatePosition();
    //绘图事件
    void paintEvent(QPaintEvent *event);

    //重写鼠标移动事件
    void mouseMoveEvent(QMouseEvent *);

    //敌机出场
    void enemyToScene();

    //碰撞检测
    void collisionDetection();

    //血量刷新
    void Lose_HP();

    //地图对象
    Map m_map;

    //创建飞机对象
    HeroPlane m_hero;

    //创建血量条对象
    HP m_hp;

    //创建得分对象
    socre m_socre;

    //定时器对象
    QTimer m_Timer;
    bool m_gameOver; // 新增变量来跟踪游戏是否结束

    //敌机数组
    EnemyPlane m_enemys[ENEMY_NUM];

    //敌机出场间隔记录
    int m_recorder;

    //爆炸数组
    Bomb m_bombs[BOMB_NUM];


    //测试子弹
    //Bullet temp_Bullet;

signals:
};

#endif // GAME_H
