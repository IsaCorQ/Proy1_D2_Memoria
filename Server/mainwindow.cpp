 #include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)//Función principal de la ventana con la conexión entre los slots de los botones y sus clicks, el cliente y sus señales y el server y su protocolo personal al igual que la parte grafica de la ventana
{
    ui->setupUi(this);
    m_server = new QTcpServer();

    connect(timer, SIGNAL(timeout()), this, SLOT(actualizar_estado()));
    connect(ui->tarjeta01, SIGNAL(clicked()), this, SLOT(tarjeta_descubierta()));
    connect(ui->tarjeta02, SIGNAL(clicked()), this, SLOT(tarjeta_descubierta()));
    connect(ui->tarjeta03, SIGNAL(clicked()), this, SLOT(tarjeta_descubierta()));
    connect(ui->tarjeta04, SIGNAL(clicked()), this, SLOT(tarjeta_descubierta()));
    connect(ui->tarjeta05, SIGNAL(clicked()), this, SLOT(tarjeta_descubierta()));
    connect(ui->tarjeta06, SIGNAL(clicked()), this, SLOT(tarjeta_descubierta()));
    connect(ui->tarjeta07, SIGNAL(clicked()), this, SLOT(tarjeta_descubierta()));
    connect(ui->tarjeta08, SIGNAL(clicked()), this, SLOT(tarjeta_descubierta()));
    connect(ui->tarjeta09, SIGNAL(clicked()), this, SLOT(tarjeta_descubierta()));
    connect(ui->tarjeta10, SIGNAL(clicked()), this, SLOT(tarjeta_descubierta()));
    connect(ui->tarjeta11, SIGNAL(clicked()), this, SLOT(tarjeta_descubierta()));
    connect(ui->tarjeta12, SIGNAL(clicked()), this, SLOT(tarjeta_descubierta()));
    connect(ui->tarjeta13, SIGNAL(clicked()), this, SLOT(tarjeta_descubierta()));
    connect(ui->tarjeta14, SIGNAL(clicked()), this, SLOT(tarjeta_descubierta()));
    connect(ui->tarjeta15, SIGNAL(clicked()), this, SLOT(tarjeta_descubierta()));
    connect(ui->tarjeta16, SIGNAL(clicked()), this, SLOT(tarjeta_descubierta()));
    connect(ui->tarjeta17, SIGNAL(clicked()), this, SLOT(tarjeta_descubierta()));
    connect(ui->tarjeta18, SIGNAL(clicked()), this, SLOT(tarjeta_descubierta()));
    connect(ui->tarjeta19, SIGNAL(clicked()), this, SLOT(tarjeta_descubierta()));
    connect(ui->tarjeta20, SIGNAL(clicked()), this, SLOT(tarjeta_descubierta()));
    connect(ui->tarjeta21, SIGNAL(clicked()), this, SLOT(tarjeta_descubierta()));
    connect(ui->tarjeta22, SIGNAL(clicked()), this, SLOT(tarjeta_descubierta()));
    connect(ui->tarjeta23, SIGNAL(clicked()), this, SLOT(tarjeta_descubierta()));
    connect(ui->tarjeta24, SIGNAL(clicked()), this, SLOT(tarjeta_descubierta()));
    connect(ui->tarjeta25, SIGNAL(clicked()), this, SLOT(tarjeta_descubierta()));
    connect(ui->tarjeta26, SIGNAL(clicked()), this, SLOT(tarjeta_descubierta()));
    connect(ui->tarjeta27, SIGNAL(clicked()), this, SLOT(tarjeta_descubierta()));
    connect(ui->tarjeta28, SIGNAL(clicked()), this, SLOT(tarjeta_descubierta()));
    connect(ui->tarjeta29, SIGNAL(clicked()), this, SLOT(tarjeta_descubierta()));
    connect(ui->tarjeta30, SIGNAL(clicked()), this, SLOT(tarjeta_descubierta()));
    connect(ui->tarjeta31, SIGNAL(clicked()), this, SLOT(tarjeta_descubierta()));
    connect(ui->tarjeta32, SIGNAL(clicked()), this, SLOT(tarjeta_descubierta()));
    connect(ui->tarjeta33, SIGNAL(clicked()), this, SLOT(tarjeta_descubierta()));
    connect(ui->tarjeta34, SIGNAL(clicked()), this, SLOT(tarjeta_descubierta()));
    connect(ui->tarjeta35, SIGNAL(clicked()), this, SLOT(tarjeta_descubierta()));
    connect(ui->tarjeta36, SIGNAL(clicked()), this, SLOT(tarjeta_descubierta()));

    iniciar_juego();

    if(m_server->listen(QHostAddress::Any, 1234))
    {
       connect(this, &MainWindow::nuevo_msj, this, &MainWindow::ensenar_msj);
       connect(m_server, &QTcpServer::newConnection, this, &MainWindow::nueva_conexion);
       ui->statusbar->showMessage("Conectando");
    }
    else
    {
        QMessageBox::critical(this,"QTCPServer",QString("Server no inicio: %1.").arg(m_server->errorString()));
        exit(EXIT_FAILURE);
    }
}

