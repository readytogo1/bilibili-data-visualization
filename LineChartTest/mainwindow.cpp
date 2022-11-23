#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

#include <QtWidgets/QGridLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
void MainWindow::on_ShowButton_clicked()
{
    //![1]
        QLineSeries *series = new QLineSeries();
        QLineSeries *series2 = new QLineSeries();
    //![1]

    //![2]
        series->append(1, 23);
        series->append(2, 45);
        series->append(3, 77);
        series->append(4, 1344);
        series->append(5, 3401);
        *series << QPointF(6, 12734) << QPointF(7, 52132);
        series->setName("predict");

        series2->append(1, 23);
        series2->append(2, 45);
        series2->append(3, 77);
        series2->append(4, 1344);
        series2->append(5, 3401);
        series2->append(6, 12734);
        series2->append(7, 42357);
        series2->setName("actual");
    //![2]

    //![3]
        QChart *chart = new QChart();
        //chart->legend()->hide();
        //chart->createDefaultAxes();
        chart->setTitle("line chart");

        //自定坐标轴
        QValueAxis *xAxis = new QValueAxis();
        QValueAxis *yAxis = new QValueAxis();
        xAxis->setRange(1, 7);
        yAxis->setRange(0,80000);
        xAxis->setTitleText(QStringLiteral("时间"));
        yAxis->setTitleText(QStringLiteral("播放量"));
        xAxis->setLabelFormat("%d");
        yAxis->setLabelFormat("%d");
        xAxis->setTickCount(7);


        chart->addSeries(series);
        chart->addSeries(series2);
        chart->addAxis(xAxis, Qt::AlignBottom);
        chart->addAxis(yAxis, Qt::AlignLeft);
        series->attachAxis(yAxis);
        series->attachAxis(xAxis);

        series2->attachAxis(yAxis);
        series2->attachAxis(yAxis);
        //chart->setAxisX(xAxis);
        //chart->setAxisY(yAxis);
    //![3]

    //![4]
        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        chartView->resize(400, 300);
        ui->gridLayout->addWidget(chartView, 1, 0); //在主窗口显示

        //在新窗口显示
        //chartView->resize(400, 300);
        //chartView->show();
    //![4]

}
*/
void MainWindow::on_ShowButton_clicked()
{
    creatChart(":/test.csv");

}

void MainWindow::on_openFileButton_clicked()
{
    //这里设置默认选择第二个过滤器
    QString arg("CSV files (*.csv");
    //tr用来解决不同编码方式乱码问题
    QString fileName = QFileDialog::getOpenFileName(
                this,tr("open File"),"D://",
                tr("CSV files (*.csv)"),&arg);
    //QMessageBox::information(this,"打开文件","您选择的文件是："+fileName);

    creatChart(fileName);
}

void MainWindow::creatChart(QString fileName)
{
    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"choose write file";
        return;
    }

    QTextStream *read = new QTextStream(&file);
    QStringList Data = read->readAll().split("\n",QString::SkipEmptyParts);

    QLineSeries *seriesP; //= new QLineSeries();
    QLineSeries *seriesA ;//= new QLineSeries();


    QChart *chart; //= new QChart();
    QChartView *chartView;// = new QChartView(chart);
    QValueAxis *xAxis;
    QValueAxis *yAxis;
    QStringList strLine;
    for(int i=1;i<7;i++){
        chart = new QChart();
        strLine = Data.at(i).split(",");

        seriesP = new QLineSeries();
        seriesA = new QLineSeries();
        seriesP->setName("predict");
        seriesA->setName("fact");
        for(int j=0;j<7;j++){
            seriesP->append(j+1,strLine.at(j+1).toInt());
            seriesA->append(j+1,strLine.at(j+8).toInt());
        }

        chart->setTitle(strLine.at(0));
        //1
        xAxis = new QValueAxis();
        yAxis = new QValueAxis();
        xAxis->setRange(1, 7);
        yAxis->setRange(0,4000);
        xAxis->setTitleText(QStringLiteral("时间"));
        yAxis->setTitleText(QStringLiteral("播放量"));
        xAxis->setLabelFormat("%d");
        yAxis->setLabelFormat("%d");
        xAxis->setTickCount(7);


        chart->addSeries(seriesP);
        chart->addSeries(seriesA);
        chart->addAxis(xAxis, Qt::AlignBottom);
        chart->addAxis(yAxis, Qt::AlignLeft);
        seriesP->attachAxis(yAxis);
        seriesP->attachAxis(xAxis);

        seriesA->attachAxis(yAxis);
        seriesA->attachAxis(xAxis);
        //

        chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        //chartView->resize(200, 100);
        //qDebug()<<(i-1)/3+1<<","<<(i-1)%3<<"\n";
        ui->gridLayout->addWidget(chartView, (i-1)/3, (i-1)%3);
    }
    file.close();
}
