#include "imageviewer.h"
#include "./ui_imageviewer.h"

ImageViewer::ImageViewer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ImageViewer)
{
    ui->setupUi(this);

    createAction();
    createConnection();
}

ImageViewer::~ImageViewer()
{
    delete ui;
}

bool ImageViewer::loadImage(const QStringList& fileList)
{
    for(size_t i=0;i<fileList.size();i++){
        QImage *img = new QImage();
        bool isSuccess = img->load(fileList[i]);

        if (!isSuccess){
            QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                     tr("Cannot open %1").arg(QDir::toNativeSeparators(fileList[i])));
            return false;
        }// end if
        imagesList.append(img);
        QImage scaledImg = processImage(*img);
        setImage(scaledImg);
    }// end for

    return true;

}// end loadImage

bool ImageViewer::saveImage(const QString &fileName)
{
    QImageWriter writer(fileName);
    if(!writer.write(*imagesList[0])){
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot write %1: %2").arg(QDir::toNativeSeparators(fileName), writer.errorString()));
        return false;
    }
    const QString successMessage = tr("Image: %1 saved to disk.").arg(QDir::toNativeSeparators(fileName));
    statusBar()->showMessage(successMessage);
    return true;
}

void ImageViewer::setImage(const QImage& img)
{

    QLabel *imageLabel = new QLabel();
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setPixmap(QPixmap::fromImage(img));

    ui->gridLayout->addWidget(imageLabel);

}

void ImageViewer::createAction()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    loadAct=fileMenu->addAction(tr("&Load"), this, &ImageViewer::doOpen);
    loadAct->setShortcuts(QKeySequence::Open);

    saveAct = fileMenu->addAction(tr("&Save"), this, &ImageViewer::doSave);
    saveAct->setShortcuts(QKeySequence::Save);
    exitAct = fileMenu->addAction(tr("&Exit"), this, &ImageViewer::doExit);
    exitAct->setShortcuts(QKeySequence::Cancel);



}

void ImageViewer::createConnection()
{
    connect(ui->colorBtn, &QRadioButton::toggled, this, &ImageViewer::doColor);
    connect(ui->grayBtn, &QRadioButton::toggled, this, &ImageViewer::doGray);
    connect(ui->binBtn, &QRadioButton::toggled, this, &ImageViewer::doBin);
}

QImage ImageViewer::processImage(QImage& img)
{
    QImage scaledImg = img.scaled(640, 480);
    return scaledImg;
}

void ImageViewer::doOpen()
{
    QFileDialog dialog(this, tr("Open File"));
    dialog.setNameFilter(tr("Images (*.png *.xpm *.jpg *jpeg)"));

    while (dialog.exec() == QDialog::Accepted && !loadImage(dialog.selectedFiles())) {}

}

void ImageViewer::doExit()
{
    QApplication::quit();
}

void ImageViewer::doColor()
{
    qDebug()<<"color img ";
}

void ImageViewer::doGray()
{
    qDebug() <<"WTF!!";
    for(size_t i =0;i<imagesList.size();i++){
        QImage gray = imagesList[i]->convertToFormat(QImage::Format_Grayscale8);
        setImage(gray);
    }

}

void ImageViewer::doBin()
{
    qDebug()<<"bin img ";
}

void ImageViewer::doSave()
{
    QFileDialog dialog(this, tr("Open File"));

    while (dialog.exec() == QDialog::Accepted && !saveImage(dialog.selectedFiles().first())) {}
}

