//
// Created by Yut Fut on 18.11.2021.
//

#ifndef VVTI_CLIENT_CLIENT_H
#define VVTI_CLIENT_CLIENT_H

#include <iostream>
#include <map>
#include "validation.h"
#include "user.h"
#include "command.h"

class Client {
private:
    User user;

    std::map <std::string, int> commands;

    enum Commands{
        UPLOAD,
        DOWNLOAD,
        EXIT,
    };
public:
    Client();

    ~Client();

    void print();

    int role_command(const std::string& command);

    int validation_command(const std::string& command);

    void run();
};

#endif //VVTI_CLIENT_CLIENT_H
