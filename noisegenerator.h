#ifndef NOISEGENERATOR_H
#define NOISEGENERATOR_H

#include <QWidget>
#include <QPen>
#include <QPainter>
#include "src/valueNoise.h"
#include "src/bicubicNoise.h"
#include "src/bilinearNoise.h"
#include "src/smoothstepNoise.h"

namespace Ui {
class NoiseGenerator;
}

class NoiseGenerator : public QWidget
{
    Q_OBJECT

public:
    explicit NoiseGenerator(QWidget *parent = nullptr);
    ~NoiseGenerator();

public slots:
    void generate() const;
    void stateScale() const;

private:
    Ui::NoiseGenerator *ui;
};

#endif // NOISEGENERATOR_H
