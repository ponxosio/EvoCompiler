#ifndef COMMUNICATIONDIALOG_H
#define COMMUNICATIONDIALOG_H

#include <QObject>
#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QHash>
#include <QString>
#include <QGroupBox>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>

#include <ExecutionMachineServer.h>
#include <fluidControl/executable/containers/actuators/communications/FileSender.h>
#include <fluidControl/executable/containers/actuators/communications/SerialSender.h>
#include <fluidControl/executable/containers/actuators/communications/CommunicationsInterface.h>
#include <fluidControl/executable/containers/actuators/communications/CommandSender.h>

class CommunicationDialog : public QDialog
{
    Q_OBJECT

public:
    CommunicationDialog(const std::string & machineReference, QWidget* parent = 0, Qt::WindowFlags f = 0);
    virtual ~CommunicationDialog();

public slots:
    void searchOutFile();
    void searchInFile();
    void ok();
    void cancel();

protected:
    std::string machineReference;

    QLineEdit* portEdit;
    QComboBox* comboBaud;
    QPushButton* createBtn;
    QHash<QString, int> boudMap;
    QLineEdit* outEdit;
    QLineEdit* inEdit;

    void checkSetCreateBtn();
    void createComboBaud();
};

#endif // COMMUNICATIONDIALOG_H
