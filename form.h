#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QTextEdit>
#include <QTimer>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>

#include <qwt_plot.h>
#include <qwt_plot_curve.h>

#include "dynsystem.h"


class Form : public QWidget
{
    Q_OBJECT

public:
    Form(QWidget *parent = nullptr);
    ~Form();

public slots:
    void startCalculation();
    void stopCalculation();
    void makeStep();
    void ValuesChanged();

private:
    QLabel *labelM1;
    QLabel *labelM2;
    QLabel *labelL1;
    QLabel *labelL2;
    QLabel *labelG;
    QLabel *labelInitAlpha1;
    QLabel *labelInitAlpha2;
    QLabel *labelInitW1;
    QLabel *labelInitW2;
    QLabel *labelDt;

    QDoubleSpinBox *doubleSpinBoxM1;
    QDoubleSpinBox *doubleSpinBoxM2;
    QDoubleSpinBox *doubleSpinBoxL1;
    QDoubleSpinBox *doubleSpinBoxL2;
    QDoubleSpinBox *doubleSpinBoxG;
    QDoubleSpinBox *doubleSpinBoxInitAlpha1;
    QDoubleSpinBox *doubleSpinBoxInitAlpha2;
    QDoubleSpinBox *doubleSpinBoxInitW1;
    QDoubleSpinBox *doubleSpinBoxInitW2;
    QDoubleSpinBox *doubleSpinBoxDt;

    QPushButton *pushButtonStart;
    QPushButton *pushButtonStop;

    QTextEdit *textEditLog;

    QGraphicsScene *Scene;
    QGraphicsView *GraphicsView;
    QGraphicsEllipseItem *podves;
    QGraphicsLineItem *line1;
    QGraphicsLineItem *line2;
    QGraphicsEllipseItem *gruz1;
    QGraphicsEllipseItem *gruz2;

    QwtPlot *plotAngles;
    QwtPlotCurve *curveAlpha1;
    QwtPlotCurve *curveAlpha2;

    QTimer * timer;

    DynSystem *system;

    QVector<double> dataT;
    QVector<double> dataAlpha1;
    QVector<double> dataAlpha2;
};
#endif // FORM_H
