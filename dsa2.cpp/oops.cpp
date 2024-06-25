#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class shopping
{
private:
    int pcode;
    float price;
    float dis;
    string pname;

public:
    void menu();
    void administrator();
    void buyer();
    void add();
    void edit();
    void rem();
    void list();
    void receipt();
};

void shopping::menu()
{
    m:
    int choice;
    string email;
    string password;

    cout << "\t\t*******************************************" << endl;
    cout << "\t\t          Supermarket Main Menu            " << endl;
    cout << "\t\t*******************************************" << endl;

    cout << "\n1) Administrator" << endl;
    cout << "\n2) Buyer" << endl;
    cout << "\n3) Exit" << endl;
    cout << "\n\t\t\t\t Please select" << endl;
    cin >> choice;

    switch (choice)
    {
    case 1:
        cout << "\t\t\tPlease Login" << endl;
        cout << "\tEnter Email : ";
        cin >> email;
        cout << "\tPassword    : ";
        cin >> password;

        if (email == "admin@email.com" && password == "123")
        {
            administrator();
        }
        else
        {
            cout << "Invalid email/password";
        }
        break;

    case 2:
        buyer();
        break;

    case 3:
        exit(0);

    default:
    {
        cout << "Please select from the given options";
    }
    }
    goto m;
}

void shopping::administrator()
{
    m:
    char ch;
    int choice;
   
    cout << "\n\n\t\t\t\tADMINISTRATOR MAIN MENU" << endl;
    cout << "\n1) Add product" << endl;
    cout << "\n2) Modify product" << endl;
    cout << "\n3) Delete product" << endl;
    cout << "\n4) Back to the main menu" << endl;

    cout << "\n\t\t\t Please enter your choice ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        add();
        break;

    case 2:
        edit();
        break;

    case 3:
        rem();
        break;

    case 4:
        menu();
        break;

    default:
        cout << "Invalid Choice ";
    }
    goto m;
}

void shopping::buyer()
{
    m:
    int choice;
    cout << "\t\t\tBUYER " << endl;
    cout << "\t\t*******************************************" << endl;
    cout << "\n1) Buy" << endl;
    cout << "\n2) Go Back" << endl;

    cout << "\n\t\t\t Please enter your choice ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        receipt();
        break;

    case 2:
        menu();
        break;

    default:
        cout << "Invalid Choice !" << endl;
    }

    goto m;
}

void shopping::add()
{
    m:
    fstream data;
    int c;
    int token = 0;
    float p;
    float d;
    string n;

    cout << "\n\t\tAdd new product" << endl;
    cout << "\tProduct code : ";
    cin >> pcode;
    cout << "\tProduct Name : ";
    cin >> pname;
    cout << "\tProduct Price: ";
    cin >> price;
    cout << "\tDiscount on product : ";
    cin >> dis;

    data.open("database.txt", ios::in);

    if (!data)
    {
        data.open("database.txt", ios::app | ios::out);
        data << pcode << " " << pname << " " << price << " " << dis << endl;
        data.close();
    }
    else
    {
        data >> c >> n >> p >> d;

        while (!data.eof())
        {
            if (c == pcode)
            {
                token++;
            }
            data >> c >> n >> p >> d;
        }
        data.close();

        if (token == 1)
        {
         goto m;
        }
        else
        {
            data.open("database.txt", ios::app | ios::out);
            data << pcode << " " << pname << " " << price << " " << dis << endl;
            data.close();
        }
    }
    cout << "\n\n\t\t\tRECORD INSERTED !" << endl;
}

void shopping::edit()
{
    fstream data, data1;
    int c;
    int token = 0;
    float p;
    float d;
    string n;
    int pkey;

    cout << "\n\t\tModify product" << endl;
    cout << "\tProduct code : ";
    cin >> pkey;

    data.open("database.txt", ios::in);

    if (!data)
    {
        cout << "\n\nFile doesn't exist !!";
    }
    else
    {
        data1.open("database1.txt", ios::app | ios::out);

        data >> c >> n >> p >> d;
        while (!data.eof())
        {
            if (pkey == c)
            {
                cout << "\tProduct code : ";
                cin >> c;
                cout << "\tProduct Name : ";
                cin >> n;
                cout << "\tProduct Price: ";
                cin >> p;
                cout << "\tDiscount on product : ";
                cin >> d;
                data1 << c << " " << n << " " << p << " " << d << endl;
                cout << "\n\n\t\tRECORD EDITED ! " << endl;
                token++;
            }
            else
            {
                data1 << c << " " << n << " " << p << " " << d << endl;
            }
            data >> c >> n >> p >> d;
        }
        data.close();
        data1.close();

        remove("database.txt");
        rename("database1.txt", "database.txt");

        if (token == 0)
        {
            cout << "\nRECORD NOT FOUND";
        }
    }
}

