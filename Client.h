#ifndef CLIENT_H
#define CLIENT_H

#include "Film.h"
#include "Notification.h"

class Client
{
    protected:
        std::string username;
        std::string password;
        std::string email;
        int age;
        int money = 0;
        int userId;
        std::vector<int> following;
        std::vector<Film*> purchased;
        std::vector<Notification*> notifications; 
    public:
        Client(std::string _username, std::string _password, std::string _email, int _age, int _userId);
        std::string getUser();
        std::string getEmail();
        int getId();
        std::string getPass();
        int getMoney();
        Film* getFilm(int id);
        void showClientData();  
        void followingPublisher(int publisherId);
        void postMoney(int amount);
        void searchFilm(std::string Name, int min_rate, int min_year, int price, int max_year, std::string director);
        void buyFilm(Film* film);
        void giveRate(int id, int score);
        void viewPurchased(std::string name, std::string director, int min_year, int price, int max_year);
        Comment* postComments(int filmId, std::string content);
        void editfilm(int filmId, std::string name, int year, int length, std::string summary, std::string director);
        void erasePurchased(std::vector<Film*> &recommended);
        void addNotification(Notification* notification);
        void printNotification();
        void printNotificationRead(int limit);
};

#endif