MainWindow::~MainWindow()//Funcion de protocolo de como deshacerse de la ventana principal cuando esta se destruya
{
    foreach (QTcpSocket* socket, connection_set)
    {
        socket->close();
        socket->deleteLater();
    }

    m_server->close();
    m_server->deleteLater();

    delete ui;
}

void MainWindow::nueva_conexion()//función que indica ue se unio un nuevo cliente y ayuda a mantener la conexion para mandar señales del cliente al server y viceversa
{
    while (m_server->hasPendingConnections())
        append_lista_socket(m_server->nextPendingConnection());
}

void MainWindow::append_lista_socket(QTcpSocket* socket)//Une el socket del cliente a los sockets que server debe mantener al tanto
{
    /*Entrada: Un socket tcp
     * Restricciones: Debe ser un socket tcp que tenga el mismo puerto que server; no puede ser cualquier socket definido
     * Salida: La conexion entre el server y el socket para mandar mensajes*/
    connection_set.insert(socket);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::leer_socket);
    connect(socket, &QTcpSocket::disconnected, this, &MainWindow::eliminar_socket);
    connect(socket, &QAbstractSocket::errorOccurred, this, &MainWindow::ensenar_error);
    ui->comboBox_receiver->addItem(QString::number(socket->socketDescriptor()));
    ensenar_msj(QString("INFO :: Cliente %1 se acaba de conectar").arg(socket->socketDescriptor()));
}

