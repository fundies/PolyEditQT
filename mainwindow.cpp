#include <QLayout>
#include <QSplitter>
#include <QStatusBar>
#include <QFileDialog>
#include <QFileInfo>
#include <quazip/JlCompress.h>
#include <QMessageBox>

#include "mainwindow.h"
#include "menubar.h"
#include "toolbar.h"
#include "grid.h"
#include "utility.h"
#include "canvas.h"
#include "imageframe.h"
#include "animationframe.h"
#include "masktab.h"
#include "aboutframe.h"
#include "qactions.h"
#include "svgreader.h"
#include "table.h"

MainWindow::MainWindow(QWidget *parent) : GLWindow()
{
    Q_UNUSED(parent);

    setWindowIcon(QIcon(":/img/icon.png"));
    mCanvas = new Canvas(this);

    animationEdit = Q_NULLPTR;
    imgLoader = Q_NULLPTR;

    mViewGrid = true;
    mViewSprite = true;
    mXsep = 16;
    mYsep = 16;

    mCoord = Coordinate(0,0);
    mGrid = QSharedPointer<Grid>(new Grid(16, 16, width(), height()));

    mCentralWidget = new QWidget(this);

    setCentralWidget(mCentralWidget);

    QHBoxLayout *mainLayout = new QHBoxLayout;

    QSplitter *splitter = new QSplitter(this);

    mTabs = new MaskTab(this, mCanvas);
    table = mTabs->table();

    splitter->addWidget(mTabs);
    splitter->addWidget(mCanvas);

    mMenuBar = new MenuBar(this);
    mToolBar = new ToolBar(this);

    setMenuBar(mMenuBar);
    addToolBar(mToolBar);

    mainLayout->addWidget(splitter);

    mainLayout->setMargin(0);
    mCentralWidget->setLayout(mainLayout);

    statusBar()->setStyleSheet("QStatusBar::item { border: 0px solid black }; ");

    statusBar()->addPermanentWidget(new QLabel("PolyEditQT 1.0", this, 0), 1);
    xCoord = new QLabel("X: ", this, 0);
    yCoord = new QLabel("Y: ", this, 0);
    statusBar()->addPermanentWidget(xCoord, 0);
    statusBar()->addPermanentWidget(yCoord, 0);

    connect(mActions->aNew, &QAction::triggered,  this, &MainWindow::reset);
    connect(mActions->aOpen, &QAction::triggered,  this, &MainWindow::open);
    connect(mActions->aSave, &QAction::triggered,  this, &MainWindow::save);
    connect(mActions->aSaveAs, &QAction::triggered,  this, &MainWindow::saveAs);
    connect(mActions->aSprite, &QAction::triggered,  this, &MainWindow::editSprite);
    connect(mActions->aAnimation, &QAction::triggered,  this, &MainWindow::editAnimation);
    connect(mActions->aAbout, &QAction::triggered,  this, &MainWindow::about);
    connect(mActions->aQuit, &QAction::triggered,  this, &MainWindow::close);

    connect(mActions->aViewGrid, &QAction::toggled,  this, &MainWindow::viewGrid);
    connect(mActions->aViewSprite, &QAction::toggled,  this, &MainWindow::viewSprite);


    connect(mToolBar->gridX, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &MainWindow::setXsep);
    connect(mToolBar->gridY, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &MainWindow::setYsep);

    connect(mToolBar->speed, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, &GLWindow::setSpeed);
    connect(mToolBar->frame, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &MainWindow::setFrame);


    mSpr = new Sprite();
}

void MainWindow::render()
{

    if (!mSpr->isNull() && mViewSprite)
    {
        std::function<void()> s;
        s = [this] { mSpr->render(subImg); };
        mCanvas->draw(s, mCanvas->width()/2, mCanvas->height()/2);
    }

    /// TODO: Move this
    int xOff = fmod(((zoom*mGrid->getXoffset()) + mCanvas->width()/2),(zoom*mGrid->getXsep()));
    int yOff = fmod(((zoom*mGrid->getYoffset()) + mCanvas->height()/2),(zoom*mGrid->getYsep()));

    int x = xOff + RoundNum((double)mCanvas->mousePos.x()-xOff, (zoom*mGrid->getXsep()));
    int y = yOff + RoundNum((double)mCanvas->mousePos.y()-yOff, (zoom*mGrid->getYsep()));

    Coordinate coord = mapToGrid(Coordinate(x,y));

    if (mViewGrid)
    {
        std::function<void(void)> g = std::bind(&Grid::render, mGrid);
        mCanvas->draw(g, 0,0);
    }

    for (auto i : *table)
    {
        i->scale(zoom);

        std::function<void()> f;

        if (i->getType() == PolyEdit::Polygon)
            f = [i] { i->render(); };
        else
            f = [i, coord] { i->render(coord); };

        mCanvas->draw(f, mCanvas->width()/2, mCanvas->height()/2);

    }

    setStatusCoord(mapToGrid(Coordinate(x,y)));
    std::function<void(void)> c = std::bind(drawCircle, Coordinate(x,y), 5, 30, false);
    mCanvas->draw(c, 0, 0);
}

