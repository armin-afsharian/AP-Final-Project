#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include <algorithm>
#include "Film.h"
#include "Client.h"
#include "Publisher.h"


class System
{
    private:
        std::vector<Film*> films;
        std::vector<Client*> clients;
        std::vector<Publisher*> publishers;
        std::vector<Comment*> comments;
        int clientId = 0;
        int filmId = 0;
        int income = 0;
        int loggedInId = 0;
    public:
        Publisher* get_publisher(int Id);
        Film* get_film(int id);
        Client* get_client(int id);
        void moneyCal(float rate, int amount, Publisher* publisher);
        void recommendedFilm();
        void signup(std::vector<std::string> &line);
        void login(std::vector<std::string> &line);
        void repeatedUser(std::string user);
        void checkData(std::string &user, std::string &pass);
        void postFilm(std::vector<std::string> &line);
        void postMoney();
        void following(std::vector<std::string> &line);
        void postMoneyClient(std::vector<std::string> &line);
        void buyFilm(std::vector<std::string> &line);
        void rateFilm(std::vector<std::string> &line);
        void postComments(std::vector<std::string> &line);
        void getFollowers();
        void deleteFilm(std::vector<std::string> &line);
        void deleteComments(std::vector<std::string> &line);
        void editFilm(std::vector<std::string> &line);
        void search(std::vector<std::string> &line);
        void findFilm(std::string name, std::string director, int min_rate, int min_year, int price, int max_year);
        void publishedFilm(std::vector<std::string> &line);
        void filmDetail(std::vector<std::string> &line);
        void purchasedFilm(std::vector<std::string> &line);
        void postReplies(std::vector<std::string> &line);
        void editfilm(int filmId, std::string name, int year, int length, std::string summary, std::string director);
        void deleteFilm(int id);
        void recommendedFilms(Film* film, Client* client);
        void getNotification();
        void getNotificationRead(std::vector<std::string> &line);
};

#endif