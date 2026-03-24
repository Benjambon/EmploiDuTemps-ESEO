#include "supprimerecuedialog.h"
#include <QPushButton>

SupprimerEcueDialog::SupprimerEcueDialog(const std::vector<Ecue>& listeEcues, QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle("Supprimer un ECUE");
    this->init_components(listeEcues);
    this->init_layout();
    this->init_slots();
}

void SupprimerEcueDialog::init_components(const std::vector<Ecue>& listeEcues)
{
    this->comboEcues = new QComboBox(this);
    for (size_t i = 0; i < listeEcues.size(); ++i) {
        this->comboEcues->addItem(QString::fromStdString(listeEcues[i].to_string()), static_cast<int>(i));
    }

    this->buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    this->buttonBox->button(QDialogButtonBox::Ok)->setText("Supprimer");
}

void SupprimerEcueDialog::init_layout(void)
{
    this->layout = new QVBoxLayout(this);
    this->layout->addWidget(this->comboEcues);
    this->layout->addWidget(this->buttonBox);
}

void SupprimerEcueDialog::init_slots(void)
{
    connect(this->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(this->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

int SupprimerEcueDialog::getSelectedIndex(void) const
{
    return this->comboEcues->currentData().toInt();
}
