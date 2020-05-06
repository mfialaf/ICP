#include "path.h"
#include <math.h>

//MARIN JE KOKOT <3

Path::Path()
{

}

Path::Path(QList<Coordinate> pathsC)
{
    paths = pathsC;
}

double Path::getDistanceOfCoordinates(Coordinate a, Coordinate b)
{
    return sqrt( pow((a.getX() - b.getX()),2) + pow((a.getY() - b.getY()),2));
}


