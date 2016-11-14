#include "communicationdialog.h"

CommunicationDialog::CommunicationDialog(const std::string & machineReference, QWidget* parent, Qt::WindowFlags f) :
    QDialog(parent, f)
{
    this->machineReference = std::string(machineReference);

    createBtn = new QPushButton("create");
    QPushButton* cancelBtn = new QPushButton("cancel");
    QPushButton* searchInFileBtn = new QPushButton("search in file");
    QPushButton* searchOutFileBtn = new QPushButton("search out file");

    portEdit = new QLineEdit();
    comboBaud = new QComboBox();
    createComboBaud();

    inEdit = new QLineEdit();
    inEdit->setReadOnly(true);

    outEdit = new QLineEdit();
    outEdit->setReadOnly(true);

    QGroupBox* serialBox = new QGroupBox("Execution Interface");
    QGridLayout* dataLayout = new QGridLayout();
    dataLayout->addWidget(new QLabel("device port:"), 0, 0);
    dataLayout->addWidget(portEdit, 0, 1);
    dataLayout->addWidget(new QLabel("baud rate:"), 1, 0);
    dataLayout->addWidget(comboBaud, 1, 1);
    serialBox->setLayout(dataLayout);

    QGroupBox* btnBox = new QGroupBox();
    QGridLayout* btnLayout = new QGridLayout();
    btnLayout->addWidget(createBtn, 0, 0);
    btnLayout->addWidget(cancelBtn, 0, 1);
    btnBox->setLayout(btnLayout);

    QGroupBox* fileBox = new QGroupBox("Test Interface");
    QGridLayout* fileLayout = new QGridLayout();
    fileLayout->addWidget(inEdit, 0, 0);
    fileLayout->addWidget(searchInFileBtn, 0, 1);
    fileLayout->addWidget(outEdit, 1, 0);
    fileLayout->addWidget(searchOutFileBtn, 1, 1);
    fileBox->setLayout(fileLayout);

    QGridLayout* mainLayout = new QGridLayout();
    mainLayout->addWidget(serialBox, 0, 0);
    mainLayout->addWidget(fileBox, 0, 1);
    mainLayout->addWidget(btnBox, 1, 1);
    setLayout(mainLayout);

    connect(searchInFileBtn, SIGNAL(clicked(bool)), this, SLOT(searchInFile()));
    connect(searchOutFileBtn, SIGNAL(clicked(bool)), this, SLOT(searchOutFile()));
    connect(createBtn, SIGNAL(clicked(bool)), this, SLOT(ok()));
    connect(cancelBtn, SIGNAL(clicked(bool)), this, SLOT(cancel()));
}

CommunicationDialog::~CommunicationDialog() {

}

void CommunicationDialog::searchOutFile() {
    QString path = QFileDialog::getSaveFileName(this, "select out file to open", QString(), tr("ALL (*.*)"));
    if (!path.isEmpty()) {
        outEdit->setText(path);
        checkSetCreateBtn();
    }
}

void CommunicationDialog::searchInFile() {
    QString path = QFileDialog::getOpenFileName(this, "select in file to open", QString(), tr("ALL (*.*)"));
    if (!path.isEmpty()) {
        inEdit->setText(path);
        checkSetCreateBtn();
    }
}

void CommunicationDialog::ok() {
    CommandSender* test = new FileSender(outEdit->text().toUtf8().constData(),
                                         inEdit->text().toUtf8().constData());
    CommandSender* exec = new SerialSender(portEdit->text().toUtf8().constData(),
                                           boudMap[comboBaud->currentText()]);

    int comId = CommunicationsInterface::GetInstance()->addCommandSenderTestExec(exec, test);
    ExecutionMachineServer::GetInstance()->changeMachineComId(machineReference, comId);
    accept();
}

void CommunicationDialog::cancel() {
    reject();
}

void CommunicationDialog::checkSetCreateBtn() {
    if (!inEdit->text().isEmpty() &&
        !outEdit->text().isEmpty())
    {
        createBtn->setEnabled(true);
    }
}

void CommunicationDialog::createComboBaud() {
    comboBaud->addItem("1200");
    boudMap.insert("1200", QSerialPort::Baud1200);

    comboBaud->addItem("2400");
    boudMap.insert("2400", QSerialPort::Baud2400);

    comboBaud->addItem("4800");
    boudMap.insert("4800", QSerialPort::Baud4800);

    comboBaud->addItem("9600");
    boudMap.insert("9600", QSerialPort::Baud9600);

    comboBaud->addItem("19200");
    boudMap.insert("19200", QSerialPort::Baud19200);

    comboBaud->addItem("38400");
    boudMap.insert("38400", QSerialPort::Baud38400);

    comboBaud->addItem("57600");
    boudMap.insert("57600", QSerialPort::Baud57600);

    comboBaud->addItem("115200");
    boudMap.insert("115200", QSerialPort::Baud115200);
}
