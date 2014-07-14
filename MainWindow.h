#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QMainWindow>
#include "HockeyGame.h"
#include "ControlPanel.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(HockeyGame* game, QWidget *parent = 0);
    ~MainWindow();

private:
    ControlPanel panel;
};

#endif // MAINWINDOW_H
