#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)//Función principal de la ventana de cliente la cual contiene su ui funciones de señal y protocolo
{
    ui->setupUi(this);
    socket=new QTcpSocket(this);


    connect(socket, &QTcpSocket::readyRead,this,&MainWindow::leer_socket);
    connect(socket, &QTcpSocket::disconnected, this, &MainWindow::eliminar_socket);

    socket-> connectToHost(QHostAddress::LocalHost,1234);

    if (socket->waitForConnected())
        ui->statusbar->showMessage("Conectado");
        else{
            QMessageBox::critical(this,"Client",QString("Error").arg(socket->errorString()));
            exit(EXIT_FAILURE);
        }
}

MainWindow::~MainWindow()//Protocolo cuando uno cierra el cliente
{
    if(socket->isOpen())
        socket->close();

    delete ui;
}

void MainWindow::leer_socket()//Función que se encarga de leer el socket e interpretar las señales y mensajes que mande para que estse llegue al cliente
{
    QByteArray buffer;
    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);
    socketStream.startTransaction();
    socketStream >> buffer;
    QString header = buffer.mid(0,128);
    QString msgSent = header.split(",")[1].split(":")[1];
    buffer = buffer.mid(128);

    if(msgSent=="message"){
        QString message = QString("%1 :: %2").arg(socket -> socketDescriptor()).arg(QString::fromStdString(buffer.toStdString()));
        emit nuevo_msj(message);
    }
}

void MainWindow::eliminar_socket()//Función que borra el socket creado por un cliente para desconectarlo del server
{
    socket->deleteLater();
    socket=nullptr;

    ui->statusbar->showMessage("Desconectado");
}

void MainWindow::on_s01_clicked()//Mensaje que envia al server cuando se da click al boton slot 1
{
    QString str = "s1";

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    QByteArray header;
    header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
    header.resize(128);

    QByteArray byteArray = str.toUtf8();
    byteArray.prepend(header);

    socketStream << byteArray;

}

void MainWindow::on_s02_clicked()//Mensaje que envia al server cuando se da click al boton slot 2
{
    QString str = "s2";

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    QByteArray header;
    header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
    header.resize(128);

    QByteArray byteArray = str.toUtf8();
    byteArray.prepend(header);

    socketStream << byteArray;

}

void MainWindow::on_s03_clicked()//Mensaje que envia al server cuando se da click al boton slot 3
{
    QString str = "s3";

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    QByteArray header;
    header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
    header.resize(128);

    QByteArray byteArray = str.toUtf8();
    byteArray.prepend(header);

    socketStream << byteArray;

}

void MainWindow::on_s04_clicked()//Mensaje que envia al server cuando se da click al boton slot 4
{
    QString str = "s4";

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    QByteArray header;
    header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
    header.resize(128);

    QByteArray byteArray = str.toUtf8();
    byteArray.prepend(header);

    socketStream << byteArray;
}

void MainWindow::on_s05_clicked()//Mensaje que envia al server cuando se da click al boton slot 5
{
    QString str = "s5";

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    QByteArray header;
    header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
    header.resize(128);

    QByteArray byteArray = str.toUtf8();
    byteArray.prepend(header);

    socketStream << byteArray;

}

void MainWindow::on_s06_clicked()//Mensaje que envia al server cuando se da click al boton slot 6
{
    QString str = "s6";

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    QByteArray header;
    header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
    header.resize(128);

    QByteArray byteArray = str.toUtf8();
    byteArray.prepend(header);

    socketStream << byteArray;

}

void MainWindow::on_s07_clicked()//Mensaje que envia al server cuando se da click al boton slot 7
{
    QString str = "s7";

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    QByteArray header;
    header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
    header.resize(128);

    QByteArray byteArray = str.toUtf8();
    byteArray.prepend(header);

    socketStream << byteArray;

}

void MainWindow::on_s08_clicked()//Mensaje que envia al server cuando se da click al boton slot 8
{
    QString str = "s8";

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    QByteArray header;
    header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
    header.resize(128);

    QByteArray byteArray = str.toUtf8();
    byteArray.prepend(header);

    socketStream << byteArray;

}

