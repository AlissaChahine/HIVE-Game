#include "VueToken.h"

VueToken::VueToken(Hive::Token &t, QGraphicsItem *parent):QObject(),QGraphicsPolygonItem(parent), token(&t),coord(nullptr){


    // Création des points de l'hexagone
    QPolygonF hexagon;

    hexagon << QPoint(0, 40)  << QPoint(40, 20)  << QPoint(40, -20)  << QPoint(0, -40)
            << QPoint(-40, -20)  << QPoint(-40, 20) ;

    this->setPolygon(QPolygonF(hexagon));
    colorier(token->getColor());

    type = new QGraphicsTextItem("", this);
    //changer la couleur du texte

    updateTextItem();






}
VueToken::VueToken(Hive::Coordinate & c,QGraphicsItem *parent):QObject(),QGraphicsPolygonItem(parent),token(nullptr),coord(new Hive::Coordinate(c.getX(),c.getY(),c.getZ())){

    // Création des points de l'hexagone
    QPolygonF hexagon;
    hexagon << QPoint(0, 40)  << QPoint(40, 20)  << QPoint(40, -20)  << QPoint(0, -40)
            << QPoint(-40, -20)  << QPoint(-40, 20) ;
    this->setPolygon(QPolygonF(hexagon));

    brush.setColor(QColor("#ffc0cb"));
    brush.setStyle(Qt::SolidPattern);
    pen.setColor(QColor("#722f37"));   // Bordure
    pen.setWidth(2);


    this->setBrush(brush);
    this->setPen(pen);
}

QColor VueToken::convertColor(Hive::PlayerColor c)
{

    if (c==Hive::PlayerColor::Black)
        return Qt::black;
    else
        return Qt::white;

}

// void VueToken::setTextColor(const QColor &color)
// {
//     if (type) {
//         type->setDefaultTextColor(color);  // Mettre à jour la couleur du texte
//     }
// // }
void VueToken::colorier(/*QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget,*/ Hive::PlayerColor c) {
    // Définir la couleur de remplissage en fonction de la couleur du joueur


    QColor color =convertColor(c);

    brush.setColor(color);
    brush.setStyle(Qt::SolidPattern);  // Utiliser un motif de remplissage solide

    // Définir la bordure
    //pen.setColor(Qt::blue);   // Bordure BLEU
    pen.setColor(QColor("#ff8849"));
    pen.setWidth(2);           // Largeur de la bordure

    // Appliquer le pinceau et le stylo au painter
    this->setBrush(brush);
    this->setPen(pen);

}
// Méthode pour mettre à jour le texte de textItem
void VueToken::updateTextItem() {
    if(!this->tokenPresent()){
        if (type) {
            type = new QGraphicsTextItem("", this);
            type->toPlainText();
            type->setPlainText(QString("%1, %2, %3")
                                   .arg(this->getcoord().getX())
                                   .arg(this->getcoord().getY())
                                   .arg(this->getcoord().getZ())
                               );
            type->setDefaultTextColor(QColor("#ff8849"));
            type->setFont(QFont("Arial", 10,QFont::Bold));
        }
    }
    else if (type) {
        // Mettre à jour le texte à partir de l'insecte
        type->setPlainText(QString::fromStdString(Hive::insectTypeToString(token->getInsectType())));

        /*
        if (token->isActive())
            type->setPlainText(QString("%1, %2, %3, %4")
                                   .arg(token->getTokenCoordinate().getX())
                                   .arg(token->getTokenCoordinate().getY())
                                   .arg(token->getTokenCoordinate().getZ())
                                   .arg(QString::fromStdString(Hive::insectTypeToString(token->getInsectType()))));
        */

        if (token->isActive())
            type->setPlainText(QString::fromStdString(Hive::insectTypeToString(token->getInsectType())));
        //type->setPlainText(QString("%2, H:%1")
        //                     .arg(token->getTokenCoordinate().getZ())
        //                   .arg(QString::fromStdString(Hive::insectTypeToString(token->getInsectType()))));

        //type->setDefaultTextColor(Qt::blue);  // Couleur pour le texte
        type->setDefaultTextColor(QColor("#ff8849"));
        type->setFont(QFont("Arial", 10,QFont::Bold));

        // Positionner le texte au centre de l'hexagone
        QRectF hexBounds = boundingRect();
        QRectF textBounds = type->boundingRect();
        type->setPos(hexBounds.center() - QPointF(textBounds.width() / 2, textBounds.height() / 2));
    }
}
void VueToken::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if (event->button() == Qt::LeftButton){
        if (Clickable)
        { emit tokenClicked(this);
                //QGraphicsPolygonItem::mousePressEvent(event);
        }
    }
}
void VueToken::affichageToken(){
    this->blockSignals(true);  // Bloquer temporairement les signaux

    setPos((coord->getX() * 80)
               + (coord->getY() * 40)
           , coord->getY() * 60);
    this->blockSignals(false);
    qDebug() << "Coord après setPos :" << coord;
}
void VueToken::setToken(Hive::Token &t){

    token=&t;
    colorier(token->getColor());

    type = new QGraphicsTextItem("", this);
    //changer la couleur du texte

    updateTextItem();

}
QVariant VueToken::itemChange(GraphicsItemChange change, const QVariant &value) {
    if (change == ItemPositionChange) {
        qDebug() << "itemChange détecté : Position change, valeur =" << value.toPointF();
        qDebug() << "Coord avant modification = " << coord;
    }
    return QGraphicsItem::itemChange(change, value);
}
