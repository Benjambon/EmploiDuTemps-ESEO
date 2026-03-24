#ifndef SUPPRIMERGROUPEETUDIANTDIALOG_H
#define SUPPRIMERGROUPEETUDIANTDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <vector>
#include "groupeetudiant.h"

class SupprimerGroupeEtudiantDialog : public QDialog
{
    Q_OBJECT

private:
    QComboBox* comboGroupes;
    QDialogButtonBox* buttonBox;
    QVBoxLayout* layout;

    void init_components(const std::vector<GroupeEtudiant>& listeGroupes);
    void init_layout(void);
    void init_slots(void);

public:
    SupprimerGroupeEtudiantDialog(const std::vector<GroupeEtudiant>& listeGroupes, QWidget *parent = nullptr);
    int getSelectedIndex(void) const;
};

#endif // SUPPRIMERGROUPEETUDIANTDIALOG_H
