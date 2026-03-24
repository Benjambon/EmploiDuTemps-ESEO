#include "salledialog.h"

SalleDialog::SalleDialog(QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle("Ajouter une salle");
    this->init_components();
    this->init_layout();
    this->init_slots();
}

void SalleDialog::init_components(void)
{
    this->editNumero = new QLineEdit(this);
    this->editNumero->setPlaceholderText("entre 000 et 999");

    this->comboType = new QComboBox(this);
    this->comboType->addItem("Salle standard", TypeSalle::SALLE);
    this->comboType->addItem("Electronique", TypeSalle::ELECTRONIQUE);
    this->comboType->addItem("Informatique", TypeSalle::INFORMATIQUE);

    this->buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
}

void SalleDialog::init_layout(void)
{
    this->formlayout = new QFormLayout(this);
    this->formlayout->addRow("Numéro de salle :", this->editNumero);
    this->formlayout->addRow("Type de salle :", this->comboType);
    this->formlayout->addRow(this->buttonBox);
}

void SalleDialog::init_slots(void)
{
    connect(this->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(this->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

std::string SalleDialog::getNumero(void) const
{
    return this->editNumero->text().toStdString();
}

TypeSalle SalleDialog::getTypeSalle(void) const
{
    return static_cast<TypeSalle>(this->comboType->currentData().toInt());
}
