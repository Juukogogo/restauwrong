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
            link = NULL;
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

    // function add data to node
    void add_read_menu_txt(string name, string menu_ID, int menu_price, int menu_price_extra) {
        auto *temp = new node_read_menu();

        temp->menu_name = name;
        temp->menu_ID = menu_ID;
        temp->menu_price = menu_price;
        temp->menu_price_extra = menu_price_extra;
        if (count_menu == 0) {
            temp->link = NULL;
            head_menu = temp;
            tail_menu = temp;
        } else {
            temp->link = NULL;
            tail_menu->link = temp;
            tail_menu = tail_menu->link;
        }

        count_menu++;
    }

    //function read data from menu.txt and then use function add_read to put data in node
    void read_file_menu_txt() {
        string read_name, read_ID;
        int read_price, read_price_extra;
        string read_pricestr, read_priceextra_str;
        string line;
        ifstream file;
        string d = ",";
        file.open("..//menu.txt", ios::in);
        if (file.fail()) {
            cout << "Can't open menu file" << endl;
        } else {
            while (getline(file, line)) {

                read_ID = line.substr(0, line.find(d));
                          line.erase(0,line.find(d) + d.length());
                read_name = line.substr(0, line.find(d));
                            line.erase(0,line.find(d) + d.length());
                read_pricestr = line.substr(0, line.find(d));
                                line.erase(0,line.find(d) + d.length());
                read_priceextra_str = line.substr(0, line.find(d));
                                      line.erase(0,line.find(d) + d.length());

                read_price = stoi(read_pricestr);
                read_price_extra = stoi(read_priceextra_str);
                add_read_menu_txt(read_name, read_ID, read_price, read_price_extra);
            }
            file.close();
        }
    }

    //function updatefile menu.txt
    void update_file_menu()
    {
        fstream data;
        data.open("..//menu.txt", ios::out );
        if ( data.is_open() )
        {
            auto *temp = new node_read_menu();
            temp = head_menu;
            while ( temp != NULL )
            {
                data << temp->menu_ID << "," << temp->menu_name << "," << temp->menu_price << "," << temp->menu_price_extra << endl;
                temp = temp->link;
            }
            data.close();
        }else {
            cout << "Sorry, Can't update file, Please check file again! " << endl;
        }
    }

    // function add menu and then updatefile menu.txt automatics
    void add_menu(string menu_id, string menu_name, int menu_pirce, int menu_price_extra){
        add_read_menu_txt(menu_name,menu_id,menu_pirce,menu_price_extra);
        update_file_menu();
    }

    void delete_menu(string menu_name){
        auto * main = new node_read_menu();
        main = head_menu;
        auto * temp = main;
        node_read_menu * prev = NULL;
        if ( temp != NULL && temp->menu_name == menu_name )
        {
            main = temp->link;
            delete temp;
            return;
        }
        else
        {
            while ( temp != NULL && temp->menu_name != menu_name )
            {
                prev = temp;
                temp = temp->link;
            }
            if ( temp == NULL )
                return;

            prev->link = temp->link;
            delete temp;
        }
        update_file_menu();
    }

    void test_print(){
        auto *temp = new node_read_menu();
        temp = head_menu;
        while ( temp != NULL ){
            cout << temp->menu_ID << " " << temp->menu_name << " " << temp->menu_price << endl;
            temp = temp->link;
        }
    }

};
int main() {
    menu_list menu;
    menu.read_file_menu_txt();
    menu.test_print();
    // test add menu and updatefile
    string testname,testid;
    int testprice,testprice_extra;
    cin >> testid >> testname >> testprice >> testprice_extra;
    menu.add_menu(testid,testname,testprice,testprice_extra);

    cin >> testid >> testname >> testprice >> testprice_extra;
    menu.add_menu(testid,testname,testprice,testprice_extra);

    // test delete menu
    string testdelete;
    cin  >> testdelete;
    menu.delete_menu(testdelete);
    menu.test_print();
    cout << "====" << endl;
    menu.test_print();
    cout << "====" << endl;
    menu.test_print();

    return 0;
}