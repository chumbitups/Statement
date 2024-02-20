#include <iostream>
#include <vector>
#include <fstream>

struct statement
{
    std::string name = "";
    std::string surname = "";
    std::string date = "";
    int money = 0;
    int money2 = 0;
};

void add(statement &client, std::vector<statement> &clients)
{
    std::cout << "Enter the name and surname of recipent: ";
    std::cin >> client.name >> client.surname;
    std::cout << "Enter the date of payment: ";
    std::cin >> client.date;
    std::cout << "Enter the amount of money: ";
    std::cin >> client.money;
    clients.push_back(client);
}

bool validate(statement &client)
{
    int day = std::stoi(client.date.substr(0, 2));
    int month = std::stoi(client.date.substr(3, 2));
    int year = std::stoi(client.date.substr(6, 4));

    if (month < 1 || month > 12 ||
        day < 1 || day > 31 ||
        year < 1900 || year > 2100)
    {
        std::cerr << "Incorrect date!";
        return false;
    }
    return true;
}

int main()
{
    std::string path = "statement.bin";
    std::vector<statement> clients;
    std::string command = "";
    while (command != "stop")
    {
        std::cout << "Enter the command: ";
        std::cin >> command;

        if (command == "add")
        {
            statement client;
            add(client, clients);
            if (validate(client))
            {
                std::ofstream statement_write(path, std::ios::app | std::ios::binary);
                if (statement_write.is_open())
                {
                    statement_write.write((char *)&client.name, client.name.length());
                    statement_write.close();
                }
                else
                {
                    std::cerr << "file can't be opened";
                }
            }
            else
            {
                return 1;
            }
        }
    }
}