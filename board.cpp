#include "board.h"

board::board(QWidget *parent)
{
    move=10;
    iniciado=false;

    connect(this,SIGNAL(tela2(int,int)),parent,SLOT(tela(int,int)));
    connect(this,SIGNAL(end()),parent,SLOT(end()));
}
void board::start(){
    this->setFocus();
    iniciado=true;
    emMov=true;
    x=10;
    y=10;
    this->update();

}

void board::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setBrush(QColor(255, 255, 255, 255));
    painter.drawRect(QRect(0,0,200,200));
    if(iniciado==true){

        painter.setBrush(QColor(255, 0, 0, 255));
        painter.drawRect(QRect(fx,fy,move,move));

   }
}



