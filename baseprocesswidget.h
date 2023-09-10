#ifndef BASEPROCESSWIDGET_H
#define BASEPROCESSWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

class BaseProcessWidget : public QWidget
{
Q_OBJECT
public:
    BaseProcessWidget(QWidget * parent = nullptr);
protected:
    QList<QLabel> labels_;
    QList<QLineEdit> parameter_edits_;
    QPushButton * process_button_;
    QPushButton * clear_data_button_;
    QPushButton * clear_params_button_;
    QGridLayout * buttons_layout_;
signals:
    void clearData();
public slots:
    void clearParams();
    void Process();
};

#endif