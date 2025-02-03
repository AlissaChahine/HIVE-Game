#ifndef TOKEN_H
#define TOKEN_H

#include "Utils.h"
#include "Coordinate.h"

#include <QGraphicsPolygonItem>
#include <QLabel>
#include <QGraphicsTextItem>
#include <QFont>
#include <QVector>
#include <QPointF>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <iostream>
#define SCALE 10

namespace Hive
{
class Token /*: public QGraphicsPolygonItem*/
{
private:
    PlayerColor color;
    TypeInsect insect;
    // QGraphicsTextItem *textItem{nullptr}; // Affichage du type d'insecte
    Coordinate *coordinate = nullptr;
    bool active{false}; // si la piece est sur le plateau ou non
    int board_level;	// pour le scarabe ou cocinnelle etc "hauteur"
    int id;				// pour identifier Spider 1,2...
    bool justSlider;

public:
    Token(PlayerColor c, TypeInsect i, int ID, bool slider)
        : color(c), insect(i), id(ID), justSlider(slider), board_level(0)
    {
        // // Définir la forme de l'hexagone
        // QVector<QPointF> points{
        //                         QPointF(0, 4) * SCALE,
        //                         QPointF(4, 2) * SCALE,
        //                         QPointF(4, -2) * SCALE,
        //                         QPointF(0, -4) * SCALE,
        //                         QPointF(-4, -2) * SCALE,
        //                         QPointF(-4, 2) * SCALE};


        // setPolygon(QPolygonF(points));
        // if(active){
        //     setPolygon(polygon().translated(getTokenCoordinate().getX()  * SCALE, getTokenCoordinate().getY()  * SCALE));
        // }
        // // Créer et configurer textItem
        // textItem = new QGraphicsTextItem(this);
        // textItem->setDefaultTextColor(Qt::yellow);  // Couleur jaune pour le texte
        // textItem->setFont(QFont("Arial", 10));     // Police et taille


        // // Initialiser le texte avec la valeur de l'attribut insect
        // updateTextItem();
    }

    virtual ~Token() {}

    Token(const Token &t) : color(t.color),
        insect(t.insect),
        coordinate(new Coordinate(t.coordinate->getX(), t.coordinate->getY(), t.coordinate->getZ())),
        active(t.active),
        board_level(t.board_level),
        id(t.id),
        justSlider(t.justSlider) {}

    // surcharge constructeur par recopie

    // void setTextColor(const QColor &color)
    // {
    //     if (textItem) {
    //         textItem->setDefaultTextColor(color);  // Mettre à jour la couleur du texte
    //     }
    // }
    // Méthode de peinture personnalisée pour afficher le jeton
    // void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override {
    //     // Définir la couleur de remplissage en fonction de la couleur du joueur
    //     QBrush brush;
    //     if (color == PlayerColor::White) {
    //         brush.setColor(Qt::white);
    //     } else {
    //         brush.setColor(Qt::black);
    //     }
    //     brush.setStyle(Qt::SolidPattern);  // Utiliser un motif de remplissage solide

    //     // Définir la bordure noire
    //     QPen pen;
    //     pen.setColor(Qt::yellow);   // Bordure jaune
    //     pen.setWidth(2);           // Largeur de la bordure

    //     // Appliquer le pinceau et le stylo au painter
    //     painter->setBrush(brush);
    //     painter->setPen(pen);

    //     // Dessiner l'hexagone avec remplissage et bordure
    //     painter->drawPolygon(polygon());

    //     // Appeler la méthode de base après avoir dessiné
    //     QGraphicsPolygonItem::paint(painter, option, widget);

    //     // Mettre à jour le texte
    //     updateTextItem();
    // }


    // // Méthode pour mettre à jour le texte de textItem
    // void updateTextItem() {
    //     if (textItem) {
    //         // Mettre à jour le texte à partir de l'insecte
    //         textItem->setPlainText(QString::fromStdString(Hive::insectTypeToString(insect)));

    // pour afficher les coordonnees au lieu du nom de l'insecte sur le plateau :
    /*if (this->active)
                textItem->setPlainText(QString("%1, %2").arg(coordinate->getX()).arg(coordinate->getY()));
            */

    //         // Positionner le texte au centre de l'hexagone
    //         QRectF hexBounds = boundingRect();
    //         QRectF textBounds = textItem->boundingRect();
    //         textItem->setPos(hexBounds.center() - QPointF(textBounds.width() / 2, textBounds.height() / 2));
    //     }
    // }


    // Méthode virtuelle pour obtenir les mouvements possibles (déplacements)
    virtual std::vector<Coordinate> getPossibleMoves() const = 0;
    vector<Coordinate> getPossiblePlacements() const;
    // Méthode virtuelle pour obtenir le type de l'insecte sous forme de chaîne de caractères
    virtual TypeInsect getType() const = 0;

    virtual vector<Coordinate> getPossibleMovesByCoordinate(const Coordinate &c) const = 0;
    bool canMove() const;
    PlayerColor getColor() const { return color; }
    TypeInsect getInsectType() const { return insect; }
    bool isActive() const { return active; }
    void setActive() { active = true; }
    int getLevel() const { return board_level; }
    void setLevel(int l) { board_level = l; }
    int getID() const { return id; }
    void setID(int i) { id = i; }
    const Coordinate &getTokenCoordinate() const { return *coordinate; }
    Coordinate &getTokenCoordinate()  { return *coordinate; }
    void setCoordinate(int x, int y, int z);
    void setCoordinate(int x, int y);

    bool getIsSlider() const { return justSlider; }

    bool canSlide(const Coordinate &coord, const Coordinate &dest) const;
    bool canSlideWithData(const Coordinate& coord, const Coordinate& dest, map<Coordinate, Token*>& board)const;

    virtual Token *deepCopy() const = 0; // méthode virtuelle pour cloner des insectes pr saveState()
};

// afficher un token
inline ostream &operator<<(ostream &f, const Token &token)
{
    string colorT;
    if (token.getColor() == PlayerColor::Black)
        colorT = "black";
    else
        colorT = "white";
    TypeInsect insectT = token.getType();
    f << colorT << " " << insectT;
    return f;
}

}

#endif
