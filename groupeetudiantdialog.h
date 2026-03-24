#ifndef GROUPEETUDIANTDIALOG_H
#define GROUPEETUDIANTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <string>

class GroupeEtudiantDialog : public QDialog
{
    Q_OBJECT

private:
    QLineEdit* editNom;
    QDialogButtonBox* buttonBox;
    QFormLayout* formlayout;

    void init_components(void);
    void init_layout(void);
    void init_slots(void);

public:
    GroupeEtudiantDialog(QWidget *parent = nullptr);

    std::string getNom(void) const;
};

#endif // GROUPEETUDIANTDIALOG_H
