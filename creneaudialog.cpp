#include "creneaudialog.h"

CreneauDialog::CreneauDialog(const std::vector<Ecue>& listeE, const std::vector<Salle>& listeS, QWidget *parent)
    : QDialog(parent), m_listeE(listeE)
{
    this->setWindowTitle("Ajouter un Créneau");
    this->init_components(listeE, listeS);
    this->init_layout();
    this->init_slots();

    if (!m_listeE.empty()) {
        this->updateTypeCoursCombo(0);
    }
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

    connect(this->comboEcue, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CreneauDialog::on_comboEcue_currentIndexChanged);
}

void CreneauDialog::updateTypeCoursCombo(int ecueIndex)
{
    this->comboTypeCours->clear();

    if (ecueIndex >= 0 && static_cast<size_t>(ecueIndex) < m_listeE.size()) {
        Ecue ecueSelectionne = m_listeE[ecueIndex];
        std::map<eTypeCours, int> heures = ecueSelectionne.getHeuresTotales();

        for (const auto& pair : heures) {
            if (pair.second > 0) {
                QString nomType = Ecue::typeCoursToString(pair.first);
                this->comboTypeCours->addItem(nomType, static_cast<int>(pair.first));
            }
        }
    }
}

void CreneauDialog::on_comboEcue_currentIndexChanged(int index)
{
    this->updateTypeCoursCombo(index);
}

QDate CreneauDialog::getDate(void) const { return this->editDate->date(); }
eHoraire CreneauDialog::getHoraire(void) const { return static_cast<eHoraire>(this->comboHoraire->currentData().toInt()); }
int CreneauDialog::getEcueIndex(void) const { return this->comboEcue->currentData().toInt(); }
eTypeCours CreneauDialog::getTypeCours(void) const {
    if (this->comboTypeCours->currentIndex() == -1) return eTypeCours::DEFAULT;
    return static_cast<eTypeCours>(this->comboTypeCours->currentData().toInt());
}
int CreneauDialog::getSalleIndex(void) const { return this->comboSalle->currentData().toInt(); }
