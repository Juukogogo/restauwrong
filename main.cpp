#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;



class menu_list{
    private:
        class node_read_menu{
             public:
                node_read_menu *link;
                string menu_name;
                string menu_amount;
                string menu_ID;
                string menu_ingredients;
                int    menu_price;
                
                node_read_menu(){
                    link=NULL;
                    menu_name = "";
                    menu_amount = "";
                    menu_ID = "";
                    menu_ingredients = "";
                    menu_price = 0;
                }


        };
    public:
        int count_menu;
        node_read_menu *head_menu;
        node_read_menu *tail_menu;

        menu_list(){
            count_menu = 0;
        }    

        void add_read_menu_txt(string name, string menu_amount, string menu_ID, int menu_price ){
            auto *temp = new node_read_menu();

           temp->menu_name = name;
            temp->menu_amount = menu_amount;
            temp->menu_ID = menu_ID;
            temp->menu_price = menu_price;
            if(count_menu == 0){
                temp->link = NULL;
                head_menu = temp;
                tail_menu = temp;
            }else{
                temp ->link = NULL;
                tail_menu->link = temp ;
                tail_menu = tail_menu -> link;
            }

        count_menu++;
        }
        
        void read_file_menu_txt(){
            string read_name, read_ID, read_amount;
            int    read_price;
            string   read_pricestr;
            string line;
            ifstream file;
            string d = "\t";
            file.open("..//menu.txt", ios::in);
            if(file.fail()){
                cout << "Can't open menu file" << endl;
            }else {
                while (getline(file, line)){
                    read_ID = line.substr(0, line.find(d)) ;
                              line.erase(line.find(d) + d.length());
                    read_name = line.substr(0, line.find(d)) ;
                                line.erase(line.find(d) + d.length());
                    read_amount = line.substr(0, line.find(d)) ;
                                  line.erase(line.find(d) + d.length());
                    read_pricestr = line.substr(0, line.find(d)) ;
                                 line.erase(line.find(d) + d.length());
                    stringstream read(read_pricestr);
                    read >> read_price;
                    add_read_menu_txt(read_name, read_amount, read_ID, read_price );                                                                                                       
                }
                file.close();
            }
        }

        void update_file_menu()
        {
            fstream data;
            data.open("..//menu.txt",ios::out);
            if(data.is_open())\
            {
                auto *temp = new node_read_menu();
                temp = head_menu;
                while(temp != NULL )
                {
                    data << temp->menu_ID << "\t" << temp->menu_name << "\t" << temp->menu_amount << "\t" << temp->menu_price << endl;
                    temp = temp->link;
                }
                data.close();    
            }else {
                cout << "Sorry, Can't update_file_menu" << endl;
            }
        }


};
int main(){
    menu_list menu;
    menu.read_file_menu_txt();
    cout << "huakuy mak" << endl;
    return 0;
}