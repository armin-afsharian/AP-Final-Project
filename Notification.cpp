#include "Notification.h"

void Notification::replyNotification(int senderId, std::string senderName)
{
    std::string Id = std::to_string(senderId);
    content = "Publisher " + senderName + " with id " + Id + " reply to your comment.\n";
}

void Notification::newFilmNotification(int senderId, std::string senderName)
{
    std::string Id = std::to_string(senderId);
    content = "Publisher " + content +  senderName + " with id " + Id + " register new film.\n";
}

void Notification::followNotification(int senderId, std::string senderName)
{
    std::string Id = std::to_string(senderId);
    content = "User " + senderName + " with id " + Id + " follow you.\n";
}

void Notification::buyFilmNotification(int senderId, std::string senderName, std::string filmName, int filmId)
{
    std::string Id = std::to_string(senderId);
    std::string FilmId = std::to_string(filmId);
    content = "User " + senderName + " with id " + Id + " buy your film " + filmName + " with id " + FilmId + ".\n";
}

void Notification::rateNotification(int senderId, std::string senderName, std::string filmName, int filmId)
{
    std::string Id = std::to_string(senderId);
    std::string FilmId = std::to_string(filmId);
    content = "User " + senderName + " with id " + Id + " rate your film " + filmName + " with id " + FilmId + ".\n";
}

void Notification::commentNotification(int senderId, std::string senderName, std::string filmName, int filmId)
{
    std::string Id = std::to_string(senderId);
    std::string FilmId = std::to_string(filmId);
    content = "User " + senderName + " with id " + Id + " comment on your film " + filmName + " with id " + FilmId + ".\n";
}

void Notification::print()
{
    read = true;
    std::cout << content;
}

bool Notification::getReadStatus()
{
    return read;
}