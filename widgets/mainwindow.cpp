#include "mainwindow.h"

MainWindow::MainWindow(QWidget * parent)
  : QWidget(parent),
    data_(new NMRData(this)),
    filesystem_widget_(new FileSystemWidget),
    log_widget_(new LogWidget),
    plot_widget_(new PlotWidget),
    spectrum_widget_(new PlotWidget),
    noise_widget_(new PlotWidget),
    process_widget_(new ProcessWidget)
{
    qRegisterMetaType<NMRDataStruct>("NMRDataStruct");
    qRegisterMetaType<NMRDataStruct>("NMRDataStruct&");
    layoutSetup();
    connections();
}

inline void MainWindow::connections()
{
    connect(this->filesystem_widget_, &FileSystemWidget::fileSelected, this->data_, &NMRData::readAsCPMG);
	connect(this->data_, SIGNAL(rawDataUpdated(const NMRDataStruct&)), this->plot_widget_, SLOT(updateAsPlot(const NMRDataStruct&)));

    connect(this->data_, &NMRData::rawDataUpdated, this->process_widget_, &ProcessWidget::updateData);

    connect(this->process_widget_, &ProcessWidget::processingDone, this->data_, &NMRData::setProcessedData);

    connect(this->data_, &NMRData::processedDataUpdated, [=](const NMRDataStruct& nmrdata){this->plot_widget_->updateAsPlot(nmrdata, 1);});
    connect(this->data_, SIGNAL(processedDataUpdated(const NMRDataStruct&)), this->spectrum_widget_, SLOT(updateAsSpectrum(const NMRDataStruct&)));

    connect(this->process_widget_, SIGNAL(clearData()), this->data_, SLOT(clearData()));
    connect(this->data_, SIGNAL(rawDataCleared()), this->plot_widget_, SLOT(clear()));
    connect(this->data_, SIGNAL(rawDataCleared()), this->spectrum_widget_, SLOT(clear()));

    connect(this->process_widget_, SIGNAL(componentsFound(const NMRDataStruct&)), this->data_, SLOT(setComponents(const NMRDataStruct&)));
    connect(this->data_, SIGNAL(componentsUpdated(const NMRDataStruct&)), this->noise_widget_, SLOT(updateAsSpectrum(const NMRDataStruct&)));
    connect(this->data_, SIGNAL(componentsUpdated(const NMRDataStruct&)), this->log_widget_, SLOT(printComponents(const NMRDataStruct&)));

    //connect(this->data_, SIGNAL())
	//connect(this->data_, SIGNAL(dataUpdated(const QVector<double>&, const QVector<double>&)), this->process_widget_, SLOT(updateData(const QVector<double>&, const QVector<double>&)));

}

inline void MainWindow::layoutSetup()
{
    /*QDockWidget * filesystem_dock = new QDockWidget("Файловая система", this);
    filesystem_dock->setWidget(this->filesystem_widget_);

    QDockWidget * log_dock = new QDockWidget(this);
    log_dock->setWidget(this->log_widget_);*/
    //this->noise_widget_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    QSizePolicy plot_policy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    plot_policy.setVerticalStretch(2);
    QSizePolicy noise_policy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    noise_policy.setVerticalStretch(1);

    QFrame * line = new QFrame;
    line->setFixedHeight(2);
    line->setFrameShape(QFrame::HLine);

    this->plot_widget_->setSizePolicy(plot_policy);
    this->spectrum_widget_->setSizePolicy(plot_policy);
    this->noise_widget_->setSizePolicy(noise_policy);

    QHBoxLayout * main_layout = new QHBoxLayout;

    QVBoxLayout * left_layout = new QVBoxLayout;
    QVBoxLayout * mid_layout = new QVBoxLayout;
    QVBoxLayout * right_layout = new QVBoxLayout;

    left_layout->addWidget(this->filesystem_widget_);
    left_layout->addWidget(this->log_widget_);

    mid_layout->addWidget(this->process_widget_);

    right_layout->addWidget(this->plot_widget_);
    right_layout->addWidget(this->noise_widget_);
    right_layout->addWidget(line);
    right_layout->addWidget(this->spectrum_widget_);

    main_layout->addLayout(left_layout);
    main_layout->addLayout(mid_layout);
    main_layout->addLayout(right_layout);

    this->setLayout(main_layout);
}