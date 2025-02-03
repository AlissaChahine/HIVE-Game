#include "Game.h"
#include "GameException.h"
#include "IA.h"

// fonctions Ahlem/menu
void Game::setPlayerIA(int level)
{
    PlayerIA = 1;
    cout << "PlayerIA set to: " << PlayerIA << endl;
    playerBlack = std::make_shared<IA>(PlayerColor::Black, "IA Player", level);
}

void Game::setPlayerNames(string name1, string name2)
{
    PlayerIA=0;
    cout << "PlayerIA set to: " << PlayerIA << endl;
    playerwhite->setName(name1);
    if (playerBlack->getIA() == false)
    {
        playerBlack->setName(name2);
        cout << "Nom player Black: " << playerBlack->getName() << endl;
    }
}

void Game::setExtension(int choice)
{
    if (choice==1)
    {
        vect_extension.push_back(Hive::TypeInsect::Ladybug);
    }
    else if (choice==2)
    {
        vect_extension.push_back(Hive::TypeInsect::Mosquito);
    }
    else if (choice==3){
        vect_extension.push_back(Hive::TypeInsect::Ladybug);
        vect_extension.push_back(Hive::TypeInsect::Mosquito);
    }
}

// fin ahlem / menu

void Game::setPlayerIA()
{
    int choix_IA;
    bool validInput = false;
    while (!validInput) {
        cout << "Jouez-vous contre un joueur ou une IA? 0 pour joueur, 1 pour IA: ";
        cin >> choix_IA;
        if (choix_IA == 0 || choix_IA == 1) {
            validInput = true;
        }
        else {std::cout << "Entree invalide. Veuillez entrer 0 pour joueur ou 1 pour IA." << std::endl;}
    }

    if (choix_IA == 1)
    {
        PlayerIA = 1;
        int choix_difficulty;
        validInput = false;
        while (!validInput) {
            cout << "Quelle difficulte d'IA voulez-vous? 1 pour IA niveau 1, 2 pour IA niveau 2: ";
            cin >> choix_difficulty;
            if (choix_difficulty && (choix_difficulty == 1 || choix_difficulty == 2)) {
                validInput = true;
            }
            else { cout << "Entree invalide. Veuillez entrer 1 pour IA niveau 1 ou 2 pour IA niveau 2." << std::endl; }
        }
        playerBlack = std::make_shared<IA>(PlayerColor::Black, "IA Player", choix_difficulty);
    }
}


void Game::setPlayerNames()
{
    string namePlayer1;
    std::cout << "Entrez le nom de player 1 : ";
    std::cin >> namePlayer1;
    playerwhite->setName(namePlayer1);

    if (playerBlack->getIA() == false)
    {
        string namePlayer2;
        std::cout << "Entrez le nom de player 2 : ";
        std::cin >> namePlayer2;
        playerBlack->setName(namePlayer2);
    }
}


void Game::setExtension()
{
    int nb_extensions;
    std::cout << "Combien d'extensions souhaitez-vous ajouter ? 0/1/2 ";
    std::cin >> nb_extensions;
    while(nb_extensions!=0 && nb_extensions!= 1 && nb_extensions!=2)
    {
        std::cout << "Erreur de saisie. Combien d'extensions souhaitez-vous ajouter ? 0/1/2 ";
        std::cin >> nb_extensions;
    }


    if (nb_extensions == 1)
    {
        // on demande quelle extension le joueur choisit
        int choix_extensions;
        std::cout << "Pour choisir ladybug, tapez 0 \n Pour choisir mosquito, tapez 1 ";
        std::cin >> choix_extensions;

        while (choix_extensions != 0 && choix_extensions != 1)
        {
            std::cout << "Erreur de saisie. Pour choisir ladybug, tapez 0 \n Pour choisir mosquito, tapez 1 ";
            std::cin >> choix_extensions;
        }

        if (choix_extensions == 0)
        {
            vect_extension.push_back(Hive::TypeInsect::Ladybug);
        }
        else if (choix_extensions == 1)
        {
            vect_extension.push_back(Hive::TypeInsect::Mosquito);
        }
    }

    else if (nb_extensions == 2)
    {
        vect_extension.push_back(Hive::TypeInsect::Ladybug);
        vect_extension.push_back(Hive::TypeInsect::Mosquito);
    }
    else if (nb_extensions != 0)
    {
        throw HiveException("mauvais choix, veuillez saisir le nombre d'extensions souhaitées: 0/1/2");
    }
    // si nb_extension=0 on fait rien car vect_extensions reste vide
}
void Game::startMatch()
{
    Board::getInstance().reset();
    // on a à présent modifié le vecteur vect_extension
    // cas ou on joue pas contre une IA
    if (PlayerIA == 0)
    {
        // on appelle le constructeur de Match
        match = new Match(playerwhite, playerBlack, 11 + vect_extension.size(), vect_extension);
        //cout << "Appel du constructeur de match sans IA\n";
    }
    else // si IA
    {
        playerBlack->setIA();
        match = new Match(playerwhite, playerBlack, 11 + vect_extension.size(), vect_extension);
        //cout << "Appel du constructeur de match avec IA\n";
    }
}

