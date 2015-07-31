#include "qactions.h"

QActions::QActions(QWidget *parent)
{
    QPixmap openPix(":/img/folder_picture.png");
    aOpen = new QAction(openPix, "&Open", parent);

    QPixmap savePix(":/img/disk.png");
    aSave = new QAction(savePix, "&Save", parent);

    QPixmap saveAsPix(":/img/disk_multiple.png");
    aSaveAs = new QAction(saveAsPix, "&Save", parent);

    QPixmap quitPix(":/img/door_out.png");
    aQuit = new QAction(quitPix, "&Quit", parent);

    QPixmap cutPix(":/img/cut_red.png");
    aCut = new QAction(cutPix, "&Cut", parent);

    QPixmap copyPix(":/img/page_white_copy.png");
    aCopy = new QAction(copyPix, "&Copy", parent);

    QPixmap pastePix(":/img/paste_plain.png");
    aPaste = new QAction(pastePix, "&Paste", parent);

    aSprite = new QAction("Sprite", parent);
    aAnimation = new QAction("Animation", parent);

    QPixmap gridPix(":/img/grid_rectangular.png");
    aViewGrid = new QAction(gridPix, "&Grid", parent);
    aViewGrid->setCheckable(true);
    aViewGrid->setChecked(true);

    aViewSprite = new QAction("Sprite", parent);
    aViewSprite->setCheckable(true);
    aViewSprite->setChecked(true);

    aViewSymmetry = new QAction("Symmetry Hints", parent);
    aViewSymmetry->setCheckable(true);
    aViewSymmetry->setChecked(true);

    QPixmap zoomInPix(":/img/zoom_in.png");
    aZoomIn = new QAction(zoomInPix, "&Zoom In", parent);

    QPixmap zoomOutPix(":/img/zoom_out.png");
    aZoomOut = new QAction(zoomOutPix, "&Zoom Out", parent);

    QPixmap zoom100Pix(":/img/zoom.png");
    aZoom100 = new QAction(zoom100Pix, "&Actual Size", parent);

    QPixmap aboutPix(":/img/star.png");
    aAbout = new QAction(aboutPix, "&About", parent);

    QPixmap playPix(":/img/control_play.png");
    aPlay = new QAction(playPix, "&Play", parent);

    QPixmap pausePix(":/img/control_pause.png");
    aPause = new QAction(pausePix, "&Pause", parent);

    QPixmap stopPix(":/img/control_stop.png");
    aStop = new QAction(stopPix, "&Stop", parent);
}