void MainWindow::on_s09_clicked()//Mensaje que envia al server cuando se da click al boton slot 9
{
    QString str = "s9";

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    QByteArray header;
    header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
    header.resize(128);

    QByteArray byteArray = str.toUtf8();
    byteArray.prepend(header);

    socketStream << byteArray;

}

void MainWindow::on_s10_clicked()//Mensaje que envia al server cuando se da click al boton slot 10
{
    QString str = "s10";

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    QByteArray header;
    header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
    header.resize(128);

    QByteArray byteArray = str.toUtf8();
    byteArray.prepend(header);

    socketStream << byteArray;

}

void MainWindow::on_s11_clicked()//Mensaje que envia al server cuando se da click al boton slot 11
{
    QString str = "s11";

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    QByteArray header;
    header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
    header.resize(128);

    QByteArray byteArray = str.toUtf8();
    byteArray.prepend(header);

    socketStream << byteArray;

}

void MainWindow::on_s12_clicked()//Mensaje que envia al server cuando se da click al boton slot 12
{
    QString str = "s12";

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    QByteArray header;
    header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
    header.resize(128);

    QByteArray byteArray = str.toUtf8();
    byteArray.prepend(header);

    socketStream << byteArray;

}

void MainWindow::on_s13_clicked()//Mensaje que envia al server cuando se da click al boton slot 13
{
    QString str = "s13";

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    QByteArray header;
    header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
    header.resize(128);

    QByteArray byteArray = str.toUtf8();
    byteArray.prepend(header);

    socketStream << byteArray;

}

void MainWindow::on_s14_clicked()//Mensaje que envia al server cuando se da click al boton slot 14
{
    QString str = "s14";

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    QByteArray header;
    header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
    header.resize(128);

    QByteArray byteArray = str.toUtf8();
    byteArray.prepend(header);

    socketStream << byteArray;

}

void MainWindow::on_s15_clicked()//Mensaje que envia al server cuando se da click al boton slot 15
{
    QString str = "s15";

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    QByteArray header;
    header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
    header.resize(128);

    QByteArray byteArray = str.toUtf8();
    byteArray.prepend(header);

    socketStream << byteArray;

}

void MainWindow::on_s16_clicked()//Mensaje que envia al server cuando se da click al boton slot 16
{
    QString str = "s16";

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    QByteArray header;
    header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
    header.resize(128);

    QByteArray byteArray = str.toUtf8();
    byteArray.prepend(header);

    socketStream << byteArray;

}

void MainWindow::on_s17_clicked()//Mensaje que envia al server cuando se da click al boton slot 17
{
    QString str = "s17";

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    QByteArray header;
    header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
    header.resize(128);

    QByteArray byteArray = str.toUtf8();
    byteArray.prepend(header);

    socketStream << byteArray;

}

void MainWindow::on_s18_clicked()//Mensaje que envia al server cuando se da click al boton slot 18
{
    QString str = "s18";

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    QByteArray header;
    header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
    header.resize(128);

    QByteArray byteArray = str.toUtf8();
    byteArray.prepend(header);

    socketStream << byteArray;

}

void MainWindow::on_s19_clicked()//Mensaje que envia al server cuando se da click al boton slot 19
{
    QString str = "s19";

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    QByteArray header;
    header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
    header.resize(128);

    QByteArray byteArray = str.toUtf8();
    byteArray.prepend(header);

    socketStream << byteArray;

}

void MainWindow::on_s20_clicked()//Mensaje que envia al server cuando se da click al boton slot 20
{
    QString str = "s20";

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    QByteArray header;
    header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
    header.resize(128);

    QByteArray byteArray = str.toUtf8();
    byteArray.prepend(header);

    socketStream << byteArray;

}

void MainWindow::on_s21_clicked()//Mensaje que envia al server cuando se da click al boton slot 21
{
    QString str = "s21";

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    QByteArray header;
    header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
    header.resize(128);

    QByteArray byteArray = str.toUtf8();
    byteArray.prepend(header);

    socketStream << byteArray;

}

void MainWindow::on_s22_clicked()//Mensaje que envia al server cuando se da click al boton slot 22
{
    QString str = "s22";

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    QByteArray header;
    header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
    header.resize(128);

    QByteArray byteArray = str.toUtf8();
    byteArray.prepend(header);

    socketStream << byteArray;

}

