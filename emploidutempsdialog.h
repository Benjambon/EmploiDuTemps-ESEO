#ifndef EMPLOIDUTEMPSDIALOG_H
#define EMPLOIDUTEMPSDIALOG_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDate>

class EmploiDuTempsDialog : public QWidget
{
    Q_OBJECT

private:
    QString m_dataPath;
    QDate dateLundiCourant;

    QPushButton* btnSemainePrecedente;
    QLabel* labelSemaine;
    QPushButton* btnSemaineSuivante;

    QTableWidget* tableCalendrier;

    QVBoxLayout* layoutPrincipal;
    QHBoxLayout* layoutSemaine;

    void init_components();
    void init_layout();
    void init_slots();
    void majAffichageSemaine();

public:
    explicit EmploiDuTempsDialog(QString dataPath, QWidget *parent = nullptr);

private slots:
    void on_btnSemainePrecedente_clicked();
    void on_btnSemaineSuivante_clicked();
};

#endif // EMPLOIDUTEMPSDIALOG_H