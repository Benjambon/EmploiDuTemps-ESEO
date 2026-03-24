#ifndef SALLEDIALOG_H
#define SALLEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QFormLayout>
#include "salle.h"

class SalleDialog : public QDialog
{
    Q_OBJECT

private:
    QLineEdit* editNumero;
    QComboBox* comboType;
    QDialogButtonBox* buttonBox;
    QFormLayout* formlayout;

    void init_components(void);
    void init_layout(void);
    void init_slots(void);

public:
    SalleDialog(QWidget *parent = nullptr);

    std::string getNumero(void) const;
    TypeSalle getTypeSalle(void) const;
};

#endif // SALLEDIALOG_H
