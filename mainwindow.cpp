#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    PythonEnvironment::GetInstance()->initEnvironment();

    ui->setupUi(this);

    protocolEdit = new QLineEdit();
    protocolEdit->setReadOnly(true);

    machineEdit = new QLineEdit();
    machineEdit->setReadOnly(true);

    timeSliceEdit = new QLineEdit();

    /*logEdit = new QLineEdit();
    logEdit->setReadOnly(true);*/

    btnExecute = new QPushButton("execute");
    btnExecute->setEnabled(false);
    QPushButton* btnExeit = new QPushButton("exit");
    btnTest = new QPushButton("test");
    btnTest->setEnabled(false);
    QPushButton* btnOpenProtocol = new QPushButton("open protocol");
    QPushButton* btnOpenMachine = new QPushButton("open machine");
    comInterfaceBtn = new QPushButton("Change communications Interface");
    comInterfaceBtn->setEnabled(false);
    QPushButton* btnAbout = new QPushButton("About");

    protocolTypeCombo = new QComboBox(this);
    protocolTypeCombo->addItem("EvoCoder");
    protocolTypeCombo->addItem("BioBlocks");
    protocolTypeCombo->setCurrentIndex(1);

    QGroupBox* boxFiles = new QGroupBox();
    QGridLayout* gridFiles = new QGridLayout();
    gridFiles->addWidget(new QLabel("time step(ms:)"), 0, 0);
    gridFiles->addWidget(timeSliceEdit, 0, 1);
    gridFiles->addWidget(protocolEdit, 1,0);
    gridFiles->addWidget(btnOpenProtocol, 1, 1);
    gridFiles->addWidget(protocolTypeCombo, 1, 2);
    gridFiles->addWidget(machineEdit, 2,0);
    gridFiles->addWidget(btnOpenMachine, 2, 1);
    boxFiles->setLayout(gridFiles);

    QGroupBox* boxBtns = new QGroupBox();
    QGridLayout* gridBtns = new QGridLayout();
    gridBtns->addWidget(btnExecute, 0, 0);
    gridBtns->addWidget(btnTest, 1, 0);
    gridBtns->addWidget(comInterfaceBtn, 2, 0);
    gridBtns->addWidget(btnAbout, 3, 0);
    gridBtns->addWidget(btnExeit, 4, 0);
    boxBtns->setLayout(gridBtns);

    QGridLayout* mainLayout = new QGridLayout();
    mainLayout->addWidget(boxFiles, 0, 0);
    mainLayout->addWidget(boxBtns, 0, 1);

    QWidget *window = new QWidget();
    window->setLayout(mainLayout);
    window->setMinimumWidth(600);

    setCentralWidget(window);

    connect(btnExecute, SIGNAL(clicked(bool)), this, SLOT(execute()));
    connect(btnTest, SIGNAL(clicked(bool)), this, SLOT(test()));
    connect(comInterfaceBtn, SIGNAL(clicked(bool)), this, SLOT(changeComInterface()));
    connect(btnExeit, SIGNAL(clicked(bool)), this, SLOT(exit()));
    connect(btnAbout, SIGNAL(clicked(bool)), this, SLOT(about()));
    connect(btnOpenProtocol, SIGNAL(clicked(bool)), this, SLOT(searchProtocol()));
    connect(btnOpenMachine, SIGNAL(clicked(bool)), this, SLOT(searchMachine()));
}

MainWindow::~MainWindow()
{
    PythonEnvironment::GetInstance()->finishEnvironment();
    delete ui;
}

void MainWindow::about() {
    QMessageBox::about(this, "About", "EvoCompiler version v" + QString::number(VERSION));
}

void MainWindow::exit() {
    this->close();
}

void MainWindow::execute() {
    try {
        std::string reference;
        if (protocolTypeCombo->currentIndex() == 0) {
            reference = ExecutionServer::GetInstance()->addProtocolOnExistingMachine(protocolEdit->text().toUtf8().constData(),
                                                                                machineReference);
        } else if (protocolTypeCombo->currentIndex() == 1) {
            reference = ExecutionServer::GetInstance()->addBioBlocksProtocolOnExistingMachine(protocolEdit->text().toUtf8().constData(),
                                                                                machineReference, timeSliceEdit->text().toLong());
            ExecutionServer::GetInstance()->getEvoCoder(reference)->printProtocol("bioblocksGraph.graph");
        }
        ExecutionServer::GetInstance()->exec(reference);

        QMessageBox::information(this, "corret execution", "protocol executed correctly");
    } catch (exception &e) {
        QMessageBox::critical(this, "error", "exception: "  + QString::fromStdString(e.what()));
    }
}

void MainWindow::test() {
    try{
        std::string reference;
        if (protocolTypeCombo->currentIndex() == 0) {
            reference = ExecutionServer::GetInstance()->addProtocolOnExistingMachine(protocolEdit->text().toUtf8().constData(),
                                                                                machineReference);
        } else if (protocolTypeCombo->currentIndex() == 1) {
            reference = ExecutionServer::GetInstance()->addBioBlocksProtocolOnExistingMachine(protocolEdit->text().toUtf8().constData(),
                                                                                machineReference, timeSliceEdit->text().toLong());
             ExecutionServer::GetInstance()->getEvoCoder(reference)->printProtocol("bioblocksGraph.graph");
        }
        ExecutionServer::GetInstance()->test(reference);

        QMessageBox::information(this, "corret execution", "protocol executed correctly");
    } catch (exception &e) {
        QMessageBox::critical(this, "error", "exception: "  + QString::fromStdString(e.what()));
    }
}

void MainWindow::changeComInterface() {
    CommunicationDialog dialog(machineReference, this);
    dialog.exec();
}

void MainWindow::searchProtocol() {
    QString path = QFileDialog::getOpenFileName(this, "select protocol to open", QString(), tr("JSON (*.json)"));
    if (!path.isEmpty()) {
        protocolEdit->setText(path);
        checkIfExecutionPossible();
    }
}

void MainWindow::searchMachine() {
    QString path = QFileDialog::getOpenFileName(this, "select machine to open", QString(), tr("JSON (*.json)"));
    if (!path.isEmpty()) {
        machineEdit->setText(path);
        machineReference = ExecutionMachineServer::GetInstance()->addNewMachine(path.toUtf8().constData());
        comInterfaceBtn->setEnabled(true);
        checkIfExecutionPossible();
    }
}

void MainWindow::setLogDir() {
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), QString(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (!dir.isEmpty()) {
        //logEdit->setText(dir);
        checkIfExecutionPossible();
    }
}

void MainWindow::checkIfExecutionPossible() {
    if (/*!logEdit->text().isEmpty() &&*/
            !protocolEdit->text().isEmpty() &&
            !machineEdit->text().isEmpty())
    {
        btnTest->setEnabled(true);
        btnExecute->setEnabled(true);
    }
}

