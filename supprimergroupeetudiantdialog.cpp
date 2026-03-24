#include "supprimergroupeetudiantdialog.h"
#include <QPushButton>

SupprimerGroupeEtudiantDialog::SupprimerGroupeEtudiantDialog(const std::vector<GroupeEtudiant>& listeGroupes, QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle("Supprimer un groupe");
    this->init_components(listeGroupes);
    this->init_layout();
    this->init_slots();
}

void SupprimerGroupeEtudiantDialog::init_components(const std::vector<GroupeEtudiant>& listeGroupes)
{
    this->comboGroupes = new QComboBox(this);

    for (size_t i = 0; i < listeGroupes.size(); ++i) {
        this->comboGroupes->addItem(QString::fromStdString(listeGroupes[i].toString()), static_cast<int>(i));
    }

    this->buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    this->buttonBox->button(QDialogButtonBox::Ok)->setText("Supprimer");
}

void SupprimerGroupeEtudiantDialog::init_layout(void)
{
    this->layout = new QVBoxLayout(this);
    this->layout->addWidget(this->comboGroupes);
    this->layout->addWidget(this->buttonBox);
}

void SupprimerGroupeEtudiantDialog::init_slots(void)
{
    connect(this->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(this->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

int SupprimerGroupeEtudiantDialog::getSelectedIndex(void) const
{
    return this->comboGroupes->currentData().toInt();
}
