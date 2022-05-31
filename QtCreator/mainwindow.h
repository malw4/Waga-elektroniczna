#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int switcher=0;

private slots:
   // void on_toolButton_clicked();
    //void onFontSizeChanged(int index);
    void on_Connect_clicked();

   // void on_Disconnect_clicked();

    void addToLogs(QString message);
    void readFromPort();

    void on_TensButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort *device;

};
#endif // MAINWINDOW_H
