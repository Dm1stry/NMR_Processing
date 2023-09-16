#ifndef BASEPROCESSWIDGET_H
#define BASEPROCESSWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QProgressBar>

#include "baseprocessor.h"
#include "plotwidget.h"

class BaseProcessWidget : public QWidget
{
Q_OBJECT
public:
    BaseProcessWidget(const QString& name, PlotWidget * plot_widget, PlotWidget * spectrum_widget, QWidget * parent = nullptr);
    const QString& getName() const;
protected:
    QString name_;
    QMap<QString, QLineEdit*> parameters_;
    QPushButton * process_button_;
    QPushButton * clear_data_button_;
    QPushButton * clear_params_button_;
    QProgressBar * progress_bar_;
    QGridLayout * buttons_layout_;

    BaseProcessor * processor_;

    PlotWidget * plot_;
    PlotWidget * spectrum_;
signals:
    void clearData();
public slots:
    virtual void clearParams() = 0;
};

#endif