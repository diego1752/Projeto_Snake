#include "windows.h"

windows::windows(QWidget *parent)
{
    Tela = new board(this);
    //QLCDNumber* Tela = new QLCDNumber(this);

    Inicio = new QPushButton("Iniciar",this);
    qhb = new QHBoxLayout;
    qvb = new QVBoxLayout;
    lcdFase = new QLCDNumber(this);
    lcdPontos = new QLCDNumber(this);
    lcdVidas = new QLCDNumber(this);
    Fase = new QLabel("Nivel:",this);
    Pontos = new QLabel("Pontos:",this);
    barra = new QProgressBar(this);

    this->setMaximumSize(500,300);
    this->setMinimumSize(100,500);

    Tela->setMinimumSize(350,101);
    Tela->setMaximumSize(350,500);
    Inicio->setMinimumWidth(50);
    Inicio->setMaximumWidth(100);
    lcdFase->setMinimumWidth(50);
    lcdFase->setMaximumWidth(120);
    lcdPontos->setMinimumWidth(60);
    lcdPontos->setMaximumWidth(120);
    lcdVidas->setMinimumWidth(0);
    lcdVidas->setMaximumWidth(50);
    Fase->setMinimumWidth(70);
    Fase->setMaximumWidth(120);
    Pontos->setMinimumWidth(80);
    Pontos->setMaximumWidth(120);

    barra->resize(200,25);
    //barra->setOrientation(Qt::Vertical);//Orientation can also be vertical
    barra->setRange(0,99);
    barra->setValue(0);

    qvb->addWidget(Fase);
    qvb->addWidget(lcdFase);
    qvb->addWidget(Pontos);
    qvb->addWidget(lcdPontos);
    qvb->addWidget(lcdVidas);
    qhb->addWidget(Tela);
    qhb->addLayout(qvb);
    qvb->addWidget(Inicio);
    qvb->addWidget(barra);
    QObject::connect(barra,SIGNAL(valueChanged(int)),lcdPontos,SLOT(display(int)));
    //connect(barra, SIGNAL(valueChanged(int)), this, SLOT(end()));


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
