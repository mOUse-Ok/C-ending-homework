#ifndef SOCRE_H
#define SOCRE_H
#include "qpixmap.h"
#include"enemyplane.h"

class socre
{
public:
    socre();
    int  Socre_X=950,Socre_Y=5,Socre=0;
    int part=1;
    QPixmap m_Socre;
    EnemyPlane enemy1;
};

#endif // SOCRE_H