void shopping::rem()
{
    fstream data, data1;
    int pkey;
    int token = 0;
    cout << "\n\n\t Delete product\n\n\tProduct code : ";
    cin >> pkey;
    data.open("database.txt", ios::in);
    if (!data)
    {
        cout << "File doesn't exist :(" << endl;
    }
    else
    {
        data1.open("database1.txt", ios::app | ios::out);
        int c;
        string n;
        float p, d;
        data >> c >> n >> p >> d;
        while (!data.eof())
        {
            if (c == pkey)
            {
                cout << "\n\n\tProduct deleted successfully";
                token++;
            }
            else
            {
                data1 << c << " " << n << " " << p << " " << d << endl;
            }
            data >> c >> n >> p >> d;
        }
        data.close();
        data1.close();

        remove("database.txt");
        rename("database1.txt", "database.txt");

        if (token == 0)
        {
            cout << "\nRECORD NOT FOUND";
        }
    }
}

void shopping::list()
{
    fstream data;

    data.open("database.txt", ios::in);
    cout << "\n---------------------------------------------------------" << endl;
    cout << "Product No \t\tName\t\tPrice" << endl;
    cout << "\n---------------------------------------------------------" << endl;

    data >> pcode >> pname >> price >> dis;

    while (!data.eof())
    {
        cout << pcode << "\t\t" << pname << "\t\t" << price << "\n";
        data >> pcode >> pname >> price >> dis;
    }

    data.close();
}

void shopping::receipt()
{
    m:
    fstream data;

    int arrc[100];
    int arrq[100];
    char choice;
    int c = 0;
    float amount = 0;
    float disc = 0;
    float total = 0;

    cout << "\n\n_________________________RECEIPT_________________________" << endl;
    data.open("database.txt", ios::in);

    if (!data)
    {
        cout << "Empty Database !!" << endl;
    }
    else
    {
        data.close();

        list();
        cout << "\n _________________________________________________________";
        cout << "\n|                                                         |";
        cout << "\n                  Please place the order                   ";
        cout << "\n|                                                         |";
        cout << "\n _________________________________________________________";
        do
        {
            cout << "\n\nEnter product Code : ";
            cin >> arrc[c];
            cout << "Enter the product quantity : ";
            cin >> arrq[c];
            for (int i = 0; i < c; i++)
            {
                if (arrc[c] == arrc[i])
                {
                    cout << "\nDuplicate product code. Please try again !" << endl;
                    goto m;
                }
            }
            c++;
            cout << "\nDo you want to buy another product(Y/N) : ";
            cin >> choice;
        } while (choice == 'y' || choice == 'Y');

        cout << "\n\n___________________________________________________RECEIPT___________________________________________________" << endl;
        cout << "Product No\tProduct name\tProduct quantity\t\tPrice\tAmount\tAmount with discount" << endl;

        for (int i = 0; i < c; i++)
        {
            data.open("database.txt", ios::in);
            data >> pcode >> pname >> price >> dis;
            while (!data.eof())
            {
                if (pcode == arrc[i])
                {
                    amount = price * arrq[i];
                    disc = amount - (amount * dis / 100);
                    total = total + disc;
                    cout << pcode << "\t\t" << pname << "\t\t" << arrq[i] << "\t\t" << price << "\t\t" << amount << "\t\t" << disc << endl;
                }
                data >> pcode >> pname >> price >> dis;
            }
            data.close();
        }
    }
    cout << "\n _____________________________________________________________________________________________________________";
    cout << "\nTotal Amount : " << total << endl;
}

int main()
{
    shopping s;
    s.menu();

    return 0;
}
