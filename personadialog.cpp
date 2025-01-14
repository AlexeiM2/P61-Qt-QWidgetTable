#include "personadialog.h"
#include "ui_personadialog.h"
#include <QRegExpValidator>
#include <QtCore>
#include <QtGui>

#define NOMBRE_RX "([a-zA-Z',.-]+( [a-zA-Z',.-]+)*){2,30}"

#define EMAIL_RX "([a-zA-Z'@.-]+( [a-zA-Z'.-]+)*){2,30}"

#define TELEFONO_RX "([0][1-9]{0,11})"

PersonaDialog::PersonaDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PersonaDialog)
{
    ui->setupUi(this);
    QRegExp rxTelefono(TELEFONO_RX);
    QRegExp rxNombre(NOMBRE_RX) , rxApellido(NOMBRE_RX), rxEmail(EMAIL_RX);
    QRegExpValidator *nombre =new QRegExpValidator(rxNombre,this);
    QRegExpValidator *apellido =new QRegExpValidator(rxApellido,this);
    QRegExpValidator *tele = new QRegExpValidator(rxTelefono, this);
    QRegExpValidator *email = new QRegExpValidator(rxEmail, this);
    ui->inNombre->setValidator(nombre);
    ui->inApellido->setValidator(apellido);
    ui->inEmail->setValidator(email);
    ui->inTelefono->setValidator(tele);
}

PersonaDialog::~PersonaDialog()
{
    delete ui;
}

void PersonaDialog::on_buttonBox_accepted(){
    QString nombre = ui->inNombre->text();
    if(nombre.isEmpty()){
         return ;
    }
    QString apellido = ui->inApellido->text();
    if(apellido.isEmpty()){
         return ;
    }
    QString telefono = ui->inTelefono->text();
    if(telefono.isEmpty()){
         return ;
    }
    QString email = ui->inEmail->text();
    if(email.isEmpty()){
         return ;
    }
    this->m_persona = new Persona(nombre, apellido, telefono, email);
    accept();
}


void PersonaDialog::on_buttonBox_rejected(){
    reject();
}

Persona *PersonaDialog::persona() const{
    return m_persona;
}

