#include "gameover.h"
#include "config.h"
#include "game.h"
#include <QIcon>
#include <QPainter>
#include <QMouseEvent>
#include<QtMultimedia/QMediaPlayer>
#include<QtMultimedia/QAudioOutput>
#include<QPushButton>
GameOver::GameOver(QWidget *parent)
    : QWidget{parent}
{    // 初始化场景
    setFixedSize(1154, 1026);
    setWindowTitle("KobeVSgege");
    setWindowIcon(QIcon(":/res/sign1.jpg"));
    over_map.load(OVERMAP);


    // 创建一个按钮并设置其位置、大小等属性
    QPushButton *b = new QPushButton("点此退出游戏", this);
    b->setGeometry(QRect(400, 500, 150, 51));

    QIcon buttonIcon(":/res/close.png");

    // 设置图标到按钮
    b->setIcon(buttonIcon);

    // （可选）设置图标大小
    b->setIconSize(QSize(51, 51));
    //b->setFixedSize(b->iconSize());
    // 连接按钮的点击信号到一个 lambda 表达式
    connect(b, &QPushButton::clicked, [=]() {
        // 播放结束音效
        QAudioOutput *audioOutput = new QAudioOutput(this);
        QMediaPlayer *endSound = new QMediaPlayer(this);
        endSound->setAudioOutput(audioOutput);
        audioOutput->setVolume(0.1);
        endSound->setSource(QUrl("qrc:/res/mambaout.MP3")); // 注意：这里应该是qrc资源路径
        // 连接positionChanged信号到一个槽函数
        connect(endSound, &QMediaPlayer::positionChanged, this, &GameOver::checkSoundEnded);

        // 开始播放音效
        endSound->play();
       // this->close(); // 关闭 GameOver 窗口
    });// 创建一个按钮并设置其位置、大小等属性


    QPushButton *re = new QPushButton("点此重新开始", this);
    re->setGeometry(QRect(540, 500, 150, 51));

    QIcon re_buttonIcon(":/res/DM_20240513170938_001.png");

    // 设置图标到按钮
    re->setIcon(re_buttonIcon);

    // （可选）设置图标大小
    re->setIconSize(QSize(51, 51));
    //b->setFixedSize(b->iconSize());
    // 连接按钮的点击信号到一个 lambda 表达式
    connect(re, &QPushButton::clicked, [=]() {

        // 播放结束音效（如果需要）
        QAudioOutput *audioOutput = new QAudioOutput(this);
        QMediaPlayer *endSound = new QMediaPlayer(this);
        endSound->setAudioOutput(audioOutput);
        audioOutput->setVolume(1.6);
        endSound->setSource(QUrl("qrc:/res/mambaout.MP3")); // 注意：这里应该是qrc资源路径
        // 连接positionChanged信号到一个槽函数
        game *rego;
        rego=new game;
        rego->show();
        connect(endSound, &QMediaPlayer::positionChanged, this, &GameOver::checkSoundEnded_re);

        this->close();
    });}






    void GameOver::paintEvent(QPaintEvent *event) {
     QPainter painter(this);
     painter.drawPixmap(0,0, over_map);
}
    void GameOver::checkSoundEnded() {
        QMediaPlayer *endSound = qobject_cast<QMediaPlayer*>(sender());
        if (!endSound) return; // 确保sender()是一个QMediaPlayer对象

        // 检查音效是否播放完毕
        if (endSound->position() == endSound->duration()) {
            // 音效已结束，关闭窗口
            this->close();

            // 断开positionChanged信号的连接
            disconnect(endSound, &QMediaPlayer::positionChanged, this, &::GameOver::checkSoundEnded);

            // 清理资源（如果不再需要endSound）
            endSound->deleteLater(); // 使用deleteLater()确保在事件循环中安全删除
        }
    }
    void GameOver::checkSoundEnded_re(){
        game* rego;
        rego=new game;
        rego->show();

    }
