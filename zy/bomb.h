#ifndef BOMB_H
#define BOMB_H
#define BOMB_PATH ":/image/images/bomb-%1.png" //设置图片路径
#include <QPixmap>							  //1%为可代替部分
#include <QVector>
#include <QString>
class Bomb
{
public:
    Bomb();
    void updateInfo();				//爆炸图片更新
    int x;
    int y;
    QVector<QPixmap> bombPix;		//爆炸图片数组
    int recored;					//爆炸时间标志
    int index;						//图片下标
    bool isPlayde;					//爆炸效果是否播放过
};
#endif // BOMB_H
