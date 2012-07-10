#include "board.h"
#include <QMessageBox>

board::board(QWidget *parent)
{
    chnglen=10;
    move=10;
    isStarted=false;
    setFrameStyle(QFrame::Raised | QFrame::StyledPanel);
    setFocusPolicy(Qt::StrongFocus);
    connect(this,SIGNAL(tela2(int,int)),parent,SLOT(tela(int,int)));
    connect(this,SIGNAL(end()),parent,SLOT(end()));
}
void board::start(){
    this->setFocus();
    isStarted=true;
    isChanged=true;
    x=10;
    y=10;
    length=1;
    fase = 1;
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
    painter.drawRect(QRect(0,0,300,450));
    if(isStarted==true){

        painter.setBrush(QColor(255, 0, 0, 255));
        painter.drawEllipse(QRect(fx,fy,move,move));
        painter.setBrush(QColor(0, 255, 0, 120));
        for(int i=0;i<qvtail.size();i++)
            painter.drawRect(QRect(qvtail[i][0],qvtail[i][1],move,move));
    }
}

void board::keyPressEvent(QKeyEvent *event){
    if(isChanged==true){
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
        isChanged=false;
    }
    this->update();
}
void board::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timer.timerId()) {
        emit(tela2(fase,pontos));
        isChanged=true;
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
            QMessageBox::information(this,"PROJETO SNAKE","GAMER OVER!");
            end_game();
            return;
        }
        if(x<0)
            x=300-move;
        if(x>300-move)
            x=0;
        if(y<0)
            y=450-move;
        if(y>450-move)
            y=0;
        if(fx==x && fy==y){
            genfood();
            length++;
            pontos+=fase*10;


            // aqui é o nível
            if(length%chnglen==0){
                fase++;
                if(fase==4){
                    QMessageBox::information(this,"PROJETO SNAKE","Fim de Jogo. Parabéns!");
                    return end_game();
                }

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
    fx=(qrand()%19)*move;
    fy=(qrand()%40)*move;
}
void board::end_game(){
    int k=0;
    timer.stop();
    isStarted=false;
    k = lowesthighscore();
    //QMessageBox msgBox;


  }
bool board::check_snake(){
    for(int i=0;i<qvtail.size();i++)
        if(qvtail[i][0]==x && qvtail[i][1]==y)
            vidas=vidas-1;
            return 1;
    return 0;
}


int board::lowesthighscore(){
    QFile fl("test.dat");
    fl.open(QIODevice::ReadOnly);
    QDataStream datas(&fl);
    datas>>qvscores;
    hs=0;
    if(qvscores.size()>0)
        hs=qvscores[qvscores.size()-1][1].toInt();
    fl.close();
    return qvscores.size();
}






