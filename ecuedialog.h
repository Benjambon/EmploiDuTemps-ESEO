#ifndef ECUEDIALOG_H
#define ECUEDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLabel>
#include <vector>
#include <map>
#include "enseignant.h"
#include "groupeetudiant.h"
#include "ecue.h"

class EcueDialog : public QDialog
{
    Q_OBJECT

private:
    QLineEdit* editNom;
    QComboBox* comboEnseignant;
    QComboBox* comboGroupe;
    std::map<eTypeCours, QSpinBox*> mapSpins;
    QDialogButtonBox* buttonBox;
    QFormLayout* formlayout;

    void init_components(const std::vector<Enseignant>& listE, const std::vector<GroupeEtudiant>& listG);
    void init_layout(void);
    void init_slots(void);

public:
    EcueDialog(const std::vector<Enseignant>& listE, const std::vector<GroupeEtudiant>& listG, QWidget *parent = nullptr);

    std::string getNom(void) const;
    int getEnseignantIndex(void) const;
    int getGroupeIndex(void) const;
    std::map<eTypeCours, int> getHeuresChoisies(void) const;
};

#endif // ECUEDIALOG_H
