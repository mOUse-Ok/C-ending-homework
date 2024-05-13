#include "game.h"
#include "config.h"
#include <QIcon>
#include <QPainter>
#include <QMouseEvent>
#include <ctime>
#include"hp.h"
//#include <QApplication>
//#include <QMediaPlayer>
//#include <QUrl>
#include<QtMultimedia/QMediaPlayer>
#include<QtMultimedia/QAudioOutput>
#include<QPushButton>
#include"gameover.h"

game::game(QWidget *parent)
    : QWidget{parent}
{initScene();
}
void game::initScene()
{
    //初始化窗口大小
    setFixedSize(GAME_WIDTH,GAME_HEIGHT);

    //设置窗口标题
    setWindowTitle(GAME_TITLE);

    //设置窗口标题
    setWindowIcon(QIcon(GAME_ICON));

    //设置定时器间隔
    m_Timer.setInterval(GAME_RATE);

    //调用启动游戏接口
    playGame();

    //敌机出场纪录变量 初始化
    m_recorder = 0;

    //随机数种子
    srand((unsigned int)time(NULL));  //头文件  #include <ctime>
}

void game::playGame()
{
    //启动背景音乐
    //QSound::play(SOUND_BACKGROUND);
    QAudioOutput *audioOutput=new  QAudioOutput(this);
    QMediaPlayer *startwhistle=new QMediaPlayer(this);  //创建一个音乐播放
    startwhistle->setAudioOutput(audioOutput );
    audioOutput->setVolume(0.02);
    startwhistle->setSource(QUrl("qrc:/res/seeuagian.MP3"));
    startwhistle->play();

    //玩游戏 启动定时器
    m_Timer.start();

    //监听定时器的信号
    connect(&m_Timer , &QTimer::timeout,[=](){
        //敌机出场
        enemyToScene();
        //更新游戏中所有元素的坐标
        updatePosition();
        //游戏中的元素 绘制到屏幕中
        update();
        //再调用paintEvent函数

        //碰撞检测
        collisionDetection();

        //游戏结束
        if (m_hp.Left_HP == -1) {
            over(); // 游戏结束，调用over函数
            return; // 退出定时器槽函数
        }
    });

}

void game::updatePosition()
{
    //更新地图坐标
    m_map.mapPosition();

    //更新血量
    Lose_HP();

    //发射子弹
    m_hero.shoot();

    //计算子弹坐标
    for(int i = 0 ;i < BULLET_NUM;i++)
    {
        //如果子弹状态为非空闲，计算发射位置
        if(m_hero.m_bullets[i].m_Free == false)
        {
            m_hero.m_bullets[i].updatePosition();
        }

    }

    //敌机坐标计算
    for(int i = 0 ; i< ENEMY_NUM;i++)
    {
        //非空闲敌机 更新坐标
        if(m_enemys[i].m_Free == false)
        {
            m_enemys[i].updatePosition();
        }
    }

    //计算爆炸播放的图片
    for(int i = 0 ; i < BOMB_NUM;i++)
    {
        if(m_bombs[i].m_Free == false)
        {
            m_bombs[i].updateInfo();
        }
    }

    //测试子弹
    //    temp_Bullet.m_Free = false;
    //    temp_Bullet.updatePosition();
}

void game::paintEvent(QPaintEvent *event)
{
    //利用画家画图图片
    QPainter painter(this);

    //绘制地图
    painter.drawPixmap(0,m_map.m_map1_posY,m_map.m_map1);
    painter.drawPixmap(0,m_map.m_map2_posY,m_map.m_map2);

    //绘制飞机
    painter.drawPixmap(m_hero.m_X,m_hero.m_Y,m_hero.m_Plane);

    //绘制血量
    for(int i=m_hp.Left_HP;i>=0;i--)
    {
        painter.drawPixmap(m_hp.HP_X+i*10,m_hp.HP_Y,m_hp.m_HP);
    }
    // 绘制剩余血量的数字
    // 假设剩余血量是 m_hp.Left_HP
    QString hpText = QString::number(m_hp.Left_HP+1); // 将剩余血量转换为字符串
    QFont font("Arial", 12, QFont::Bold); // 设置字体样式
    painter.setFont(font); // 应用字体样式
    int textX = m_hp.HP_X; // 确定文本的位置（在血量图标的右侧）
    painter.drawText(textX, m_hp.HP_Y + painter.fontMetrics().height()+50, hpText); // 绘制文本

    //绘制得分
    painter.drawPixmap(m_socre.Socre_X,m_socre.Socre_Y,m_socre.m_Socre);
    // 绘制得分的数字
    QString socreText = QString::number(m_socre.Socre); // 将得分转换为字符串
    QFont font1("Arial", 12, QFont::Bold); // 设置字体样式
    painter.setFont(font1); // 应用字体样式
    int textX1 = m_socre.Socre_X+96; // 确定文本的位置（在得分图标的右侧）
    painter.drawText(textX1, m_socre.Socre_Y+ painter.fontMetrics().height()+190, socreText); // 绘制文本

    //绘制子弹
    for(int i = 0 ;i < BULLET_NUM;i++)
    {
        //如果子弹状态为非空闲 ，绘制图片
        if(m_hero.m_bullets[i].m_Free == false)
        {
            painter.drawPixmap(m_hero.m_bullets[i].m_X,m_hero.m_bullets[i].m_Y,m_hero.m_bullets[i].m_Bullet);
        }

    }

    //绘制敌机
    for(int i = 0 ; i< ENEMY_NUM;i++)
    {
        if(m_socre.Socre<=10)
        { m_enemys[i].m_Speed= ENEMY_SPEED1;}
        else
        {
            if(m_socre.Socre>10&&m_socre.Socre<=20)
                m_enemys[i].m_Speed= ENEMY_SPEED2;
            else
                m_enemys[i].m_Speed= ENEMY_SPEED3;
        }
        if(m_enemys[i].m_Free == false)
        {
            painter.drawPixmap(m_enemys[i].m_X,m_enemys[i].m_Y,m_enemys[i].m_enemy);
        }
    }

    //绘制爆炸图片
    for(int i = 0 ; i < BOMB_NUM;i++)
    {
        if(m_bombs[i].m_Free == false)
        {
            painter.drawPixmap(m_bombs[i].m_X,m_bombs[i].m_Y,m_bombs[i].m_pixArr[m_bombs[i].m_index]);
        }
    }

    //测试子弹
    //painter.drawPixmap(temp_Bullet.m_X,temp_Bullet.m_Y,temp_Bullet.m_Bullet);
}

