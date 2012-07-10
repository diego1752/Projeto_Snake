#include "windows.h"

windows::windows(QWidget *parent)
{
    Tela = new board(this);
    Inicio = new QPushButton("Iniciar",this);
    qhb = new QHBoxLayout;
    qvb = new QVBoxLayout;
    lcdFase = new QLCDNumber(this);
    lcdPontos = new QLCDNumber(this);
    Fase = new QLabel("Nivel:",this);
    Pontos = new QLabel("Pontos:",this);


    this->setMaximumSize(500,300);
    this->setMinimumSize(500,100);

    Tela->setMinimumSize(201,201);
    Tela->setMaximumSize(201,201);
    Inicio->setMinimumWidth(50);
    Inicio->setMaximumWidth(100);
    lcdFase->setMinimumWidth(50);
    lcdFase->setMaximumWidth(120);
    lcdPontos->setMinimumWidth(60);
    lcdPontos->setMaximumWidth(120);
    Fase->setMinimumWidth(70);
    Fase->setMaximumWidth(120);
    Pontos->setMinimumWidth(80);
    Pontos->setMaximumWidth(120);

    qvb->addWidget(Fase);
    qvb->addWidget(lcdFase);
    qvb->addWidget(Pontos);
    qvb->addWidget(lcdPontos);
    qhb->addWidget(Tela);
    qhb->addLayout(qvb);
    qvb->addWidget(Inicio);
    this->setLayout(qhb);
    connect(Inicio,SIGNAL(clicked()),Tela,SLOT(start()));
}

void windows::tela(int i,int j){
    lcdFase->display(QString::number(i));
    lcdPontos->display(QString::number(j));
}
void windows::end(){
    this->close();
}
