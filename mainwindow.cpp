#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    protocolEdit = new QLineEdit();
    protocolEdit->setReadOnly(true);

    machineEdit = new QLineEdit();
    machineEdit->setReadOnly(true);

    logEdit = new QLineEdit();
    logEdit->setReadOnly(true);

    btnExecute = new QPushButton("execute");
    btnExecute->setEnabled(false);
    QPushButton* btnExeit = new QPushButton("exit");
    btnTest = new QPushButton("test");
    btnTest->setEnabled(false);
    QPushButton* btnOpenProtocol = new QPushButton("open protocol");
    QPushButton* btnOpenMachine = new QPushButton("open machine");
    QPushButton* btnLog = new QPushButton("set log directory");

    QGroupBox* boxFiles = new QGroupBox();
    QGridLayout* gridFiles = new QGridLayout();
    gridFiles->addWidget(protocolEdit, 0,0);
    gridFiles->addWidget(btnOpenProtocol, 0, 1);
    gridFiles->addWidget(machineEdit, 1,0);
    gridFiles->addWidget(btnOpenMachine, 1, 1);
    gridFiles->addWidget(logEdit, 2,0);
    gridFiles->addWidget(btnLog, 2, 1);
    boxFiles->setLayout(gridFiles);

    QGroupBox* boxBtns = new QGroupBox();
    QGridLayout* gridBtns = new QGridLayout();
    gridBtns->addWidget(btnExecute, 0, 0);
    gridBtns->addWidget(btnTest, 1, 0);
    gridBtns->addWidget(btnExeit, 2, 0);
    boxBtns->setLayout(gridBtns);

    QGridLayout* mainLayout = new QGridLayout();
    mainLayout->addWidget(boxFiles, 0, 0);
    mainLayout->addWidget(boxBtns, 0, 1);

    QWidget *window = new QWidget();
    window->setLayout(mainLayout);

    setCentralWidget(window);

    connect(btnExecute, SIGNAL(clicked(bool)), this, SLOT(execute()));
    connect(btnTest, SIGNAL(clicked(bool)), this, SLOT(test()));
    connect(btnExeit, SIGNAL(clicked(bool)), this, SLOT(exit()));
    connect(btnLog, SIGNAL(clicked(bool)), this, SLOT(setLogDir()));
    connect(btnOpenProtocol, SIGNAL(clicked(bool)), this, SLOT(searchProtocol()));
    connect(btnOpenMachine, SIGNAL(clicked(bool)), this, SLOT(searchMachine()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::exit() {
    this->close();
}

void MainWindow::execute() {
    std::shared_ptr<ProtocolGraph> bioBlocksprotocol = std::shared_ptr<ProtocolGraph>(BioBlocksJSONReader::GetInstance()->loadFile(protocolEdit->text().toUtf8().constData()));
    std::string reference = ExecutionServer::GetInstance()->addProtocolOnNewMachine(bioBlocksprotocol,
                                                                                    machineEdit->text().toUtf8().constData());
    ExecutionServer::GetInstance()->exec(reference);
}

void MainWindow::test() {
    std::shared_ptr<ProtocolGraph> bioBlocksprotocol = std::shared_ptr<ProtocolGraph>(BioBlocksJSONReader::GetInstance()->loadFile(protocolEdit->text().toUtf8().constData()));
    std::string reference = ExecutionServer::GetInstance()->addProtocolOnNewMachine(bioBlocksprotocol,
                                                                                    machineEdit->text().toUtf8().constData());
    ExecutionServer::GetInstance()->test(reference);
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
        checkIfExecutionPossible();
    }
}

void MainWindow::setLogDir() {
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), QString(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (!dir.isEmpty()) {
        logEdit->setText(dir);
        checkIfExecutionPossible();
    }
}

void MainWindow::checkIfExecutionPossible() {
    if (!logEdit->text().isEmpty() &&
            !protocolEdit->text().isEmpty() &&
            !machineEdit->text().isEmpty())
    {
        btnTest->setEnabled(true);
        btnExecute->setEnabled(true);
    }
}

