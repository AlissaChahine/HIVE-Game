#ifndef GAMEEXCEPTION_H
#define GAMEEXCEPTION_H

#include <exception>
#include <string>

// Classe personnalisée pour les erreurs liées au jeu
class GameException : public std::exception
{
private:
    std::string message;

public:
    // Constructeur prenant un message d'erreur
    explicit GameException(const std::string &msg) : message(msg) {}

    // Redéfinition de la méthode what() pour retourner le message d'erreur
    const char *what() const noexcept override
    {
        return message.c_str();
    }
};

#endif // GAMEEXCEPTION_H
