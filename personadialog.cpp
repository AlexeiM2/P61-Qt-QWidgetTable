#include "personadialog.h"
#include "ui_personadialog.h"

PersonaDialog::PersonaDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PersonaDialog)
{
    ui->setupUi(this);
}

PersonaDialog::~PersonaDialog()
{
    delete ui;
}

/*QString PersonaDialog::nombre()
{
    return ui->inNombre->text();
}

QString PersonaDialog::apellido()
{
    return ui->inApellido->text();
}

QString PersonaDialog::telefono()
{
    return ui->inTelefono->text();
}

QString PersonaDialog::email()
{
    return ui->inEmail->text();
}
*/
void PersonaDialog::on_buttonBox_accepted()
{
    QString nombre  =ui->inNombre->text();


    QString apellido =ui->inApellido->text();


    QString telefono = ui->inTelefono->text();


    QString email = ui->inEmail->text();

    this->m_persona = new Persona(nombre,apellido,telefono,email);

    accept();
}


void PersonaDialog::on_buttonBox_rejected()
{
    reject();
}

Persona *PersonaDialog::persona() const
{
    return m_persona;
}

