#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QWidget>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize({1080,800});
    schoolMapWidget = new SchoolMapWidget(this);
    schoolMapWidget->setGeometry(300,0,750,750);
    connect(ui->isIllcheckBox, SIGNAL(clicked(bool)), this->schoolMapWidget, SLOT(setIsIll(bool)));
    connect(ui->hasMaskcheckBox, SIGNAL(clicked(bool)), this->schoolMapWidget, SLOT(setHasMask(bool)));
    ui->areaDepen->setMinimum(0);
    ui->areaDepen->setMaximum(10);
    ui->areaDepen->setSliderPosition(4);
    schoolMapWidget->setAreaDepenValue(4);
    ui->moveSpeed->setMinimum(1);
    ui->moveSpeed->setMaximum(99);
    ui->moveSpeed->setTickInterval(2);
    ui->moveSpeed->setSliderPosition(19);
    schoolMapWidget->seMoveSpeed(19);
    ui->minComDistance->setMinimum(0);
    ui->minComDistance->setMaximum(80);
    ui->minComDistance->setSliderDown(0);
    schoolMapWidget->setCommDistance(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startSimBtn_clicked()
{
    this->schoolMapWidget->setSimStatus(true);
}

void MainWindow::on_stopSimBtn_clicked()
{
    this->schoolMapWidget->setSimStatus(false);
}

void MainWindow::on_moveSpeed_valueChanged(int value)
{
    this->ui->moveSpeedVal->setText(QString::number(value));
    schoolMapWidget->seMoveSpeed(value);
}

void MainWindow::on_minComDistance_valueChanged(int value)
{
    this->ui->comDistanceVal->setText(QString::number(value));
    schoolMapWidget->setCommDistance(value);
}

void MainWindow::on_areaDepen_valueChanged(int value)
{
    this->ui->areaDepebVal->setText(QString::number(value));
    schoolMapWidget->setAreaDepenValue(value);
}

void MainWindow::on_showResultBtn_clicked()
{
    auto statData = schoolMapWidget->getStatVal();
    using  namespace QtCharts ;
    QLineSeries *healthSeries  = new QLineSeries();
    QLineSeries *illSeries  = new QLineSeries();
    for(auto i  = 0;i < statData.size() ;i++){
        healthSeries->append(i,statData[i].first);
        illSeries->append(i,statData[i].second);
    }

    QChart *chart = new QChart();
        //chart->legend()->hide();
    chart->addSeries(healthSeries);
       chart->addSeries(illSeries);
       chart->createDefaultAxes();
       chart->setTitle("折线图");
    this->cView = new QChartView(chart);
       this->cView->setGeometry(0,0,800,600);
    cView->show();
}
