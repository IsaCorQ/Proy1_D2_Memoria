#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractSocket>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QHostAddress>
#include <QMessageBox>
#include <QMetaType>
#include <QString>
#include <QStandardPaths>
#include <QTcpSocket>

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void nuevo_msj(QString);

private slots:
    void leer_socket();
    void eliminar_socket();

    void on_s01_clicked();
    void on_s02_clicked();
    void on_s03_clicked();
    void on_s04_clicked();
    void on_s05_clicked();
    void on_s06_clicked();
    void on_s07_clicked();
    void on_s08_clicked();
    void on_s09_clicked();
    void on_s10_clicked();
    void on_s11_clicked();
    void on_s12_clicked();
    void on_s13_clicked();
    void on_s14_clicked();
    void on_s15_clicked();
    void on_s16_clicked();
    void on_s17_clicked();
    void on_s18_clicked();
    void on_s19_clicked();
    void on_s20_clicked();
    void on_s21_clicked();
    void on_s22_clicked();
    void on_s23_clicked();
    void on_s24_clicked();
    void on_s25_clicked();
    void on_s26_clicked();
    void on_s27_clicked();
    void on_s28_clicked();
    void on_s29_clicked();
    void on_s30_clicked();
    void on_s31_clicked();
    void on_s32_clicked();
    void on_s33_clicked();
    void on_s34_clicked();
    void on_s35_clicked();
    void on_s36_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket* socket;
};
#endif // MAINWINDOW_H