int Game::playerTurn()
{
    int placeOrMove;
    bool choice1 = false;
    bool placeToken = true;
    cout << "Tapez 0 pour placer, 1 pour deplacer : " << endl;
    cin >> placeOrMove;
    // ajouter qqc pour obliger a placer la bee au 4eme tour
    while (!choice1)
    {
        if (placeOrMove == 0)
        {
            choice1 = true;
            placeToken = true;
            if (match->getHand(match->getCurrentPlayer().getColor()).empty() == true)
            {
                cout << "Vous n'avez plus de pieces a placer" << endl;
                placeToken = false; // on force le joueur a deplacer une piece
            }
        }
        else if (placeOrMove == 1)
        {
            choice1 = true;
            placeToken = false; //Move
            if (match->getActiveTokens(match->getCurrentPlayer().getColor()).empty() == true)
            {
                cout << "Vous n'avez aucune pieces sur le plateau a deplacer." << endl;
                placeToken = true; // on force le joueur a placer une piece
            }
            else {
                if (match->getTokensMovable().empty() == true)
                {
                    cout << "Aucune piece a deplacer possible\n";
                    placeToken = true;

                }
            }

        }
        else
        {
            cout << "Veuillez entrer un choix valide" << endl;
            cout << "Tapez 0 pour placer, 1 pour deplacer : " << endl;
            cin >> placeOrMove;

        }
    }
    if (placeToken)
    {
        vector<Token*> handPlayer = match->getHand(match->getCurrentPlayer().getColor());
        // Placer une piece
        int tokenChoice = -1;

        cout << "Voici votre main : ";
        match->printhand(match->getCurrentPlayer().getColor());
        size_t tokensInHand = handPlayer.size();
        while (tokenChoice<0 || tokenChoice>tokensInHand)

        {
            cout << "Quelle piece voulez-vous placer ? (tapez un chiffre entre 0 et " << tokensInHand - 1 << ") : " << endl;
            cin >> tokenChoice;

            if (tokenChoice < 0 || tokenChoice >= tokensInHand)
            {
                cout << "Veuillez entrer un numero de piece valide" << endl;

            }

        }
        Token* tokenToPLace = handPlayer[tokenChoice];
        bool place = false;
        while (!place)
        {
            int x;
            int y;
            int z;

            match->showPlacements(tokenToPLace);
            cout << "Ou voulez-vous deplacer la piece " << *tokenToPLace << " ? Position de type (x,y) :" << endl;
            cout << "x= "; cin >> x; cout << "y= "; cin >> y;
            if (tokenToPLace->getInsectType() == TypeInsect::Beetle)
            {
                cout << "z= "; cin >> z;
                while (z != 0 && z != 1)
                {
                    cout << "entrez une hauteur de 0 ou 1";
                    cin >> z;
                    cout << "\n";
                }
            }
            else z = 0;

            cout << "\n";
            int placementResult = match->placeOnBoard(tokenToPLace, Coordinate(x, y, z));
            if (placementResult == 1)
            {
                place = true;
                cout << "La piece a ete place\n";
            }
            else {
                cout << "Veuillez choisir un autre placement" << endl;
            }
        }


    }
    else {
        // pour le deplacement
        int tokenChoice = -1;
        vector<Token*> tokensCanMove= match->getTokensMovable();
        bool move1 = false;
        //if (tokensCanMove.empty() == true)
        //{
        //    cout << "Aucune piece a deplacer possible\n";
        //    move1 = true; // le deplacement est fini comme impossible

        //}

        while (!move1)
        {
            cout << "Pieces a deplacer : \n";
            match->showMovable();
            cout << "Quelle piece voulez-vous deplacer ? (tapez un chiffre entre 0 et " << tokensCanMove.size() - 1 << ") : " << endl;
            cin >> tokenChoice;

            if (tokenChoice < 0 || tokenChoice >= tokensCanMove.size())
            {
                cout << "Veuillez entrer un numero de piece valide pour le deplacement" << endl;
                move1 = false;
            }
            else move1 = true;
        }

        Token* tokenToMove = tokensCanMove[tokenChoice];
        bool move2 = false;
        while (!move2)
        {
            int x;
            int y;
            int z;
            match->showPlacements(tokenToMove);
            cout << "Ou voulez-vous deplacer la piece " << *tokenToMove << " ? Position de type (x,y) :" << endl;
            cout << "x= "; cin >> x; cout << "y= "; cin >> y;
            if (tokenToMove->getInsectType() == TypeInsect::Beetle)
            {
                cout << "z= "; cin >> z;
                while (z != 0 && z != 1)
                    cin >> z;
            }
            else z = 0;

            cout << "\n";
            int moveResult = match->placeOnBoard(tokenToMove, Coordinate(x, y, z));
            if (moveResult == 1)
            {
                move2 = true;
                cout << "La piece a ete deplace\n";
            }
            else {
                cout << "Veuillez chosir un autre deplacement\n";
            }
        }
    }
    // appeler le nexTurn ici plutot que dans placeOnBoard de Match
    // mais on passe bien au joueur suivant
    return 1; // le player a joue
}