void MainWindow::canvasResized(int w, int h)
{
    mGrid->setSize(0, 0, mXsep, mYsep, w, h, zoom);
}

const Coordinate MainWindow::mapToGrid(Coordinate c)
{
    int x = (c.x() - mCanvas->width()/2 - mGrid->getXoffset())/zoom;
    int y = (mCanvas->height()/2 + mGrid->getYoffset() - c.y())/zoom;

    return Coordinate(x,y);
}

const Coordinate MainWindow::mapToReal(Coordinate c)
{
    int x = mCanvas->width()/2 + (c.x() + mGrid->getXoffset())*zoom;
    int y = mCanvas->height()/2 + (mGrid->getYoffset() - c.y())*zoom;

    return Coordinate(x,y);
}

void MainWindow::setSprite(const SpritePtr &spr)
{
    mSpr = spr;

    mToolBar->frame->setMaximum(std::max(0, static_cast<int>(spr->count()-1)));

    if (animationEdit == Q_NULLPTR)
        animationEdit = new AnimationFrame(this);

    //if (imgLoader != Q_NULLPTR)
    //  imgLoader->setSpr(spr);
}


void MainWindow::setStatusCoord(Coordinate c)
{
    xCoord->setText("X: " + QString::number(c.rx()));
    yCoord->setText("Y: " + QString::number(c.ry()));

    mCoord = c;
}

const Coordinate MainWindow::getStatusCoord() const
{
    return mCoord;
}

void MainWindow::addCoord(Coordinate c)
{
    currentMask->addCoord(c);
}

void MainWindow::setMask(Table *mask)
{
    currentMask = mask;
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                       tr("Open Image"), QString(), tr("Image Files (*.png *.jpg *.bmp *.svg *.spr)"), 0, QFileDialog::DontUseNativeDialog);

    QFileInfo f(fileName);
    if(f.suffix() == "svg")
        openSVG(fileName);
    else if(f.suffix() == "spr")
        openSpr(fileName);
    else
        openImage(fileName);

}

void MainWindow::addMask(SVG &svg)
{
    Table *t = new Table(this, mCanvas);
    t->setMaskType(svg.getType());

    if (mTabs->currentTable()->size() > 0)
        mTabs->addTab(t);
    else
        mTabs->replaceCurrentTable(t);

    for (auto c : svg.getCoords())
        t->addCoord(c);

    if(svg.getType() == PolyEdit::Circle)
        t->setRadius(svg.getRadius());

    if(svg.getType() == PolyEdit::Box)
        t->setBoxSize(svg.getWidth(), svg.getHeight());

    setMask(t);

}

void MainWindow::openSVG(QString fpath)
{
    SVGReader reader(fpath);
    SVG svg = reader.read();
    addMask(svg);
}

void MainWindow::openImage(QString fpath)
{
    QImage img;
    if (!fpath.isEmpty())
        img = QImage(fpath);

    if (!img.isNull() && imgLoader == Q_NULLPTR)
        delete imgLoader;

    if (!img.isNull())
    {
        QFileInfo f(fpath);
        imgLoader = new ImageFrame(this, img);
        imgLoader->setWindowTitle(f.fileName());
        imgLoader->show();
    }
}

void MainWindow::openImage(QString fpath, int rows, int columns)
{
    QImage img(fpath);

    QFileInfo f(fpath);
    imgLoader = new ImageFrame(this, img);
    imgLoader->setWindowTitle(f.fileName());

    Sprite *spr = new Sprite(img);
    spr->genSubimg(rows, columns, 0, 0);
    setSprite(spr);
}

