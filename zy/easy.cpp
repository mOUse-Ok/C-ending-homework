#include "easy.h"

Easy::Easy(QWidget *parent) :
    QWidget(parent),
    life(this), // 直接在初始化列表中创建 QLabel 对象
    score(this) // 同样
{
    //设置属性::当窗口关闭时，窗口对象将被销毁，内存得以释放
    setAttribute(Qt::WA_DeleteOnClose, true);
    //设置游戏界面500宽，600高
    resize(500, 600);
    //为游戏窗口设置背景
    setAutoFillBackground(true);
    QPalette pal;
    QPixmap pixmap(":/image/images/background.png");
    pal.setBrush(QPalette::Window, QBrush(pixmap));
    setPalette(pal);

    //设定标签样式
    life.setFont(QFont("Algerian", 16));
    life.setStyleSheet("QLabel{background:transparent;color:white;}");
    score.setFont(QFont("Algerian", 16));
    score.setStyleSheet("QLabel{background:transparent;color:white;}");

    // 假设这里还有其他初始化的工作
    initial();
}
void Easy::initial(){			//游戏初始化
    Timer.setInterval(10);		//设置定时器间隔，每10ms刷新一次
    startGame();				//开始游戏
    EnemyRecored1 = 0;			//设置出场间隔初始值
    EnemyRecored2 = 0;
    srand((unsigned int)time(NULL));	//设置随机数种子
}
void Easy::startGame(){
    Timer.start();
    connect(&Timer , &QTimer::timeout,[=](){
        EnemyShow();
        BossShow();
        updatePositino();
        collisionDetection();
        update();
    }); 	//connect开始计时刷新
}
void Easy::EnemyShow(){				//敌机出场函数
    EnemyRecored1++;
    if(EnemyRecored1<150)
        return;
    EnemyRecored1=0;
    for(int i=0;i<10;i++)
        if(Enemy1[i].isFree&&!Enemy1[i].isDestroyed){
            Enemy1[i].isFree = false;
            Enemy1[i].x = rand()%(500-Enemy1[i].enemy1.width());
            Enemy1[i].y = 0;
            break;
        }
}
void Easy::BossShow(){			//Boss出场函数
    EnemyRecored2++;
    if(EnemyRecored2<500)
        return;
    EnemyRecored2=0;
    for(int i=0;i<2;i++)
        if(Enemy2[i].isFree){
            Enemy2[i].isFree = false;
            Enemy2[i].x = rand()%(500-Enemy2[i].enemy2.width());
            Enemy2[i].y = 0;
            break;
        }
}

