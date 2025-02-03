#include "Utils.h"
#include "Player.h"
#include "Token.h"
#include "IA.h"
#include "Board.h"
#include "Coordinate.h"
#include "Game.h"

namespace Hive {
    //retourne le move ou le placement choisi parmi les moves possibles ou les placements possibles
    Coordinate IA::choseMoveOrPlacement(const std::vector<Coordinate>& possibleMovesOrPlacements, Token* chosenToken) const {
        if (possibleMovesOrPlacements.empty())
        {
            throw HiveException("Aucun move valide disponible pour IA.");
        }
        if (difficultyLevel == 1) {
            //IA niveau 1 : choix aléatoire
            int randomIndex = std::rand() % possibleMovesOrPlacements.size();
            return possibleMovesOrPlacements[randomIndex];
        }
        else if (difficultyLevel == 2) {
            //IA niveau 2 : choisit le move le plus proche de l'abeille
            Game& gameInstance = Game::getInstance();
            Match& matchInstance = gameInstance.getMatch();
            //si l'abeille blanche est placée et si ce n'est pas l'abeille noire que l'on déplace
            if (matchInstance.beePlaced(PlayerColor::White) && chosenToken->getInsectType() != TypeInsect::Bee)
            {
                //alors on choisit le move le plus proche de l'abeille blanche
                vector<int> distances;
                for (const auto& move : possibleMovesOrPlacements)
                {
                    int distance = calculateDistanceFromWhiteBee(move);
				    // cout << "distance entre "<< move <<" et l'abeille blanche : " << distance << endl;
                    if (distance < 0) 
                    {
                        throw HiveException("Impossible de calculer la distance depuis l'abeille blanche.");
                        //replacer par ia exception
                    }
                    distances.push_back(distance);
                }
                //on cherche l'index de la plus petite distance dans les moves possibles
                auto minIt = std::min_element(distances.begin(), distances.end());
                size_t minIndex = std::distance(distances.begin(), minIt);

                return possibleMovesOrPlacements[minIndex];
            }
			else
			{
				//si l'abeille blanche n'est pas placée, on choisit un move aléatoire
                int randomIndex = std::rand() % possibleMovesOrPlacements.size();
                return possibleMovesOrPlacements[randomIndex];
			}
        }
        throw HiveException("Niveau de difficulté de l'IA non pris en charge.");
    }

    
    //retourne un token de la main à placer
    Token* IA::choseTokenFromHand() const
    {
        Game& gameInstance = Game::getInstance();
        Match& matchInstance = gameInstance.getMatch();
        vector<Token*> iaHand = matchInstance.getHand(PlayerColor::Black);
        //si c'est le 4eme tour et abeille noire pas placée, on la place
        if (matchInstance.isFourthMove() && matchInstance.beeNotPlaced())
        {
            for (const auto& token : iaHand)
            {
                if (token && token->getInsectType() == TypeInsect::Bee && token->getColor() == PlayerColor::Black) {
					cout << "quatrieme tour : l'IA est obligee de poser son abeille " << endl;
                    return token;  
                }
            }
        }
        //si le nombre de tours est différent de 3, IA choisit une piece random et la place
		//mais on verifie avant que la main n'est pas vide
        if (iaHand.empty())
        {
            return nullptr;
        }
        int randomIndex = std::rand() % iaHand.size();

        return iaHand[randomIndex];
    }
    
    //retourne un token de ceux placés sur le board par l'IA
    Token* IA::choseTokenFromBoard() const
    {
        Game& gameInstance = Game::getInstance();
        Match& matchInstance = gameInstance.getMatch();
        vector<Token*> iaMovabeTokens = matchInstance.getTokensMovable();
		//verifier que iaMovabeTokens n'est pas vide
		if (iaMovabeTokens.empty())
		{
			return nullptr;
		}
        int randomIndex = std::rand() % iaMovabeTokens.size();
        //tant que la piece n'est pas valide (elle ne peut pas bouger), on en choisit une autre
        //si la piece est deja a cote de l'abeille blanche, on en choisit une autre
		while (!iaMovabeTokens[randomIndex]->canMove()&& whiteBeeIsNeighbour(iaMovabeTokens[randomIndex]))
        {
            randomIndex = std::rand() % iaMovabeTokens.size();
        }
        return iaMovabeTokens[randomIndex];
        
    }

    int IA::calculateDistanceFromWhiteBee(const Coordinate& initialToken)const{
        map<Coordinate, Token*> board = Board::getInstance().getData();
        Coordinate whiteBeePosition(-1, -1, -1);

        for (const auto& insect : board) {
            if (insect.second->getInsectType() == TypeInsect::Bee && insect.second->getColor() == PlayerColor::White) {
                whiteBeePosition=insect.first;
            }
        }
        //vérifier si l'abeille est trouvée
        if (whiteBeePosition != Coordinate(-1, -1, -1)) {
            //calculer la distance dans une grille hexagonale
            return Coordinate::hexDistance(whiteBeePosition, initialToken);
        }
        return -1; //distance non calculable
    }

	//fonction pour savoir si une piece est a coté de la bee blanche
    //on ne la déplace pas si true
    bool IA::whiteBeeIsNeighbour(Token* token) const
    {
		Board& boardInstance = Board::getInstance();
        vector<Coordinate> adjacents = boardInstance.getAdjacentTokens(token->getTokenCoordinate());
        for (const auto& adj : adjacents)
        {
			if (boardInstance.getData()[adj]->getInsectType() == TypeInsect::Bee)
			{
				return true;
			}
        }
		return false;
    }


    //choisit quel token a bouger
    Token* IA::IA_whatToMove() const
    {
        Game& gameInstance = Game::getInstance();
        Match& matchInstance = gameInstance.getMatch();
		//tant que on est pas au 4eme tour, on ne fait que placer des tokens
        if (matchInstance.getBlackMoveCount() < 4)
        {
            return choseTokenFromHand();
        }
        else
        {
            //sinon on effectue une action random entre placer des token ou deplacer des token
            int randomAction = std::rand() % 2;
            if (randomAction == 1) {
                if (choseTokenFromHand() == nullptr) { return choseTokenFromBoard(); }
                return choseTokenFromHand();
            }
			else {
				if (choseTokenFromBoard() == nullptr) { return choseTokenFromHand(); }
                return choseTokenFromBoard(); 
            }
        }
    }

    Coordinate IA::IA_whereToMove(Token* chosenToken) const
    {
        //si c'est une piece non placee, on la place
        if (!chosenToken->isActive()) { 
			cout << "l'IA a choisi de placer un token" << endl;
            const vector<Coordinate> possibePlacements = chosenToken->getPossiblePlacements();
            Coordinate c = choseMoveOrPlacement(possibePlacements, chosenToken);
			cout << "choix de placement de l'IA: " << c << endl;
            return c;
        }
        //sinon on la deplace
        else { 
			cout << "l'IA a choisi de deplacer un token" << endl;
            const vector<Coordinate> possibeMoves = chosenToken->getPossibleMoves();
            Coordinate c = choseMoveOrPlacement(possibeMoves, chosenToken);
            cout << "choix de deplacement de l'IA: " << c << endl;
            return c; 
        }
    }

}
