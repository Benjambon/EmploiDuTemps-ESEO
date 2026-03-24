#include "supprimersalledialog.h"

SupprimerSalleDialog::SupprimerSalleDialog(const std::vector<Salle>& listeSalles, QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle("Supprimer une salle");
    this->init_components(listeSalles);
    this->init_layout();
    this->init_slots();
}

void SupprimerSalleDialog::init_components(const std::vector<Salle>& listeSalles)
{
    this->comboSalles = new QComboBox(this);

    for (size_t i = 0; i < listeSalles.size(); ++i) {
        this->comboSalles->addItem(QString::fromStdString(listeSalles[i].toString()), static_cast<int>(i));
    }

    this->buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    this->buttonBox->button(QDialogButtonBox::Ok)->setText("Supprimer");
}

void SupprimerSalleDialog::init_layout(void)
{
    this->layout = new QVBoxLayout(this);
    this->layout->addWidget(this->comboSalles);
    this->layout->addWidget(this->buttonBox);
}

void SupprimerSalleDialog::init_slots(void)
{
    connect(this->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(this->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

int SupprimerSalleDialog::getSelectedIndex(void) const
{
    return this->comboSalles->currentData().toInt();
}
