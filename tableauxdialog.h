#ifndef TABLEAUXDIALOG_H
#define TABLEAUXDIALOG_H

#include <QWidget>
#include <QTableWidget>
#include <QRadioButton>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <vector>
#include "enseignant.h"
#include "groupeetudiant.h"
#include "ecue.h"
#include "creneau.h"

class TableauxDialog : public QWidget
{
    Q_OBJECT

private:
    QString m_dataPath;

    QRadioButton* radioGroupe;
    QRadioButton* radioEnseignant;
    QComboBox* comboSelection;
    QTableWidget* tableEcues;

    std::vector<Enseignant> listeEnseignants;
    std::vector<GroupeEtudiant> listeGroupes;
    std::vector<Ecue> listeEcues;
    std::vector<Creneau> listeCreneaux;

    void init_components();
    void init_layout();
    void init_slots();
    void chargerDonnees();
    void majTableau();

public:
    explicit TableauxDialog(QString dataPath, QWidget *parent = nullptr);
    void rafraichir();

private slots:
    void on_radio_toggled();
    void on_comboSelection_currentIndexChanged(int index);
};

#endif // TABLEAUXDIALOG_H
