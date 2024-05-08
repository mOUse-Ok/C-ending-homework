#include "bomb.h"

Bomb::Bomb()
{
    for(int i=0;i<7;i++){
        QString str = QString(BOMB_PATH).arg(i);
        bombPix.push_back(str);
    }					//初始化将所有图片添加值向量中
    recored = 0;
    index = 0;
    x = 0;
    y = 0;
    isPlayde = false;
}
void Bomb::updateInfo(){
    recored++;				//设置播放间隔
    if(recored<20)
        return;
    recored = 0;
    index++;				//设置播放图片位置
    if(index>6)
        isPlayde = true;		//全部播放完毕改变状态
}
