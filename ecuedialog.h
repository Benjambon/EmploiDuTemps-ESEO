#ifndef ECUEDIALOG_H
#define ECUEDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QSpinBox>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <vector>
#include "enseignant.h"
#include "groupeetudiant.h"
#include "ecue.h"

class EcueDialog : public QDialog
{
    Q_OBJECT

private:
    QComboBox* comboEnseignant;
    QComboBox* comboGroupe;
    QComboBox* comboTypeCours;
    QSpinBox* spinHeureTotal;
    QSpinBox* spinHeureRestante;
    QDialogButtonBox* buttonBox;
    QFormLayout* formlayout;

    void init_components(const std::vector<Enseignant>& listE, const std::vector<GroupeEtudiant>& listG);
    void init_layout(void);
    void init_slots(void);

public:
    EcueDialog(const std::vector<Enseignant>& listE, const std::vector<GroupeEtudiant>& listG, QWidget *parent = nullptr);

    int getEnseignantIndex(void) const;
    int getGroupeIndex(void) const;
    eTypeCours getTypeCours(void) const;
    int getHeureTotal(void) const;
    int getHeureRestante(void) const;
};

#endif // ECUEDIALOG_H
