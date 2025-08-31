#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class Product {
public:
    void displayProd() { // to display all products
        string st;
        ifstream in("products.txt");
        if (!in) {
            cout << "No products found!" << endl;
            return;
        }
        cout << "\n===============================\n";
        cout << " THE AVAILABLE PRODUCTS ARE\n";
        cout << "===============================\n";
        cout << "Id | Item | Price | Quantity\n";
        
        while (getline(in, st)) {
            cout << st << endl;
        }
        in.close();
    }

    void addProd(int id, string item, float price, int quantity) { 
        ofstream out("products.txt", ios::app); // append mode
        if (!out) {
            cout << "Error opening file!" << endl;
            return;
        }
        // write product in one line, separated by |
        out << id << "|" << item << "|" << price << "|" << quantity << endl;
        out.close();
        cout << " Product added successfully!\n";
    }
    void searchbyId(int id) {
        ifstream in("products.txt");
        if (!in) {
            cout << "Error opening file!" << endl;
            return;
        }

        string line;
        bool found = false;

        while (getline(in, line)) {
            stringstream ss(line);
            string tempId, name, priceStr, quantityStr;

            getline(ss, tempId, '|');   // extract id
            getline(ss, name, '|');     // extract item name
            getline(ss, priceStr, '|'); // extract price
            getline(ss, quantityStr, '|'); // extract quantity

            int fileId = stoi(tempId);        // convert string → int
            float price = stof(priceStr);     // convert string → float
            int quantity = stoi(quantityStr); // convert string → int

            if (fileId == id) {
                cout << "Product Found!\n"
                    << "Item Name: " << name << "\n"
                    << "Price: " << price << "\n"
                    << "Quantity: " << quantity << "\n";
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Product with ID " << id << " not found.\n";
        }

        in.close();
    }
    //Buy product function
    void buyProd(int searchId , int qty){
        ifstream in("products.txt");
        ofstream out("temp.txt");
        string line ;
        bool found = false ;
        while(getline(in , line)){
            stringstream ss(line);
            int id ;
            string name ;
            float price ;
            int quantity ;

            char sep ;
            ss>> id >>sep;
            getline(ss, name ,'|');
            ss >>price >>sep >>quantity ;
            if(id == searchId){
                found = true ;
                if(quantity >= qty){
                    quantity -= qty ;
                    cout<< "Purchased " << qty << " of " << name << ".\n";
                }
                else{
                    cout<< "Not enough stock ! only left " << quantity<< "available\n";
                }
            }
            out << id << "|" << name << "|" << price << "|" << quantity << endl;
        }
        in.close();
        out .close(); 
        remove("products.txt");
        rename("temp.txt", "products.txt");

    if (!found) {
        cout << "Product not found!\n";
    }

    }
    //authentication system 
    bool log(){
        string user , pass ;
        string corruser = "admin" ;
        string corrpass = "12345" ;
        cout << "========== LOGIN ==========\n";
        cout << "Enter Username: ";
        cin >> user;
        cout << "Enter Password: ";
        cin >> pass;
        if(user == corruser && pass == corrpass){
            cout << "Login Successfull\n" ;
            return true ;
        }else{
            cout<< "invalid Username or password \n" ;
            return false ;
        }

    }
};

int main() {
    Product p;
    int ident;

    cout << "Are you a Customer or Admin? (1 = Customer, 0 = Admin): ";
    cin >> ident;

    if (ident == 1) {
        // Customer Menu
        int choose;
        do {
            cout << "\n===== CUSTOMER MENU =====\n";
            cout << "1. Display Products\n";
            cout << "2. Buy Product\n";
            cout << "3. Exit\n";
            cout << "Enter your choice: ";
            cin >> choose;

            if (choose == 1) {
                p.displayProd();
            } else if (choose == 2) {
                int id, qty;
                cout << "Enter ID and quantity to buy product: ";
                cin >> id >> qty;
                p.buyProd(id, qty);
            } else if (choose == 3) {
                cout << "Thank you for visiting! \n";
            } else {
                cout << "Invalid choice, try again.\n";
            }

        } while (choose != 3);  // loop until customer exits
    }
    else {
        // Admin Menu (requires login)
        if (p.log() == true) {
            int choice;
            do {
                cout << "\n========= ADMIN MENU =========\n";
                cout << "1. Add Product\n";
                cout << "2. Display Products\n";
                cout << "3. Search Product by ID\n";
                cout << "4. Buy Product\n";
                cout << "5. Exit\n";
                cout << "Enter your choice: ";
                cin >> choice;

                if (choice == 1) {
                    int id, quantity;
                    float price;
                    string item;
                    cout << "Enter product details (id item price quantity): ";
                    cin >> id >> item >> price >> quantity;
                    p.addProd(id, item, price, quantity);
                } 
                else if (choice == 2) {
                    p.displayProd();
                } 
                else if (choice == 3) {
                    int id;
                    cout << "Enter ID to search: ";
                    cin >> id;
                    p.searchbyId(id);
                } 
                else if (choice == 4) {
                    int id, qty;
                    cout << "Enter ID and quantity to buy product: ";
                    cin >> id >> qty;
                    p.buyProd(id, qty);
                } 
                else if (choice == 5) {
                    cout << "Logging out... \n";
                } 
                else {
                    cout << " Invalid choice, try again.\n";
                }

            } while (choice != 5);  // loop until admin exits
        } else {
            cout << " Authentication failed. Access denied.\n";
        }
    }

    return 0;
}
