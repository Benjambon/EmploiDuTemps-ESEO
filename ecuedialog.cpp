#include "ecuedialog.h"

EcueDialog::EcueDialog(const std::vector<Enseignant>& listE, const std::vector<GroupeEtudiant>& listG, QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle("Ajouter un ECUE");
    this->init_components(listE, listG);
    this->init_layout();
    this->init_slots();
}

void EcueDialog::init_components(const std::vector<Enseignant>& listE, const std::vector<GroupeEtudiant>& listG)
{
    this->comboEnseignant = new QComboBox(this);
    for (size_t i = 0; i < listE.size(); ++i) {
        this->comboEnseignant->addItem(QString::fromStdString(listE[i].toString()), static_cast<int>(i));
    }

    this->comboGroupe = new QComboBox(this);
    for (size_t i = 0; i < listG.size(); ++i) {
        this->comboGroupe->addItem(QString::fromStdString(listG[i].toString()), static_cast<int>(i));
    }

    this->comboTypeCours = new QComboBox(this);
    this->comboTypeCours->addItem("CM", static_cast<int>(eTypeCours::CM));
    this->comboTypeCours->addItem("TD", static_cast<int>(eTypeCours::TD));
    this->comboTypeCours->addItem("TP Informatique", static_cast<int>(eTypeCours::TP_INFO));
    this->comboTypeCours->addItem("TP Electronique", static_cast<int>(eTypeCours::TP_ELEC));
    this->comboTypeCours->addItem("Examen Salle", static_cast<int>(eTypeCours::EXAMEN_EN_SALLE));
    this->comboTypeCours->addItem("Examen Info", static_cast<int>(eTypeCours::EXAMEN_INFO));
    this->comboTypeCours->addItem("Examen Elec", static_cast<int>(eTypeCours::EXAMEN_ELEC));

    this->spinHeureTotal = new QSpinBox(this);
    this->spinHeureTotal->setRange(1, 100);

    this->spinHeureRestante = new QSpinBox(this);
    this->spinHeureRestante->setRange(0, 100);

    this->buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
}

void EcueDialog::init_layout(void)
{
    this->formlayout = new QFormLayout(this);
    this->formlayout->addRow("Enseignant :", this->comboEnseignant);
    this->formlayout->addRow("Groupe :", this->comboGroupe);
    this->formlayout->addRow("Type de cours :", this->comboTypeCours);
    this->formlayout->addRow("Heures totales :", this->spinHeureTotal);
    this->formlayout->addRow("Heures restantes :", this->spinHeureRestante);
    this->formlayout->addRow(this->buttonBox);
}

void EcueDialog::init_slots(void)
{
    connect(this->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(this->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

int EcueDialog::getEnseignantIndex(void) const { return this->comboEnseignant->currentData().toInt(); }
int EcueDialog::getGroupeIndex(void) const { return this->comboGroupe->currentData().toInt(); }
eTypeCours EcueDialog::getTypeCours(void) const { return static_cast<eTypeCours>(this->comboTypeCours->currentData().toInt()); }
int EcueDialog::getHeureTotal(void) const { return this->spinHeureTotal->value(); }
int EcueDialog::getHeureRestante(void) const { return this->spinHeureRestante->value(); }
