#ifndef MATCHEXCEPTION_H
#define MATCHEXCEPTION_H

#include <exception>
#include <string>

// Classe personnalisée pour les erreurs liées au jeu
class MatchException : public std::exception
{
private:
    std::string message;

public:
    // Constructeur prenant un message d'erreur
    explicit MatchException(const std::string& msg) : message(msg) {}

    // Redéfinition de la méthode what() pour retourner le message d'erreur
    const char* what() const noexcept override
    {
        return message.c_str();
    }
};

#endif // MATCHEXCEPTION_H
