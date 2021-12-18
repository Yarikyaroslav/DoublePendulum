#include "form.h"

#include <cmath>

#define _USE_MATH_DEFINES

#include <qwt_plot_legenditem.h>

#include <QLayout>

Form::Form(QWidget *parent)
    : QWidget(parent), system(nullptr)
{
    timer = new QTimer(this);
    timer->setInterval(5);

    labelM1 = new QLabel("mass1[0,1..100,0 kg]");
    labelM2 = new QLabel("mass2[0,1..100,0 kg]");
    labelL1 = new QLabel("length1[50..150 m]");
    labelL2 = new QLabel("length2[50..150 m]");
    labelG = new QLabel("g[1..100 m/sec^2]");
    labelInitAlpha1 = new QLabel("initial alpha1[-180..180 degrees]");
    labelInitAlpha2 = new QLabel("initial alpha2[-180..180 degrees]");
    labelInitW1 = new QLabel("initial w1[-100..100 degrees/sec]");
    labelInitW2 = new QLabel("initial w2[-100..100 degrees/sec]");
    labelDt = new QLabel("time step[1e-6..1e-3 sec]");

    doubleSpinBoxM1 = new QDoubleSpinBox;
    doubleSpinBoxM1->setMinimum(0.1);
    doubleSpinBoxM1->setMaximum(100.0);
    doubleSpinBoxM1->setSingleStep(1.0);
    doubleSpinBoxM1->setDecimals(2);
    doubleSpinBoxM1->setValue(10.0);
    doubleSpinBoxM2 = new QDoubleSpinBox;
    doubleSpinBoxM2->setMinimum(0.1);
    doubleSpinBoxM2->setMaximum(100.0);
    doubleSpinBoxM2->setSingleStep(1.0);
    doubleSpinBoxM2->setDecimals(2);
    doubleSpinBoxM2->setValue(10.0);
    doubleSpinBoxL1 = new QDoubleSpinBox;
    doubleSpinBoxL1->setMinimum(50);
    doubleSpinBoxL1->setMaximum(150.0);
    doubleSpinBoxL1->setSingleStep(1.0);
    doubleSpinBoxL1->setDecimals(2);
    doubleSpinBoxL1->setValue(100);
    doubleSpinBoxL2 = new QDoubleSpinBox;
    doubleSpinBoxL2->setMinimum(50);
    doubleSpinBoxL2->setMaximum(150.0);
    doubleSpinBoxL2->setSingleStep(1.0);
    doubleSpinBoxL2->setDecimals(2);
    doubleSpinBoxL2->setValue(100);
    doubleSpinBoxG = new QDoubleSpinBox;
    doubleSpinBoxG->setMinimum(1.0);
    doubleSpinBoxG->setMaximum(100.0);
    doubleSpinBoxG->setSingleStep(0.1);
    doubleSpinBoxG->setDecimals(2);
    doubleSpinBoxG->setValue(9.81);
    doubleSpinBoxInitAlpha1 = new QDoubleSpinBox;
    doubleSpinBoxInitAlpha1->setMinimum(-180.0);
    doubleSpinBoxInitAlpha1->setMaximum(180.0);
    doubleSpinBoxInitAlpha1->setSingleStep(1.0);
    doubleSpinBoxInitAlpha1->setDecimals(2);
    doubleSpinBoxInitAlpha1->setValue(50.0);
    doubleSpinBoxInitAlpha2 = new QDoubleSpinBox;
    doubleSpinBoxInitAlpha2->setMinimum(-180.0);
    doubleSpinBoxInitAlpha2->setMaximum(180.0);
    doubleSpinBoxInitAlpha2->setSingleStep(1.0);
    doubleSpinBoxInitAlpha2->setDecimals(2);
    doubleSpinBoxInitAlpha2->setValue(50.0);
    doubleSpinBoxInitW1 = new QDoubleSpinBox;
    doubleSpinBoxInitW1->setMinimum(-100.0);
    doubleSpinBoxInitW1->setMaximum(100.0);
    doubleSpinBoxInitW1->setSingleStep(1.0);
    doubleSpinBoxInitW1->setDecimals(2);
    doubleSpinBoxInitW2 = new QDoubleSpinBox;
    doubleSpinBoxInitW2->setMinimum(-100.0);
    doubleSpinBoxInitW2->setMaximum(100.0);
    doubleSpinBoxInitW2->setSingleStep(1.0);
    doubleSpinBoxInitW2->setDecimals(2);
    doubleSpinBoxDt = new QDoubleSpinBox;
    doubleSpinBoxDt->setMinimum(1e-6);
    doubleSpinBoxDt->setMaximum(1e-3);
    doubleSpinBoxDt->setSingleStep(1e-3);
    doubleSpinBoxDt->setDecimals(6);
    doubleSpinBoxDt->setValue(1e-3);

    pushButtonStart = new QPushButton("start");
    pushButtonStop = new QPushButton("stop");

    textEditLog = new QTextEdit;
    textEditLog->setReadOnly(true);

    plotAngles = new QwtPlot(QString("Deflection angles"));
    plotAngles->setAxisTitle(QwtPlot::yLeft,"Angle(mod 360 deg)");
    plotAngles->setAxisTitle(QwtPlot::xBottom,"Time(sec)");

    curveAlpha1 = new QwtPlotCurve("alpha1");
    curveAlpha1->setPen(Qt::blue,3.0,Qt::DotLine);
    curveAlpha1->attach(plotAngles);

    curveAlpha2 = new QwtPlotCurve("alpha2");
    curveAlpha2->setPen(Qt::red,3.0,Qt::SolidLine);
    curveAlpha2->attach(plotAngles);

    QwtPlotLegendItem *legendAngles = new QwtPlotLegendItem;
    legendAngles->attach(plotAngles);
    legendAngles->setAlignment(Qt::AlignRight);
    legendAngles->setMaxColumns(1);

    Scene = new QGraphicsScene(-350,-350,700,700,this);

    podves = new QGraphicsEllipseItem(-3,-3,6,6);
    podves->setBrush(Qt::black);

    Scene->addItem(podves);


    gruz1 = new QGraphicsEllipseItem(-7*log(1+doubleSpinBoxM1->value())/2,-7*log(1+doubleSpinBoxM1->value())/2,7*log(1+doubleSpinBoxM1->value()),7*log(1+doubleSpinBoxM1->value()));
    gruz1->setBrush(Qt::blue);
    gruz2 = new QGraphicsEllipseItem(-7*log(1+doubleSpinBoxM2->value())/2,-7*log(1+doubleSpinBoxM2->value())/2,7*log(1+doubleSpinBoxM2->value()),7*log(1+doubleSpinBoxM2->value()));
    gruz2->setBrush(Qt::red);

    line1 = new QGraphicsLineItem();
    line1->setPen(QPen(Qt::black));
    line2 = new QGraphicsLineItem();
    line2->setPen(QPen(Qt::black));


    Scene->addItem(line1);
    Scene->addItem(line2);
    Scene->addItem(gruz1);
    Scene->addItem(gruz2);
    gruz1->setPos(doubleSpinBoxL1->value()*sin(M_PI/180*doubleSpinBoxInitAlpha1->value()),doubleSpinBoxL1->value()*cos(M_PI/180*doubleSpinBoxInitAlpha1->value()));
    gruz2->setPos(doubleSpinBoxL1->value()*sin(M_PI/180*doubleSpinBoxInitAlpha1->value())+doubleSpinBoxL2->value()*sin(M_PI/180*doubleSpinBoxInitAlpha2->value())
                  ,doubleSpinBoxL1->value()*cos(M_PI/180*doubleSpinBoxInitAlpha1->value())+doubleSpinBoxL2->value()*cos(M_PI/180*doubleSpinBoxInitAlpha2->value()));
    line1->setLine(0,0,doubleSpinBoxL1->value()*sin(M_PI/180*doubleSpinBoxInitAlpha1->value()),doubleSpinBoxL1->value()*cos(M_PI/180*doubleSpinBoxInitAlpha1->value()));
    line2->setLine(doubleSpinBoxL1->value()*sin(M_PI/180*doubleSpinBoxInitAlpha1->value()),
                   doubleSpinBoxL1->value()*cos(M_PI/180*doubleSpinBoxInitAlpha1->value()),
                   doubleSpinBoxL1->value()*sin(M_PI/180*doubleSpinBoxInitAlpha1->value())+doubleSpinBoxL2->value()*sin(M_PI/180*doubleSpinBoxInitAlpha2->value()),
                   doubleSpinBoxL1->value()*cos(M_PI/180*doubleSpinBoxInitAlpha1->value())+doubleSpinBoxL2->value()*cos(M_PI/180*doubleSpinBoxInitAlpha2->value()));
    Scene->advance();

    GraphicsView = new QGraphicsView(Scene);


    QGridLayout *layoutParameters = new QGridLayout;
    layoutParameters->addWidget(labelM1,0,0);
    layoutParameters->addWidget(labelM2,1,0);
    layoutParameters->addWidget(labelL1,2,0);
    layoutParameters->addWidget(labelL2,3,0);
    layoutParameters->addWidget(labelG,4,0);
    layoutParameters->addWidget(doubleSpinBoxM1,0,1);
    layoutParameters->addWidget(doubleSpinBoxM2,1,1);
    layoutParameters->addWidget(doubleSpinBoxL1,2,1);
    layoutParameters->addWidget(doubleSpinBoxL2,3,1);
    layoutParameters->addWidget(doubleSpinBoxG,4,1);
    layoutParameters->addWidget(labelInitAlpha1,0,2);
    layoutParameters->addWidget(labelInitAlpha2,1,2);
    layoutParameters->addWidget(labelInitW1,2,2);
    layoutParameters->addWidget(labelInitW2,3,2);
    layoutParameters->addWidget(labelDt,4,2);
    layoutParameters->addWidget(doubleSpinBoxInitAlpha1,0,3);
    layoutParameters->addWidget(doubleSpinBoxInitAlpha2,1,3);
    layoutParameters->addWidget(doubleSpinBoxInitW1,2,3);
    layoutParameters->addWidget(doubleSpinBoxInitW2,3,3);
    layoutParameters->addWidget(doubleSpinBoxDt,4,3);

    QHBoxLayout *layoutButtons = new QHBoxLayout;
    layoutButtons->addWidget(pushButtonStart);
    layoutButtons->addWidget(pushButtonStop);

    QVBoxLayout *layoutLeft = new QVBoxLayout;
    layoutLeft->addLayout(layoutParameters);
    layoutLeft->addLayout(layoutButtons);
    layoutLeft->addWidget(GraphicsView);


    QVBoxLayout *layoutRight = new QVBoxLayout;
    layoutRight->addWidget(plotAngles);
    layoutRight->addWidget(textEditLog);

    QHBoxLayout *layoutMain = new QHBoxLayout;
    layoutMain->addLayout(layoutLeft);
    layoutMain->addLayout(layoutRight);

    this->setLayout(layoutMain);

    connect(pushButtonStart, &QPushButton::clicked, this, &Form::startCalculation);
    connect(pushButtonStop, &QPushButton::clicked, this, &Form::stopCalculation);
    connect(doubleSpinBoxM1,&QDoubleSpinBox::editingFinished, this,&Form::ValuesChanged);
    connect(doubleSpinBoxM2,&QDoubleSpinBox::editingFinished, this,&Form::ValuesChanged);
    connect(doubleSpinBoxL1,&QDoubleSpinBox::editingFinished, this,&Form::ValuesChanged);
    connect(doubleSpinBoxL2,&QDoubleSpinBox::editingFinished, this,&Form::ValuesChanged);
    connect(doubleSpinBoxInitAlpha1,&QDoubleSpinBox::editingFinished, this,&Form::ValuesChanged);
    connect(doubleSpinBoxInitAlpha2,&QDoubleSpinBox::editingFinished, this,&Form::ValuesChanged);
    connect(timer, &QTimer::timeout, this, &Form::makeStep);
}

