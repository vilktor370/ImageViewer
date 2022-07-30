#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QMainWindow>
#include <QDebug>
#include <QPixmap>
#include <QFileDialog>
#include <QImageWriter>
#include <QMessageBox>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QLabel>



// additional files
#include "imageprocessor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ImageViewer; }
QT_END_NAMESPACE

class ImageViewer : public QMainWindow
{
    Q_OBJECT

public:
    ImageViewer(QWidget *parent = nullptr);
    ~ImageViewer();

public slots:
    void doOpen();
    void doSave();
    void doExit();
    void doColor();
    void doGray();
    void doBin();

private:
    // functions
    bool loadImage(const QStringList& fileName);
    bool saveImage(const QString& fileName);
    void setImage(const QImage& img);
    void createAction();
    void createConnection();
    QImage processImage(QImage& img);



    Ui::ImageViewer *ui;
    QList<QImage*> imagesList;
    QAction* loadAct;
    QAction* exitAct;
    QAction* saveAct;

};
#endif // IMAGEVIEWER_H
