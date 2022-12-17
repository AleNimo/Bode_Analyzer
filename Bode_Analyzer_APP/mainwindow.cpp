#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <math.h>
#include <QList>

#include "globales.h"
#include "libusb.h"



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

    r = libusb_init(&ctx);

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
                return;
            }
        }
    }
}

void MainWindow::on_Receive_USB_clicked()
{

//    unsigned char RxData [TRANSFER_SIZE];

//    QList<float*> freq_mag_phase;

//    unsigned char RxDataTotal[2400];

//    float* RxData_float;

//    int actual_length;

//    libusb_claim_interface(dev_handle, 0);

//    //38 transferencias de usb para recuperar 4bytes * 600 de 64 bytes cada transfer

//    //pide primero la cantidad de puntos calculados
//    unsigned char total_points = 0;
//    libusb_interrupt_transfer(dev_handle , 0x81 , &total_points , 1 , &actual_length , 0);

//    if(total_points>0) // hay datos
//    {
//        for(unsigned char n = 0; n<3;n++)
//        {
//            for(unsigned char i = 0; i<37;i++)
//            {
//                libusb_interrupt_transfer(dev_handle , 0x81 , RxData , sizeof (RxData) , &actual_length , 0);
//                for(unsigned char j = 0;j<64;j++)
//                    RxDataTotal[i*64+j] = RxData[j];
//            }
//            //ultima transferencia
//            libusb_interrupt_transfer(dev_handle , 0x81 , RxData , sizeof (RxData) , &actual_length , 0);
//            for(unsigned char j = 0;j<32;j++)
//                RxDataTotal[37*64+j] = RxData[j];

//            //Casteo de la data en byts de freq,mag,phase a float
//            float* aux = new float[total_points];
//            aux = (float*) RxDataTotal;
//            freq_mag_phase.append(aux);

//        }

//        Filter* filtro = new Filter(freq_mag_phase[0],freq_mag_phase[1],freq_mag_phase[2],total_points);
//        filters.append(filtro);

//        ui->PlotWidget->addGraph(magAxisRect->axis(QCPAxis::atBottom), magAxisRect->axis(QCPAxis::atLeft));
//        ui->PlotWidget->graph(0)->setPen(QPen(Qt::red));
//        ui->PlotWidget->graph(0)->data()->set(filters[0]->mag);

//        ui->PlotWidget->addGraph(phaseAxisRect->axis(QCPAxis::atBottom), phaseAxisRect->axis(QCPAxis::atLeft));
//        ui->PlotWidget->graph(1)->setPen(QPen(Qt::blue));
//        ui->PlotWidget->graph(1)->data()->set(filters[0]->phase);


////        ui->PlotWidget->addGraph();
////        ui->PlotWidget->graph(0)->setData()
//        //ui->gridLayout->addWidget(filters.last()->chart);

//    }else
//        //no hay datos

    float freq[] = {1, 50, 100000};
    float mag[] = {0, -3, -40};
    float phase[] = {0, -45, -90};
    unsigned int total_points = 3;

    Filter* filtro = new Filter(freq,mag,phase,total_points);
    filters.append(filtro);

    ui->PlotWidget->addGraph(magAxisRect->axis(QCPAxis::atBottom), magAxisRect->axis(QCPAxis::atLeft));
    ui->PlotWidget->graph(0)->setPen(QPen(Qt::red));
    ui->PlotWidget->graph(0)->data()->set(filters[0]->mag);

    ui->PlotWidget->addGraph(phaseAxisRect->axis(QCPAxis::atBottom), phaseAxisRect->axis(QCPAxis::atLeft));
    ui->PlotWidget->graph(1)->setPen(QPen(Qt::blue));
    ui->PlotWidget->graph(1)->data()->set(filters[0]->phase);

    ui->PlotWidget->rescaleAxes();
    ui->PlotWidget->replot();
    ui->PlotWidget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    //qDebug() << "Dispositivo N°:" << Dispositivo;
}


