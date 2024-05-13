#ifndef GAMEOVER_H
#define GAMEOVER_H
#include "qmediaplayer.h"
#include <QObject>
#include <QWidget>
#include <QTimer>
//#include "bullet.h"
//#include <QSound>
#include <QWidget>
class GameOver : public QWidget
{
    Q_OBJECT
public:
    explicit GameOver(QWidget *parent = nullptr);
    QPixmap over_map;
    void paintEvent(QPaintEvent *event);
    void over();
    QMediaPlayer *endSound;
    void checkSoundEnded();
    void checkSoundEnded_re();
   // game rego;
signals:
};

#endif // GAMEOVER_H
