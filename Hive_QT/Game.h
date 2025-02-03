// #ifndef GAME_H_INCLUDED
// #define GAME_H_INCLUDED

// #include <list>
// #include "Utils.h"
// #include "Player.h"
// #include "Match.h"
// #include "GameException.h"
// #include <memory>
// #include "IA.h"
// using namespace std;
// namespace Hive
// {
//     class Game
//     {
//         std::shared_ptr<Player> playerwhite;
//         std::shared_ptr<Player> playerBlack;
//         bool PlayerIA;
//         Match* match;
//         int undocount; // retour arriere
//         // bool isGameOver;
//         std::vector<Hive::TypeInsect> vect_extension;

//         // si on fait plusieurs parties on peut faire un tableau
//         // si on fait plusieurs parties on peut faire un score final
//         // Match *match;
//         // int nb_match;
//         // int max_match;
//         // Score final_score; pas sur de que�a soit le role du jeu

//         //constructeur privé car singleton
//         Game(string nom1="White", string nom2="Black")
//         {
//            /* if (nom1.empty() || nom2.empty())
//             {
//                 throw GameException("Les noms des joueurs ne peuvent pas être vides.");
//             }*/
//             // on crée les joueurs
//             //  on initialise playerIA, undocout, et le reste

//             playerwhite = std::make_shared<Player>(PlayerColor::White, nom1);
//             playerBlack = std::make_shared<Player>(PlayerColor::Black, nom2);
//             // c'est dans play qu'on crée match et on demande les extensions
//             match = nullptr;
//             PlayerIA = 0;
//             undocount = 0;
//             // vect_extension reste vide
//         }
//     public:
//         // si on fait plusieurs parties constructeur met le tableau de partie � nullptr

//         // explicit Game(string  nom1, string nom2) :playerwhite(nom1, PlayerColor::White), playerBlack(nom2, PlayerColor::Black) {}
//         //  avec IA :
//         //  explicit Game(string nom1) :playerwhite(nom1, White), playerBlack(nullptr) {}

//         //methode statique pour obtenir l'instance unique
//         static Game& getInstance(const std::string& nom1 = "White", const std::string& nom2 = "Black") {
//             static Game instance(nom1, nom2); // variable statique locale
//             return instance;
//         }

//         ~Game() {
//             delete match;
//         }
//         Game(const Game& g) = delete;
//         Game& operator=(const Game& g) = delete;

//         //const Player& getPlayerWhite() const { return *playerwhite; }
//         //const Player& getPlayerBlack() const { return *playerBlack; }
//         Match& getMatch()const { return *match; }
//         std::vector<Hive::TypeInsect> const& getVect_extension() const { return vect_extension; }
//         void setPlayerIA();

//         void setPlayerNames();

//         void setExtension();

//         void startMatch();
//         int playerTurn();
//         int IATurn();
//         void play();
//         void finishMatch();
//     };

// }


// #endif // GAME_H_INCLUDED
#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <list>
#include "Utils.h"
#include "Player.h"
#include "Match.h"
#include "GameException.h"
#include <memory>
#include "IA.h"
using namespace std;
namespace Hive
{
class Game
{
    std::shared_ptr<Player> playerwhite;
    std::shared_ptr<Player> playerBlack;
    bool PlayerIA;
    Match* match;
    int undocount; // retour arriere
    // bool isGameOver;
    std::vector<Hive::TypeInsect> vect_extension;
    MatchCount num = MatchCount::First;

    // si on fait plusieurs parties on peut faire un tableau
    // si on fait plusieurs parties on peut faire un score final
    // Match *match;
    // int nb_match;
    // int max_match;
    // Score final_score; pas sur de que�a soit le role du jeu

    //constructeur privé car singleton
    Game(string nom1="White", string nom2="Black")
    {
        /* if (nom1.empty() || nom2.empty())
            {
                throw GameException("Les noms des joueurs ne peuvent pas être vides.");
            }*/
        // on crée les joueurs
        //  on initialise playerIA, undocout, et le reste

        playerwhite = std::make_shared<Player>(PlayerColor::White, nom1);
        playerBlack = std::make_shared<Player>(PlayerColor::Black, nom2);
        // c'est dans play qu'on crée match et on demande les extensions
        match = nullptr;
        PlayerIA = 0;
        undocount = 0;
        // vect_extension reste vide
    }
public:
    // si on fait plusieurs parties constructeur met le tableau de partie � nullptr

    // explicit Game(string  nom1, string nom2) :playerwhite(nom1, PlayerColor::White), playerBlack(nom2, PlayerColor::Black) {}
    //  avec IA :
    //  explicit Game(string nom1) :playerwhite(nom1, White), playerBlack(nullptr) {}

    //methode statique pour obtenir l'instance unique
    static Game& getInstance(const std::string& nom1 = "White", const std::string& nom2 = "Black") {
        static Game instance(nom1, nom2); // variable statique locale
        return instance;
    }

    ~Game() {
        delete match;
    }
    Game(const Game& g) = delete;
    Game& operator=(const Game& g) = delete;

    //const Player& getPlayerWhite() const { return *playerwhite; }
    //const Player& getPlayerBlack() const { return *playerBlack; }
    Match& getMatch()const { return *match; }
    std::vector<Hive::TypeInsect> const& getVect_extension() const { return vect_extension; }
    void setPlayerIA();
    void setPlayerNames();
    void setExtension();
    void startMatch();
    int playerTurn();
    int IATurn();
    void play();
    void finishMatch(int choix_rejouer);
    void deleteMatch();
    void setPlayerIA(int level);
    void setPlayerNames(string name1, string name2);
    void setExtension(int choix);

    // pour pvr utiliser dans Qt en attendant d'avoir le menu
    void setGameQt() {
        playerwhite = std::make_shared<Player>(PlayerColor::White, "A");
        playerBlack = std::make_shared<Player>(PlayerColor::Black, "B");
        vect_extension.push_back(Hive::TypeInsect::Ladybug);
        vect_extension.push_back(Hive::TypeInsect::Mosquito);
        match = new Match(playerwhite, playerBlack, 11+vect_extension.size(), vect_extension);
        playerwhite->setName("Au");
        playerBlack->setName("Bc");
    }
};
}

#endif // GAME_H_INCLUDED

