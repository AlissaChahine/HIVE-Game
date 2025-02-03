#include "Board.h"
using namespace std;
using namespace Hive;

Board& Board::getInstance()
{
    static Board instance; //instance unique de Board
    return instance;
}

//fonction pour afficher le contenu de la map

void Board::printBoard() const
{
    for (const auto& token : data)
    {
        cout << "Coordinate (" << token.first.getX() << ", " << token.first.getY() << ") : ";
        cout << token.second->getType() << endl;
    }
}

void Board::showBoard() const
{
    // affiche le plateau avec comme format pour une piece : |BW1(x,y)|
    // B ou W pour la couleur
    // La premiere lettre du type d'insecte (Q pour Queen Bee)
    // Son ID
    // ses coordonnees (x,y)

    if (data.empty()) {
        cout << "Le plateau est vide.\n";
        return;
    }

    int min = 0;
    int max = 0;
    for (const auto& token : data)
    {
        int x = token.first.getX();
        int y = token.first.getY();
        if (x > max) max = x;
        if (y > max) max = y;
        if (x < min) min = x;
        if (y < min) min = y;
    }

    // pour les marges ext
    max = max + 1;
    min = min - 1;

    int nbMax = max + abs(min) + 1; // pour gere la prsence de coord ngatives
    // pour retrouver la coordonne dans la map on fait r - abs(min)
    int space = 14;
    // if (min < 0) space = 12;

    int i = nbMax / 2;
    int vali = nbMax / 2;
    bool desc = false;
    //cout << "nbMax : " << nbMax << ", i:" << i;
    cout << "\n";

    for (int r = 0; r < nbMax; r++)
    {
        for (int q = 0; q < nbMax; q++)
        {
            if (q < i)
            {
                for (int s = 0; s < space / 2;s++) cout << " ";
            }
            else
            {
                cout << "|";
                for (int s = 0; s < space - 2;s++) cout << " ";
                cout << "|";
            }
        }
        cout << "\n";
        for (int q = 0; q < nbMax; q++)
        {
            if (q < i)
            {
                for (int s = 0; s < space / 2;s++) cout << " ";
            }
            else
            {
                //auto it0 = data.find(data.begin(), data.end(), Coordinate(q - abs(min), r - abs(min)) );
                auto it0 = data.find(Coordinate(q - abs(min), r - abs(min), 0));
                if (desc == true)
                {
                    it0 = data.find(Coordinate(vali, r - abs(min)));
                    vali++;
                }
                if (it0 != data.end()) //piece de niveau 0
                {
                    auto& it = it0;
                    auto it1 = data.find(Coordinate(q - abs(min), r - abs(min), 1));
                    if (desc == true)
                    {
                        vali--;
                        it1 = data.find(Coordinate(vali, r - abs(min), 1));
                        //auto it1 = data.find(Coordinate(q - abs(min), r - abs(min), 1));
                        vali++;
                    }
                    if (it1 != data.end()) //piece de niveau 1
                    {
                        it = it1;
                    }
                    cout << "|";
                    //PlayerColor colorI = it0->second->getColor();
                    if (it->second->getColor() == PlayerColor::Black)
                    {
                        cout << "B";
                    }
                    else cout << "W";
                    // TypeInsect typeI = it0->second->getInsectType();
                    if (it->second->getInsectType() == TypeInsect::Bee)
                    {
                        cout << "Q"; //queen B
                    }
                    else if (it->second->getInsectType() == TypeInsect::Spider) cout << "S";
                    else if (it->second->getInsectType() == TypeInsect::Ant) cout << "A";
                    else if (it->second->getInsectType() == TypeInsect::Beetle) cout << "B";
                    else if (it->second->getInsectType() == TypeInsect::Grasshopper) cout << "G";
                    else if (it->second->getInsectType() == TypeInsect::Ladybug) cout << "L";
                    else if (it->second->getInsectType() == TypeInsect::Mosquito) cout << "M";

                    cout << it->second->getID();
                    cout << "(";
                    if (it->first.getX() >= 0) cout << " ";
                    cout << it->first.getX();
                    cout << ",";
                    if (it->first.getY() >= 0) cout << " ";
                    cout << it->first.getY();
                    cout << "," << it->first.getZ() << ")|";
                    //cout << "|BQ1( q, r)|";
                }
                else
                {
                    // cout << "|";
                    for (int s = 0; s < space;s++) cout << " ";
                    // cout << "|";
                }
            }
        }
        cout << "\n";
        for (int q = 0; q < nbMax; q++)
        {
            if (q < i)
            {
                for (int s = 0; s < space / 2;s++) cout << " ";
            }
            else
            {
                cout << "|";
                for (int s = 0; s < space - 2;s++) cout << " ";
                cout << "|";
            }
        }
        cout << "\n";
        for (int q = 0; q < nbMax; q++)
        {
            if (q < i)
            {
                for (int s = 0; s < space / 2;s++) cout << " ";
            }
            else
            {
                cout << "   .    .   ";
            }
        }
        cout << "\n";
        if (r < nbMax / 2)
        {
            i--;
            vali--;
        }
        else
        {
            i++;
            vali = min;
            desc = true;
        }
    }
}



