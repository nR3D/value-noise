#include "src/valueNoise.h"
#include "src/bicubicNoise.h"
#include "src/bilinearNoise.h"
#include "src/smoothstepNoise.h"
#include <QApplication>
#include <QLabel>
#include <QPen>
#include <QPainter>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QLabel ql;
    int sizeCanvas = 4;
    int scaleFactor = 128;
    QImage qi(sizeCanvas*scaleFactor, sizeCanvas*scaleFactor, QImage::Format_RGB32);
    QPainter p(&qi);
    
    float (*interpolation)(float,float,int,float*,int) = bicubicValueNoise;
    float* grid = valueNoise2d(sizeCanvas, scaleFactor, 110, 120, interpolation, 1234);
    for(int i=0; i < sizeCanvas*sizeCanvas*scaleFactor*scaleFactor; i++)
    {
	if(grid[i] > 255 || grid[i] < 0)
	    std::cout << i << ": " << grid[i] << std::endl;
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

    ql.setPixmap(QPixmap::fromImage(qi));
    ql.show();

    return a.exec();
}
