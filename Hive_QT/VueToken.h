#ifndef VUETOKEN_H
#define VUETOKEN_H


#include <QPen>
#include <QBrush>
#include <QPolygonF>
#include <QPointF>
#include <QGraphicsPolygonItem>
#include <QColor>
#include "Token.h"
#include <QGraphicsTextItem>
#include <QGraphicsItem>
#include "Utils.h"
#include <QGraphicsSceneMouseEvent>
#include <QObject>


class VueToken : public QObject, public QGraphicsPolygonItem
{
    Q_OBJECT
public :
    VueToken(Hive::Token &t, QGraphicsItem *parent=nullptr);
    VueToken(Hive::Coordinate &c,QGraphicsItem *parent=nullptr);
    QColor convertColor(Hive::PlayerColor c);
    ~VueToken(){token=nullptr;
        delete coord;}

    void setTextColor(const QColor &color);
    void updateTextItem();
    void colorier( Hive::PlayerColor c);
    bool tokenPresent() const { return token != nullptr; }
    Hive::Token & gettoken(){return *token;}

    const Hive::Token & gettoken()const {return *token;}
    void setToken(Hive::Token &t);
    void affichageToken();
    bool isClickable() const {return Clickable;}
    void setClickable(){Clickable=true;}
    void setNonClickable(){Clickable=false;}
    void setCoordinate(){if (token!=nullptr) coord=&token->getTokenCoordinate();}
    const Hive::Coordinate & getcoord()const {return *coord;}
    void setCoord(int x,int y, int z){coord=new Hive::Coordinate(x,y,z);}
private:

    Hive::Token * token;
    QGraphicsTextItem * type;
    QPen pen;
    QBrush brush;
    bool Clickable=true;
    Hive::Coordinate* coord;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
signals :

    void tokenClicked(VueToken*);
    // private slots:
    //     void clickedEvent() { emit tokenClicked(this); }




};

#endif
