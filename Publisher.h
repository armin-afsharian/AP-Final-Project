#ifndef PUBLISHER_H
#define PUBLISHER_H

#include "Film.h"
#include "Client.h"
#include "Notification.h"


class Publisher : public Client
{
    private:
        int credit = 0;
        std::vector<Film*> films;
        std::vector<Client*> followers;
    public:
        Publisher(std::string _username, std::string _password, std::string _email, int _age, int _userId);
        void deleteFilm (int filmId);
        void followersList();
        void takeMoney();
        void publishedFilm(std::string name, std::string director, int min_rate, int min_year, int price, int max_year);
        void postFilm(Film*& film);
        void addCredit(int amount);
        void deleteComment(int filmId, int commentId);
        void postReply(int filmId, int commentId, std::string content, Client* client);
        void addFollower(Client* client);
        Film* getFilm(int id);
        void editFilm(int filmId, std::string name, int year, int length, std::string summary, std::string director);
        void sendNotification();

};

#endif