// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>


class QPushButton;
class QLabel;
class QScrollArea;
class QWheelEvent;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void wheelEvent(QWheelEvent *event) override;


private slots:
    void openImage();


private:
    void updateScaledImage();

    QWidget *centralWidget;
    QPushButton *openButton;
    QLabel *imageLabel;
    QScrollArea *scrollArea;
    QPixmap originalPixmap;
    double scaleFactor;

};
#endif // MAINWINDOW_H