void MainWindow::save()
{
    if (saveFile.isEmpty())
    {
        saveFile = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                "untitled.spr",
                                                tr("Sprite (*.spr)"),  0, QFileDialog::DontUseNativeDialog);
    }

    QString workDir = QDir::temp().path() + "/" + random_string(5) + "/";
    QDir dir(workDir);
    dir.mkdir(workDir);

    if (!mSpr->isNull())
    {
        mSpr->exportStrip(workDir + "image.png");

        QFile data(workDir + "image.xml");
        if (data.open(QFile::WriteOnly | QFile::Truncate))
        {
            QXmlStreamWriter stream(&data);
            stream.setAutoFormatting(true);
            stream.writeStartDocument();
            stream.writeStartElement("image");
            stream.writeAttribute("fileName", "image.png");
            stream.writeAttribute("rows", QString::number(mSpr->rows()));
            stream.writeAttribute("columns", QString::number(mSpr->columns()));
            stream.writeEndElement(); // image
            stream.writeEndDocument();
        }
    }


    if (table->size() > 0)
    {
        int m = 0;
        for (auto i : *table)
        {
            QString f = workDir + QString::number(m) + ".svg";
            i->exportSVG(f);
            m++;
        }
    }

    JlCompress::compressDir(saveFile, workDir);

    dir.removeRecursively();
}

void MainWindow::saveAs()
{
    QString temp = QFileDialog::getSaveFileName(this, tr("Save File"),
                   "untitled.spr",
                   tr("Sprite (*.spr)"),  0, QFileDialog::DontUseNativeDialog);
    if (!temp.isEmpty())
    {
        saveFile = temp;
        save();
    }
}

void MainWindow::openSpr(QString fpath)
{
    reset();
    QString workDir = QDir::temp().path() + "/" + random_string(5) + "/";
    QDir dir(workDir);
    dir.mkdir(workDir);

    QStringList files = JlCompress::getFileList(fpath);
    JlCompress::extractDir(fpath, workDir);

    for (auto f : files)
    {
        QFileInfo file(workDir + f);
        if (file.suffix() == "svg")
            openSVG(file.absoluteFilePath());

        if (file.suffix() == "xml")
        {
            QXmlStreamReader xml;
            QFile xmlFile(file.absoluteFilePath());
            xmlFile.open(QIODevice::ReadOnly);
            xml.setDevice(&xmlFile);
            xml.readNextStartElement();

            QString image;
            int rows;
            int columns;
            bool ok;

            for(auto a: xml.attributes())
            {
                if (a.name() == "fileName")
                    image = a.value().toString();

                if (a.name() == "rows")
                    rows = a.value().toInt(&ok, 10);

                if (a.name() == "columns")
                    columns = a.value().toInt(&ok, 10);
            }

            openImage(workDir + image, rows, columns);
        }
    }
}

void MainWindow::editSprite()
{
    if (imgLoader != Q_NULLPTR)
        delete imgLoader;

    if (!mSpr->isNull())
    {
        QImage img = mSpr->generateStrip();
        imgLoader = new ImageFrame(this, img);
        imgLoader->show();
    }
    else
        open();
}

void MainWindow::editAnimation()
{
    if (animationEdit == Q_NULLPTR)
        animationEdit = new AnimationFrame(this);

    animationEdit->setSprite(mSpr);
    animationEdit->show();
}

void MainWindow::viewGrid(bool value)
{
    mViewGrid = value;
}

void MainWindow::viewSprite(bool value)
{
    mViewSprite = value;
}

void MainWindow::updateGrid()
{
    mGrid->setSize(0, 0, mXsep, mYsep, mCanvas->width(), mCanvas->height(), zoom);
}

void MainWindow::setXsep(int value)
{
    mXsep = value;
    updateGrid();
}

void MainWindow::setYsep(int value)
{
    mYsep = value;
    updateGrid();
}

void MainWindow::setZoom(double factor)
{
    GLWindow::setZoom(factor);
    updateGrid();
}

void MainWindow::reset()
{
    delete mSpr;
    setSprite(new Sprite());
    table->clear();
    mTabs->clear();
}

void MainWindow::about()
{
    new AboutFrame(this);
}

void MainWindow::pause()
{
    GLWindow::pause();
    mToolBar->frame->setValue(subImg);
}

void MainWindow::stop()
{
    GLWindow::stop();
    mToolBar->frame->setValue(0);
}

void MainWindow::setFrame(int frame)
{
    subImg = frame;
}
