#include "emploidutempsdialog.h"
#include <QHeaderView>

EmploiDuTempsDialog::EmploiDuTempsDialog(QString dataPath, QWidget *parent)
    : QWidget(parent), m_dataPath(dataPath)
{

    QDate dateDuJour = QDate::currentDate();
    int jourDeLaSemaine = dateDuJour.dayOfWeek();


    this->dateLundiCourant = dateDuJour.addDays(1 - jourDeLaSemaine);
    this->init_components();
    this->init_layout();
    this->init_slots();

    this->majAffichageSemaine();
}

void EmploiDuTempsDialog::init_components()
{

    this->btnSemainePrecedente = new QPushButton("< Précédent", this);
    this->labelSemaine = new QLabel("Semaine 1", this);
    this->labelSemaine->setAlignment(Qt::AlignCenter);
    this->btnSemaineSuivante = new QPushButton("Suivant >", this);

    this->tableCalendrier = new QTableWidget(5, 5, this);
    this->tableCalendrier->setHorizontalHeaderLabels({"Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi"});


    this->tableCalendrier->setVerticalHeaderLabels({"8h-10h", "10h-12h", "", "14h-16h", "16h-18h"});

    this->tableCalendrier->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->tableCalendrier->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->tableCalendrier->verticalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
    this->tableCalendrier->setRowHeight(2, 30);

    this->tableCalendrier->setSpan(2, 0, 1, 5);

    QTableWidgetItem* itemPause = new QTableWidgetItem("Pause Déjeuner");
    itemPause->setTextAlignment(Qt::AlignCenter);
    itemPause->setBackground(QBrush(QColor(230, 230, 230)));

    QFont font = itemPause->font();
    font.setItalic(true);
    itemPause->setFont(font);

    this->tableCalendrier->setItem(2, 0, itemPause);

    this->tableCalendrier->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void EmploiDuTempsDialog::init_layout()
{
    this->layoutPrincipal = new QVBoxLayout(this);

    this->layoutSemaine = new QHBoxLayout();
    this->layoutSemaine->addWidget(this->btnSemainePrecedente);
    this->layoutSemaine->addWidget(this->labelSemaine);
    this->layoutSemaine->addWidget(this->btnSemaineSuivante);

    this->layoutPrincipal->addLayout(this->layoutSemaine);
    this->layoutPrincipal->addWidget(this->tableCalendrier);
}

void EmploiDuTempsDialog::init_slots()
{
    connect(this->btnSemainePrecedente, &QPushButton::clicked, this, &EmploiDuTempsDialog::on_btnSemainePrecedente_clicked);
    connect(this->btnSemaineSuivante, &QPushButton::clicked, this, &EmploiDuTempsDialog::on_btnSemaineSuivante_clicked);
}

void EmploiDuTempsDialog::majAffichageSemaine()
{
    int weekNum = this->dateLundiCourant.weekNumber();
    this->labelSemaine->setText("Semaine " + QString::number(weekNum));

    QStringList headers;
    QString nomsJours[] = {"Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi"};

    for (int i = 0; i < 5; ++i) {
        QDate dateDuJour = this->dateLundiCourant.addDays(i);

        QString texteColonne = nomsJours[i] + " " + dateDuJour.toString("dd/MM");
        headers << texteColonne;
    }
    this->tableCalendrier->setHorizontalHeaderLabels(headers);

}

void EmploiDuTempsDialog::on_btnSemainePrecedente_clicked()
{
    this->dateLundiCourant = this->dateLundiCourant.addDays(-7);
    this->majAffichageSemaine();
}

void EmploiDuTempsDialog::on_btnSemaineSuivante_clicked()
{
    this->dateLundiCourant = this->dateLundiCourant.addDays(7);
    this->majAffichageSemaine();
}