#include "System.h"

Publisher* System::get_publisher(int Id)
{
    for(int i = 0; i<publishers.size(); i++)
        if(Id == publishers[i]->getId())
            return publishers[i];
    return nullptr;
}

Film * System::get_film(int id)
{
    for(int i = 0; i<films.size(); i++)
        if(id == films[i]->getId())
            return films[i];
    return nullptr;
}

Client* System::get_client(int id)
{
    for(int i = 0 ; i < clients.size(); i++)
        if(clients[i]->getId() == id)
            return clients[i];
    return nullptr;
}

void System::moneyCal(float rate, int amount, Publisher* publisher)
{   
    int sum = 0;
    if(rate < 5)
        sum = amount * (0.8);
    else if(rate >= 5 && rate < 8)
        sum = amount * (0.9);
    else
        sum = amount * (0.95);
    publisher->addCredit(sum);
    income = amount - sum;
    std::cout << "OK\n";
}


void System::signup(std::vector<std::string> &line)
{
    std::string email = "",username = "",pass = "",publisher = "false";
    int age = 0;
    for(int i = 1; i < line.size(); i = i+2)
    {
        if(line[i] == "email")
            email = line[i+1];
        else if(line[i] == "username")
        {
            repeatedUser(line[i+1]);
            username = line[i+1];
        }
        else if(line[i] == "password")
            pass = line[i+1];
        else if(line[i] == "age")
            age = stoi(line[i+1]);
        else if(line[i] == "publisher")
            publisher = line[i+1];
    }
    if((email == "") || (username == "") || (pass == "") || (age == 0))
            throw BadRequest();
    clientId++;
    loggedInId = clientId;
    clients.push_back(new Client(username,pass,email,age,clientId));
    if(publisher == "true")
        publishers.push_back(new Publisher(username,pass,email,age,clientId));
    std::cout << "OK\n";
}

void System::repeatedUser(std::string user)
{
    for(int i = 0; i <clients.size(); i++)
        if(clients[i]->getUser() == user)
            throw BadRequest();
}

void System::login(std::vector<std::string> &line)
{
    std::string user = "",pass = "";
    for(int i = 0; i < line.size(); i++)
    {
        if(line[i] == "username")
            user = line[i+1];
        else if(line[i] == "password")
            pass = line[i+1];
    }
    if((user == "") || (pass == ""))
        throw BadRequest();
    checkData(user,pass);
    std::cout << "OK\n";
}

void System::checkData(std::string &user, std::string &pass)
{
    bool exists = false;
    for(int i = 0; i < clients.size(); i++)
    {
        if(clients[i]->getUser() == user && clients[i]->getPass() == pass)
        {
            exists = true;
            loggedInId = clients[i]->getId();
        }
    }
    if(exists == false)
        throw BadRequest();
        
}

void System::postFilm(std::vector<std::string> &line)
{
    Publisher* publisher = get_publisher(loggedInId);
    if(publisher == nullptr)
        throw PermissionDenied();
    std::string name = "",summary = "",director = "";
    int year = 0,length = 0,price = -1;
    for(int i = 0; i <line.size(); i++)
    {
        if(line[i] == "name")
            name = line[i+1];
        else if(line[i] == "year")
            year = stoi(line[i+1]);
        else if(line[i] == "length")
            length = stoi(line[i+1]);
        else if(line[i] == "price")
            price = stoi(line[i+1]);
        else if(line[i] == "summary")
            summary = line[i+1];
        else if(line[i] == "director")
            director = line[i+1];
    }
    if((name == "") || (summary == "") || (director == "") || (year == 0) || (length == 0) || (price == -1))
        throw BadRequest();
    filmId++;
    Film* film = new Film(name, year, length, price, summary, director, filmId, publisher->getId());
    films.push_back(film);
    publisher->postFilm(film);
    std::cout << "OK\n";
}

void System::postMoney()
{
    Publisher* publisher = get_publisher(loggedInId);
    if(publisher == nullptr)
        throw PermissionDenied();
    std::cout << "OK\n";
    publisher->takeMoney();
}

void System::following(std::vector<std::string> &line)
{
    Publisher* publisher = nullptr;
    Client* client = get_client(loggedInId);
    for(int i = 0; i < line.size(); i++)
        if(line[i] == "user_id")
            publisher = get_publisher(stoi(line[i+1]));
    if(publisher == nullptr)
        throw NotFound();
    client->followingPublisher(publisher->getId());
    publisher->addFollower(client);
    std::cout << "OK\n";
}

void System::postMoneyClient(std::vector<std::string> &line)
{
    Client* client = get_client(loggedInId);
    for(int i = 0; i<line.size(); i++)
        if(line[i] == "amount")
            client->postMoney(stoi(line[i+1]));
    std::cout << "OK\n";    
}

