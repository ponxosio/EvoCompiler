#ifndef MAINWINDOW_H
#define MAINWINDOW_H

# define VERSION 0.02

#include <QMainWindow>
#include <QFileDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QComboBox>

#include <ExecutionServer.h>
#include <ExecutionMachineServer.h>
#include <protocolGraph/ProtocolGraph.h>
#include <plugin/PythonEnvironment.h>

#include "communicationdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void exit();
    void execute();
    void test();
    void searchProtocol();
    void searchMachine();
    void setLogDir();
    void changeComInterface();
    void about();

private:
    Ui::MainWindow *ui;
    QLineEdit* protocolEdit;
    QLineEdit* machineEdit;
    //QLineEdit* logEdit;
    QPushButton* btnTest;
    QPushButton* btnExecute;
    QPushButton* comInterfaceBtn;

    QComboBox* protocolTypeCombo;
    std::string machineReference;

    void checkIfExecutionPossible();
};

#endif // MAINWINDOW_H
