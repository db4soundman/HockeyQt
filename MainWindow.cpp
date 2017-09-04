#include "MainWindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QFile>
#include <QTextStream>
#include <QStringList>

MainWindow::MainWindow(HockeyGame* game, StandingsGraphic* graphic, CommercialGraphic* comGraphic,
                       NchcScoreboardGraphic* confSbGraphic, ScheduleGraphic *scheduleGraphic,
                       SerialConsole *serial, ComparisonGraphic *comparisonGraphic, QWidget *parent)

    : QMainWindow(parent), panel(game, graphic, comGraphic, confSbGraphic, scheduleGraphic, comparisonGraphic), standingsPanel(graphic), nchcGui(confSbGraphic),
      awayPlayerEdit(game, false), homePlayerEdit(game, true), awayEdit(game->getAwayTeam()), homeEdit(game->getHomeTeam()),
      ltCreator(game->getLt()), compCreator(game), customLts(game->getLt(), game->getPreviewLt()),
      homePops(game,true), awayPops(game, false), homeLts(game, true),awayLts(game,false),
      sogUi(game), faceoffUi(game), customCompUi(game), clockControls(game, comGraphic, true),
      displayControls(game,graphic,comGraphic,confSbGraphic,scheduleGraphic,comparisonGraphic),
      goalies(game), ppCompUi(game), gameStateUi(game)

{
    createAlternateContent();
    mainContent.addWidget(&panel);
    setCentralWidget(&alternateContent);
    connectWithCG(serial);

    makeMenu(game, serial, comGraphic);
    connect(&scheduleGui, SIGNAL(show(QList<ScheduleEntry>,bool)), scheduleGraphic, SLOT(receiveData(QList<ScheduleEntry>,bool)));
    connect(&scheduleGui, SIGNAL(show(QList<ScheduleEntry>,bool)), scheduleGraphic, SLOT(toggleShow()));
    connect(&treeView, SIGNAL(clicked(QModelIndex)), this, SLOT(changeScreen(QModelIndex)));

    QStringList headers;
    headers << "Graphic";
    QFile file(":/resources/graphicsTree.txt");
    file.open(QIODevice::ReadOnly);
    model = new TreeModel(headers, file.readAll());
    file.close();
    treeView.setModel(model);
    treeView.setAlternatingRowColors(true);
    treeView.setHeaderHidden(true);
    treeView.setAnimated(true);
    leftDock.setWindowTitle("Graphic Selector");
    leftDock.setFeatures(0);
    leftDock.setWidget(&treeView);
    addDockWidget(Qt::LeftDockWidgetArea, &leftDock);

    rightDock.setFeatures(0);
    rightDock.setWidget(&clockControls);
    addDockWidget(Qt::RightDockWidgetArea, &rightDock);

    topDock.setFeatures(0);
    topDock.setWidget(&displayControls);
    addDockWidget(Qt::TopDockWidgetArea, &topDock);


    //treeView.setEnabled(false);

}

MainWindow::~MainWindow() {

}

void MainWindow::connectWithCG(SerialConsole *con)
{
    connect(con, SIGNAL(dataReceived(QByteArray)), &gameStateUi, SLOT(updateData(QByteArray)));
}

void MainWindow::connectWithSerialSimulator(CGSimulator *console)
{
    connect(console, SIGNAL(dataReceived(QByteArray)), &gameStateUi, SLOT(updateData(QByteArray)));
}

void MainWindow::changeScreen(QModelIndex index)
{
    if (modelMap.contains(model->data(index, Qt::DisplayRole).toString()))
        alternateContent.setCurrentIndex(modelMap[model->data(index, Qt::DisplayRole).toString()]);
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

    QAction* customCompCreator = new QAction("Create Comparison", this);
    connect(customCompCreator, SIGNAL(triggered()), &compCreator, SLOT(show()));
    lowerThirdMenu->addAction(customCompCreator);

    QMenu* consoleMenu = new QMenu("All Sport CG");
    QAction* showConsole = new QAction("Show Console", this);
    connect(showConsole, SIGNAL(triggered()), console, SLOT(show()));
    consoleMenu->addAction(showConsole);

    menuBar()->addMenu(awayMenu);
    menuBar()->addMenu(homeMenu);
    menuBar()->addMenu(lowerThirdMenu);
    menuBar()->addMenu(consoleMenu);


}

void MainWindow::createAlternateContent()
{
    alternateContent.addWidget(&gameStateUi);
    alternateContent.addWidget(&awayPops);
    alternateContent.addWidget(&homePops);
    alternateContent.addWidget(&awayLts);
    alternateContent.addWidget(&homeLts);
    alternateContent.addWidget(&customLts);
    alternateContent.addWidget(&faceoffUi);
    alternateContent.addWidget(&sogUi);
    alternateContent.addWidget(&ppCompUi);
    alternateContent.addWidget(&customCompUi);
    alternateContent.addWidget(&nchcGui);
    alternateContent.addWidget(&standingsPanel);
    alternateContent.addWidget(&scheduleGui);


    int x = 0;
    modelMap.insert("Game State", x++);
    modelMap.insert("Away Pops", x++);
    modelMap.insert("Home Pops", x++);
    modelMap.insert("Away LTs", x++);
    modelMap.insert("Home LTs", x++);
    modelMap.insert("Custom LTs", x++);
    modelMap.insert("Faceoff", x++);
    modelMap.insert("Shots On Goal", x++);
    modelMap.insert("Power play", x++);
    modelMap.insert("Custom", x++);
    modelMap.insert("NCHC Scoreboard", x++);
    modelMap.insert("NCHC Standings", x++);
    modelMap.insert("Upcoming Schedule", x++);

}