void System::buyFilm(std::vector<std::string> &line)
{
    Client* client = get_client(loggedInId);
    Film* film = nullptr;
    for(int i = 0; i < line.size(); i++)
        if(line[i] == "film_id")
            film = get_film(stoi(line[i+1]));
    if(film == nullptr)
        throw NotFound();
    client->buyFilm(film);
    Publisher* publisher = get_publisher(film->get_publisher());
    Notification* n = new Notification;
    n->buyFilmNotification(client->getId(), client->getUser(), get_film(film->getId())->getName(), film->getId());
    publisher->addNotification(n);
    moneyCal(film->getRate(), film->getPrice(), publisher);
}

void System::rateFilm(std::vector<std::string> &line)
{
    Client* client = get_client(loggedInId);
    int filmId = 0,score = -1;
    for(int i = 0; i < line.size(); i++)
    {
        if(line[i] == "film_id")
            filmId = stoi(line[i+1]);
        else if(line [i] == "score")
            score = stoi(line[i+1]);
    }
    if((score < 0) || (filmId <= 0))
        throw BadRequest();
    client->giveRate(filmId, score);
    Publisher* publisher = get_publisher(client->getFilm(filmId)->get_publisher());
    Notification* n = new Notification;
    n->rateNotification(client->getId(), client->getUser(), get_film(filmId)->getName(), filmId);
    publisher->addNotification(n);
    std::cout << "OK\n";
}

void System::postComments(std::vector<std::string> &line)
{
    Client* client = get_client(loggedInId);
    int filmId = 0;
    std::string content = "";
    for(int i = 0 ; i < line.size(); i++)
    {
        if(line[i] == "film_id")
            filmId = stoi(line[i+1]);
        else if(line[i] == "content")
            content = line[i+1];
    }
    if((content == "") || (filmId <= 0))
        throw BadRequest();
    Publisher* publisher = get_publisher(client->getFilm(filmId)->get_publisher());
    Notification* n = new Notification;
    n->commentNotification(client->getId(), client->getUser(), get_film(filmId)->getName(), filmId);
    publisher->addNotification(n);
    Comment* comment = client->postComments(filmId, content);
    comments.push_back(comment);
    std::cout << "OK\n";
}

void System::getFollowers()
{
    Publisher* publisher = get_publisher(loggedInId);
    if(publisher == nullptr)
        throw PermissionDenied();
    publisher->followersList();
}

void System::deleteFilm(std::vector<std::string> &line)
{
    Publisher* publisher = get_publisher(loggedInId);
    int film_id = 0;
    if(publisher == nullptr)
        throw PermissionDenied();
    for(int i = 0; i < line.size(); i++)
            if(line[i] == "film_id")
                film_id = stoi(line[i+1]);
    publisher->deleteFilm(film_id);
    std::cout << "OK\n";
}

void System::deleteComments(std::vector<std::string> &line)
{
    Publisher* publisher = get_publisher(loggedInId);
    int filmId = 0, commentId = 0;
    if(publisher == nullptr)
        throw PermissionDenied();
    for(int i = 0; i < line.size(); i++)
    {
        if(line[i] == "film_id")
            filmId = stoi(line[i+1]);
        else if(line[i] == "comment_id")
            commentId = stoi(line[i+1]);
    }
    if((filmId <= 0) || (commentId <= 0))
        throw BadRequest();
    publisher->deleteComment(filmId, commentId);
    std::cout << "OK\n";
}

void System::editFilm(std::vector<std::string> &line)
{
    Publisher* publisher = get_publisher(loggedInId);
    Client* client = get_client(loggedInId);
    if(publisher == nullptr)
        throw PermissionDenied();
    std::string name = "",summary = "",director = "";
    int year = 0,length = 0, filmId = 0;
    for(int i = 0; i <line.size(); i++)
    {
        if(line[i] == "name")
            name = line[i+1];
        else if(line[i] == "year")
            year = stoi(line[i+1]);
        else if(line[i] == "length")
            length = stoi(line[i+1]);
        else if(line[i] == "summary")
            summary = line[i+1];
        else if(line[i] == "director")
            director = line[i+1];
        else if(line[i] == "film_id")
            filmId = stoi(line[i+1]);
    }
    if(filmId <= 0)
        throw BadRequest();
    publisher->editFilm(filmId, name, year, length, summary, director);
    std::cout << "OK\n";
}

void System::search(std::vector<std::string> &line)
{
    std::string name = "",director = "";
    int min_rate = -1,min_year = 0, max_year = 0 , price = -1;
    for(int i = 0; i < line.size(); i++)
    {
        if(line[i] == "name")
            name = line[i+1];
        else if(line[i] == "director")
            director = line[i+1];
        else if(line[i] == "min_rate")
            min_rate = stoi(line[i+1]);
        else if(line[i] == "price")
            price = stoi(line[i+1]);
        else if(line[i] == "min_year")
            min_year = stoi(line[i+1]);
        else if(line[i] == "max_year")
            max_year = stoi(line[i+1]);
    }
    findFilm(name, director, min_rate, min_year, price, max_year);
}

