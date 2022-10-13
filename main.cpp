#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;



class linked_list{
    private:
        class node_read{
             public:
                node_read *link;
                string menu_name;
                string menu_amount;
                string menu_ID;
                string menu_ingredients;
                int    menu_price;
                
                node_read(){
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
        node_read *head_menu;
        node_read *tail_menu;

        linked_list(){
            count_menu = 0;
        }    

        void add_read_menu_txt(string menu_name, string menu_amount, string menu_ID, int menu_price ){
            auto *temp = new node_read();

            this->menu_name = menu_name;
            this->menu_amount = menu_amount;
            this->menu_ID = menu_ID;
            this->menu_price = menu_price;
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
            string line;
            ifstream file;
            string d = "\t";
            file.open("..//menu.txt", ios::in);
            if(file.fail()){
                cout << "Can't open menu file" << endl;
            }else {
                while (getline(file, line)
                {
                    read_ID = line.substr(0, line.find(d)) ;
                              line.erase(line.find(d) + d.length());
                    read_name = line.substr(0, line.find(d)) ;
                                line.erase(line.find(d) + d.length());
                    read_amount = line.substr(0, line.find(d)) ;
                                  line.erase(line.find(d) + d.length());
                    read_price = line.substr(0, line.find(d)) ;
                                 line.erase(line.find(d) + d.length());
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
                auto *temp = new node_read();
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
    


int main(){
    linked_list obj;
    obj.read_file_menu_txt();
    
    return 0;
}