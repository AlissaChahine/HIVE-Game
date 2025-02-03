// <<<<<<< HEAD
// #include <QApplication>
// #include <QGraphicsScene>
// #include <QGraphicsView>
// #include <QPushButton>
// #include "VueToken.h"


// int main(int argc, char *argv[]) {
//     QApplication app(argc, argv);
//     QPushButton b;
//     VueToken vt(Qt::black);
//     QGraphicsPolygonItem* polynome= vt.createHexagon();

//     QGraphicsScene scene;
//     scene.addItem(polynome);
//     QGraphicsView view(&scene);
//     view.show();

//     return app.exec();
// =======
//
//#include "Match.h"
//
//
//int main() {
//    // Cr�ation des joueurs
//    Player whitePlayer(PlayerColor::White, "Alice");
//    Player blackPlayer(PlayerColor::Black, "Bob");
//
//    std::shared_ptr<Player> ptr1 = std::make_shared<Player>(whitePlayer);
//    std::shared_ptr<Player> ptr2 = std::make_shared<Player>(blackPlayer);
//    // Extension avec de nouveaux types d'insectes
//    std::vector<TypeInsect> extensions = { TypeInsect::Ladybug, TypeInsect::Mosquito };
//
//    // Initialisation de la partie
//    int nbPieces = 13; // Nombre total de pi�ces pour chaque joueur
//    Match match(ptr1, ptr2, nbPieces, extensions);
//
//    // Affichage des mains des joueurs
//    std::cout << "Main des pi�ces blanches :" << std::endl;
//    match.printhand(PlayerColor::White);
//
//    std::cout << "Main des pi�ces noires :" << std::endl;
//    match.printhand(PlayerColor::Black);
//
//    // Simulation de placement
//
//    Coordinate whiteBeePlacement(0, 0, 0);
//    Coordinate blackSpiderPlacement(1, 0, 0);
//    Token* twhite = match.getToken_noplaced(TypeInsect::Bee);
//    if (twhite != nullptr)
//        // Placer des pi�ces sur le plateau
//    {
//
//        std::cout << "Placement de l'abeille blanche au centre du plateau..." << std::endl;
//        if (match.placeOnBoard(twhite, whiteBeePlacement) == 1) {
//            std::cout << "Abeille plac�e avec succ�s !" << std::endl;
//            Board::getInstance().showBoard();
//        }
//        else {
//            std::cout << "Erreur lors du placement de l'abeille blanche !" << std::endl;
//        }
//    }
//    if (match.getCurrentPlayer().getColor() == PlayerColor::Black)
//    {
//        cout << "au tour du joueur" << match.getCurrentPlayer().getColor() << std::endl;
//    }
//    else
//        cout << "erreur du jeu" << endl;
//
//    Token* tblack = match.getToken_noplaced(TypeInsect::Spider);
//    if (tblack != nullptr)
//        // Placer des pi�ces sur le plateau
//    {
//        if (match.placeOnBoard(tblack, blackSpiderPlacement) == 1) {
//            std::cout << "Spider plac�e avec succ�s !" << std::endl;
//            Board::getInstance().showBoard();
//        }
//        else {
//            std::cout << "Erreur lors du placement de l'araign�e noire !" << std::endl;
//        }
//    }
//    if (match.getCurrentPlayer().getColor() == PlayerColor::White)
//    {
//        cout << "au tour du joueur" << match.getCurrentPlayer().getColor() << std::endl;
//    }
//    else
//        cout << "erreur du jeu" << endl;
//
//    whiteBeePlacement.setY(1);
//
//
//   if (match.placeOnBoard(twhite, whiteBeePlacement) == 1) {
//        std::cout << "Abeille plac�e avec succ�s !" << std::endl;
//        Board::getInstance().showBoard();
//    }
//    else {
//        std::cout << "Erreur lors du placement de l'abeille blanche !" << std::endl;
//    }
//   cout << "la main du joueur current" << endl;
//   match.printhand(match.getCurrentPlayer().getColor());
//
//   //essayer d'encercler la reine blanche
//
//   Token *beetleb= match.getToken_noplaced(TypeInsect::Beetle);
//   if (beetleb!= nullptr)
//   {
//       cout << "placements possibles pour la pieces" << endl;
//       match.showPlacements(beetleb);
//       Coordinate coorb2b(1, -1, 0);
//       if (match.placeOnBoard(beetleb, coorb2b) == 1) {
//           std::cout << "beetle plac�e avec succ�s !" << std::endl;
//           Board::getInstance().showBoard();
//       }
//       else {
//           std::cout << "Erreur lors du placement de beetle noire !" << std::endl;
//       }
//
//   }
//   Token* spiderw = match.getToken_noplaced(TypeInsect::Spider);
//   if (spiderw != nullptr)
//   {
//       cout << "placements possibles pour la pieces" << endl;
//       match.showPlacements(spiderw);
//       Coordinate coorsw(-1, 2, 0);
//       if (match.placeOnBoard(spiderw, coorsw) == 1) {
//           std::cout << "spider plac�e avec succ�s !" << std::endl;
//           Board::getInstance().showBoard();
//       }
//       else {
//           std::cout << "Erreur lors du placement de spider noire !" << std::endl;
//       }
//
//   }
//   Token* spiderb2 = match.getToken_noplaced(TypeInsect::Spider);
//   if (spiderb2 != nullptr)
//   {
//       cout << "placements possibles pour la pieces" << endl;
//       match.showPlacements(spiderb2);
//       Coordinate coorbb(2, -1, 0);
//       if (match.placeOnBoard(spiderb2, coorbb) == 1) {
//           std::cout << "spider plac�e avec succ�s !" << std::endl;
//           Board::getInstance().showBoard();
//       }
//       else {
//           std::cout << "Erreur lors du placement de spider noire !" << std::endl;
//       }
//
//   }
//   Token* beetlew = match.getToken_noplaced(TypeInsect::Beetle);
//   if (beetlew != nullptr)
//   {
//       cout << "placements possibles pour la pieces" << endl;
//       match.showPlacements(beetlew);
//       Coordinate coorbw(0, 2, 0);
//       if (match.placeOnBoard(beetlew, coorbw) == 1) {
//           std::cout << "beetle plac�e avec succ�s !" << std::endl;
//           Board::getInstance().showBoard();
//       }
//       else {
//           std::cout << "Erreur lors du placement de spider noire !" << std::endl;
//       }
//
//   }
//   Token* beeb2 = match.getToken_noplaced(TypeInsect::Bee);
//   if (beeb2 != nullptr)
//   {
//       cout << "placements possibles pour la pieces" << endl;
//       match.showPlacements(beeb2);
//       Coordinate coorbb2(2, 0, 0);
//       if (match.placeOnBoard(beeb2, coorbb2) == 1) {
//           std::cout << "beetle plac�e avec succ�s !" << std::endl;
//           Board::getInstance().showBoard();
//       }
//       else {
//           std::cout << "Erreur lors du placement de spider noire !" << std::endl;
//       }
//
//   }
//   Token* beetlew2 = match.getToken_noplaced(TypeInsect::Beetle);
//   if (beetlew2 != nullptr)
//   {
//       cout << "placements possibles pour la pieces" << endl;
//       match.showPlacements(beetlew2);
//       Coordinate coorbw2(-1, 1, 0);
//       if (match.placeOnBoard(beetlew2, coorbw2) == 1) {
//           std::cout << "beetle plac�e avec succ�s !" << std::endl;
//           Board::getInstance().showBoard();
//       }
//       else {
//           std::cout << "Erreur lors du placement de spider noire !" << std::endl;
//       }
//
//   }
//   Coordinate coorbb2(1, 1, 0);
//   match.showPlacements(beeb2);
//
//  if (match.placeOnBoard(beeb2, coorbb2) == 1) {
//       std::cout << "bee deplac�e avec succ�s !" << std::endl;
//       Board::getInstance().showBoard();
//   }
//   else {
//       std::cout << "Erreur lors du placement de spider noire !" << std::endl;
//   }
//
//  Token* beetlew3 = match.getToken_noplaced(TypeInsect::Beetle);
//  if (beetlew3 != nullptr)
//  {
//      cout << "placements possibles pour la pieces" << endl;
//      match.showPlacements(beetlew3);
//      Coordinate coorbw3(-2, 2, 0);
//      if (match.placeOnBoard(beetlew3, coorbw3) == 1) {
//          std::cout << "beetle plac�e avec succ�s !" << std::endl;
//          Board::getInstance().showBoard();
//      }
//      else {
//          std::cout << "Erreur lors du placement de spider noire !" << std::endl;
//      }
//
//  }
//  Coordinate coorb2b(0, 0, 0);
//  match.showPlacements(beetleb);
//
//  if (match.placeOnBoard(beetleb, coorb2b) == 1) {
//      std::cout << "bee deplac�e avec succ�s !" << std::endl;
//      Board::getInstance().showBoard();
//  }
//  else {
//      std::cout << "Erreur lors du placement de spider noire !" << std::endl;
//  }
//
//  cout << "l'abeille est elle encerclee ? " << match.checkGameOver() << endl;
//  cout << "le gagnant est " << match.getWinner().getColor() << endl;
//
//
//
//    /*  std::cout << "Placement de l'araign�e noire � c�t� de l'abeille blanche..." << std::endl;
//      if (match.placeOnBoard(blackSpider, blackSpiderPlacement) == 1) {
//          std::cout << "Araign�e noire plac�e avec succ�s !" << std::endl;
//      } else {
//          std::cout << "Erreur lors du placement de l'araign�e noire !" << std::endl;
//      }
//
//      // Affichage des placements possibles pour une pi�ce
//      std::cout << "Possibilit�s de placements pour l'abeille blanche :" << std::endl;
//      match.showPlacements(whiteBee);
//
//      // V�rification de l'�tat du jeu
//      if (match.checkGameOver()) {
//          std::cout << "Le jeu est termin�. Une abeille est encercl�e !" << std::endl;
//      } else {
//          std::cout << "Le jeu continue..." << std::endl;
//      }*/
//
//    return 0;
//}
//
//

/*#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

}
*/
