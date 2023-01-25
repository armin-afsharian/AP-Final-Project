#include "Client.h"

std::string Client::getUser()
{
    return username;
}

std::string Client::getEmail()
{
    return email;
}

int Client::getId()
{
    return userId;
}

std::string Client::getPass()
{
    return password;
}

int Client::getMoney()
{
    return money;
}

Film* Client::getFilm(int id)
{
    for(int i = 0; i < purchased.size(); i++)
        if(id == purchased[i]->getId())
            return purchased[i];
    return nullptr;
}

void Client::showClientData()
{
    std::cout<< userId <<  " | ";
    std::cout<< username << " | " << email << std::endl;
}

Client::Client(std::string _username, std::string _password, std::string _email, int _age, int _userId)
{
    username = _username;
    password = _password;
    email = _email;
    age = _age;
    userId = _userId;
}

void Client::followingPublisher(int publisherId)
{
    following.push_back(publisherId);
}

void Client::postMoney(int amount)
{
    money += amount;
}

void Client::buyFilm(Film* film)
{
    if(money - film->getPrice() < 0)
        throw PermissionDenied();
    purchased.push_back(film);
    money -= film->getPrice();
}

void Client::giveRate(int id, int score)
{
   Film* film = getFilm(id);
   if(film == nullptr)
        throw PermissionDenied();
    film->rateCal(score);
}

void Client::viewPurchased(std::string name, std::string director, int min_year, int price, int max_year)
{
    std::vector<Film*> found = purchased;
    for(int i = 0; i < found.size(); i++)
    {
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

Comment* Client::postComments(int filmId, std::string content)
{
    Film* film = getFilm(filmId);
    if(film == nullptr)
        throw PermissionDenied();
    Comment* comment = film->addComments(content, userId);
    return comment;
}

void Client::editfilm(int filmId, std::string name, int year, int length, std::string summary, std::string director)
{
    Film* film = getFilm(filmId);
    if(film != nullptr)
    film->editData(name, year, length, summary, director);
}

void Client::erasePurchased(std::vector<Film*> &recommended)
{
    for(int i = 0 ; i < recommended.size(); i++)
        for(int j = 0 ; j < purchased.size(); j++)
            if(recommended[i]->getId() == purchased[j]->getId())
                recommended.erase(recommended.begin() + i);
}

void Client::addNotification(Notification* notification)
{
    notifications.push_back(notification);
}

void Client::printNotification()
{
    std::cout << "#. Notification Message\n";
    for(int i = notifications.size() - 1; i >= 0; i--)
    {
        if(notifications[i]->getReadStatus() == false)
        {
            std::cout << notifications.size()- i<< ". ";
            notifications[i]->print();
        }
    }
}

void Client::printNotificationRead(int limit)
{
    std::cout << "#. Notification Message\n";
    for(int i = notifications.size() - 1; i >= limit; i--)
    {
        if(notifications[i]->getReadStatus() == true)
        {
            std::cout << notifications.size() - i<< ". ";
            notifications[i]->print();
        }
    }
}