void Easy::collisionDetection(){
    //遍历敌机
    for(int i=0;i<10;i++){
        if(!Enemy1[i].isFree){							//如果敌机非空闲
            if(getDistanceEAM(Enemy1[i],MyPlane)<30)	//如果我机与敌机距离小于30
            {
                MyPlane.life--;							//我机生命值减一
                Score+=10;
                         Enemy1[i].isDestroyed = true;			//设定敌机被摧毁
            }
            for(int j=0;j<30;j++){                      //遍历我机子弹
                if(MyPlane.myBullet[j].isFree)			//子弹空闲则跳过
                    continue;
                        //检测子弹与敌机距离并要求敌机未被摧毁
                        if(getDistanceBAE(MyPlane.myBullet[j],Enemy1[i])<30&&!Enemy1[i].isDestroyed){
                        MyPlane.myBullet[j].isFree = true;		//子弹消失，直接设定为空闲状态
                            Score+=10;
                                 Enemy1[i].isDestroyed = true;			//敌机摧毁
                    }
            }
        }
        for(int j=0;j<30;j++){                          //遍历敌机子弹
            if(Enemy1[i].enemy1Bullet[j].isFree)
                continue;
            if(getDistanceBAM(Enemy1[i].enemy1Bullet[j],MyPlane)<30){
                MyPlane.life--;
                Enemy1[i].enemy1Bullet[j].isFree = true;
            }
        }
    }
    //遍历Boss
    for(int i=0;i<2;i++){
        if(!Enemy2[i].isFree&&!Enemy2[i].isDestroyed){
            for(int j=0;j<30;j++){                          //遍历我机子弹
                if(MyPlane.myBullet[j].isFree)
                    continue;
                if(MyPlane.myBullet[j].x<Enemy2[i].x+Enemy2[i].enemy2.width()&&MyPlane.myBullet[j].x>Enemy2[i].x&&
                    MyPlane.myBullet[j].y<Enemy2[i].y){		//这里的检测碰撞的方法是子弹的x坐标在Boss图片的宽度之间，y坐标小于敌机y
                    Enemy2[i].life--;						//Boss生命值减一
                    MyPlane.myBullet[j].isFree = true;		//我机子弹消失
                    if(Enemy2[i].life<=0){					//当Boss生命值归零时
                        Score+=20;
                        Enemy2[i].isDestroyed = true;		//Boss被摧毁
                    }
                }
            }
        }
        for(int j=0;j<30;j++){											//遍历敌机子弹
            if(Enemy2[i].enemy2Bullet1[j].isFree)						//遍历第一个弹匣
                continue;
            if(getDistanceBAM(Enemy2[i].enemy2Bullet1[j],MyPlane)<30){	//子弹与我机距离小于30
                MyPlane.life--;											//我机生命值减一
                Enemy2[i].enemy2Bullet1[j].isFree = true;
            }
            if(Enemy2[i].enemy2Bullet2[j].isFree)						//遍历第二个弹匣
                continue;
            if(getDistanceBAM(Enemy2[i].enemy2Bullet2[j],MyPlane)<30){
                MyPlane.life--;
                Enemy2[i].enemy2Bullet2[j].isFree = true;
            }
            if(Enemy2[i].enemy2Bullet3[j].isFree)						//遍历第三个弹匣
                continue;
            if(getDistanceBAM(Enemy2[i].enemy2Bullet3[j],MyPlane)<30){
                MyPlane.life--;
                Enemy2[i].enemy2Bullet3[j].isFree = true;
            }
        }
    }
}
void Easy::updatePositino(){
    MyPlane.shoot();
    for(int i=0;i<30;i++)
        MyPlane.myBullet[i].updatePosition();
    for(int i=0;i<5;i++)
        MyPlane.myBullet[i].updatePosition();
            //敌机射击与运动
    for(int i=0;i<10;i++){
        if(!Enemy1[i].isFree&&!Enemy1[i].isDestroyed){
            Enemy1[i].shoot();
            Enemy1[i].updatePosition();
        }
        if(Enemy1[i].isDestroyed&&!Enemy1[i].isFree){
            Enemy1[i].bomb.updateInfo();
        }
        for(int j=0;j<30;j++)
            Enemy1[i].enemy1Bullet[j].EnemyUpdatePosition();
    }

    life.setText(QString(LIFE).arg(MyPlane.life));	//随时更新相关信息
    score.setText(QString(SCORE).arg(Score));
        //Boss射击与运动
    for(int i=0;i<2;i++){
        if(!Enemy2[i].isFree&&!Enemy2[i].isDestroyed){
            Enemy2[i].shoot();
            Enemy2[i].updatePosition();
        }
        if(Enemy2[i].isDestroyed&&!Enemy2[i].isFree)
            Enemy2[i].bomb.updateInfo();
        for(int j=0;j<30;j++){
            Enemy2[i].enemy2Bullet1[j].EnemyUpdatePositionLeft();
            Enemy2[i].enemy2Bullet2[j].EnemyUpdatePosition();
            Enemy2[i].enemy2Bullet3[j].EnemyUpdatePositionRight();
        }
    }
}
void Easy::paintEvent(QPaintEvent *){
    QPainter painter(this);
        //我机及其子弹动画
    painter.drawPixmap(MyPlane.x,MyPlane.y,MyPlane.myplane);
    for(int i=0;i<30;i++)
        if(!MyPlane.myBullet[i].isFree)//如果子弹不空闲，画出子弹
            painter.drawPixmap(MyPlane.myBullet[i].x,MyPlane.myBullet[i].y,MyPlane.myBullet[i].bullet);                                                                                                                                       //敌机及其子弹动画
    for(int i=0;i<10;i++){
        if(!Enemy1[i].isFree){		//敌机不空闲
            if(!Enemy1[i].isDestroyed)		//敌机未被摧毁
                painter.drawPixmap(Enemy1[i].x,Enemy1[i].y,Enemy1[i].enemy1);	//画出敌机
            else							//若敌机被摧毁
                if(!Enemy1[i].bomb.isPlayde)	//没有播放过爆炸动画
                    painter.drawPixmap(Enemy1[i].x,Enemy1[i].y,Enemy1[i].bomb.bombPix[Enemy1[i].bomb.index]);	//画出爆炸动画中的图片
        }
        for(int j=0;j<30;j++){		//敌机子弹非空闲，画出子弹
            if(!Enemy1[i].enemy1Bullet[j].isFree)
                painter.drawPixmap(Enemy1[i].enemy1Bullet[j].x,Enemy1[i].enemy1Bullet[j].y,
                                   Enemy1[i].enemy1Bullet[j].EnemyBullet);
        }
    }
    for(int i=0;i<2;i++)	//Boos与画图事件与敌机基本相同
        if(!Enemy2[i].isFree){
            if(!Enemy2[i].isDestroyed)
                painter.drawPixmap(Enemy2[i].x,Enemy2[i].y,Enemy2[i].enemy2);
            else
                if(!Enemy2[i].bomb.isPlayde)
                    painter.drawPixmap(Enemy2[i].x+50,Enemy2[i].y,Enemy2[i].bomb.bombPix[Enemy2[i].bomb.index]);
            for(int j=0;j<30;j++){
                if(!Enemy2[i].enemy2Bullet1[j].isFree)
                    painter.drawPixmap(Enemy2[i].enemy2Bullet1[j].x,Enemy2[i].enemy2Bullet1[j].y,
                                       Enemy2[i].enemy2Bullet1[j].EnemyBullet2);
            }
            for(int j=0;j<30;j++){
                if(!Enemy2[i].enemy2Bullet2[j].isFree)
                    painter.drawPixmap(Enemy2[i].enemy2Bullet2[j].x,Enemy2[i].enemy2Bullet2[j].y,
                                       Enemy2[i].enemy2Bullet2[j].EnemyBullet2);
            }
            for(int j=0;j<30;j++){
                if(!Enemy2[i].enemy2Bullet3[j].isFree)
                    painter.drawPixmap(Enemy2[i].enemy2Bullet3[j].x,Enemy2[i].enemy2Bullet3[j].y,
                                       Enemy2[i].enemy2Bullet3[j].EnemyBullet2);
            }
        }
}
void Easy::mouseMoveEvent(QMouseEvent *E){
    QPointF pos = E->position(); // 获取鼠标位置，返回QPointF
    QPoint point = pos.toPoint(); // 将QPointF转换为QPoint
    int x = point.x() - 35;
    int y = point.y() - 40;
    if(x>0&&x<415)					//飞机不能出游戏界面
        MyPlane.x = x;
    if(y>0&&y<505)
        MyPlane.y = y;
    update();
}
