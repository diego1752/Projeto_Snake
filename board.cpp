#include "board.h"
#include <QMessageBox>

board::board(QWidget *parent)
{
    //Tamanho da Ma�a e da Cobra
    chnglen=10;
    move=10;
    Iniciar=false;
    QObject::connect(this,SIGNAL(tela2(int,int,int)),parent,SLOT(tela(int,int,int)));
    QObject::connect(this,SIGNAL(end()),parent,SLOT(end()));
}

void board::start(){
    this->setFocus();

    Iniciar=true;
    Altera=true;
    x=10;
    y=10;
    length=1;
    fase=1;
    locomocao=4;
    pontos=0;
    vidas=3;

    genfood();
    this->update();
    timer.start(timeoutTime(), this);
}

void board::movex(int i){
    x=i;
    this->update();
}

void board::movey(int j){
    y=-j;
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
    if(Altera==true){
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
        Altera=false;
    }
    this->update();
}

void board::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timer.timerId()) {
        emit(tela2(fase,pontos,vidas));
        Altera=true;
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
        if(check_snake()and vidas==0){
            QMessageBox::information(this,"SNAKE","GAME OVER!");
            end_game();
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
            genfood();
            length++;
            pontos=pontos+100;

            if(pontos==3000){
                QMessageBox::information(this,"PROJETO SNAKE","Fim de Jogo. Parab�ns! Voc� completou os N�veis");
                return end_game();
            }

            // aqui � o n�vel
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

void board::genfood(){
    fx=(qrand()%18)*move;
    fy=(qrand()%18)*move;
}

void board::end_game(){
    timer.stop();
    Iniciar=false;
}

bool board::check_snake(){
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




