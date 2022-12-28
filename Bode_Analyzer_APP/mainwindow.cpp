#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <math.h>
#include <QList>

#include "globales.h"
#include "libusb.h"

#define MOD_SAMPLES 10
#define PHASE_SAMPLES 10

#define MAX_POINTS 600


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->Connect_USB->setEnabled(true);

    ui->PlotWidget->plotLayout()->clear();

    magAxisRect = new QCPAxisRect(ui->PlotWidget);
    phaseAxisRect = new QCPAxisRect(ui->PlotWidget);

    ui->PlotWidget->plotLayout()->addElement(0, 0, magAxisRect);
    ui->PlotWidget->plotLayout()->addElement(1, 0, phaseAxisRect);

    //Se colocan los ejes en la capa de ejes, y la grilla en capa de grilla para dibujarlos en orden
    QList<QCPAxis*> allAxes;
    allAxes << magAxisRect->axes() << phaseAxisRect->axes();
    foreach (QCPAxis *axis, allAxes)
    {
        axis->setLayer("axes");
        axis->grid()->setLayer("grid");
    }

    //Eje de frecuencias logarítmico
    magAxisRect->axis(QCPAxis::atBottom)->grid()->setSubGridVisible(true);
    magAxisRect->axis(QCPAxis::atBottom)->setScaleType(QCPAxis::stLogarithmic);

    phaseAxisRect->axis(QCPAxis::atBottom)->grid()->setSubGridVisible(true);
    phaseAxisRect->axis(QCPAxis::atBottom)->setScaleType(QCPAxis::stLogarithmic);

    //Para separarlos en decadas
    QSharedPointer<QCPAxisTickerLog> logTicker(new QCPAxisTickerLog);
    magAxisRect->axis(QCPAxis::atBottom)->setTicker(logTicker);
    phaseAxisRect->axis(QCPAxis::atBottom)->setTicker(logTicker);

    ui->label_connection_ok->setText("<font color='green'>Conexión exitosa</font>");
    ui->label_connection_ok->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;

    if(connected > 0)
    {
        libusb_free_device_list(devs,1);
        libusb_exit(ctx);
    }
}

void MainWindow::on_Connect_USB_clicked()
{
    signed int r;
    unsigned int cnt;
    unsigned int i;
    signed int j, k, p;

    connected = 1;

    libusb_init(&ctx);

    libusb_set_debug(ctx, 3); //set verbosity level to 3, as suggested in the documentation

    cnt = libusb_get_device_list(ctx,&devs);

    qDebug() << "Hay" << cnt << "dispositivos conectados";

    for (i = 0; i < cnt; i++)
    {
        r = libusb_get_device_descriptor(devs[i],&desc);

        if(r < 0)
        {
            qDebug() << "Error con el device descriptor del dispositivo";
        }

        if(desc.idProduct == MY_PRODUCT && desc.idVendor == MY_VENDOR)
        {
            ui->Receive_USB->setEnabled(true);

            Dispositivo = i;

            qDebug() << "Mi dispositivo es el N°" << i;
            qDebug() << "Tiene " << desc.bNumConfigurations << " cantidad de configuraciones";
            qDebug() << "El Vendor ID es el N°: " << Qt::hex << desc.idVendor;
            qDebug() << "El Product ID es el N°: " << Qt::hex << desc.idProduct;
            qDebug() << "Device Class: " << desc.bDeviceClass;
            qDebug() << "Serial Number: " << desc.iSerialNumber;


            libusb_get_config_descriptor(devs[Dispositivo], 0, &config);


            qDebug() <<"Interfaces: "<<(uint8_t)config->bNumInterfaces;

            for(j=0; j<(uint8_t )(config->bNumInterfaces); j++)
            {
                 inter = &config->interface[j];

                 qDebug()<<"Cantidad de conf. alternativas: "<<(uint8_t) (inter->num_altsetting);

                 for(k=0; k < (uint8_t) (inter->num_altsetting); k++)
                 {
                     interdesc = &inter->altsetting[k];

                     qDebug() << "Cant. de Interfaces: "<<(uint8_t )interdesc->bInterfaceNumber;

                     qDebug() << "Cant. de Endpoints: "<<(uint8_t )interdesc->bNumEndpoints;

                     for(p= 0 ; p<(uint8_t )interdesc->bNumEndpoints; p++)
                     {
                            epdesc = &interdesc->endpoint[p];

                            qDebug() << "Tipo de Descriptor: "<<(uint8_t )epdesc->bDescriptorType;

                            qDebug() << "Dirección de EP: "<< Qt::hex << (uint8_t )epdesc->bEndpointAddress;
                     }

                 }
            }

            libusb_free_config_descriptor(config);


            r = libusb_open(devs[Dispositivo],&dev_handle);

            if(r<0)
            {
                qDebug() << "Error" << r << "abriendo dispositivo";
                ui->label_connection_ok->setText("<font color='red'>Error conectando con dispositivo</font>");
                ui->label_connection_ok->setVisible(true);
                return;
            }
            else
            {
                ui->label_connection_ok->setText("<font color='green'>Conexión exitosa</font>");
                ui->label_connection_ok->setVisible(true);
                return;
            }
        }
    }
    ui->label_connection_ok->setText("<font color='red'>Bode Analyzer no conectado</font>");
    ui->label_connection_ok->setVisible(true);
}

