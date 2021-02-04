#include <iostream>
#include <fstream>
#include <string.h>
#include <Windows.h>
#include <vector>

using namespace std;

class car
{
public:
    int nr;
    string name;
    int kmTotal;
    int year;
    int isRented;
    int needsMaintenance;
};

class rental
{
public:
    car rent;
    int kmTraveled;
    int nr;
    void addToDatabase(car x);
    car pickFromDatabase(int n);
    void modifyDatabase(car x);
    void removeFromDatabase(car x);
};

void rental::addToDatabase(car x)
{
    ifstream in("database.txt");
    vector <car> all;
    car aux;
    int a;
    in >> a;
    while (in >> aux.nr >> aux.name >> aux.kmTotal >> aux.year >> aux.isRented >> aux.needsMaintenance)
    {
        all.push_back(aux);
    }
    a++;
    x.nr = a;
    all.push_back(x);
    in.close();
    ofstream out("database.txt");
    out << a << endl;
    for (auto it : all)
    {
        out << it.nr << " " << it.name << " " << it.kmTotal << " " << it.year << " " << it.isRented << " " << it.needsMaintenance << endl;
    }
    out.close();
}

car rental::pickFromDatabase(int n)
{
    ifstream in("database.txt");
    int a;
    car aux;
    in >> a;
    for (int i = 1; i <= n; i++)
    {
        in >> aux.nr >> aux.name >> aux.kmTotal >> aux.year >> aux.isRented >> aux.needsMaintenance;
    }
    in.close();
    return aux;
}

void rental::modifyDatabase(car x)
{
    ifstream in("database.txt");
    vector <car> all;
    car aux;
    int a;
    in >> a;
    while (in >> aux.nr >> aux.name >> aux.kmTotal >> aux.year >> aux.isRented >> aux.needsMaintenance)
    {
        if (aux.nr == x.nr)
            all.push_back(x);
        else
            all.push_back(aux);
    }
    in.close();
    ofstream out("database.txt");
    out << a << endl;
    for (auto it : all)
    {
        out << it.nr << " " << it.name << " " << it.kmTotal << " " << it.year << " " << it.isRented << " " << it.needsMaintenance << endl;
    }
    out.close();
}

void rental::removeFromDatabase(car x)
{
    ifstream in("database.txt");
    vector <car> all;
    car aux;
    int a;
    in >> a;
    while (in >> aux.nr >> aux.name >> aux.kmTotal >> aux.year >> aux.isRented >> aux.needsMaintenance)
    {
        if(x.nr != aux.nr)
            all.push_back(aux);
    }
    in.close();
    ofstream out("database.txt");
    out << a << endl;
    a--;
    int i = 1;
    for (auto it : all)
    {
        it.nr = i;
        i++;
        out << it.nr << " " << it.name << " " << it.kmTotal << " " << it.year << " " << it.isRented << " " << it.needsMaintenance << endl;
    }
    out.close();
}

void rentalAddToDatabase()
{
    rental newRental;
    cout << "Enter the car name : "; cin >> newRental.rent.name;
    cout << "Enter the car year : "; cin >> newRental.rent.year;
    cout << "Enter the car actual kilometer : "; cin >> newRental.rent.kmTotal;
    if (newRental.rent.year <= 2011)
        newRental.rent.needsMaintenance = 1;
    else
        newRental.rent.needsMaintenance = 0;
    newRental.rent.isRented = 0;
    newRental.rent.nr = 0;
    newRental.addToDatabase(newRental.rent);
}

void showCarDatabase(bool rentMode)
{
    system("clear");
    ifstream in("database.txt");
    car aux;
    int a;
    in >> a;
    aux.nr = 0;
    while (in >> aux.nr >> aux.name >> aux.kmTotal >> aux.year >> aux.isRented >> aux.needsMaintenance)
    {
        if (rentMode == true && aux.isRented == 0)
        {
            cout << aux.nr << " " << aux.name << " " << aux.kmTotal << " " << aux.year << " " << "NOT RENTED, ";
            if (aux.needsMaintenance == 1)
                cout << "NEEDS MAINTENANCE\n";
            else
                cout << "CAR IS OK\n";
        }
        if (rentMode == false)
        {
            cout << aux.nr << " " << aux.name << " " << aux.kmTotal << " " << aux.year << " ";
            if (aux.isRented == 1)
                cout << "RENTED, ";
            else
                cout << "NOT RENTED, ";
            if (aux.needsMaintenance == 1)
                cout << "NEEDS MAINTENANCE\n";
            else
                cout << "CAR IS OK\n";
        }
    }
    in.close();
    if (aux.nr == 0)
        cout << "Empty database\n";
}

