#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <utility>

using namespace std;

class promotion {
public:
    string ID;
    int day;
    int month;
    int year;
    string code;
    string dish1;
    string dish2;
    float discount_fix_price;
    float discount_percent;
    int require_amount;
    int extra_amount;
    bool active;
    int type;
    promotion *link;

    promotion(string id, int d, int m, int y, string co, string d1, string d2, float dis_f, float dis_p, int req_a,
              int ex_a, int t) {
                ID = std::move(id);
                day = d;
                month = m;
                year = y;
                code = std::move(co);
                dish1 = std::move(d1);
                dish2 = std::move(d2);
                discount_fix_price = dis_f;
                discount_percent = dis_p;
                require_amount = req_a;
                extra_amount = ex_a;
                type = t;
    }

};

class menu_list {
private:
    class node_read_menu {
    public:
        node_read_menu *link;
        string menu_name;
        string menu_ID;
        int menu_price;
        int menu_price_extra;

        node_read_menu() {
            link = nullptr;
            menu_name = "";
            menu_ID = "";
            menu_price = 0;
            menu_price_extra = 0;
        }


    };

public:
    int count_menu;
    node_read_menu *head_menu;
    node_read_menu *tail_menu;

    menu_list() {
        count_menu = 0;
        head_menu = NULL;
        tail_menu = NULL;
    }

    void add_read_menu_txt(string name, string menu_ID, int menu_price, int menu_price_extra) {
        auto *temp = new node_read_menu();

        temp->menu_name = std::move(name);
        temp->menu_ID = std::move(menu_ID);
        temp->menu_price = menu_price;
        temp->menu_price_extra = menu_price_extra;
        if (count_menu == 0) {
            temp->link = nullptr;
            head_menu = temp;
            tail_menu = temp;
        } else {
            temp->link = nullptr;
            tail_menu->link = temp;
            tail_menu = tail_menu->link;
        }

        count_menu++;
    }

    void read_file_menu_txt() {
        string read_name, read_ID;
        int read_price, read_price_extra;
        string read_pricestr, read_priceextra_str;
        string line;
        ifstream file;
        string d = "\t";
        file.open("..//menu.txt", ios::in);
        if (file.fail()) {
            cout << "Can't open menu file" << endl;
        } else {
            while (getline(file, line)) {
                read_ID = line.substr(0, line.find(d));
                line.erase(line.find(d) + d.length());
                read_name = line.substr(0, line.find(d));
                line.erase(line.find(d) + d.length());
                read_pricestr = line.substr(0, line.find(d));
                line.erase(line.find(d) + d.length());
                read_priceextra_str = line.substr(0, line.find(d));
                line.erase(line.find(d) + d.length());
                stringstream read(read_pricestr);
                read >> read_price;
                stringstream read_extraprice(read_priceextra_str);
                read_extraprice >> read_price_extra;
                add_read_menu_txt(read_name, read_ID, read_price, read_price_extra);
            }
            file.close();
        }
    }

};
int main() {
    menu_list menu;
    menu.read_file_menu_txt();
    cout << "huakuy mak" << endl;
    return 0;
}