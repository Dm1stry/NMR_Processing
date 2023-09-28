#ifndef BASEPROCESSWIDGET_H
#define BASEPROCESSWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QValidator>
#include <QPushButton>
#include <QGridLayout>
#include <QProgressBar>
#include <QVariant>
#include <QThread>

#include "baseprocessor.h"
#include "nmrdatastruct.h"

class BaseProcessWidget : public QWidget
{
Q_OBJECT
public:
    BaseProcessWidget(const QString& name, QWidget * parent = nullptr);
    virtual ~BaseProcessWidget();
    const QString& getName() const;
    BaseProcessor * getProcessor() const;
protected:
    void setProcessor(BaseProcessor * processor);
    void setProcessorInSeparateThread(BaseProcessor * processor);
    void addParameter(const QString& name, const QString& label, QVariant default_value, QValidator * validator = nullptr);
    QGridLayout * getButtonsLayout() const;
    QGridLayout * getParametersLayout() const;
private:
    QString name_;  // Processor Widget name

    QMap<QString, QLabel*> parameters_labels_;
    QMap<QString, QLineEdit*> parameters_edits_;  //Processing parameters
    QMap<QString, QVariant> parameters_defaults_;
    uint parameters_amount_;

    QGridLayout * parameters_layout_;

    //--------- Buttons panel same for all processing widgets -----------------
    QPushButton * process_button_;
    QPushButton * clear_data_button_;
    QPushButton * clear_params_button_;
    QProgressBar * progress_bar_;
    QGridLayout * buttons_layout_;
    //---------------------------------------------------------------------------

    BaseProcessor * processor_;  // Pointer to processor object
    QThread * thread_;

private slots:
    void clearParams();
public slots:
    void updateData(const NMRDataStruct& raw_data);
signals:
    void clearData();
    void clearProcessingData();
};

#endif