#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include <QDialog>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QMessageBox>
#include <QComboBox>
#include <vector>
#include "enseignant.h"
#include "groupeetudiant.h"
#include "salle.h"
#include "controleur_salle.h"
#include "controleur_groupeetudiant.h"
#include "controleur_enseignant.h"
#include "controleur_ecue.h"
#include <QGroupBox>
#include <QGroupBox>
#include <QTabWidget>
#include <QIcon>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QString dataPath, QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_btnAjouterEnseignant_clicked();
    void on_btnAfficherEnseignants_clicked();
    void on_btnSupprimerEnseignant_clicked();

    void on_btnAjouterGroupe_clicked();
    void on_btnAfficherGroupes_clicked();
    void on_btnSupprimerGroupe_clicked();

    void on_btnAjouterSalle_clicked();
    void on_btnAfficherSalles_clicked();
    void on_btnSupprimerSalle_clicked();

    void on_btnAjouterEcue_clicked();
    void on_btnSupprimerEcue_clicked();
    void on_btnAfficherEcues_clicked();

private:
    Ui::MainWindow *ui;
    QString m_dataPath;
    void init_style(void);
    void init_layout(void);
};
#endif // MAINWINDOW_Hx
