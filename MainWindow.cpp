#include "MainWindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QAction>
#include <QMenu>
#include <QMenuBar>

MainWindow::MainWindow(HockeyGame* game, StandingsGraphic* graphic, CommercialGraphic* comGraphic, NchcScoreboardGraphic* confSbGraphic, QWidget *parent)
    : QMainWindow(parent), panel(game, graphic, comGraphic), standingsPanel(graphic), nchcGui(confSbGraphic),
    awayPlayerEdit(game, false), homePlayerEdit(game, true) {
    setCentralWidget(&panel);
    setMaximumWidth(800);
    makeMenu(game);

}

MainWindow::~MainWindow() {

}

void MainWindow::makeMenu(HockeyGame* game)
{
    QMenu* nchcMenu = new QMenu("NCHC");
    QAction* standings = new QAction(QIcon(QPixmap(":/images/NCHCmenu.png")), "Edit Standings", NULL);
    nchcMenu->addAction(standings);
    connect(standings, SIGNAL(triggered()), &standingsPanel, SLOT(show()));
    QAction* confSb = new QAction(QIcon(QPixmap(":/images/NCHCmenu.png")), "NCHC Scoreboard", NULL);
    connect(confSb, SIGNAL(triggered()), &nchcGui, SLOT(show()));
    nchcMenu->addAction(confSb);
    menuBar()->addMenu(nchcMenu);

    QMenu* awayMenu = new QMenu(game->getAwayName());
    QAction* awayPlayerEditor = new QAction("Edit Player Stats", this);
    connect(awayPlayerEditor, SIGNAL(triggered()), &awayPlayerEdit, SLOT(show()));
    awayMenu->addAction(awayPlayerEditor);

    QMenu* homeMenu = new QMenu(game->getHomeName());
    QAction* homePlayerEditor = new QAction("Edit Player Stats", this);
    connect(homePlayerEditor, SIGNAL(triggered()), &homePlayerEdit, SLOT(show()));
    homeMenu->addAction(homePlayerEditor);

    menuBar()->addMenu(awayMenu);
    menuBar()->addMenu(homeMenu);


}
