#include "principal.h"
#include "ui_principal.h"

#define DEFAULT_ANCHO 3

Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);
    // Instanciando la imagen (creando)
    mImagen = new QImage(this->size(),QImage::Format_ARGB32_Premultiplied);
    // Rellenar la imagen de color blanco
    mImagen->fill(Qt::white);
    // Instanciar el Painter a partir de la imagen
    mPainter = new QPainter(mImagen);
    mPainter->setRenderHint(QPainter::Antialiasing);
    // Inicializar otras variables
    mPuedeDibujar = false;
    mColor = Qt::black;
    mAncho = DEFAULT_ANCHO;
    mNumLineas = 0;
    mOpcion = -1; // Para no iniciar ninguna accion
}

Principal::~Principal()
{
    delete ui;
    delete mPainter;
    delete mImagen;
}

void Principal::paintEvent(QPaintEvent *event)
{
    // Crear el painter de la ventana principal
    QPainter painter(this);
    // Dibujar la imagen
    painter.drawImage(0, 0, *mImagen);
    // Aceptar el evento
    event->accept();
}

void Principal::mousePressEvent(QMouseEvent *event)
{
    mPuedeDibujar = true;
    mInicial = event->pos();
    event->accept();
}

void Principal::mouseMoveEvent(QMouseEvent *event)
{
    // Validar si se puede dibujar
    if ( !mPuedeDibujar ) {
        event->accept();
        return;
    }
    if(mOpcion == 1){
        mFinal = event->pos();
        pincel.setColor(mColor);
        pincel.setWidth(mAncho);

        mPainter->setPen(pincel);
    }
    if(mOpcion == 2){
        mFinal = event->pos();

        pincel.setColor(mColor);
        pincel.setWidth(mAncho);
        // Dibujar puntos como lineas
        mPainter->setPen(pincel);
        mPainter->drawLine(mInicial, mFinal);

        // actualizar el punto inicial
        mInicial = mFinal;
        update();

        // Mostrar el número de líneas en la barra de estado
        ui->statusbar->showMessage(tr("Número de líneas: ") + QString::number(++mNumLineas));
    }
    if(mOpcion == 3){
        mFinal = event->pos();
        pincel.setColor(mColor);
        pincel.setWidth(mAncho);

        mPainter->setPen(pincel);
    }
    if(mOpcion == 4){
        mFinal = event->pos();
        pincel.setColor(mColor);
        pincel.setWidth(mAncho);

        mPainter->setPen(pincel);
    }
}

void Principal::mouseReleaseEvent(QMouseEvent *event)
{
    mPuedeDibujar = false;

    if(mOpcion == 1){
        QLine line(mInicial, mFinal);
        mPainter->drawLine(line);
        ui->statusbar->showMessage(tr("Número de líneas: ") + QString::number(++mNumLineas));
    }else if(mOpcion == 3){
        QRect rect(mInicial, mFinal);
        mPainter->drawRect(rect);
        ui->statusbar->showMessage(tr("Número de líneas: ") + QString::number(++mNumLineas));
    }else if(mOpcion == 4){
        QRect rect(mInicial, mFinal);
        mPainter->drawEllipse(rect);
        ui->statusbar->showMessage(tr("Número de líneas: ") + QString::number(++mNumLineas));
    }
    update();
    event->accept();
}

void Principal::on_actionAncho_triggered()
{
    mAncho = QInputDialog::getInt(this,
                                  tr("Ancho del pincel"),
                                  tr("Ingrese el ancho del pincel de dibujo"),
                                  mAncho,
                                  1, 100);
}

void Principal::on_actionSalir_triggered()
{
    this->close();
}

void Principal::on_actionColor_triggered()
{
    mColor = QColorDialog::getColor(mColor,
                                    this,
                                    tr("Color del pincel"));
}

void Principal::on_actionNuevo_triggered()
{
    mImagen->fill(Qt::white);
    mNumLineas = 0;
    update();
}

void Principal::on_actionGuardar_triggered()
{
    QString nombreArchivo = QFileDialog::getSaveFileName(this,
                                                         "Guardar imagen",
                                                         QString(),
                                                         "Imágenes (*.png)");
    if ( !nombreArchivo.isEmpty() ){
        if (mImagen->save(nombreArchivo))
            QMessageBox::information(this,
                                     "Guardar imagen",
                                     "Archivo almacenado en: " + nombreArchivo);
        else
            QMessageBox::warning(this,
                                 "Guardar imagen",
                                 "No se pudo almacenar la imagen.");
    }
}

void Principal::on_actionLineas_triggered()
{
    ui->actionLineas->setChecked(true);
    ui->actionLibre->setChecked(false);
    ui->actionRect_nculos->setChecked(false);
    ui->actionCircunferencias->setChecked(false);
    mOpcion = 1;
}

void Principal::on_actionLibre_triggered()
{
    ui->actionLibre->setChecked(true);
    ui->actionLineas->setChecked(false);
    ui->actionRect_nculos->setChecked(false);
    ui->actionCircunferencias->setChecked(false);
    mOpcion = 2;
}

void Principal::on_actionRect_nculos_triggered()
{
    ui->actionRect_nculos->setChecked(true);
    ui->actionLineas->setChecked(false);
    ui->actionLibre->setChecked(false);
    ui->actionCircunferencias->setChecked(false);
    mOpcion = 3;
}

void Principal::on_actionCircunferencias_triggered()
{
    ui->actionCircunferencias->setChecked(true);
    ui->actionLineas->setChecked(false);
    ui->actionLibre->setChecked(false);
    ui->actionRect_nculos->setChecked(false);
    mOpcion = 4;
}