int Hive::Game::IATurn()
{
    if (PlayerIA) {
        //utilisation de dynamic_pointer_cast pour vérifier et convertir playerBlack en IA
        std::shared_ptr<IA> iaPlayer = std::dynamic_pointer_cast<IA>(playerBlack);

        if (iaPlayer) {
            // Appeler la méthode IA_whatToMove() pour choisir un token

            Token* chosenToken = iaPlayer->IA_whatToMove();
            cout << "choix token : " << *chosenToken << endl;
            // Si un token a été choisi, appeler IA_whereToMove() pour choisir la destination
            if (chosenToken) {

                Coordinate chosenMove = iaPlayer->IA_whereToMove(chosenToken);
                int result = match->placeOnBoard(chosenToken, chosenMove);
            }
        }
    }
    return 1; // l'IA a joue
}

void Game::play()
{
    // Après avoir construit Game
    // Cette fonction va modifier vect_extension en demandant à
    // l'utilisateur, puis appeler startmatch()
    if (num==MatchCount::First)
    {setExtension();
        // on appelle à présent le constructeur de match
        // on devra plus tard gérer l'IA, la on fait pour playerIA=False et on a deux joueurs
        setPlayerIA();
        setPlayerNames();}
    startMatch();
    cout << "Le match va commencer\n";


    while (match->checkGameOver()==false)
    {
        cout << "Tour du joueur: " << match->getCurrentPlayer().getName() << endl;

        if (match->getCurrentPlayer().getIA() == false)
        {
            int res = playerTurn();
            if (res == 1)
            {
                match->nextTurn();
            }
            else
            {
                cout << "Le tour n'a pas ete effectue\n";
            }
        }
        else
        {
            int res = IATurn();
            if (res == 1)
            {

                match->nextTurn();
            }
            else
            {
                cout << "Le tour n'a pas ete effectue\n";
            }
        }
        cout << "\nPlateau actuel : \n";
        Board::getInstance().showBoard();
    }
    if (match->checkGameOver())
    {
        int choix_rejouer;
        bool validInput = false;
        while (!validInput) {
            cout << "Voulez vous rejouer? 0 pour non, 1 pour oui : " << endl;
            cin >> choix_rejouer;
            if (!std::cin.good())
            {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                validInput = false;
            }
            else if (choix_rejouer == 0 || choix_rejouer == 1) {
                validInput = true;
            }
            else { std::cout << "Entree invalide. Veuillez entrer 0 pour non ou 1 pour oui." << std::endl; }
        }

        finishMatch(choix_rejouer);
    }
}

void Hive::Game::finishMatch(int choix_rejouer)
{
    Player& winner = match->getWinner();
    cout << "Le gagnant est le joueur " << winner.getName() << endl;
    Board::getInstance().clear();

    if (choix_rejouer == 1)
    {
        delete match;
        num = MatchCount::Several;
        play();
    }
}


void Hive::Game::deleteMatch(){
    if (match != nullptr) {
        delete match;
        match = nullptr;
        std::cout << "match deleted " << std::endl;
    } else {
        std::cout << "noo match to delete" << std::endl;
    }
}


