#ifndef COORD_H
#define COORD_H

#include "Utils.h"

namespace Hive {

class Coordinate {
    int x;
    int y;
    int z;
public:
    Coordinate(int x, int y, int z=0) : x(x), y(y),z(z) {} // oblige a construire avec valeurs pour x et y mais z=0 par defaut
    //mettre a jour les fonctions pour la hauteur
    int getX() const { return x; }
    int getY() const { return y; }
    void setX(int newx) { x = newx; }
    void setY(int newy) { y = newy; }
    int getZ()const {return z;}
    void setZ(int newz) { z = newz; }

    bool operator==(const Coordinate& other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }

    bool operator!=(const Coordinate& other) const
    {
        return x != other.x || y != other.y || z != other.z;
    }

    bool operator<(const Coordinate& other) const
    {
        return x < other.x || (x == other.x && y < other.y) || (x == other.x && y == other.y && z<other.z);
    }
    Coordinate operator+(const Coordinate& other) const
    {
        return Coordinate(x + other.x, y + other.y, z + other.z);
    }

    vector<Coordinate> getAdjacentCoordinates() const {
        return {
            {x + 1, y - 1}, {x + 1, y}, {x, y + 1},
            {x - 1, y + 1}, {x - 1, y}, {x, y - 1}
        };
    }
    static int hexDistance(const Coordinate& a, const Coordinate& b) {
        int dx = a.x - b.x;
        int dy = a.y - b.y;
        int dz = -(a.x + a.y) - (b.x + b.y);
        return std::max({ std::abs(dx), std::abs(dy), std::abs(dz) });
    }

};


inline std::ostream& operator<<(ostream& f,const Coordinate& c)
{
    f<<"("<<c.getX()<<","<<c.getY()<<","<<c.getZ()<<")";
    return f;
}

}

#endif
