#ifndef EDITAR_H
#define EDITAR_H
#include <QRegExpValidator>
#include <QtCore>
#include <QtGui>
#define NOMBRE_RX "([a-zA-Z',.-]+( [a-zA-Z',.-]+)*){2,30}"

#define EMAIL_RX "([a-zA-Z'@.-]+( [a-zA-Z'.-]+)*){2,30}"

#define TELEFONO_RX "([0][1-9]{0,11})"
#include <QDialog>
#include "persona.h"
#include <QMessageBox>
#include "principal.h"
#include "ui_principal.h"
namespace Ui {
class Editar;
}

class Editar : public QDialog
{
    Q_OBJECT

public:
    explicit Editar(QWidget *parent = nullptr);
    ~Editar();
    Persona *persona() const;
private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    int m_u;
    int m_f;
    Ui::Editar *ui;
    Persona *m_persona;
};

#endif // EDITAR_H
