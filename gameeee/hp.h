#ifndef HP_H
#define HP_H
#include "qpixmap.h"
#include"enemyplane.h"
class HP
{
public:
    HP();
    int  HP_X=10,HP_Y=10,Left_HP=3;
    QPixmap m_HP;
    EnemyPlane enemy1;
};

#endif // HP_H