void System::findFilm(std::string name, std::string director, int min_rate, int min_year, int price, int max_year)
{
    std::vector<Film*> found = films;
    for(int i = 0; i < found.size(); i++)
    {
        if(found[i]->getDeleteStatus() != 0)
        {
            found.erase(found.begin()+i);
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

void System::publishedFilm(std::vector<std::string> &line)
{
    Publisher* publisher = get_publisher(loggedInId);
    if(publisher == nullptr)
        throw PermissionDenied();
    std::string name = "",director = "";
    int min_rate = -1,min_year = 0, max_year = 0 , price = -1;
    for(int i = 0; i < line.size(); i++)
    {
        if(line[i] == "name")
            name = line[i+1];
        else if(line[i] == "director")
            director = line[i+1];
        else if(line[i] == "min_rate")
            min_rate = stoi(line[i+1]);
        else if(line[i] == "price")
            price = stoi(line[i+1]);
        else if(line[i] == "min_year")
            min_year = stoi(line[i+1]);
        else if(line[i] == "max_year")
            max_year = stoi(line[i+1]);
    }
    publisher->publishedFilm(name, director, min_rate, min_year, price, max_year);
}

void System::filmDetail(std::vector<std::string> &line)
{
    Film* film = nullptr;
    Client* client = get_client(loggedInId);
    for(int i = 0; i < line.size(); i++)
        if(line[i] == "film_id")
            film = get_film(stoi(line[i+1]));
    if(film == nullptr || film->getDeleteStatus() == 1)
        throw NotFound();
    recommendedFilms(film, client);
}

void System::purchasedFilm(std::vector<std::string> &line)
{
    Client* client = get_client(loggedInId);
    std::string name = "",director = "";
    int min_year = 0, max_year = 0 , price = -1;
    for(int i = 0; i < line.size(); i++)
    {
        if(line[i] == "name")
            name = line[i+1];
        else if(line[i] == "director")
            director = line[i+1];
        else if(line[i] == "price")
            price = stoi(line[i+1]);
        else if(line[i] == "min_year")
            min_year = stoi(line[i+1]);
        else if(line[i] == "max_year")
            max_year = stoi(line[i+1]);
    }
    client->viewPurchased(name, director, min_year, price, max_year);
}

void System::postReplies(std::vector<std::string> &line)
{
    Publisher* publisher = get_publisher(loggedInId);
    int filmId = 0, commentId = 0;
    std::string content = "";
    if(publisher == nullptr)
        throw PermissionDenied();
    for(int i = 0; i < line.size(); i++)
    {
        if(line[i] == "film_id")
            filmId = stoi(line[i+1]);
        else if(line[i] == "comment_id")
            commentId = stoi(line[i+1]);
        else if(line[i] == "content")
            content = line[i+1];
    }
    if((filmId == 0) || (commentId == 0) || (content == ""))
        throw BadRequest();
    Client* client = get_client(get_film(filmId)->getComment(commentId)->getClientId());
    publisher->postReply(filmId, commentId, content, client);
    std::cout << "OK\n";
}

void System::editfilm(int filmId, std::string name, int year, int length, std::string summary, std::string director)
{
    Film* film = get_film(filmId);
    film->editData(name, year, length, summary, director);
}

void System::deleteFilm(int id)
{
    Film* film = get_film(id);
    film->deleteStatus();
}

bool compareFilm(Film* film1, Film* film2)
{
    if(film1->getRate() != film2->getRate())
        return film1->getRate() > film2->getRate();
    return film1->getId() < film2->getId();
}

void System::recommendedFilms(Film* film, Client* client)
{
    std::vector<Film*> recommended = films;
    for(int i = 0; i < recommended.size(); i++)
        if(recommended[i]->getId() == film->getId())
            recommended.erase(recommended.begin() + i);
    for(int i = 0; i < recommended.size(); i++)
        if(recommended[i]->getDeleteStatus() == 1)
            recommended.erase(recommended.begin() + i);
    std::sort(recommended.begin(), recommended.end(), compareFilm);
    client->erasePurchased(recommended);
    film->printDetail();
    for(int i = 0; i < recommended.size(); i++)
    {
            std::cout << i+1 << ". " ;
            recommended[i]->printRecommended();
    }
}

void System::getNotification()
{
    Publisher* publisher = get_publisher(loggedInId);
    if(publisher != nullptr)
    {
        publisher->printNotification();
        return;
    }
    Client* client = get_client(loggedInId);
    client->printNotification();
}

void System::getNotificationRead(std::vector<std::string> &line)
{
    int limit = 0;
    for(int i = 0; i < line.size(); i++)
        if(line[i] == "limit")
            limit = stoi(line[i+1]);
    Publisher* publisher = get_publisher(loggedInId);
    if(publisher != nullptr)
    {
        publisher->printNotificationRead(limit);
        return;
    }
    Client* client = get_client(loggedInId);
    client->printNotificationRead(limit);
}

