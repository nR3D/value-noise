#include "noisegenerator.h"
#include "ui_noisegenerator.h"

NoiseGenerator::NoiseGenerator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NoiseGenerator)
{
    ui->setupUi(this);

    // connect slot generate()
    connect(ui->bilinearButton, SIGNAL(clicked()), this, SLOT(generate()));
    connect(ui->smoothstepButton, SIGNAL(clicked()), this, SLOT(generate()));
    connect(ui->bicubicButton, SIGNAL(clicked()), this, SLOT(generate()));
    connect(ui->seedValue, SIGNAL(valueChanged(int)), this, SLOT(generate()));
    connect(ui->sizeValue, SIGNAL(valueChanged(int)), this, SLOT(generate()));
    connect(ui->scaleValue, SIGNAL(valueChanged(int)), this, SLOT(generate()));

    // connect adaptive scale
    connect(ui->adaptiveCheck, SIGNAL(stateChanged(int)), this, SLOT(stateScale()));

    // initial generation
    generate();
}

void NoiseGenerator::generate() const
{
    int seed = ui->seedValue->value(), sizeCanvas = ui->sizeValue->value(), scaleFactor;
    if(ui->adaptiveCheck->isEnabled() && ui->adaptiveCheck->isChecked())
    {
        scaleFactor = 375/sizeCanvas > 2 ? 375/sizeCanvas : 2;
        if(scaleFactor > 2 && sizeCanvas%375!=0)
            ++scaleFactor;
    }
    else
        scaleFactor = ui->scaleValue->value();

    QImage qi(sizeCanvas*scaleFactor, sizeCanvas*scaleFactor, QImage::Format_RGB32);
    QPainter p(&qi);

    float (*interpolation)(float,float,int,float*,int);
    if(ui->bilinearButton->isChecked())
        interpolation = bilinearValueNoise;
    else if(ui->smoothstepButton->isChecked())
        interpolation = smoothstepValueNoise;
    else
        interpolation = bicubicValueNoise;
    float* grid = valueNoise2d(sizeCanvas, scaleFactor, 110, 120, interpolation, seed+1);
    for(int i=0; i < sizeCanvas*sizeCanvas*scaleFactor*scaleFactor; i++)
    {
    if(grid[i] > 255)
        grid[i] = 255;
    else if(grid[i] < 0)
        grid[i] = 0;
    QColor grayColor(grid[i], grid[i], grid[i]);
    p.setPen(QPen(grayColor));
    p.drawPoint(i%(sizeCanvas*scaleFactor), i/(sizeCanvas*scaleFactor));
    }
    p.end();
    delete[] grid;

    ui->mapNoise->setPixmap(QPixmap::fromImage(qi));
}

void NoiseGenerator::stateScale() const
{
    if(ui->scaleValue->isEnabled())
    {
        ui->scaleValue->setEnabled(false);
        ui->scaleLabel->setEnabled(false);
    }
    else
    {
        ui->scaleValue->setEnabled(true);
        ui->scaleLabel->setEnabled(true);
    }
    generate();
}

NoiseGenerator::~NoiseGenerator()
{
    delete ui;
}
