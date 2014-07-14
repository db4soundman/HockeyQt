#include "MainWindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>


MainWindow::MainWindow(HockeyGame* game, QWidget *parent)
    : QMainWindow(parent), panel(game) {
    setCentralWidget(&panel);
    setMaximumWidth(800);
}

MainWindow::~MainWindow() {

}