void MainWindow::leer_socket()//Registra y analiza las señales mandadas por el cliente, el cliente solo manda señal por sus botones entonces este analiza cual boton fue presionado
{
    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());
    QString socketname= QString("%1").arg(socket->socketDescriptor());
    QByteArray buffer;
    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);
    socketStream.startTransaction();
    socketStream >> buffer;
    //Espera a la transmision de client para iniciar sus funciones
    if(!socketStream.commitTransaction())
    {

        QString message = QString("%1 :: wait").arg(socket->socketDescriptor());
        emit nuevo_msj(message);
        return;
    }

    QString header = buffer.mid(0,128);
    QString fileType = header.split(",")[0].split(":")[1];

    buffer = buffer.mid(128);
    //Manera cavernicola xd pero funciona para cumplir su proposito
    QString s1 =  socketname +" :: s1";
    QString s2 =  socketname +" :: s2";
    QString s3 =  socketname +" :: s3";
    QString s4 =  socketname +" :: s4";
    QString s5 =  socketname +" :: s5";
    QString s6 =  socketname +" :: s6";
    QString s7 =  socketname +" :: s7";
    QString s8 =  socketname +" :: s8";
    QString s9 =  socketname +" :: s9";
    QString s10 =  socketname +" :: s10";
    QString s11 =  socketname +" :: s11";
    QString s12 =  socketname +" :: s12";
    QString s13 =  socketname +" :: s13";
    QString s14 =  socketname +" :: s14";
    QString s15 =  socketname +" :: s15";
    QString s16 =  socketname +" :: s16";
    QString s17 =  socketname +" :: s17";
    QString s18 =  socketname +" :: s18";
    QString s19 =  socketname +" :: s19";
    QString s20 =  socketname +" :: s20";
    QString s21 =  socketname +" :: s21";
    QString s22 =  socketname +" :: s22";
    QString s23 =  socketname +" :: s23";
    QString s24 =  socketname +" :: s24";
    QString s25 =  socketname +" :: s25";
    QString s26 =  socketname +" :: s26";
    QString s27 =  socketname +" :: s27";
    QString s28 =  socketname +" :: s28";
    QString s29 =  socketname +" :: s29";
    QString s30 =  socketname +" :: s30";
    QString s31 =  socketname +" :: s31";
    QString s32 =  socketname +" :: s32";
    QString s33 =  socketname +" :: s33";
    QString s34 =  socketname +" :: s34";
    QString s35 =  socketname +" :: s35";
    QString s36 =  socketname +" :: s36";
    //Analiza los "mensajes" e.p. las señales mandadas por los botones y espera a leer el espesifico entre slot y tarjeta de cliente y server respectivamente
    if(fileType == "message"){
        QString message = QString("%1 :: %2").arg(socket->socketDescriptor()).arg(QString::fromStdString(buffer.toStdString()));
        qDebug() << message;
        emit nuevo_msj(message);
        //Manera forzada de mandar señales
        if (QString::compare(s1, message,Qt::CaseInsensitive) == 0){
            emit ui->tarjeta01->clicked(true);
        }
        if (QString::compare(s2, message,Qt::CaseInsensitive) == 0){
            emit ui->tarjeta02->clicked(true);
        }
        if (QString::compare(s3, message,Qt::CaseInsensitive) == 0){
            emit ui->tarjeta03->clicked(true);
        }
        if (QString::compare(s4, message,Qt::CaseInsensitive) == 0){
            emit ui->tarjeta04->clicked(true);
        }
        if (QString::compare(s5, message,Qt::CaseInsensitive) == 0){
            emit ui->tarjeta05->clicked(true);
        }
        if (QString::compare(s6, message,Qt::CaseInsensitive) == 0){
            emit ui->tarjeta06->clicked(true);
        }
        if (QString::compare(s7, message,Qt::CaseInsensitive) == 0){
            emit ui->tarjeta07->clicked(true);
        }
        if (QString::compare(s8, message,Qt::CaseInsensitive) == 0){
            emit ui->tarjeta08->clicked(true);
        }
        if (QString::compare(s9, message,Qt::CaseInsensitive) == 0){
            emit ui->tarjeta09->clicked(true);
        }
        if (QString::compare(s10, message,Qt::CaseInsensitive) == 0){
            emit ui->tarjeta10->clicked(true);
        }
        if (QString::compare(s11, message,Qt::CaseInsensitive) == 0){
            emit ui->tarjeta11->clicked(true);
        }
        if (QString::compare(s12, message,Qt::CaseInsensitive) == 0){
            emit ui->tarjeta12->clicked(true);
        }
        if (QString::compare(s13, message,Qt::CaseInsensitive) == 0){
            emit ui->tarjeta13->clicked(true);
        }
        if (QString::compare(s14, message,Qt::CaseInsensitive) == 0){
            emit ui->tarjeta14->clicked(true);
        }
        if (QString::compare(s15, message,Qt::CaseInsensitive) == 0){
            emit ui->tarjeta15->clicked(true);
        }
        if (QString::compare(s16, message,Qt::CaseInsensitive) == 0){
            emit ui->tarjeta16->clicked(true);
        }
        if (QString::compare(s17, message,Qt::CaseInsensitive) == 0){
            emit ui->tarjeta17->clicked(true);
        }
        if (QString::compare(s18, message,Qt::CaseInsensitive) == 0){
            emit ui->tarjeta18->clicked(true);
        }
        if (QString::compare(s19, message,Qt::CaseInsensitive) == 0){
            emit ui->tarjeta19->clicked(true);
        }
        if (QString::compare(s20, message,Qt::CaseInsensitive) == 0){
            emit ui->tarjeta20->clicked(true);
        }
        if (QString::compare(s21, message,Qt::CaseInsensitive) == 0){
            emit ui->tarjeta21->clicked(true);
        }
        if (QString::compare(s22, message,Qt::CaseInsensitive) == 0){
            emit ui->tarjeta22->clicked(true);
        }
        if (QString::compare(s23, message,Qt::CaseInsensitive) == 0){
            emit ui->tarjeta23->clicked(true);
        }
        if (QString::compare(s24, message,Qt::CaseInsensitive) == 0){
            emit ui->tarjeta24->clicked(true);
        }
        if (QString::compare(s25, message,Qt::CaseInsensitive) == 0){
            emit ui->tarjeta25->clicked(true);
        }
        if (QString::compare(s26, message,Qt::CaseInsensitive) == 0){
            emit ui->tarjeta26->clicked(true);
        }
        if (QString::compare(s27, message,Qt::CaseInsensitive) == 0){
            emit ui->tarjeta27->clicked(true);
        }
        if (QString::compare(s28, message,Qt::CaseInsensitive) == 0){
            emit ui->tarjeta28->clicked(true);
        }
        if (QString::compare(s29, message,Qt::CaseInsensitive) == 0){
            emit ui->tarjeta29->clicked(true);
        }
        if (QString::compare(s30, message,Qt::CaseInsensitive) == 0){
            emit ui->tarjeta30->clicked(true);
        }
        if (QString::compare(s31, message,Qt::CaseInsensitive) == 0){
            emit ui->tarjeta31->clicked(true);
        }
        if (QString::compare(s32, message,Qt::CaseInsensitive) == 0){
            emit ui->tarjeta32->clicked(true);
        }
        if (QString::compare(s33, message,Qt::CaseInsensitive) == 0){
            emit ui->tarjeta33->clicked(true);
        }
        if (QString::compare(s34, message,Qt::CaseInsensitive) == 0){
            emit ui->tarjeta34->clicked(true);
        }
        if (QString::compare(s35, message,Qt::CaseInsensitive) == 0){
            emit ui->tarjeta35->clicked(true);
        }
        if (QString::compare(s36, message,Qt::CaseInsensitive) == 0){
            emit ui->tarjeta36->clicked(true);
        }
    }
}

