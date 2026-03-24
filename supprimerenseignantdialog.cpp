#include "supprimerenseignantdialog.h"
#include <QPushButton>

SupprimerEnseignantDialog::SupprimerEnseignantDialog(const std::vector<Enseignant>& listeEnseignants, QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle("Supprimer un enseignant");
    this->init_components(listeEnseignants);
    this->init_layout();
    this->init_slots();
}

void SupprimerEnseignantDialog::init_components(const std::vector<Enseignant>& listeEnseignants)
{
    this->comboEnseignants = new QComboBox(this);

    for (size_t i = 0; i < listeEnseignants.size(); ++i) {
        this->comboEnseignants->addItem(QString::fromStdString(listeEnseignants[i].toString()), static_cast<int>(i));
    }

    this->buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    this->buttonBox->button(QDialogButtonBox::Ok)->setText("Supprimer");
}

void SupprimerEnseignantDialog::init_layout(void)
{
    this->layout = new QVBoxLayout(this);
    this->layout->addWidget(this->comboEnseignants);
    this->layout->addWidget(this->buttonBox);
}

void SupprimerEnseignantDialog::init_slots(void)
{
    connect(this->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(this->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

int SupprimerEnseignantDialog::getSelectedIndex(void) const
{
    return this->comboEnseignants->currentData().toInt();
}
