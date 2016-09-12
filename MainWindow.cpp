#include "MainWindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QAction>
#include <QMenu>
#include <QMenuBar>

MainWindow::MainWindow(HockeyGame* game, StandingsGraphic* graphic, CommercialGraphic* comGraphic,
                       NchcScoreboardGraphic* confSbGraphic, ScheduleGraphic *scheduleGraphic, SerialConsole *serial, QWidget *parent)
    : QMainWindow(parent), panel(game, graphic, comGraphic, confSbGraphic, scheduleGraphic), standingsPanel(graphic), nchcGui(confSbGraphic),
    awayPlayerEdit(game, false), homePlayerEdit(game, true), awayEdit(game->getAwayTeam()), homeEdit(game->getHomeTeam()),
    ltCreator(game->getLt()) {
    setCentralWidget(&panel);
    //setMaximumWidth(800);
    makeMenu(game, serial, comGraphic);
    connect(&scheduleGui, SIGNAL(show(QList<ScheduleEntry>,bool)), scheduleGraphic, SLOT(receiveData(QList<ScheduleEntry>,bool)));
    connect(&scheduleGui, SIGNAL(show(QList<ScheduleEntry>,bool)), scheduleGraphic, SLOT(toggleShow()));

}

MainWindow::~MainWindow() {

}

void MainWindow::makeMenu(HockeyGame* game, SerialConsole* console, CommercialGraphic* comGraphic)
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
    connect(awayPlayerEditor, SIGNAL(triggered()), &awayPlayerEdit, SLOT(updateSpinBoxes()));
    connect(awayPlayerEditor, SIGNAL(triggered()), &awayPlayerEdit, SLOT(show()));
    awayMenu->addAction(awayPlayerEditor);
    QAction* awayTeamEdit = new QAction("Edit Team Stats", this);
    connect(awayTeamEdit, SIGNAL(triggered()), &awayEdit, SLOT(updateSpinBoxes()));
    connect(awayTeamEdit, SIGNAL(triggered()), &awayEdit, SLOT(show()));
    awayMenu->addAction(awayTeamEdit);
    QAction* toggleLogoBackground = new QAction("Black Logo Background", this);
    toggleLogoBackground->setCheckable(true);
    awayMenu->addAction(toggleLogoBackground);
    connect(toggleLogoBackground, SIGNAL(toggled(bool)), game->getSb(), SLOT(toggleAwayLogoBg(bool)));
    connect(toggleLogoBackground, SIGNAL(toggled(bool)), comGraphic, SLOT(toggleAwayLogoBg(bool)));

    QMenu* homeMenu = new QMenu(game->getHomeName());
    QAction* homePlayerEditor = new QAction("Edit Player Stats", this);
    connect(homePlayerEditor, SIGNAL(triggered()), &homePlayerEdit, SLOT(updateSpinBoxes()));
    connect(homePlayerEditor, SIGNAL(triggered()), &homePlayerEdit, SLOT(show()));
    homeMenu->addAction(homePlayerEditor);
    QAction* homeTeamEdit = new QAction("Edit Team Stats", this);
    connect(homeTeamEdit, SIGNAL(triggered()), &homeEdit, SLOT(updateSpinBoxes()));
    connect(homeTeamEdit, SIGNAL(triggered()), &homeEdit, SLOT(show()));
    homeMenu->addAction(homeTeamEdit);
    QAction* scheduleEdit = new QAction("Schedule", this);
    connect(scheduleEdit, SIGNAL(triggered(bool)), &scheduleGui, SLOT(show()));
    homeMenu->addAction(scheduleEdit);

    QMenu* lowerThirdMenu = new QMenu("Lower Third");
    QAction* customLtCreator = new QAction("Create custom Lt", this);
    connect(customLtCreator, SIGNAL(triggered()), &ltCreator, SLOT(show()));
    customLtCreator->setShortcut(Qt::CTRL + Qt::Key_1);
    lowerThirdMenu->addAction(customLtCreator);

    QMenu* consoleMenu = new QMenu("All Sport CG");
    QAction* showConsole = new QAction("Show Console", this);
    connect(showConsole, SIGNAL(triggered()), console, SLOT(show()));
    consoleMenu->addAction(showConsole);

    menuBar()->addMenu(awayMenu);
    menuBar()->addMenu(homeMenu);
    menuBar()->addMenu(lowerThirdMenu);
    menuBar()->addMenu(consoleMenu);


}
