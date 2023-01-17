#ifndef PERSONADIALOG_H
#define PERSONADIALOG_H

#include <QDialog>

#include "persona.h"
#include <QMessageBox>

namespace Ui {
class PersonaDialog;
}

class PersonaDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PersonaDialog(QWidget *parent = nullptr);
    ~PersonaDialog();
    Persona *persona() const;

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::PersonaDialog *ui;

    Persona *m_persona;
};

#endif // PERSONADIALOG_H
