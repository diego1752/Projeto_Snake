#ifndef WINDOWS_H
#define WINDOWS_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLCDNumber>
#include "board.h"
#include <QProgressBar>

class windows:public QWidget
{
    Q_OBJECT
public:
    windows(QWidget *parent=0);
    QPushButton *Inicio;
    QLabel *Fase;
    QLabel *Pontos;
    board *Tela;
    QHBoxLayout *qhb;
    QVBoxLayout *qvb;
    QLCDNumber *lcdFase;
    QLCDNumber *lcdPontos;
    QProgressBar *barra;
    int Tela1;
public slots:
    void tela(int,int);
    void end();
};

#endif // WINDOW_H
