#include "principal.h"
#include "ui_principal.h"
#include <QRegExpValidator>
#include <QtCore>
#include <QtGui>
#include "editar.h"
#include "ui_editar.h"


#include "QDebug"

#define NOMBRE_RX "([a-zA-Z',.-]+( [a-zA-Z',.-]+)*){2,30}"

#define EMAIL_RX "([a-zA-Z'@.-]+( [a-zA-Z'.-]+)*){2,30}"

Principal::Principal(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);
    QRegExp rxNombre(NOMBRE_RX) , rxApellido(NOMBRE_RX), rxEmail(EMAIL_RX),rxTelefono(TELEFONO_RX);
    QRegExpValidator *valinombre =new QRegExpValidator(rxNombre,this);
    QRegExpValidator *valiapellido =new QRegExpValidator(rxApellido,this);
    QRegExpValidator *valiemail = new QRegExpValidator(rxEmail, this);
    QRegExpValidator *valitelefono = new QRegExpValidator(rxTelefono, this);
    ui->inNombre->setValidator(valinombre);
    ui->inApellido->setValidator(valiapellido);
    ui->inEmail->setValidator(valiemail);
    ui->inTelefono->setValidator(valitelefono);
    m_u=0;
    m_f=-1;
    setWindowTitle("Agenda telefónica");
    // Configurar la tabla
    ui->tblLista->setColumnCount(4);
    QStringList titulo;
    titulo << "Nombre" << "Apellido" << "Teléfono" << "E-mail";
    ui->tblLista->setHorizontalHeaderLabels(titulo);
    // Leer desde el archivo
    cargarContactos();

}

Principal::~Principal()
{
    delete ui;
}


void Principal::on_btnAgregar_clicked()
{
    // Crear y mostrar el dialogo
    PersonaDialog pd(this);
    pd.setWindowTitle("Agregar contacto");
    // Abrir la ventana y evaluar respuesta
    int res = pd.exec();
    if (res == QDialog::Rejected){
        return;
    }
    // Recuperar el objeto del cuadro de dialogo
    Persona *p = pd.persona();
    //Agregar a la tabla
    int fila = ui->tblLista->rowCount();
    ui->tblLista->insertRow(fila);
    ui->tblLista->setItem(fila, NOMBRE, new QTableWidgetItem(p->nombre()));
    ui->tblLista->setItem(fila, APELLIDO, new QTableWidgetItem(p->apellido()));
    ui->tblLista->setItem(fila, TELEFONO, new QTableWidgetItem(p->telefono()));
    ui->tblLista->setItem(fila, EMAIL, new QTableWidgetItem(p->email()));

}


void Principal::on_btnGuardar_clicked()
{
    // Verificar que exista datos para guardar
    int filas = ui->tblLista->rowCount();
    if (filas == 0){
        QMessageBox::warning(this,"Guardar contactos","Agenda sin datos para guardar");
        return;
    }
    // Abrir el archivo y guardar
    QFile archivo(ARCHIVO);
    if (archivo.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream salida(&archivo);
        for (int i=0; i<filas; i++) {
            QTableWidgetItem *nombre = ui->tblLista->item(i, NOMBRE);
            QTableWidgetItem *apellido = ui->tblLista->item(i, APELLIDO);
            QTableWidgetItem *telefono = ui->tblLista->item(i, TELEFONO);
            QTableWidgetItem *email = ui->tblLista->item(i, EMAIL);
            salida << nombre->text() << ";" << apellido->text() << ";";
            salida << telefono->text() << ";" << email->text() << "\n";
        }
        archivo.close();
        QMessageBox::information(this,"Guardar contactos","Contactos guardados con éxito");
    }else{
        QMessageBox::critical(this,"Guardar contactos", "No se puede escribir sobre " + ARCHIVO);
    }

}

void Principal::cargarContactos()
{
    // Verificar si el archivo existe
    QFile archivo(ARCHIVO);
    if (!archivo.exists())
        return;

    // cargar datos
    if (archivo.open(QFile::ReadOnly)) {
        QTextStream entrada(&archivo);
        int fila;
        while(!entrada.atEnd()){
            QString linea = entrada.readLine();
            QStringList datos = linea.split(";");
            //Agregar a la tabla
            fila = ui->tblLista->rowCount();
            ui->tblLista->insertRow(fila);
            ui->tblLista->setItem(fila, NOMBRE, new QTableWidgetItem(datos[NOMBRE]));
            ui->tblLista->setItem(fila, APELLIDO, new QTableWidgetItem(datos[APELLIDO]));
            ui->tblLista->setItem(fila, TELEFONO, new QTableWidgetItem(datos[TELEFONO]));
            ui->tblLista->setItem(fila, EMAIL, new QTableWidgetItem(datos[EMAIL]));
        }
        archivo.close();
    }
}


void Principal::on_btnEliminar_clicked()
{
    ui->tblLista->removeRow(m_f);
}



void Principal::on_tblLista_itemClicked(QTableWidgetItem *item)
{
    m_f= item->row();
    QTableWidgetItem *nombre =ui->tblLista->item(m_f,0);
    QTableWidgetItem *apellido =ui->tblLista->item(m_f,1);
    QTableWidgetItem *telefono =ui->tblLista->item(m_f,2);
    QTableWidgetItem *email =ui->tblLista->item(m_f,3);
    ui->inNombre->setText(nombre->text());
    ui->inApellido->setText(apellido->text());
    ui->inTelefono->setText(telefono->text());
    ui->inEmail->setText(email->text());
}


void Principal::on_btnEditar_clicked()
{
    Editar ed(this);
    ed.setWindowTitle("Edidat");
    int res = ed.exec();
    if (res == QDialog::Rejected){
        return;
    }
}


