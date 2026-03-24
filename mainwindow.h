#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
};
#endif // MAINWINDOW_Hx
