#include "windows.h"

windows::windows(QWidget *parent)
{

        Tela = new board(this);
        Inicio = new QPushButton("Iniciar",this);
        qhb = new QHBoxLayout;
        qvb = new QVBoxLayout;
        lcdFase = new QLCDNumber(this);
        lcdPontos = new QLCDNumber(this);
        lcdVidas = new QLCDNumber(this);
        Fase = new QLabel("Nível",this);
        Pontos = new QLabel("Pontos",this);
        Vidas = new QLabel("Vidas",this);
        barra = new QProgressBar(this);

        this->setMaximumSize(500,300);
        this->setMinimumSize(280,320);

        Tela->setGeometry(QRect(0, 50, 256, 161));
        Tela->setMinimumSize(QSize(46, 0));

        Inicio->setGeometry(QRect(10, 260, 75, 23));
        Pontos->setGeometry(QRect(100, 200, 46, 13));
        Pontos->setMinimumSize(QSize(46, 0));
        Fase->setGeometry(QRect(20, 200, 46, 13));
        Fase->setMinimumSize(QSize(46, 0));
        Vidas->setGeometry(QRect(180, 200, 46, 13));
        Vidas->setMinimumSize(QSize(46, 0));
        lcdFase->setGeometry(QRect(10, 220, 64, 31));
        lcdFase->setMinimumSize(QSize(64, 0));
        barra->setGeometry(QRect(10, 200, 251, 23));
        lcdVidas->setGeometry(QRect(180, 220, 64, 31));
        lcdVidas->setMinimumSize(QSize(64, 0));
        lcdPontos->setGeometry(QRect(90, 220, 64, 31));
        lcdPontos->setMinimumSize(QSize(64, 0));

        qvb->addWidget(Tela);
        qvb->addWidget(barra);
        qvb->addWidget(Inicio);


        qhb->addLayout(qvb);
        this->setLayout(qhb);

        QObject::connect(barra, SIGNAL(valueChanged(int)), lcdPontos, SLOT(display(int)));
        QObject::connect(Inicio,SIGNAL(clicked()),Tela,SLOT(start()));

}

void windows::tela(int i,int j,int v){
    lcdFase->display(QString::number(i));
    lcdPontos->display(QString::number(j));
    lcdVidas->display(QString::number(v));

    if (i==1){
        barra->setValue(j/10);
    }
    if (j==1000){
        barra->setValue(0);
    }
    if (i==2){
        barra->setValue((j-1000)/10);
    }
    if (j==2000){
        barra->setValue(0);
    }
    if (i==3){
        barra->setValue(((j-2000)/10));
    }

}

void windows::end(){
    this->close();
}
