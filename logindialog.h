// logindialog.h
#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H
#include <QDialog>
#include <QPoint>
class QLineEdit;
class QPushButton;
class LoginDialog : public QDialog
{
    Q_OBJECT
public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
private slots:
    void onLoginClicked();
private:
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QPushButton *loginButton;
    QPoint dragPosition;
};
#endif // LOGINDIALOG_H
