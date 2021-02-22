#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QDialog>
#include <QLineEdit>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QKeyEvent>
#include <QProcess>
#include <QEvent>
#include <QShortcut>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    LoadList();
    space = new QShortcut(this);
    space->setKey(Qt::Key_Space);
    QObject::connect(space, &QShortcut::activated, this,[=]{
        SpaceEvent();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Add link
void MainWindow::on_pushButton_2_clicked()
{

    QDialog *addDialog = new QDialog(this);
    QVBoxLayout *layout = new QVBoxLayout;
    //QLineEdit *name = new QLineEdit;  Add name
    QLineEdit *url = new QLineEdit;
    QPushButton *addButton = new QPushButton;
    QPushButton *prevButton = new QPushButton;

    //name->setPlaceholderText("Name :");   Add name
    //name->setTextMargins(10, 5, 10, 5);   Add name
    url->setPlaceholderText("Url :");
    url->setTextMargins(10, 5, 10, 5);

    addButton->setText("Ajouter");
    QObject::connect(addButton, &QPushButton::clicked, [=]{
        //Add url into list

        QString link = url->text(); //Change to name
        if(link == "" || link == nullptr){
            QMessageBox::warning(this, "URL Vide", "Il manque l'url");
        } else {
            list.append(link);
            addDialog->close();

            //Refresh link list
            RefreshList(link);
        }

    });

    prevButton->setText("Retour");
    QObject::connect(prevButton, &QPushButton::clicked, [=]{
        addDialog->close();
    });

    //layout->addWidget(name);  Add name
    layout->addWidget(url);
    layout->addWidget(addButton);
    layout->addWidget(prevButton);

    addDialog->setFixedSize(250, 200);
    addDialog->setLayout(layout);
    addDialog->exec();
}

//Delete link
void MainWindow::on_pushButton_3_clicked()
{
    qDebug() << "ca rentre";
    if(selectLink == nullptr){
        return;
    }
    for(int i =0; i< list.size(); i++){
        qDebug() << "ca rentre for";
        if(list.at(i) == selectLink){
            qDebug() << "ca rentre if";

            QLayoutItem *child;
            while((child = ui->layoutLeft->takeAt(0))){
                delete child->widget();
                delete child;

            }
            list.removeOne(selectLink);
            selectLink = nullptr;
        }
    }
    for(QString item : list){
        RefreshList(item);
    }
}

void MainWindow::RefreshList(QString link){

    QPushButton *linkButton = new QPushButton;
    linkButton->setText(link);
    ui->layoutLeft->addWidget(linkButton);
    QObject::connect(linkButton, &QPushButton::clicked, [=]{
        selectLink = linkButton->text();
    });
}

void MainWindow::SaveList(){

    QString path = QDir::currentPath();
    qDebug() << path;
    QFile file(path + "\\Save.txt");
    QTextStream stream(&file);
    if (!file.open(QIODevice::WriteOnly  | QIODevice::Text)){
            qDebug() << "File now exist";
    }
    for(QString item : list){
        qDebug() << item;
        stream << item + "\n";
        qDebug() << "item add";
    }
    file.close();
}

void MainWindow::LoadList(){

    QString path = QDir::currentPath();
    qDebug() << path;
    qDebug() << path;
    QFile file(path + "\\Save.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);
    while(!in.atEnd()){
        QString line = in.readLine();
        QPushButton *link = new QPushButton;
        link->setText(line);
        QObject::connect(link, &QPushButton::clicked, this, [=]{
            selectLink = link->text();
        });
        ui->layoutLeft->addWidget(link);
        list.append(line);
    }
}

void MainWindow::closeEvent(QCloseEvent *event){

    SaveList();
}

void MainWindow::SpaceEvent(){

    qDebug() << selectLink;
    QProcess *process = new QProcess;
    process->execute("cmd /c start "+selectLink);
}

void MainWindow::on_pushButton_clicked()
{
    QString fichier = QFileDialog::getSaveFileName(this, "Enregistrer un fichier", QString(), "Save.txt");
    SaveList();
}
