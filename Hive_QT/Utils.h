#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
using namespace std;

namespace Hive
{

enum class PlayerColor
{
    Black,
    White
};

enum class TypeInsect
{
    Bee,
    Spider,
    Ant,
    Beetle,
    Grasshopper,
    Ladybug,
    Mosquito
};

class HiveException
{
public:
    HiveException(const string& i) : info(i) {}
    string getInfo() const { return info; }

private:
    string info;
};


//operator<< pour PlayerColor
inline ostream& operator<<(ostream& os, const PlayerColor& color)
{
    switch (color)
    {
    case PlayerColor::Black:
        os << "Black";
        break;
    case PlayerColor::White:
        os << "White";
        break;
    }
    return os;
}

inline string insectTypeToString(TypeInsect type) {
    switch (type) {
    case TypeInsect::Ant: return "Ant";
    case TypeInsect::Beetle: return "Beetle";
    case TypeInsect::Spider: return "Spider";
    case TypeInsect::Grasshopper: return "Grasshopper";
    case TypeInsect::Bee: return "Bee";
    case TypeInsect::Ladybug: return "LadyBug";
    case TypeInsect::Mosquito: return "Mosquito";
    default: return "Unknown";
    }
}

//pperator<< pour TypeInsect
inline ostream& operator<<(ostream& os, const TypeInsect& insect)
{
    switch (insect)
    {
    case TypeInsect::Bee:
        os << "Bee";
        break;
    case TypeInsect::Spider:
        os << "Spider";
        break;
    case TypeInsect::Ant:
        os << "Ant";
        break;
    case TypeInsect::Beetle:
        os << "Beetle";
        break;
    case TypeInsect::Grasshopper:
        os << "Grasshopper";
        break;
    case TypeInsect::Ladybug:
        os << "Ladybug";
        break;
    case TypeInsect::Mosquito:
        os << "Mosquito";
        break;
    }
    return os;
}

//operator<< pour HiveException
inline ostream& operator<<(ostream& os, const HiveException& ex)
{
    os << "HiveException: " << ex.getInfo();
    return os;
}

enum class MatchCount {
    First,
    Several
};

}

#endif

