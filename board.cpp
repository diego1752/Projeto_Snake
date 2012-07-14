#include "board.h"
#include <QMessageBox>

board::board(QWidget *parent)
{
    //Tamanho da Maça e da Cobra
    chnglen=10;
    move=10;
    Iniciar=false;
    QObject::connect(this,SIGNAL(tela2(int,int,int)),parent,SLOT(tela(int,int,int)));
    QObject::connect(this,SIGNAL(end()),parent,SLOT(end()));
}

void board::start(){
    this->setFocus();

    Iniciar=true;
    Tecla=true;
    x=10;
    y=10;
    length=1;
    fase=1;
    locomocao=4;
    pontos=0;
    vidas=3;

    maca();
    this->update();
    timer.start(timeoutTime(), this);
}

void board::movex(int i){
    x=i;
    this->update();
}

void board::movey(int j){
    y=j;
    this->update();
}

void board::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setBrush(QColor(255, 255, 255, 255));
    painter.drawRect(QRect(0,0,250,180));
    if(Iniciar==true){

        painter.setBrush(QColor(255, 0, 0, 255));
        painter.drawEllipse(QRect(fx,fy,move,move));
        painter.setBrush(QColor(0, 255, 0, 120));
        for(int i=0;i<qvtail.size();i++)
            painter.drawRect(QRect(qvtail[i][0],qvtail[i][1],move,move));
    }
}

void board::keyPressEvent(QKeyEvent *event){
    if(Tecla==true){
        switch (event->key()) {
        case Qt::Key_Left:
            if(locomocao!=4)
                locomocao=1;
            break;
        case Qt::Key_Right:
            if(locomocao!=1)
                locomocao=4;
            break;
        case Qt::Key_Down:
            if(locomocao!=2)
                locomocao=3;
            break;
        case Qt::Key_Up:
            if(locomocao!=3)
                locomocao=2;
            break;
        default:
            QFrame::keyPressEvent(event);
        }
        Tecla=false;
    }
}

void board::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timer.timerId()) {
        emit(tela2(fase,pontos,vidas));
        Tecla=true;
        switch (locomocao) {

        case 1:
            x-=move;
            break;
        case 4:
            x+=move;
            break;
        case 3:
            y+=move;
            break;
        case 2:
            y-=move;
            break;
        }
        if(bate_cobra()and vidas==0){
            QMessageBox::information(this,"SNAKE","GAME OVER!");
            fim_jogo();
            return;
        }
        if(x<0)
            x=250-move;
        if(x>250-move)
            x=0;
        if(y<0)
            y=180-move;
        if(y>180-move)
            y=0;
        if(fx==x && fy==y){
            maca();
            length++;
            pontos=pontos+100;

            if(pontos==3000){
                QMessageBox::information(this,"PROJETO SNAKE","Fim de Jogo. Parabéns! Você completou os Níveis");
                return fim_jogo();
                this->update();
            }


            if(length%chnglen==1){
                fase++;

                timer.stop();
                timer.start(timeoutTime(), this);

            }

        }

        this->update();
        qvtemp.clear();
        qvtemp.push_front(y);
        qvtemp.push_front(x);
        qvtail.push_front(qvtemp);
        while(qvtail.size()>length)
            qvtail.pop_back();
    }
    else {
        QFrame::timerEvent(event);
    }
}

void board::maca(){
    fx=(qrand()%18)*move;
    fy=(qrand()%18)*move;
}

void board::fim_jogo(){
    timer.stop();
    Iniciar=false;
}

bool board::bate_cobra(){
    for(int i=0;i<qvtail.size();i++)
        if(qvtail[i][0]==x && qvtail[i][1]==y)
            vidas=vidas-1;
            return 1;
    return 0;
}

void board::vida(int v){
    vidas=v;
    this->update();
}




