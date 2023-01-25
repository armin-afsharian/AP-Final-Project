#ifndef FILM_H
#define FILM_H

#include <iostream>
#include "Comment.h"
#include "Error.h"


class Film
{
    private:
        std::string name;
        int year;
        int length;
        int price;
        float rate = 0;
        int numVotes = 0;
        int filmId;
        int deleted = 0;
        std::string summary;
        std::string director;
        int  publisherId;
        int commentCount = 0;
        std::vector<Comment*> comments;
    public:
        int getId();
        int getYear();
        int getLength();
        int getPrice();
        int getDeleteStatus();
        float getRate();
        std::string getName();
        std::string getDirector();
        Film(std::string _name, int _year, int _length, int _price, std::string _summary, std::string _director, int _filmId, int pubId);
        void deleteStatus();
        void listFilm(int Num);
        void printDetail();
        void rateCal(int score);
        int get_publisher();
        Comment* addComments(std::string content, int clientId);
        void printComments();
        void deleteComment(int commentId);
        void addReply(int commentId, std::string content);
        Comment* getComment(int id);
        void editData(std::string _name, int _year, int _length, std::string _summary, std::string _director);
        void printRecommended();
}; 

#endif