#ifndef CONFIG_H
#define CONFIG_H


/**********  游戏配置数据 **********/
#define GAME_WIDTH  1152  //宽度
#define GAME_HEIGHT 1024  //高度
#define GAME_TITLE "牢大大战鸽鸽 v2.0" //标题
#define GAME_ICON ":/res/sign1.jpg"  //图标路径
#define GAME_RATE  10  //单位毫秒
#define MAP_SCROLL_SPEED 0
/**开始界面数据**/
#define STARTMAP ":/res/kobehello.jpg"
/**结束界面数据**/
#define OVERMAP ":/res/kobebye1.jpg"
/**********  地图配置数据 **********/
#define MAP_PATH  ":/res/R-C1.jpg" //地图图片路径
/**********  主角配置数据 **********/
#define HERO_PATH ":/res/man.png"

/**血量显示配置数据**/
#define HP_PATH ":/res/HP.png"

/**得分显示配置数据**/
#define Socre_PATH ":/res/socre.png"

/**********  篮球配置数据 **********/
#define BULLET_PATH ":/res/ball.png"   //子弹图片路径
#define BULLET_SPEED 5  //子弹移动速度

#define BULLET_NUM 30   //弹匣中子弹总数
#define BULLET_INTERVAL 40 //发射子弹时间间隔

/**********  敌机配置数据 **********/
#define ENEMY_PATH  ":/res/kun.png"  //敌机资源图片
#define ENEMY_SPEED1 10  //敌机移动速度1
#define ENEMY_SPEED2 20  //2
#define ENEMY_SPEED3 30  //3
#define ENEMY_NUM   30  //敌机总数量
#define ENEMY_INTERVAL  120  //敌机出场时间间隔

/**********  爆炸配置数据 **********/
#define BOMB_PATH  ":/res/bomb-%1.png"   //爆炸资源图片
#define BOMB_NUM  20     //爆炸数量
#define BOMB_MAX  7      //爆炸图片最大索引
#define BOMB_INTERVAL 20   //爆炸切图时间间隔

#define SOUND_BACKGROUND ":/res/bg.wav"
#define SOUND_BOMB ":/res/bomb.wav"

#endif // CONFIG_H
