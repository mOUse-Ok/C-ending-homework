#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QWidget>
#include"game.h"
class MainScene : public QWidget
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = 0);
    ~MainScene();

    game *g=NULL;
    QPixmap begin_map;
    void paintEvent(QPaintEvent *event);

};

#endif // MAINSCENE_H
