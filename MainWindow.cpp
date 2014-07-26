#include "MainWindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QAction>
#include <QMenu>
#include <QMenuBar>

MainWindow::MainWindow(HockeyGame* game, StandingsGraphic* graphic, CommercialGraphic* comGraphic, NchcScoreboardGraphic* confSbGraphic, QWidget *parent)
    : QMainWindow(parent), panel(game, graphic, comGraphic), standingsPanel(graphic), nchcGui(confSbGraphic) {
    setCentralWidget(&panel);
    setMaximumWidth(800);

    QMenu* nchcMenu = new QMenu("NCHC");
    QAction* standings = new QAction(QIcon(QPixmap(":/images/NCHCmenu.png")), "Edit Standings", NULL);
    nchcMenu->addAction(standings);
    connect(standings, SIGNAL(triggered()), &standingsPanel, SLOT(show()));
    QAction* confSb = new QAction(QIcon(QPixmap(":/images/NCHCmenu.png")), "NCHC Scoreboard", NULL);
    connect(confSb, SIGNAL(triggered()), &nchcGui, SLOT(show()));
    nchcMenu->addAction(confSb);
    menuBar()->addMenu(nchcMenu);
}

MainWindow::~MainWindow() {

}

void MainWindow::makeMenu()
{



}