void MainWindow::on_Receive_USB_clicked()
{
//    unsigned char RxData [TRANSFER_SIZE];

//    QList<float*> freq_mag_phase;

    int actual_length;

    unsigned char freq_char[MAX_POINTS*4];
    unsigned char mag_char[MOD_SAMPLES*4];
    unsigned char phase_char[PHASE_SAMPLES*4];

    float* freq;
    float* mag_samples;
    float* phase_samples;

    float mag_mean[MAX_POINTS];

    float vin_ui[MAX_POINTS];
    float vout_ui[MAX_POINTS];
    float mag_ui[MAX_POINTS];

    float acumulador_vin;
    float acumulador_vout;
    float acumulador_phase;

    float vin_mean[MAX_POINTS] = {0};
    float vout_mean[MAX_POINTS] = {0};

    float phase_mean[MAX_POINTS];
    float phase_ui[MAX_POINTS];

    libusb_claim_interface(dev_handle, 0);

    //38 transferencias de usb para recuperar 4bytes * 600 de 64 bytes cada transfer

    //pide primero la cantidad de puntos calculados
    unsigned char total_points_char[4];

    libusb_interrupt_transfer(dev_handle, 0x81 , total_points_char, 4 , &actual_length, 0);

    unsigned int total_points = *(unsigned int*)total_points_char;

    if(total_points>0 && total_points <= MAX_POINTS) // hay datos y son menos del máximo
    {
        libusb_interrupt_transfer(dev_handle, 0x81, freq_char, 4*total_points , &actual_length , 0);

        freq = (float*)freq_char; //Casteo la data para trabajar con los floats

        for(unsigned int i = 0; i<total_points; i++)
        {
            libusb_interrupt_transfer(dev_handle , 0x81 , mag_char , 4*MOD_SAMPLES * 2 , &actual_length , 0);

            libusb_interrupt_transfer(dev_handle , 0x81 , phase_char , 4*PHASE_SAMPLES , &actual_length , 0);

            mag_samples = (float*)mag_char;

            phase_samples = (float*)phase_char;

            //Media de tensiones de vin y vout
            for(unsigned int k = 0; k< MOD_SAMPLES*2; k+=2)
            {
                vin_mean[i] += mag_samples[k];
                vout_mean[i] += mag_samples[k+1];
            }
            vin_mean[i] /= MOD_SAMPLES;
            vout_mean[i] /= MOD_SAMPLES;

            acumulador_vin = 0;
            acumulador_vout = 0;

            //Incertidumbres tipo A de vin y vout
            for(unsigned int j = 0; j<MOD_SAMPLES*2; j+=2)
            {
                acumulador_vin += (mag_samples[j] - vin_mean[i]) * (mag_samples[j] - vin_mean[i]);
                acumulador_vout += (mag_samples[j+1] - vout_mean[i]) * (mag_samples[j+1] - vout_mean[i]);
            }

            vin_ui[i] = sqrt(acumulador_vin/(MOD_SAMPLES*(MOD_SAMPLES-1)));
            vout_ui[i] = sqrt(acumulador_vout/(MOD_SAMPLES*(MOD_SAMPLES-1)));

            //Media de fase
            for(unsigned int k = 0; k<PHASE_SAMPLES; k++)
                phase_mean[i] += phase_samples[k];

            phase_mean[i] /= PHASE_SAMPLES;

            //Incertidumbre tipo A de fase
            acumulador_phase = 0;
            for(unsigned int j = 0; j<PHASE_SAMPLES; j++)
                acumulador_phase += (phase_samples[j] - phase_mean[i]) * (phase_samples[j] - phase_mean[i]);

            phase_ui[i] = sqrt(acumulador_phase/(MOD_SAMPLES*(MOD_SAMPLES-1)));
        }




        Filter* filtro = new Filter(freq,mag_mean,phase_mean,total_points);
        filters.append(filtro);

        ui->PlotWidget->addGraph(magAxisRect->axis(QCPAxis::atBottom), magAxisRect->axis(QCPAxis::atLeft));
        ui->PlotWidget->graph(0)->setPen(QPen(Qt::red));
        ui->PlotWidget->graph(0)->data()->set(filters.last()->mag);

        ui->PlotWidget->addGraph(phaseAxisRect->axis(QCPAxis::atBottom), phaseAxisRect->axis(QCPAxis::atLeft));
        ui->PlotWidget->graph(1)->setPen(QPen(Qt::blue));
        ui->PlotWidget->graph(1)->data()->set(filters.last()->phase);

    }
        //no hay datos

    ui->PlotWidget->rescaleAxes();
    ui->PlotWidget->replot();
    ui->PlotWidget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

void MainWindow::on_Reset_Axis_clicked()
{
    ui->PlotWidget->rescaleAxes();
    ui->PlotWidget->replot();
}

