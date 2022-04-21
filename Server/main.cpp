#include "mainwindow.h"

#include <QApplication>

/*Instituto Tecnlogico Costarricense
 * Proyecto 1 para la clase de algortmos y estructuras de datos 2
 * Profesor Isaac Ramirez
 * Autor: Isa Córdoba Quesada
 * Carné: 2021067015
 * Version:5 del proyecto*/
int main(int argc, char *argv[])//Función donde se cosntruye la ventana y todos sus procesos
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
