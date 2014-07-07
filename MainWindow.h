#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QMainWindow>
#include "Scoreboard.h"
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(Scoreboard* sb, QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