void game::mouseMoveEvent(QMouseEvent * event)
{
    /*int x =  event->x() -m_hero.m_Rect.width() * 0.5;
    int y =  event->y() -m_hero.m_Rect.height() *0.5;*/
    QPoint mousePosition = event->pos();
    int x = mousePosition.x() - m_hero.m_Rect.width()*0.5; //鼠标位置 - 飞机矩形的一半
    int y = mousePosition.y() - m_hero.m_Rect.height()*0.5;
    //边界检测

    if(x <= 0 )
    {
        x = 0;
    }
    if(x >= GAME_WIDTH - m_hero.m_Rect.width())
    {
        x = GAME_WIDTH - m_hero.m_Rect.width();
    }
    if(y <= 0)
    {
        y = 0;
    }
    if(y >= GAME_HEIGHT - m_hero.m_Rect.height())
    {
        y = GAME_HEIGHT - m_hero.m_Rect.height();
    }

    m_hero.setPosition(x,y);
}

void game::enemyToScene()
{
    //累加出场间隔
    m_recorder++;
    if(m_recorder < ENEMY_INTERVAL)
    {
        return;
    }

    m_recorder = 0;

    for(int i = 0 ; i< ENEMY_NUM;i++)
    {
        if(m_enemys[i].m_Free)
        {
            //敌机空闲状态改为false
            m_enemys[i].m_Free = false;
            //设置坐标
            m_enemys[i].m_X = rand() % (GAME_WIDTH - m_enemys[i].m_Rect.width());
            m_enemys[i].m_Y = -m_enemys[i].m_Rect.height();
            break;
        }
    }
}

void game::collisionDetection()
{
    //遍历所有非空闲的敌机
    for(int i = 0 ;i < ENEMY_NUM;i++)
    {
        if(m_enemys[i].m_Free)
        {
            //空闲飞机 跳转下一次循环
            continue;
        }

        //遍历所有 非空闲的子弹
        for(int j = 0 ; j < BULLET_NUM;j++)
        {
            if(m_hero.m_bullets[j].m_Free)
            {
                //空闲子弹 跳转下一次循环
                continue;
            }

            //如果子弹矩形框和敌机矩形框相交，发生碰撞，同时变为空闲状态即可
            if(m_enemys[i].m_Rect.intersects(m_hero.m_bullets[j].m_Rect))
            {
                //播放音效
                QAudioOutput *audioOutput=new  QAudioOutput(this);
                QMediaPlayer *startwhistle=new QMediaPlayer(this);  //创建一个音乐播放
                startwhistle->setAudioOutput(audioOutput );
                audioOutput->setVolume(0.08);
                startwhistle->setSource(QUrl("qrc:/res/man.MP3"));
                startwhistle->play();
                m_enemys[i].m_Free = true;
                m_hero.m_bullets[j].m_Free = true;

                //得分+1
                m_socre.Socre++;

                //调用爆炸特效
                //播放爆炸效果
                for(int k = 0 ; k < BOMB_NUM;k++)
                {
                    if(m_bombs[k].m_Free)
                    {
                        //爆炸状态设置为非空闲
                        m_bombs[k].m_Free = false;
                        //更新坐标
                        m_bombs[k].m_X = m_enemys[i].m_X;
                        m_bombs[k].m_Y = m_enemys[i].m_Y;
                        break;
                    }
                }

            }
        }
    }
}
void game::Lose_HP(){
    for(int i = 0 ;i < ENEMY_NUM;i++)
    {
        if(m_enemys[i].m_Y==812)
        {
            m_hp.Left_HP--;
           // m_enemys[i].m_Y=813;
           // m_enemys[i].m_Speed=0;


            QAudioOutput *audioOutput=new  QAudioOutput(this);
            QMediaPlayer *startwhistle=new QMediaPlayer(this);  //创建一个音乐播放
            startwhistle->setAudioOutput(audioOutput );
            audioOutput->setVolume(0.08);
            startwhistle->setSource(QUrl("qrc:/res/whatcanisay.MP3"));
            startwhistle->play();
        }
    }
}
void game::over(){
    if (m_hp.Left_HP == -1) {
        if (m_gameOver) return; // 如果已经调用过over，直接返回

        m_gameOver = true; // 设置游戏结束标志

        // 停止定时器
        m_Timer.stop();
        // 断开定时器连接（可选，因为定时器已经停止）
        disconnect(&m_Timer, &QTimer::timeout, nullptr, nullptr);

        // 显示GameOver窗口
        go = new GameOver;
        go->show();

        this->close();
    }
}
