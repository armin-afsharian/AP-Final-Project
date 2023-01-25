#include "Comment.h"

Comment::Comment(int _id, std::string _content, int _clientId)
{
    id = _id;
    content = _content;
    clientId = _clientId;
}

void Comment::printReplies()
{
    for(int i = 0; i<replies.size(); i++)
        std::cout  << id << " " << replies[i] << std::endl;
}

void Comment::addReply(std::string reply)
{
    replies.push_back(reply);
}

int Comment::get_id()
{
    return id;
}

std::string Comment::get_content()
{
    return content;
}

int Comment::getClientId()
{
    return clientId;
}