void MainWindow::eliminar_socket()//Elimina el socket del cliente a la transmision del server cuando el cliente se salga
{
    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());
    QSet<QTcpSocket*>::iterator it = connection_set.find(socket);
    if (it != connection_set.end()){
        ensenar_msj(QString("Se a desconectado un cliente").arg(socket->socketDescriptor()));
        connection_set.remove(*it);
    }

    socket->deleteLater();
}

void MainWindow::ensenar_error(QAbstractSocket::SocketError socketError)//Se encarga de enseñar si existe algun error en la conexion del cliente al server y cual tipo fue
{
    /*Entrada: EL error identificado entre el cliente y el server
     * Restricciones: Debe de ser uo de los errores comunes reconocidos para que pueda espicificar el error
     * Salida: El tipo del error*/
    switch (socketError) {
        case QAbstractSocket::RemoteHostClosedError:
        break;
        case QAbstractSocket::HostNotFoundError:
            QMessageBox::information(this, "QTCPServer", "No se encontro el host apropiado");
        break;
        case QAbstractSocket::ConnectionRefusedError:
            QMessageBox::information(this, "QTCPServer", "Server no acepto la conexión revise el puerto");
        break;
        default:
            QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
            QMessageBox::information(this, "QTCPServer", QString("Error: %1.").arg(socket->errorString()));
        break;
    }
}

void MainWindow::on_pushButton_sendMessage_clicked()//Función que hace el boton enviar_msj del server
{

    foreach (QTcpSocket* socket,connection_set)
        {
            enviar_msj(socket);
        }

    ui->lineEdit_message->clear();
}

void MainWindow::enviar_msj(QTcpSocket* socket)//Envia el mensaje que el cliente quiera mandar
{
    /*Entrada: Mensaje mandado por el socket del cliente
     * Restricciones.Debe de ser un string y capaz de ser interpretado por el server
     * Salida:Interpretación del mensaje mandado por el cliente*/
    if(socket)
    {
        if(socket->isOpen())
        {
            QString str = ui->lineEdit_message->text();

            QDataStream socketStream(socket);
            socketStream.setVersion(QDataStream::Qt_5_15);

            QByteArray header;
            header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
            header.resize(128);

            QByteArray byteArray = str.toUtf8();
            byteArray.prepend(header);

            socketStream.setVersion(QDataStream::Qt_5_15);
            socketStream << byteArray;
        }
        else
            QMessageBox::critical(this,"QTCPServer","Socket esta cerrdo");
    }
    else
        QMessageBox::critical(this,"QTCPServer","No existe conexión");
}

void MainWindow::ensenar_msj(const QString& str)//Visualiza el mensaje mandado por el cliente en el txtbrowser del server
{
    /*Entrada:Mensaje mandado por el cliente
     * Restricciones:Debe de ser un string
     * Salida:Visualización el textbrowser del server*/
    ui->textBrowser_receivedMessages->append(str);
}

void MainWindow::tarjeta_descubierta()//Indica que se elije una tarjeta entonces se "descubre" su posicion
{
    tarjetaActual=qobject_cast<QPushButton*>(sender());
    mostrar_imagen();
    tarjetaActual->setEnabled(false);

    if (!jugadaIniciada){
        tarjetaAnterior=tarjetaActual;
        jugadaIniciada=true;
    }
    else{
        resultado_parcial();
        jugadaIniciada=false;
    }
}

void MainWindow::mostrar_imagen()//Muestra la imagen que es elegida aleatoriamente de una tarjeta cuando esta es seleccionada
{
    QString nombre_tarjeta=tarjetaActual->objectName();
    QString img=reparto[nombre_tarjeta];
    tarjetaActual->setStyleSheet("#" + nombre_tarjeta + "{ background-image: url(://" + img + ") }");
}

