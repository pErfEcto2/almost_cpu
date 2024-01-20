#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_run_button_clicked();
    void on_get_desc_button_clicked();
    void on_save_button_clicked();
    void on_import_button_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
