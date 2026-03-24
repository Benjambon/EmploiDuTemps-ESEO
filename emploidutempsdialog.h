#ifndef EMPLOIDUTEMPSDIALOG_H
#define EMPLOIDUTEMPSDIALOG_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDate>
#include <QRadioButton>
#include <QComboBox>
#include <vector>
#include "enseignant.h"
#include "groupeetudiant.h"

class EmploiDuTempsDialog : public QWidget
{
    Q_OBJECT

private:
    QString m_dataPath;
    QDate dateLundiCourant;

    QRadioButton* radioGroupe;
    QRadioButton* radioEnseignant;
    QComboBox* comboSelection;

    QPushButton* btnSemainePrecedente;
    QLabel* labelSemaine;
    QPushButton* btnSemaineSuivante;

    QTableWidget* tableCalendrier;

    QVBoxLayout* layoutPrincipal;
    QHBoxLayout* layoutSelection;
    QHBoxLayout* layoutSemaine;

    std::vector<Enseignant> listeEnseignants;
    std::vector<GroupeEtudiant> listeGroupes;

    void init_components();
    void init_layout();
    void init_slots();
    void majAffichageSemaine();
    void chargerDonnees();

public:
    explicit EmploiDuTempsDialog(QString dataPath, QWidget *parent = nullptr);

private slots:
    void on_btnSemainePrecedente_clicked();
    void on_btnSemaineSuivante_clicked();
    void on_radio_toggled();
    void on_comboSelection_currentIndexChanged(int index);
};

#endif // EMPLOIDUTEMPSDIALOG_H