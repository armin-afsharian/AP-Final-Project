#include "Input.h"

Input::Input(System* _s)
{
    s = _s;
}

void Input::getInput()
{
    std::string str;
    while(getline(std::cin,str))
        input.push_back(str);
    inputDivider();
}

void Input::inputDivider()
{
    for(int i = 0; i < input.size(); i++)
    {
        std::vector<std::string> temp;
        for(int j = 0; j < input[i].size(); j++)
        {
            std::string word = "";
            while(input[i][j] != ' ')
            {
                word = word + input[i][j];
                j++;
                if(j == input[i].size())
                    break;
            }
            temp.push_back(word);
        }
        inputhandler.push_back(temp);
    }
    checkCommand();
}

void Input::checkCommand()
{
    for(int i = 0; i < inputhandler.size(); i++)
    {
        try
        {
            if(inputhandler[i].size() == 0)
                continue;
            if(inputhandler[i][0] == "PUT")
                putCommands(inputhandler[i]);
            else if(inputhandler[i][0] == "POST")
                postCommands(inputhandler[i]);
            else if(inputhandler[i][0] == "GET")
                getCommands(inputhandler[i]);
            else if(inputhandler[i][0] == "DELETE")
                deleteCommands(inputhandler[i]);
            else
                throw BadRequest();
        }
        catch(Exception &e)
        {
            e.what();
            continue;
        }       
    }
}

void Input::putCommands(std::vector<std::string> &line)
{
    if(line[1] == "films")
        s->editFilm(line);
    else
        throw BadRequest();
}

void Input::postCommands(std::vector<std::string> &line)
{
    if(line[1] == "signup")
        s->signup(line);
    else if(line[1] == "login")
        s->login(line);
    else if(line[1] == "films")
        s->postFilm(line);
    else if(line[1] == "followers")
        s->following(line);
    else if(line[1] == "money" && line.size() > 2)
    {
        s->postMoneyClient(line);
        return;
    }
    else if(line[1] == "money")
        s->postMoney();
    else if(line[1] == "buy")
        s->buyFilm(line);
    else if(line[1] == "rate")
        s->rateFilm(line);
    else if(line[1] == "comments")
        s->postComments(line);
    else if(line[1] == "replies")
        s->postReplies(line);
    else
        throw BadRequest();
}

void Input::getCommands(std::vector<std::string> &line)
{
    if(line[1] == "followers")
        s->getFollowers();
    else if((line[1] == "films") && (line[3] == "film_id"))
    {
        s->filmDetail(line);
        return;
    }
    else if(line[1] == "films")
        s->search(line);
    else if(line[1] == "published")
        s->publishedFilm(line);
    else if(line[1] == "purchased")
        s->purchasedFilm(line);
    else if(line[1] == "notifications" && line.size() > 2)
        s->getNotificationRead(line);
    else if(line[1] == "notifications")
        s->getNotification();
    else
        throw BadRequest();
}

void Input::deleteCommands(std::vector<std::string> &line)
{
    if(line[1] == "films")
        s->deleteFilm(line);
    else if(line[1] == "comments")
        s->deleteComments(line);
    else
        throw BadRequest();
}
