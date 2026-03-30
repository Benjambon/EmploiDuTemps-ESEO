#include "creneaudialog.h"

CreneauDialog::CreneauDialog(const std::vector<Ecue>& listeE, const std::vector<Salle>& listeS, QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle("Ajouter un Créneau");
    this->init_components(listeE, listeS);
    this->init_layout();
    this->init_slots();
}

void CreneauDialog::init_components(const std::vector<Ecue>& listeE, const std::vector<Salle>& listeS)
{
    this->editDate = new QDateEdit(QDate::currentDate(), this);
    this->editDate->setCalendarPopup(true);

    this->comboHoraire = new QComboBox(this);
    this->comboHoraire->addItem("Matin 1 (8h-10h)", eHoraire::MATIN1);
    this->comboHoraire->addItem("Matin 2 (10h-12h)", eHoraire::MATIN2);
    this->comboHoraire->addItem("Après-midi 1 (14h-16h)", eHoraire::APRESMIDI1);
    this->comboHoraire->addItem("Après-midi 2 (16h-18h)", eHoraire::APRESMIDI2);

    this->comboEcue = new QComboBox(this);
    for (size_t i = 0; i < listeE.size(); ++i) {
        this->comboEcue->addItem(QString::fromStdString(listeE[i].to_string()), static_cast<int>(i));
    }

    this->comboTypeCours = new QComboBox(this);
    this->comboTypeCours->addItem("CM", static_cast<int>(eTypeCours::CM));
    this->comboTypeCours->addItem("TD", static_cast<int>(eTypeCours::TD));
    this->comboTypeCours->addItem("TP Info", static_cast<int>(eTypeCours::TP_INFO));
    this->comboTypeCours->addItem("TP Elec", static_cast<int>(eTypeCours::TP_ELEC));
    this->comboTypeCours->addItem("Exam Salle", static_cast<int>(eTypeCours::EXAMEN_EN_SALLE));
    this->comboTypeCours->addItem("Exam Info", static_cast<int>(eTypeCours::EXAMEN_INFO));
    this->comboTypeCours->addItem("Exam Elec", static_cast<int>(eTypeCours::EXAMEN_ELEC));

    this->comboSalle = new QComboBox(this);
    for (size_t i = 0; i < listeS.size(); ++i) {
        this->comboSalle->addItem(QString::fromStdString(listeS[i].toString()), static_cast<int>(i));
    }

    this->buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
}

void CreneauDialog::init_layout(void)
{
    this->formlayout = new QFormLayout(this);
    this->formlayout->addRow("Date :", this->editDate);
    this->formlayout->addRow("Horaire :", this->comboHoraire);
    this->formlayout->addRow("ECUE :", this->comboEcue);
    this->formlayout->addRow("Type de cours :", this->comboTypeCours);
    this->formlayout->addRow("Salle :", this->comboSalle);
    this->formlayout->addRow(this->buttonBox);
}

void CreneauDialog::init_slots(void)
{
    connect(this->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(this->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

QDate CreneauDialog::getDate(void) const { return this->editDate->date(); }
eHoraire CreneauDialog::getHoraire(void) const { return static_cast<eHoraire>(this->comboHoraire->currentData().toInt()); }
int CreneauDialog::getEcueIndex(void) const { return this->comboEcue->currentData().toInt(); }
eTypeCours CreneauDialog::getTypeCours(void) const { return static_cast<eTypeCours>(this->comboTypeCours->currentData().toInt()); }
int CreneauDialog::getSalleIndex(void) const { return this->comboSalle->currentData().toInt(); }
