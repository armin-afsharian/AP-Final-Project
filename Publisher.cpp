#include "Publisher.h"

Publisher::Publisher(std::string _username, std::string _password, std::string _email, int _age, int _userId)
: Client(_username, _password, _email, _age, _userId){}

void Publisher::deleteFilm (int filmId)
{
    Film* film = getFilm(filmId);
    if(film == nullptr)
        throw PermissionDenied();
    film->deleteStatus();
}

void Publisher::followersList()
{
    std::cout<<"List of Followers\n";
    std::cout<<"#. User Id | User Username | User Email\n";
    for(int i = 0; i<followers.size(); i++)
    {
        std::cout<<i+1<<". ";
        followers[i]->showClientData();
    }
}

void Publisher::takeMoney()
{
    money = credit;
    credit = 0;
}

void Publisher::publishedFilm(std::string name, std::string director, int min_rate, int min_year, int price, int max_year)
{
    std::vector<Film*> found = films;
    for(int i = 0; i < found.size(); i++)
    {
        if(found[i]->getDeleteStatus() == 1)
        {
            found.erase(found.begin() + i);
                continue;
        }
            if((name != "") && (found[i]->getName() != name))
            {
                found.erase(found.begin() + i);
                continue;
            }
            if((director != "") && (found[i]->getDirector() != director))
            {
                found.erase(found.begin() + i);
                continue;
            }
            if((min_rate != -1) && (found[i]->getRate() < min_rate))
            {
                found.erase(found.begin() + i);
                continue;
            }
            if((price != -1) && (found[i]->getPrice() != price))
            {
                found.erase(found.begin() + i);
                continue;
            }
            if((max_year != 0) && (found[i]->getYear() > max_year))
            {
                found.erase(found.begin() + i);
                continue;
            }
            if((min_year != 0) && (found[i]->getYear() < min_year))
            {
                found.erase(found.begin() + i);
                continue;
            }
    }
    std::cout<<"#. Film Id | Film Name | Film Length | Film price | ";
    std::cout<<"Rate | Production Year | Film Director\n";
    for(int i = 0; i < found.size(); i++)
        found[i]->listFilm(i+1); 
}

void Publisher::postFilm(Film*& film)
{
    films.push_back(film);

}

void Publisher::addCredit(int amount)
{
    credit += amount;  
}

void Publisher::deleteComment(int filmId, int commentId)
{
    Film* film = getFilm(filmId);
    if(film == nullptr)
        throw PermissionDenied();
    film->deleteComment(commentId);
}

void Publisher::postReply(int filmId, int commentId, std::string content, Client* client)
{
    Film* film = getFilm(filmId);
    if(film == nullptr)
        throw PermissionDenied();
    Notification* n = new Notification;
    n->replyNotification(userId, username);
    client->addNotification(n);
    film->addReply(commentId, content);
}

void Publisher::addFollower(Client* client)
{
    followers.push_back(client);
    Notification* n = new Notification;
    n->followNotification(client->getId(), client->getUser());
    this->addNotification(n);
}

Film* Publisher::getFilm(int id)
{
    for(int i = 0; i < films.size(); i++)
        if(id == films[i]->getId())
            return films[i];
    return nullptr;
}

void Publisher::editFilm(int filmId, std::string name, int year, int length, std::string summary, std::string director)
{
    Film* film = getFilm(filmId);
    if(film == nullptr)
        throw PermissionDenied();
    film->editData(name, year, length, summary, director);
}

void Publisher::sendNotification()
{
    Notification* n = new Notification;
    n->newFilmNotification(userId,username);
    for(int i = 0; i < followers.size(); i++)
        followers[i]->addNotification(n);

}