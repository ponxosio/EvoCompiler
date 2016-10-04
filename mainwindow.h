#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QGroupBox>

#include <ExecutionServer.h>
#include <BioBlocksJSONReader.h>
#include <protocolGraph/ProtocolGraph.h>

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

private:
    Ui::MainWindow *ui;
    QLineEdit* protocolEdit;
    QLineEdit* machineEdit;
    QLineEdit* logEdit;
    QPushButton* btnTest;
    QPushButton* btnExecute;

    void checkIfExecutionPossible();
};

#endif // MAINWINDOW_H