Form::~Form()
{
    delete system;
}

void Form::startCalculation()
{
    Scene->clear();
    podves = new QGraphicsEllipseItem(-3,-3,6,6);
    podves->setBrush(Qt::black);
    Scene->addItem(podves);
    textEditLog->clear();
    dataT.clear();
    dataAlpha1.clear();
    dataAlpha2.clear();
    delete system;

    system = new DynSystem(doubleSpinBoxM1->value(),doubleSpinBoxM2->value(),doubleSpinBoxL1->value(),doubleSpinBoxL2->value(),
                           doubleSpinBoxG->value(),M_PI/180*doubleSpinBoxInitAlpha1->value(),M_PI/180*doubleSpinBoxInitAlpha2->value(),
                           M_PI/180*doubleSpinBoxInitW1->value(),M_PI/180*doubleSpinBoxInitW2->value(),0.0,doubleSpinBoxDt->value());
    double energy =system->m1()/2*(pow(system->l1()*cos(system->alpha1())*system->w1(),2)+pow(system->l1()*sin(system->alpha1())*system->w1(),2))+
            system->m2()/2*(pow(system->l1()*system->w1()*cos(system->alpha1())+system->l2()*system->w2()*cos(system->alpha2()),2)+
                            pow(system->l1()*system->w1()*sin(system->alpha1())+system->l2()*system->w2()*sin(system->alpha2()),2))-
            system->m1()*system->g()*system->l1()*cos(system->alpha1())-system->m2()*system->g()*(system->l1()*cos(system->alpha1())+system->l2()*cos(system->alpha2()));
    textEditLog->append("system created");
    textEditLog->append("parameters:");
    textEditLog->append("mass1 = " + QString::number(system->m1()));
    textEditLog->append("mass2 = " + QString::number(system->m2()));
    textEditLog->append("length1 = " + QString::number(system->l1()));
    textEditLog->append("length2 = " + QString::number(system->l2()));
    textEditLog->append("alpha1 = " + QString::number(180/M_PI*system->alpha1()));
    textEditLog->append("alpha2 = " + QString::number(180/M_PI*system->alpha2()));
    textEditLog->append("time\talpha1(rad)\talpha2(rad)\tenergy");
    textEditLog->append(QString("%1\t%2\t%3\t%4")
                        .arg(system->t())
                        .arg(system->alpha1())
                        .arg(system->alpha2())
                        .arg(energy));
    dataT.append(system->t());
    dataAlpha1.append(180/M_PI*(fmod(system->alpha1(),2*M_PI)));
    dataAlpha2.append(180/M_PI*(fmod(system->alpha2(),2*M_PI)));

    curveAlpha1->setSamples(dataT,dataAlpha1);
    curveAlpha2->setSamples(dataT,dataAlpha2);

    gruz1 = new QGraphicsEllipseItem(-7*log(1+system->m1())/2,-7*log(1+system->m1())/2,7*log(1+system->m1()),7*log(1+system->m1()));
    gruz1->setBrush(Qt::blue);
    gruz2 = new QGraphicsEllipseItem(-7*log(1+system->m2())/2,-7*log(1+system->m2())/2,7*log(1+system->m2()),7*log(1+system->m2()));
    gruz2->setBrush(Qt::red);

    line1 = new QGraphicsLineItem();
    line1->setPen(QPen(Qt::black));
    line2 = new QGraphicsLineItem();
    line2->setPen(QPen(Qt::black));



    gruz1->setPos(system->l1()*sin(system->alpha1()),system->l1()*cos(system->alpha1()));
    gruz2->setPos(system->l1()*sin(system->alpha1())+system->l2()*sin(system->alpha2()),system->l1()*cos(system->alpha1())+system->l2()*cos(system->alpha2()));
    line1->setLine(0,0,system->l1()*sin(system->alpha1()),system->l1()*cos(system->alpha1()));
    line2->setLine(system->l1()*sin(system->alpha1()),system->l1()*cos(system->alpha1()),system->l1()*sin(system->alpha1())+system->l2()*sin(system->alpha2()),
                   system->l1()*cos(system->alpha1())+system->l2()*cos(system->alpha2()));
    Scene->addItem(line1);
    Scene->addItem(line2);
    Scene->addItem(gruz1);
    Scene->addItem(gruz2);
    Scene->advance();

    plotAngles->replot();

    doubleSpinBoxG->setEnabled(false);
    doubleSpinBoxM1->setEnabled(false);
    doubleSpinBoxM2->setEnabled(false);
    doubleSpinBoxL1->setEnabled(false);
    doubleSpinBoxL2->setEnabled(false);
    doubleSpinBoxInitAlpha1->setEnabled(false);
    doubleSpinBoxInitAlpha2->setEnabled(false);
    doubleSpinBoxInitW1->setEnabled(false);
    doubleSpinBoxInitW2->setEnabled(false);
    doubleSpinBoxDt->setEnabled(false);
    pushButtonStart->setEnabled(false);
    timer->start();
}

