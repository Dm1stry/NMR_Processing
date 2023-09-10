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
    BaseProcessWidget(const QString& name, QWidget * parent = nullptr);
    const QString& getName() const;
protected:
    QString name_;
    QMap<QString, QLineEdit*> parameters_;
    QPushButton * process_button_;
    QPushButton * clear_data_button_;
    QPushButton * clear_params_button_;
    QGridLayout * buttons_layout_;
signals:
    void clearData();
public slots:
    virtual void clearParams() = 0;
    virtual void Process() = 0;
};

#endif