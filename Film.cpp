#include "Film.h"

int Film::getId()
{
    return filmId;
}

int Film::getYear()
{
    return year;
}

int Film::getLength()
{
    return length;
}

int Film::getPrice()
{
    return price;
}

float Film::getRate()
{
    return rate;
}

std::string Film::getName()
{
    return name;
}

std::string Film::getDirector()
{
    return director;
}

int Film::get_publisher()
{
    return publisherId;
}

Comment* Film::getComment(int id)
{
    for(int i = 0; comments.size(); i++)
        if(id == comments[i]->get_id())
            return comments[i];
    return nullptr;
}

Film::Film(std::string _name, int _year, int _length, int _price, std::string _summary, std::string _director, int _filmId, int pubId)
{
    name = _name;
    year = _year;
    length = _length;
    price = _price;
    summary = _summary;
    director = _director;
    filmId = _filmId;
    publisherId = pubId;
}

void Film::deleteStatus()
{
    deleted = 1;
}

void Film::listFilm(int Num)
{
    std::cout << Num << ". ";
    std::cout << filmId << " | " << name << " | ";
    std::cout << length << " | " << price << " | ";
    std::cout << rate << " | " <<year << " | ";
    std::cout << director << std::endl;
}

void Film::printDetail()
{
    std::cout << "Details of Film " << name << std::endl;
    std::cout << "Id = "<< filmId << std::endl << "Director = "<< director << std::endl;
    std::cout << "Lenght = " << length << std::endl << "Year = " << year << std::endl;
    std::cout << "Summary = " << summary << std::endl << "Rate = " << rate << std::endl;
    std::cout << "Price = " << price << std::endl << std::endl;
    std::cout << "Comments\n";
    printComments();
    std::cout << std::endl;
    std::cout << "Recommendation Film\n";
    std::cout << "#. Film Id | Film Name | Film Length | Film Director\n";
}

void Film::rateCal(int score)
{
    if(score < 0)
        throw PermissionDenied();
    float sum = rate * numVotes + score;
    numVotes++;
    rate = sum / numVotes;
}


Comment* Film::addComments(std::string content, int clientId)
{
    commentCount++;
    Comment * comment = new Comment(commentCount, content, clientId);
    comments.push_back(comment);
    return comment;
}

void Film::printComments()
{
    for(int i = 0; i<comments.size(); i++)
    {
        std::cout << comments[i]->get_id() << " " << comments[i]->get_content() << std::endl;
        comments[i]->printReplies();
    }
}

void Film::deleteComment(int commentId)
{
     Comment* comment = getComment(commentId);
    if(comment == nullptr)
        throw NotFound();
    for(int i = 0; i < comments.size(); i++)
        if(commentId == comments[i]->get_id())
            comments.erase(comments.begin() + i);
}

void Film::addReply(int commentId, std::string content)
{
    Comment* comment = getComment(commentId);
    if(comment == nullptr)
        throw NotFound();
    comment->addReply(content);
}

void Film::editData(std::string _name, int _year, int _length, std::string _summary, std::string _director)
{
    if(_name != "")
        name = _name;
    if(_year != 0)
        year = _year;
    if(_length != 0)
        length = _length;
    if(_summary != "")
        summary = _summary;
    if(_director != "")
        director = _director;
}

int Film::getDeleteStatus()
{
    return deleted;
}

void Film::printRecommended()
{
    std::cout << filmId << " | " << name << " | ";
    std::cout << length << " | " << director << "\n";
}