void Form::stopCalculation()
{
    doubleSpinBoxG->setEnabled(true);
    doubleSpinBoxM1->setEnabled(true);
    doubleSpinBoxM2->setEnabled(true);
    doubleSpinBoxL1->setEnabled(true);
    doubleSpinBoxL2->setEnabled(true);
    doubleSpinBoxInitAlpha1->setEnabled(true);
    doubleSpinBoxInitAlpha2->setEnabled(true);
    doubleSpinBoxInitW1->setEnabled(true);
    doubleSpinBoxInitW2->setEnabled(true);
    doubleSpinBoxDt->setEnabled(true);
    pushButtonStart->setEnabled(true);
    timer->stop();
}

void Form::makeStep()
{

    for (int i = 0; i < 50; ++i)
    {
        system->step();
    }
    double energy =system->m1()/2*(pow(system->l1()*cos(system->alpha1())*system->w1(),2)+pow(system->l1()*sin(system->alpha1())*system->w1(),2))+
            system->m2()/2*(pow(system->l1()*system->w1()*cos(system->alpha1())+system->l2()*system->w2()*cos(system->alpha2()),2)+
                            pow(system->l1()*system->w1()*sin(system->alpha1())+system->l2()*system->w2()*sin(system->alpha2()),2))-
            system->m1()*system->g()*system->l1()*cos(system->alpha1())-system->m2()*system->g()*(system->l1()*cos(system->alpha1())+system->l2()*cos(system->alpha2()));
    textEditLog->append(QString("%1\t%2\t%3\t%4")
                        .arg(system->t())
                        .arg(system->alpha1())
                        .arg(system->alpha2())
                        .arg(energy));
    dataT.append(system->t());
    dataAlpha1.append(180/M_PI*(fmod(system->alpha1(),2*M_PI)));
    dataAlpha2.append(180/M_PI*(fmod(system->alpha2(),2*M_PI)));

    curveAlpha1->setSamples(dataT,dataAlpha1);
    curveAlpha2->setSamples(dataT,dataAlpha2);

    gruz1->setPos(system->l1()*sin(system->alpha1()),system->l1()*cos(system->alpha1()));
    gruz2->setPos(system->l1()*sin(system->alpha1())+system->l2()*sin(system->alpha2()),system->l1()*cos(system->alpha1())+system->l2()*cos(system->alpha2()));
    line1->setLine(0,0,system->l1()*sin(system->alpha1()),system->l1()*cos(system->alpha1()));
    line2->setLine(system->l1()*sin(system->alpha1()),system->l1()*cos(system->alpha1()),system->l1()*sin(system->alpha1())+system->l2()*sin(system->alpha2()),
                   system->l1()*cos(system->alpha1())+system->l2()*cos(system->alpha2()));
    Scene->advance();
    plotAngles->replot();
}