vector<Coordinate> Board::getAdjacentTokens(const Coordinate& current) const {
    vector<Coordinate> adjacentTokens;
    vector<Coordinate> adjCoordinates = current.getAdjacentCoordinates();
    for (const auto& adj : adjCoordinates) {
        if (data.find(adj) != data.end()) {
            adjacentTokens.push_back(adj);
        }
    }
    return adjacentTokens;
}

//on met les adjacents d'un premier element dans not tested et on l'enleve de keys
//on prends le premier element de not tested, si il est dans keys on ajoute ses voisins dans not tested et on le supprime de keys
//ainsi de suite en avancant dans not tested

//si on vide not tested et qu'il y a encore des eleents dans keys alors la regle de la ruche unique n'est pas verifiee
// Recherche l'lment dans `keys` et le supprime



bool Board::beehiveIsCompact(map<Coordinate, Token*> board) const
{
    if (board.empty()) return true; // Cas o la ruche est vide, considre comme compacte

    vector<const Coordinate*> keys; // Vecteur de pointeurs vers les coordonnes
    for (auto it = board.begin(); it != board.end(); ++it) {
        if (it->first.getZ() == 0)
        {
            // on prend car Z=0 ds ruche
            keys.push_back(&(it->first)); // Ajout des cls dans keys
        }
        else
        {
            // on ignore pour Z>0 car la coord en Z=0 sera deja testee
        }
    }

    vector<const Coordinate*> not_tested; // Vecteur pour les lments  tester

    // Commence par le dernier lment de la map
    not_tested.push_back(keys.back()); // Met dans not_tested
    keys.pop_back(); // Supprime de keys

    while (!not_tested.empty()) {
        const Coordinate* current = not_tested.back(); // Prend l'lment  tester
        not_tested.pop_back(); // Supprime de not_tested

        // Rcupre les coordonnes adjacentes
        vector<Coordinate> adjTokens = getDataAdjacentTokens(*current, board);

        // Pour chaque voisin, s'il est dans keys, l'ajoute  not_tested et le supprime de keys
        for (const auto& adj : adjTokens) {
            for (size_t i = 0; i < keys.size(); ++i) {
                if (*keys[i] == adj) { // Si trouv
                    not_tested.push_back(keys[i]); // Ajoute  not_tested
                    keys.erase(keys.begin() + i); // Supprime de keys
                    break; // Sort de la boucle une fois trouv
                }
            }
        }
    }

    return keys.empty(); // Si keys est vide, alors la ruche est compacte
}

vector<Coordinate> Board::getDataAdjacentTokens(const Coordinate& current, map<Coordinate, Token*> board) const {
    vector<Coordinate> adjacentTokens;
    vector<Coordinate> adjCoordinates = current.getAdjacentCoordinates();
    for (const auto& adj : adjCoordinates) {
        if (board.find(adj) != board.end()) {
            adjacentTokens.push_back(adj);
        }
    }
    return adjacentTokens;
}
void Board::showPlacements(Token* token) const
{
    int n = 1;
    if (token->isActive())
    {

        for (auto i = 0; i < (token->getPossibleMoves()).size(); i++)
            cout << "possibilites de deplacements " << n++ << " : " << (token->getPossibleMoves())[i] << "\n";


        //=======
        //        if (token->getPossibleMoves().size() == 0)
        //        {
        //            cout << "Aucune possibilit? de deplacement"<<"\n";
        //            return;
        //        }
        /*for (auto i = 0; i < token->getPossibleMoves().size(); i++)
                    cout <<"possibilites de deplacements " << n++ << " : " << (token->getPossibleMoves())[i] << "\n";*/

    }
    else
    {
        if (token->getPossiblePlacements().size() == 0)
        {
            cout << "Aucune possibilit? de placement" << "\n";
            return;

        }

        for (auto i = 0; i < (token->getPossiblePlacements()).size(); i++)
            cout << "possibilites de placements " << n++ << " : " << (token->getPossiblePlacements())[i] << "\n";
    }
}
