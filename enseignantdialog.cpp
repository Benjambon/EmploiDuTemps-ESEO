#include "enseignantdialog.h"

EnseignantDialog::EnseignantDialog(QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle("Ajouter un enseignant");
    this->init_components();
    this->init_layout();
    this->init_slots();
}

void EnseignantDialog::init_components(void)
{
    this->editNom = new QLineEdit(this);
    this->editPrenom = new QLineEdit(this);

    this->editMail = new QLineEdit(this);
    this->editMail->setPlaceholderText("Optionnel");

    this->buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
}

void EnseignantDialog::init_layout(void)
{
    this->formlayout = new QFormLayout(this);
    this->formlayout->addRow("Nom :", this->editNom);
    this->formlayout->addRow("Prénom :", this->editPrenom);
    this->formlayout->addRow("Mail :", this->editMail);
    this->formlayout->addRow(this->buttonBox);
}

void EnseignantDialog::init_slots(void)
{
    connect(this->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(this->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

std::string EnseignantDialog::getNom(void) const
{
    return this->editNom->text().toStdString();
}

std::string EnseignantDialog::getPrenom(void) const
{
    return this->editPrenom->text().toStdString();
}

std::string EnseignantDialog::getMail(void) const
{
    return this->editMail->text().toStdString();
}
