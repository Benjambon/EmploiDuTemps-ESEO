#include "supprimercreneaudialog.h"

SupprimerCreneauDialog::SupprimerCreneauDialog(const std::vector<Creneau>& listeCreneaux, QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle("Supprimer un créneau");
    this->init_components(listeCreneaux);
    this->init_layout();
    this->init_slots();
}

void SupprimerCreneauDialog::init_components(const std::vector<Creneau>& listeCreneaux)
{
    this->comboCreneaux = new QComboBox(this);
    for (size_t i = 0; i < listeCreneaux.size(); ++i) {
        this->comboCreneaux->addItem(QString::fromStdString(listeCreneaux[i].to_string()), static_cast<int>(i));
    }

    this->buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    this->buttonBox->button(QDialogButtonBox::Ok)->setText("Supprimer");
}

void SupprimerCreneauDialog::init_layout(void)
{
    this->layout = new QVBoxLayout(this);
    this->layout->addWidget(this->comboCreneaux);
    this->layout->addWidget(this->buttonBox);
}

void SupprimerCreneauDialog::init_slots(void)
{
    connect(this->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(this->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

int SupprimerCreneauDialog::getSelectedIndex(void) const
{
    return this->comboCreneaux->currentData().toInt();
}
