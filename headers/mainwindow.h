#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "cpu.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void print_info();

private slots:
    void on_run_button_clicked();
    void on_get_desc_button_clicked();
    void on_save_button_clicked();
    void on_import_button_clicked();

private:
    Ui::MainWindow *ui;
    void perror(std::string s);

    Memory *mem;
    CPU *cpu;
};
#endif // MAINWINDOW_H
