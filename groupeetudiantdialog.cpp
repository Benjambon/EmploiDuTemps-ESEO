#include "groupeetudiantdialog.h"

GroupeEtudiantDialog::GroupeEtudiantDialog(QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle("Ajouter un groupe");
    this->init_components();
    this->init_layout();
    this->init_slots();
}

void GroupeEtudiantDialog::init_components(void)
{
    this->editNom = new QLineEdit(this);

    this->buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
}

void GroupeEtudiantDialog::init_layout(void)
{
    this->formlayout = new QFormLayout(this);
    this->formlayout->addRow("Nom du groupe :", this->editNom);
    this->formlayout->addRow(this->buttonBox);
}

void GroupeEtudiantDialog::init_slots(void)
{
    connect(this->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(this->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

std::string GroupeEtudiantDialog::getNom(void) const
{
    return this->editNom->text().toStdString();
}
