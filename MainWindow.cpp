#include "MainWindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>


MainWindow::MainWindow(Scoreboard* sb, QWidget *parent)
    : QMainWindow(parent) {
    QPushButton* button = new QPushButton("Penalty");
    //setCentralWidget(&button);
    QWidget* widget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(button);
    widget->setLayout(layout);
    setCentralWidget(widget);

    connect(button, SIGNAL(clicked()), sb, SLOT(togglePenalty()));
}

MainWindow::~MainWindow() {

}