void MainWindow::reiniciar_tarjetas()//Devuelve las tarjetas a su estado anterior al igual que el frame donde se encuentran los botones
{
    tarjetaAnterior->setStyleSheet("#" + tarjetaAnterior->objectName() + "{ }");
    tarjetaActual->setStyleSheet("#" + tarjetaActual->objectName() + "{ }");

    tarjetaActual->setEnabled(true);
    tarjetaAnterior->setEnabled(true);

    ui->frame->setEnabled(true);
}

void MainWindow::resultado_final()//Indica cuando termina el juego y en que estado
{
    msgBox.setWindowTitle("Juego terminado");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    msgBox.setEscapeButton(QMessageBox::No);

    if (parejasRestantes==0){
        timer->stop();
        msgBox.setText("Puntaje final: " + QString::number(puntaje) + "\nVolver a jugar?");
        if (QMessageBox::Yes == msgBox.exec()){
            iniciar_juego();
        }
        else{
            QCoreApplication::quit();
        }
    }
    else{
        if (time.toString()=="00:00:00"){
            timer->stop();
            ui->frame->setEnabled(false);
            msgBox.setText("Sin tiempo \n¿Volver a jugar?");
            if (QMessageBox::Yes == msgBox.exec()){
                iniciar_juego();
            }
            else{
                QCoreApplication::quit();
            }
        }
    }
}

void MainWindow::resultado_parcial()//Indica si dos parejas si son iguales o diferentes y las elimina del array si son iguales o las devuelve a su estado oculto si son diferentes
{
    if (reparto[tarjetaActual->objectName()]==reparto[tarjetaAnterior->objectName()]){
        puntaje+=10;
        ui->lblPuntaje->setText(QString::number(puntaje));
        parejasRestantes--;
        resultado_final();
    }
    else{
        ui->frame->setEnabled(false);
        QTimer::singleShot(1000, this, SLOT(reiniciar_tarjetas()));
    }
}

void MainWindow::iniciar_juego()//Cuando el cliente entrqa al server se inicia el juego donde llama el resto de las funciones para que estas esten atentas a las señales mandadas por el cliente
{
    jugadaIniciada=false;
    puntaje=0;
    ui->lblPuntaje->setText(QString::number(puntaje));;
    parejasRestantes=18;
    time.setHMS(0,10,0);
    ui->cronometro->setText(time.toString("m:ss"));
    timer->start(1000);
    mezclar(tarjetas);
    repartir(tarjetas, reparto);
    ui->frame->setEnabled(true);

    QList<QPushButton *> botones =  ui->centralwidget->findChildren<QPushButton*>();
    foreach (QPushButton* b, botones) {
        b->setEnabled(true);
        b->setStyleSheet("#" + b->objectName() + "{ }");
    }
}

void MainWindow::actualizar_cronometro()//Actualiza el cronometro que indica cuando tiempo sobra para jugar
{
    time=time.addSecs(-1);
    ui->cronometro->setText(time.toString("m:ss"));
}

void MainWindow::actualizar_estado()//Actualiza el estado de las tarjetas si estas se deben de eliminar o devolver a ocultar y el cronometro para que haya una continuidad constante durante la partida
{
    actualizar_cronometro();
    resultado_final();
}

void MainWindow::mezclar(QVector<QString> &tarjetas)//Mezcla el rray de tarjetas para que estas caigan aleatoriamente con sus pares
{
    /*Entrada:Array de tarjetas
     * Restricción: EL array no puede ser modificado
     * Salida:La ubicacion de cada tarjeta con su imagen*/
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle (tarjetas.begin(), tarjetas.end(), std::default_random_engine(seed));
}

void MainWindow::repartir(QVector<QString> &tarjetas, QHash<QString, QString> &reparto)//Indica cual imagen va con cual slot de tarjeta se indica dos veces iteración y reparto considerando que cada imagen tiene 2 slots correspondientes
{
    /*Entrada: E array de las tarjetas y las imagenes utilizadas en el juego
     * Restricción:No se pueden añadir mas imagenes ni tarjetas
     * Salida:Concordancia entre las imagenes y las tarjetas*/
    auto iterador=tarjetas.begin();
    for (int i=1; i<=18; i++){
        QString file_name=QString::number(i)+".png";
        reparto[(*iterador)]=file_name;
        iterador++;
        reparto[(*iterador)]=file_name;
        iterador++;
    }
}
