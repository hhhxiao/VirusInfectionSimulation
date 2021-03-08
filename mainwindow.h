#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "schoolmapwidget.h"
#include <QtCharts>
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
    void on_startSimBtn_clicked();
    void on_stopSimBtn_clicked();
    void on_moveSpeed_valueChanged(int value);

    void on_minComDistance_valueChanged(int value);

    void on_areaDepen_valueChanged(int value);

    void on_showResultBtn_clicked();

private:
    Ui::MainWindow *ui;
    SchoolMapWidget *schoolMapWidget;
    QtCharts::QChartView *cView;
};
#endif // MAINWINDOW_H
