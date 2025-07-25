// mainwindow.cpp
#include "mainwindow.h"
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QScrollArea>
#include <QWheelEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), scaleFactor(1.0)
{
    setWindowFlags(Qt::FramelessWindowHint);

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    openButton = new QPushButton("打开图片");
    imageLabel = new QLabel;
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    scrollArea->setVisible(false);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->addWidget(openButton);
    mainLayout->addWidget(scrollArea);

    connect(openButton, &QPushButton::clicked, this, &MainWindow::openImage);

    resize(800, 600);
    setWindowTitle("刑侦现场还原系统 V2.0 - 图片查看");
}

MainWindow::~MainWindow()
{
}

void MainWindow::openImage()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "选择一张图片",
                                                    QDir::homePath(),
                                                    "图片文件 (*.png *.jpg *.jpeg *.bmp)");
    if (!fileName.isEmpty()) {
        originalPixmap.load(fileName);
        if (originalPixmap.isNull()) {
            imageLabel->setText("无法加载图片。");
            scrollArea->setVisible(true);
            return;
        }
        imageLabel->setPixmap(originalPixmap);
        scaleFactor = 1.0;
        scrollArea->setVisible(true);
        imageLabel->adjustSize();
    }
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    if (originalPixmap.isNull()) {
        event->ignore();
        return;
    }
    if (event->angleDelta().y() > 0) {
        scaleFactor *= 1.15;
    } else {
        scaleFactor /= 1.15;
    }
    updateScaledImage();
    event->accept();
}

void MainWindow::updateScaledImage()
{
    if (originalPixmap.isNull()) {
        return;
    }
    QSize newSize = originalPixmap.size() * scaleFactor;
    imageLabel->setPixmap(originalPixmap.scaled(newSize,
                                                Qt::KeepAspectRatio,
                                                Qt::SmoothTransformation));
    imageLabel->resize(newSize);
}

