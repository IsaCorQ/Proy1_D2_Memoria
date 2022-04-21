#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QMetaType>
#include <QSet>
#include <QStandardPaths>
#include <QTcpServer>
#include <QTcpSocket>


#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QString>
#include <QVector>
#include <QHash>
#include <QPushButton>
#include <QMessageBox>
#include <random>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTimer *timer=new QTimer();
    QTime time;
    QVector<QString> tarjetas{"tarjeta01", "tarjeta02", "tarjeta03", "tarjeta04",
                              "tarjeta05", "tarjeta06", "tarjeta07", "tarjeta08",
                              "tarjeta09", "tarjeta10", "tarjeta11", "tarjeta12",
                              "tarjeta13", "tarjeta14", "tarjeta15", "tarjeta16",
                              "tarjeta17", "tarjeta18", "tarjeta19", "tarjeta20",
                              "tarjeta21", "tarjeta22", "tarjeta23", "tarjeta24",
                              "tarjeta25", "tarjeta26", "tarjeta27", "tarjeta28",
                              "tarjeta29", "tarjeta30", "tarjeta31", "tarjeta32",
                              "tarjeta33", "tarjeta34", "tarjeta35", "tarjeta36"};
    QHash<QString, QString> reparto;
    int puntaje=0;
    bool jugadaIniciada;
    QPushButton* tarjetaAnterior;
    QPushButton* tarjetaActual;
    int parejasRestantes;
    QMessageBox msgBox;

signals:
    void nuevo_msj(QString);
private slots:
    void nueva_conexion();
    void append_lista_socket(QTcpSocket* socket);

    void leer_socket();
    void eliminar_socket();
    void ensenar_error(QAbstractSocket::SocketError socketError);

    void ensenar_msj(const QString& str);
    void enviar_msj(QTcpSocket* socket);

    void on_pushButton_sendMessage_clicked();


    void actualizar_cronometro();
    void tarjeta_descubierta();
    void mezclar(QVector<QString> &tarjetas);
    void repartir(QVector<QString> &tarjetas, QHash<QString, QString> &reparto);
    void resultado_parcial();
    void reiniciar_tarjetas();
    void mostrar_imagen();
    void resultado_final();
    void actualizar_estado();
    void iniciar_juego();



private:
    Ui::MainWindow *ui;

    QTcpServer* m_server;
    QSet<QTcpSocket*> connection_set;
};

#endif // MAINWINDOW_H
