#ifndef NDITRICASTERHANDLER_H
#define NDITRICASTERHANDLER_H

//#define DEBUG

#include <QThread>
#include <QGraphicsView>
#include <QColor>
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include "Processing.NDI.Lib.h"
#include <QImage>
#include <QRectF>

class NDITricasterHandler : public QThread
{
    Q_OBJECT
public:
    NDITricasterHandler(QGraphicsView* view, QColor pAlphaBlack, NDIlib_send_instance_t *ptricaster);
    ~NDITricasterHandler();
    void run();

signals:

public slots:
    void updatePortion(QList<QRectF> rects);
    void addAlphaRect(int x, int y, int w, int h);
    void removeAlphaRect(int x, int y, int w, int h);
    void addNoTransparencyZone(QRect r);
    void removeNoTransparencyZone(QRect r);
    void closing();

private:
    void drawTransparentRectangle();
    NDIlib_send_instance_t* tricaster;
    NDIlib_video_frame_v2_t videoFrame;
    bool done;

    QGraphicsView* screen;
    const QColor alphaBlack;
    BYTE* pixels;
    QImage view;
    QList<QRect> transparentRects;
    QList<QRect> noTransparencyZones;
#ifdef DEBUG
    int x;
#endif
};

#endif // NDITRICASTERHANDLER_H
