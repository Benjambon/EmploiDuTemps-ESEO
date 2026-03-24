#ifndef SUPPRIMERSALLEDIALOG_H
#define SUPPRIMERSALLEDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <vector>
#include "salle.h"
#include <QPushButton>

class SupprimerSalleDialog : public QDialog
{
    Q_OBJECT

private:
    QComboBox* comboSalles;
    QDialogButtonBox* buttonBox;
    QVBoxLayout* layout;

    void init_components(const std::vector<Salle>& listeSalles);
    void init_layout(void);
    void init_slots(void);

public:
    SupprimerSalleDialog(const std::vector<Salle>& listeSalles, QWidget *parent = nullptr);
    int getSelectedIndex(void) const;
};

#endif // SUPPRIMERSALLEDIALOG_H
