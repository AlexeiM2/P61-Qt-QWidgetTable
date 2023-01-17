#include "editar.h"
#include "ui_editar.h"

Editar::Editar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Editar)
{
    m_u=0;
    m_f=-1;
    ui->tblLista->setItem(m_f,0,new QTableWidgetItem(ui->inNombre->text()));
    ui->tblLista->setItem(m_f,1,new QTableWidgetItem(ui->inApellido->text()));
    ui->tblLista->setItem(m_f,2,new QTableWidgetItem(ui->inTelefono->text()));
    ui->tblLista->setItem(m_f,3,new QTableWidgetItem(ui->inEmail->text()));
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

Editar::~Editar()
{
    delete ui;
}

void Editar::on_buttonBox_accepted()
{
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


void Editar::on_buttonBox_rejected()
{
    reject();
}

Persona *Editar::persona() const{
    return m_persona;
}
