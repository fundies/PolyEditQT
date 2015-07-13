#include "qactions.h"

QActions::QActions(QWidget *parent)
{
    QPixmap openPix("img/folder_picture.png");
    open = new QAction(openPix, "&Open", parent);

    QPixmap savePix("img/disk.png");
    save = new QAction(savePix, "&Save", parent);

    QPixmap saveAsPix("img/disk.png");
    saveAs = new QAction(saveAsPix, "&Save", parent);

    QPixmap quitPix("img/door_out.png");
    quit = new QAction(quitPix, "&Quit", parent);

    QPixmap cutPix("img/cut.png");
    cut = new QAction(cutPix, "&Cut", parent);

    QPixmap copyPix("img/copy.png");
    copy = new QAction(copyPix, "&Copy", parent);

    QPixmap pastePix("img/paste.png");
    paste = new QAction(pastePix, "&Paste", parent);

    QPixmap gridPix("img/grid.png");
    viewGrid = new QAction(gridPix, "&Grid", parent);
    viewGrid->setCheckable(true);
    viewGrid->setChecked(true);

    viewSprite = new QAction("Sprite", parent);
    viewSprite->setCheckable(true);
    viewSprite->setChecked(true);

    viewSymmetry = new QAction("Symmetry Hints", parent);
    viewSymmetry->setCheckable(true);
    viewSymmetry->setChecked(true);

    QPixmap zoomInPix("img/zoom_in.png");
    zoomIn = new QAction(zoomInPix, "&Zoom In", parent);

    QPixmap zoomOutPix("img/zoom_out.png");
    zoomOut = new QAction(zoomOutPix, "&Zoom Out", parent);

    QPixmap zoom100Pix("img/zoom.png");
    zoom100 = new QAction(zoom100Pix, "&Actual Size", parent);

    QPixmap aboutPix("img/star.png");
    about = new QAction(aboutPix, "&About", parent);

    QPixmap playPix("img/play.png");
    play = new QAction(playPix, "&Play", parent);

    QPixmap pausePix("img/pause.png");
    pause = new QAction(pausePix, "&Pause", parent);

    QPixmap stopPix("img/stoc.png");
    stop = new QAction(stopPix, "&Stop", parent);
}

