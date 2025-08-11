#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>
#include <unordered_map>


struct Command {
    std::string comm;
    int id;
    int pages = -1;
};

Command ParseLine(std::string_view line) {
    Command cmd;
    std::vector<std::string> tokens;
    
    std::istringstream iss{std::string(line)};
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    
    if (tokens.empty()) {
        return {};
    }
    
    cmd.comm = tokens[0];
    
    if (cmd.comm == "CHEER") {    
        cmd.id = std::stoi(tokens[1]);
    }
    else if (cmd.comm == "READ") {
        cmd.id = std::stoi(tokens[1]);
        cmd.pages = std::stoi(tokens[2]);
    }
    
    return cmd;
}

class BookAchivement {
public:

    BookAchivement();
    void PagesRead(int id, int pages);
    void CheerUser(int id);

private:
    std::unordered_map<int, int> users_page_;
    std::vector<int> pages_;
};

BookAchivement::BookAchivement()
:pages_(1000, 0)
{}

void BookAchivement::PagesRead(int id, int pages) {
    int old_page = 0;
    if (users_page_.count(id) > 0) {
        old_page = users_page_[id];
    }

    users_page_[id] = pages;

    for (size_t i = old_page; i != pages; ++i) {
        ++pages_[i+1];
    }
}

void BookAchivement::CheerUser(int id) {
    if (users_page_.count(id) == 0) {
        std::cout << 0 << '\n';
        return;
    }
    if (users_page_.count(id) > 0 && users_page_.size() == 1) {
        std::cout << 1 << '\n';
        return;
    }
    int pages = users_page_[id];
    int user_amount_on_page = pages_[pages] - 1;
    int all_users = users_page_.size() - 1;
    double result = 1.0 * (all_users - user_amount_on_page) / all_users;
    
    std::cout << std::setprecision(6) << result << '\n';
}

int main(){
    BookAchivement books;
    std::string line;
    int i = 0;
    int amount;

    std::cin >> amount;
    while(i < amount) {
        std::getline(std::cin, line);
        if (line.empty()){
            continue;
        }

        const Command command = ParseLine(line);

        if (command.comm == "READ") {
            books.PagesRead(command.id, command.pages);
        }
        if (command.comm == "CHEER") {
            books.CheerUser(command.id);
        }
        ++i;
    }
}
