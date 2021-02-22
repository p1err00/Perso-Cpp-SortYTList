#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QShortcut>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QList<QString> list;
    QString selectLink;
    void SpaceEvent();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void closeEvent(QCloseEvent *event);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    void LoadLayout();
    void RefreshList(QString link);
    void SaveList();
    void LoadList();

    QShortcut *space;

};
#endif // MAINWINDOW_H