void Form::ValuesChanged()
{
    Scene->clear();
    podves = new QGraphicsEllipseItem(-3,-3,6,6);
    podves->setBrush(Qt::black);
    Scene->addItem(podves);


    gruz1 = new QGraphicsEllipseItem(-7*log(1+doubleSpinBoxM1->value())/2,-7*log(1+doubleSpinBoxM1->value())/2,7*log(1+doubleSpinBoxM1->value()),7*log(1+doubleSpinBoxM1->value()));
    gruz1->setBrush(Qt::blue);

    gruz2 = new QGraphicsEllipseItem(-7*log(1+doubleSpinBoxM2->value())/2,-7*log(1+doubleSpinBoxM2->value())/2,7*log(1+doubleSpinBoxM2->value()),7*log(1+doubleSpinBoxM2->value()));
    gruz2->setBrush(Qt::red);


    line1 = new QGraphicsLineItem();
    line1->setPen(QPen(Qt::black));

    line2 = new QGraphicsLineItem();
    line2->setPen(QPen(Qt::black));



    gruz1->setPos(doubleSpinBoxL1->value()*sin(M_PI/180*doubleSpinBoxInitAlpha1->value()),doubleSpinBoxL1->value()*cos(M_PI/180*doubleSpinBoxInitAlpha1->value()));
    gruz2->setPos(doubleSpinBoxL1->value()*sin(M_PI/180*doubleSpinBoxInitAlpha1->value())+doubleSpinBoxL2->value()*sin(M_PI/180*doubleSpinBoxInitAlpha2->value())
                  ,doubleSpinBoxL1->value()*cos(M_PI/180*doubleSpinBoxInitAlpha1->value())+doubleSpinBoxL2->value()*cos(M_PI/180*doubleSpinBoxInitAlpha2->value()));
    line1->setLine(0,0,doubleSpinBoxL1->value()*sin(M_PI/180*doubleSpinBoxInitAlpha1->value()),doubleSpinBoxL1->value()*cos(M_PI/180*doubleSpinBoxInitAlpha1->value()));
    line2->setLine(doubleSpinBoxL1->value()*sin(M_PI/180*doubleSpinBoxInitAlpha1->value()),
                   doubleSpinBoxL1->value()*cos(M_PI/180*doubleSpinBoxInitAlpha1->value()),
                   doubleSpinBoxL1->value()*sin(M_PI/180*doubleSpinBoxInitAlpha1->value())+doubleSpinBoxL2->value()*sin(M_PI/180*doubleSpinBoxInitAlpha2->value()),
                   doubleSpinBoxL1->value()*cos(M_PI/180*doubleSpinBoxInitAlpha1->value())+doubleSpinBoxL2->value()*cos(M_PI/180*doubleSpinBoxInitAlpha2->value()));
    Scene->addItem(line1);
    Scene->addItem(line2);
    Scene->addItem(gruz1);
    Scene->addItem(gruz2);
    Scene->advance();
}