void MainWindow::on_s23_clicked()//Mensaje que envia al server cuando se da click al boton slot 23
{
    QString str = "s23";

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    QByteArray header;
    header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
    header.resize(128);

    QByteArray byteArray = str.toUtf8();
    byteArray.prepend(header);

    socketStream << byteArray;

}

void MainWindow::on_s24_clicked()//Mensaje que envia al server cuando se da click al boton slot 24
{
    QString str = "s24";

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    QByteArray header;
    header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
    header.resize(128);

    QByteArray byteArray = str.toUtf8();
    byteArray.prepend(header);

    socketStream << byteArray;

}

void MainWindow::on_s25_clicked()//Mensaje que envia al server cuando se da click al boton slot 25
{
    QString str = "s25";

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    QByteArray header;
    header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
    header.resize(128);

    QByteArray byteArray = str.toUtf8();
    byteArray.prepend(header);

    socketStream << byteArray;

}

void MainWindow::on_s26_clicked()//Mensaje que envia al server cuando se da click al boton slot 26
{
    QString str = "s26";

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    QByteArray header;
    header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
    header.resize(128);

    QByteArray byteArray = str.toUtf8();
    byteArray.prepend(header);

    socketStream << byteArray;

}

void MainWindow::on_s27_clicked()//Mensaje que envia al server cuando se da click al boton slot 27
{
    QString str = "s27";

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    QByteArray header;
    header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
    header.resize(128);

    QByteArray byteArray = str.toUtf8();
    byteArray.prepend(header);

    socketStream << byteArray;

}

void MainWindow::on_s28_clicked()//Mensaje que envia al server cuando se da click al boton slot 28
{
    QString str = "s28";

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    QByteArray header;
    header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
    header.resize(128);

    QByteArray byteArray = str.toUtf8();
    byteArray.prepend(header);

    socketStream << byteArray;

}

void MainWindow::on_s29_clicked()//Mensaje que envia al server cuando se da click al boton slot 29
{
    QString str = "s29";

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    QByteArray header;
    header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
    header.resize(128);

    QByteArray byteArray = str.toUtf8();
    byteArray.prepend(header);

    socketStream << byteArray;

}

void MainWindow::on_s30_clicked()//Mensaje que envia al server cuando se da click al boton slot 30
{
    QString str = "s30";

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    QByteArray header;
    header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
    header.resize(128);

    QByteArray byteArray = str.toUtf8();
    byteArray.prepend(header);

    socketStream << byteArray;

}

void MainWindow::on_s31_clicked()//Mensaje que envia al server cuando se da click al boton slot 31
{
    QString str = "s31";

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    QByteArray header;
    header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
    header.resize(128);

    QByteArray byteArray = str.toUtf8();
    byteArray.prepend(header);

    socketStream << byteArray;

}

void MainWindow::on_s32_clicked()//Mensaje que envia al server cuando se da click al boton slot 32
{
    QString str = "s32";

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    QByteArray header;
    header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
    header.resize(128);

    QByteArray byteArray = str.toUtf8();
    byteArray.prepend(header);

    socketStream << byteArray;

}

void MainWindow::on_s33_clicked()//Mensaje que envia al server cuando se da click al boton slot 33
{
    QString str = "s33";

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    QByteArray header;
    header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
    header.resize(128);

    QByteArray byteArray = str.toUtf8();
    byteArray.prepend(header);

    socketStream << byteArray;

}

void MainWindow::on_s34_clicked()//Mensaje que envia al server cuando se da click al boton slot 34
{
    QString str = "s34";

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    QByteArray header;
    header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
    header.resize(128);

    QByteArray byteArray = str.toUtf8();
    byteArray.prepend(header);

    socketStream << byteArray;

}

void MainWindow::on_s35_clicked()//Mensaje que envia al server cuando se da click al boton slot 35
{
    QString str = "s35";

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    QByteArray header;
    header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
    header.resize(128);

    QByteArray byteArray = str.toUtf8();
    byteArray.prepend(header);

    socketStream << byteArray;

}

void MainWindow::on_s36_clicked()//Mensaje que envia al server cuando se da click al boton slot 36
{
    QString str = "s36";

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    QByteArray header;
    header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
    header.resize(128);

    QByteArray byteArray = str.toUtf8();
    byteArray.prepend(header);

    socketStream << byteArray;

}
