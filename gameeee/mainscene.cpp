#include "mainscene.h"
#include "config.h"
#include <QIcon>
#include <QPainter>
#include <QPushButton>
#include "game.h"

MainScene::MainScene(QWidget *parent)
    : QWidget(parent)
{
    // 初始化场景
    setFixedSize(1118, 730);
    setWindowTitle("KobeVSgege");
    setWindowIcon(QIcon(":/res/sign1.jpg"));
    begin_map.load(STARTMAP);


    // 创建一个按钮并设置其位置、大小等属性
    QPushButton *b = new QPushButton("", this);
    b->setGeometry(QRect(490, 500, 172, 56)); //大小为 100x50

    QIcon buttonIcon(":/res/gogame.png");

    // 设置图标到按钮
    b->setIcon(buttonIcon);

    // （可选）设置图标大小，例如 48x48 像素
    b->setIconSize(QSize(172, 56));
    b->setFixedSize(b->iconSize());
    // 连接按钮的点击信号到一个 lambda 表达式
    connect(b, &QPushButton::clicked, [=]() {
        game *g = new game;
        g->show();
        this->close(); // 关闭 MainScene 窗口
    });
}

MainScene::~MainScene()
{

}

//paintEvent 函数以绘制 QPixmap
void MainScene::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(0,0, begin_map);
}

