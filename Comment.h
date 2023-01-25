#ifndef COMMENT_H
#define COMMENT_H

#include <string>
#include <vector>
#include <iostream>

class Comment
{
    private:
        int id;
        int clientId;
        std::string content;
        std::vector<std::string> replies;
    public:
        int get_id();
        std::string get_content();
        int getClientId();
        Comment(int _id, std::string _content, int _clientId);
        void addReply(std::string reply);
        void printReplies();
};

#endif