void rentACar()
{
    showCarDatabase(true);
    int n;
    cout << "Select a car BY REFERENCE NUMBER : "; cin >> n;
    rental New;
    New.rent = New.pickFromDatabase(n);
    cout << "SELECTED CAR : \n";
    cout << New.rent.nr << " " << New.rent.name << " " << New.rent.kmTotal << " " << New.rent.year << " ";
    if (New.rent.isRented == 1)
        cout << "RENTED, ";
    else
        cout << "NOT RENTED, ";
    if (New.rent.needsMaintenance == 1)
        cout << "NEEDS MAINTENANCE\n";
    else
        cout << "CAR IS OK\n";
    if (New.rent.isRented == 0)
    {
        cout << "The car will now be set to rented\n";
        New.rent.isRented = 1;
        New.modifyDatabase(New.rent);
    }
    else
        cout << "Car already rented\n";
}

void unrentACar()
{
    showCarDatabase(false);
    int n;
    cout << "Select a car BY REFERENCE NUMBER : "; cin >> n;
    rental New;
    New.rent = New.pickFromDatabase(n);
    cout << "SELECTED CAR : \n";
    cout << New.rent.nr << " " << New.rent.name << " " << New.rent.kmTotal << " " << New.rent.year << " ";
    if (New.rent.isRented == 1)
        cout << "RENTED, ";
    else
        cout << "NOT RENTED, ";
    if (New.rent.needsMaintenance == 1)
        cout << "NEEDS MAINTENANCE\n";
    else
        cout << "CAR IS OK\n";
    if (New.rent.isRented == 1)
    {
        cout << "Please enter the kilometers made : "; cin >> New.kmTraveled;
        New.rent.kmTotal += New.kmTraveled;
        cout << "The car will now be set to unrented\n";
        New.rent.isRented = 0;
        New.modifyDatabase(New.rent);
    }
    else
        cout << "CAR IS NOT RENTED\n";
}

void rentalRemoveFromDatabase()
{
    showCarDatabase(false);
    int n;
    cout << "Select a car BY REFERENCE NUMBER : "; cin >> n;
    rental New;
    New.rent = New.pickFromDatabase(n);
    cout << "SELECTED CAR : \n";
    cout << New.rent.nr << " " << New.rent.name << " " << New.rent.kmTotal << " " << New.rent.year << " ";
    if (New.rent.isRented == 1)
        cout << "RENTED, ";
    else
        cout << "NOT RENTED, ";
    if (New.rent.needsMaintenance == 1)
        cout << "NEEDS MAINTENANCE\n";
    else
        cout << "CAR IS OK\n";
    char op;
    cout << "DO YOU REALLY WANT TO DELETE THIS ENTRY? (Y/N) : "; cin >> op;
    if (op == 'Y' || op == 'y')
    {
        New.removeFromDatabase(New.rent);
        cout << "CAR DELETED\n";
    }
    else if (op == 'N' || op == 'n') cout << "ABORTING...\n";
}

void logic(bool& running)
{
    system("clear");
    cout << "CAR RENTAL PROGRAM\n";
    cout << "1. Check car database\n";
    cout << "2. Rent a car\n";
    cout << "3. UnRent a car\n";
    cout << "4. Add a car to the database\n";
    cout << "5. Remove a car from the database\n";
    cout << "0. EXIT\n";
    int op = -1;
    cin >> op;
    if (op >= 0 && op <= 5)
    {
        switch (op)
        {
        case 0:
            //Stops the program
            running = false;
            break;
        case 1:
            //Show the list of cars
            showCarDatabase(false);
            break;
        case 2:
            //Rent a car
            rentACar();
            break;
        case 3:
            //UnRent a rented car
            unrentACar();
            break;
        case 4:
            rentalAddToDatabase();
            break;
        case 5:
            rentalRemoveFromDatabase();
        }
    }
    system("pause");
}

int main()
{
    bool isRunning = true;
    while (isRunning)
    {
        logic(isRunning);
    }
    return 0;
}