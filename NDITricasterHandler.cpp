#include "NDITricasterHandler.h"
#include "Processing.NDI.Lib.h"
//#include "AirSend_api.h"
#include <QHostAddress>
#include <QMessageBox>
#ifdef DEBUG
#include <QImage>
#endif

NDITricasterHandler::NDITricasterHandler(QGraphicsView *view, QColor pAlphaBlack, NDIlib_send_instance_t* ptricaster) :
    alphaBlack(pAlphaBlack)
{
    screen = view;
    done = false;
    tricaster = ptricaster;

    pixels = new BYTE[1920*1080*4];
    for (int i = 0; i < 1920*1080*4 - 1; i+=4) {
        ::memset(&pixels[i], 0, 1);
        ::memset(&pixels[i + 1], 0, 1);
        ::memset(&pixels[i + 2], 0, 1);
        ::memset(&pixels[i + 3], 0, 1);
    }
    videoFrame.xres = 1920;
    videoFrame.yres = 1080;
    videoFrame.FourCC = NDIlib_FourCC_type_BGRA;
    videoFrame.frame_rate_N = 30000;
    videoFrame.frame_rate_D = 1001;
    videoFrame.picture_aspect_ratio = 16.0f/9.0f;
    videoFrame.frame_format_type = NDIlib_frame_format_type_progressive;
    videoFrame.timecode = 0;
    videoFrame.p_data = pixels;
    videoFrame.line_stride_in_bytes = 1920*4;
#ifdef DEBUG
    x=0;
#endif
}
NDITricasterHandler::~NDITricasterHandler() {
//    AirSend_Destroy(tricaster);
}


void NDITricasterHandler::updatePortion(QList<QRectF> rects)
{
    QPixmap img = QPixmap::grabWidget(screen);
    view = img.toImage();
    bool redrawAlpha = false;
    bool ignoreAlpha = false;
    for (int i = 0; i < rects.size(); i++) {
        int x = rects.at(i).x();
        int y = rects.at(i).y();
        int w = rects.at(i).width();
        int h = rects.at(i).height();
        int endX = x + w;
        for (int j = x; j < endX && j < 1920; j++) {
            int endY = y + h;
            for (int k = y; k < endY && k < 1080; k++) {
                QColor pixel = view.pixel(j, k);
                ignoreAlpha = false;
                // Does the graphic actually want to be keyed out?
                for (QRect r: qAsConst(noTransparencyZones)) {
                    if (r.contains(j, k)) {
                        ignoreAlpha = true;
                        break;
                    }
                }
                int arrIndex = (k * 1920 + j) * 4;
                ::memset(&pixels[arrIndex], pixel.blue(), 1);
                ::memset(&pixels[arrIndex+1], pixel.green(), 1);
                ::memset(&pixels[arrIndex+2], pixel.red(), 1);
                ::memset(&pixels[arrIndex+3], pixel == alphaBlack  && !ignoreAlpha ? 0 : 255, 1);
            }
        }
        for (int r = 0; r < transparentRects.size() && !redrawAlpha; r++) {
            if (rects.at(i).contains(transparentRects.at(r)))
                redrawAlpha = true;
        }
    }
    if (redrawAlpha)
        drawTransparentRectangle();
    start();
}

void NDITricasterHandler::addAlphaRect(int x, int y, int w, int h)
{
    QRect r(x,y,w,h);
    if (!transparentRects.contains(r))
        transparentRects.append(r);
}

void NDITricasterHandler::removeAlphaRect(int x, int y, int w, int h)
{
    transparentRects.removeAll(QRect(x,y,w,h));
}

void NDITricasterHandler::addNoTransparencyZone(QRect r)
{
    if (!noTransparencyZones.contains(r)) {
        noTransparencyZones.append(r);
    }
}

void NDITricasterHandler::removeNoTransparencyZone(QRect r)
{
    noTransparencyZones.removeAll(r);
}

void NDITricasterHandler::closing()
{
    done = true;
}

void NDITricasterHandler::drawTransparentRectangle()
{
    for (int i = 0; i < transparentRects.size(); i++) {
        int x = transparentRects.at(i).x();
        int y = transparentRects.at(i).y();
        int w = transparentRects.at(i).width();
        int h = transparentRects.at(i).height();
        int endX = x + w;
        for (int j = x; j < endX && j < 1920; j++) {
            int endY = y + h;
            for (int k = y; k < endY && k < 1080; k++) {
                QColor pixel = view.pixel(j, k);
                int arrIndex = (k * 1920 + j) * 4;
                ::memset(&pixels[arrIndex], pixel == alphaBlack ? 1 : pixel.blue(), 1);
                ::memset(&pixels[arrIndex+1],pixel == alphaBlack ? 1 : pixel.green(), 1);
                ::memset(&pixels[arrIndex+2], pixel == alphaBlack ? 1 : pixel.red(), 1);
                ::memset(&pixels[arrIndex+3], pixel == alphaBlack ? 128 : 255, 1);
            }
        }
    }
}

void NDITricasterHandler::run()
{    
    while(!done) {
        NDIlib_send_send_video_async_v2(*tricaster, &videoFrame);
    }
#ifdef DEBUG
    QImage img(1920,1080, QImage::Format_ARGB32);
    for(int i = 0; i < 1920; i++) {
        for(int j = 0; j < 1080; j++) {
            int arrIndex = (j * 1920 + i) * 4;
            QColor pixel(pixels[arrIndex + 2],pixels[arrIndex + 1], pixels[arrIndex + 0], pixels[arrIndex + 3]);
            img.setPixelColor(i,j,pixel);
        }
    }
    img.save("test" + QString::number(x) + ".png");
    x++;
#endif
}
