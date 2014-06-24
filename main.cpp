#include "MainWindow.h"
#include <QApplication>
#include <QGraphicsScene>
#include "Scoreboard.h"
#include <QGraphicsView>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    Scoreboard* sb = new Scoreboard();
    QGraphicsScene* scene = new QGraphicsScene();
    scene->addItem(sb);
//    QGraphicsRectItem* rect = scene.addRect(QRectF(0,100,90,100));
//    scene.addText("Hellow World!");

    QGraphicsView view(scene);
    view.showFullScreen();
    //sb->setScale(1.68);
   // sb->setPos(view.mapToScene(view.width()/2, -200));
    sb->setY(-700);

    //view.show();

    return a.exec();
}
