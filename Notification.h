#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <iostream>
#include <string>

class Notification
{
    private:
        bool read = false;
        int a = 1;
        std::string content = "";
    public:
        int geta(){return a;}
        std::string getcon(){return content;}
        void replyNotification(int senderId, std::string senderName);
        void newFilmNotification(int senderId, std::string senderName);
        void followNotification(int senderId, std::string senderName);
        void buyFilmNotification(int senderId, std::string senderName, std::string filmName, int filmId);
        void rateNotification(int senderId, std::string senderName, std::string filmName, int filmId);
        void commentNotification(int senderId, std::string senderName, std::string filmName, int filmId);
        void print();
        bool getReadStatus();
};

#endif