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
    this->editNom = new QLineEdit(this);
    this->editNom->setPlaceholderText("ex: Mathématiques");

    this->comboEnseignant = new QComboBox(this);
    for (size_t i = 0; i < listE.size(); ++i) {
        this->comboEnseignant->addItem(QString::fromStdString(listE[i].toString()), static_cast<int>(i));
    }

    this->comboGroupe = new QComboBox(this);
    for (size_t i = 0; i < listG.size(); ++i) {
        this->comboGroupe->addItem(QString::fromStdString(listG[i].toString()), static_cast<int>(i));
    }

    eTypeCours types[] = { eTypeCours::CM, eTypeCours::TD, eTypeCours::TP_INFO, eTypeCours::TP_ELEC, eTypeCours::EXAMEN_EN_SALLE, eTypeCours::EXAMEN_INFO, eTypeCours::EXAMEN_ELEC };

    for (eTypeCours type : types) {
        QSpinBox* spin = new QSpinBox(this);
        spin->setRange(0, 100);
        spin->setSingleStep(2); // Les flèches feront sauter les valeurs de 2 en 2
        this->mapSpins[type] = spin;
    }

    this->buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
}

void EcueDialog::init_layout(void)
{
    this->formlayout = new QFormLayout(this);
    this->formlayout->addRow("Nom de l'ECUE :", this->editNom);
    this->formlayout->addRow("Enseignant :", this->comboEnseignant);
    this->formlayout->addRow("Groupe :", this->comboGroupe);

    QLabel* labelSep = new QLabel("<b>Heures à programmer :</b>", this);
    this->formlayout->addRow(labelSep);

    this->formlayout->addRow("CM :", this->mapSpins[eTypeCours::CM]);
    this->formlayout->addRow("TD :", this->mapSpins[eTypeCours::TD]);
    this->formlayout->addRow("TP Info :", this->mapSpins[eTypeCours::TP_INFO]);
    this->formlayout->addRow("TP Elec :", this->mapSpins[eTypeCours::TP_ELEC]);
    this->formlayout->addRow("Exam Salle :", this->mapSpins[eTypeCours::EXAMEN_EN_SALLE]);
    this->formlayout->addRow("Exam Info :", this->mapSpins[eTypeCours::EXAMEN_INFO]);
    this->formlayout->addRow("Exam Elec :", this->mapSpins[eTypeCours::EXAMEN_ELEC]);

    this->formlayout->addRow(this->buttonBox);
}

void EcueDialog::init_slots(void)
{
    connect(this->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(this->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

std::string EcueDialog::getNom(void) const { return this->editNom->text().toStdString(); }
int EcueDialog::getEnseignantIndex(void) const { return this->comboEnseignant->currentData().toInt(); }
int EcueDialog::getGroupeIndex(void) const { return this->comboGroupe->currentData().toInt(); }

std::map<eTypeCours, int> EcueDialog::getHeuresChoisies(void) const
{
    std::map<eTypeCours, int> heures;
    // On ne récupère que les types de cours où l'utilisateur a mis des heures > 0
    for (auto const& pair : mapSpins) {
        if (pair.second->value() > 0) {
            heures[pair.first] = pair.second->value();
        }
    }
    return heures;
}
