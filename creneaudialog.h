#ifndef CRENEAUDIALOG_H
#define CRENEAUDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QDateEdit>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <vector>
#include "ecue.h"
#include "salle.h"
#include "creneau.h"

class CreneauDialog : public QDialog
{
    Q_OBJECT

private:
    QDateEdit* editDate;
    QComboBox* comboHoraire;
    QComboBox* comboEcue;
    QComboBox* comboTypeCours;
    QComboBox* comboSalle;
    QDialogButtonBox* buttonBox;
    QFormLayout* formlayout;

    std::vector<Ecue> m_listeE;

    void init_components(const std::vector<Ecue>& listeE, const std::vector<Salle>& listeS);
    void init_layout(void);
    void init_slots(void);
    void updateTypeCoursCombo(int ecueIndex);

private slots:
    void on_comboEcue_currentIndexChanged(int index);

public:
    CreneauDialog(const std::vector<Ecue>& listeE, const std::vector<Salle>& listeS, QWidget *parent = nullptr);

    QDate getDate(void) const;
    eHoraire getHoraire(void) const;
    int getEcueIndex(void) const;
    eTypeCours getTypeCours(void) const;
    int getSalleIndex(void) const;
};

#endif // CRENEAUDIALOG_H
