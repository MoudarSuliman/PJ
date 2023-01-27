#include <iostream>
#include "ride1.h"
#include<sstream>
#include<limits>
using namespace std;

Ridesharing::Ridesharing(){}

Ridesharing::~Ridesharing(){}

Payment::Payment(){
    fund = 0;
}

void Ridesharing::Booking(User& acc){
    int input =0;
    int choice = 0;
    while (true){
        cout << "Would you like to book a ride?" << endl;
        cout<< "1.Book a ride"<< endl;
        cout<< "2.Wallet"<<endl;
        cout<< "3.Show awaiting trips" << endl;
        cout<< "4.logout"<< endl;
        cout << "5.Exit" << endl;
        cin >> input;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if(input == 1){

            cout << "Would you like to book for later on or Now?" << endl;
            cout << "1.NOW" << endl;
            cout << "2.Later" << endl;
            cin >> choice;
            if(choice == 1){
                int price = 36;
                int pay = 0;
                int inc=0;
                string pickup,dropoff;
                cout << "Please enter your pickup location" << endl;
                cin >> pickup;
                cout << "Please enter your destination" << endl;
                cin >> dropoff;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Looking for a car around you please wait...\n" << endl;
                addReservationNow();
                CarSearch();
                cout << "Your ride will arrive in 5 minutes" << endl;
                cout << "You have reached your destination "<< endl;
                
                while(true){
                    cout << "Your trip fee cost  " << price << " pln"<< endl;
                    cout << "1.Pay" << endl;
                    cout << "2.Increase balance "<< endl;
                    cin >> pay;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    if (pay == 1)
                    {
                        bool check = checkAmount(price,acc);
                        if (check == true)
                        {
                            cout <<"You don't have sufficient amount please increase your balance " << endl;
                        }else{
                            removeAmount(price,acc);
                            cout << "Thanks for your ride :)" << endl;
                            Booking(acc);
                        }


                    }else if(pay == 2){
                        cout << "You have " << Amount(acc) << " pln" << endl;
                        cout << "How much would you like to add? " << endl;
                        cin >> inc;
                        addAmount(inc,acc);
                    }else
                    {
                        cout << "Invalid service, try again\n" << endl;
                    }

                }
            }
            else if(choice == 2){
                string pickup,dropoff;
                int hour = 0, min = 0;
                cout << "Please enter your pickup location" << endl;
                cin >> pickup;
                cout << "Please enter your destination" << endl;
                cin >> dropoff;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "At which hour would you like your car[00-24]" << endl;
                cin >> hour;
                while(hour > 24 || hour < 0 || !cin){
                    cout << "Please enter a valid hour" << endl;
                    cin >> hour;
                }
                cout << "At which minute would you like your car[00-59]" << endl;
                cin >> min;
                while(min > 59 || min < 0 || !cin){
                    cout << "Please enter a valid minute" << endl;
                    cin >> min;
                }
                addReservationLater(pickup,dropoff,hour,min,acc);
                cout << "Your ride was saved to 'awaiting trips'\n " << endl;
                Booking(acc);
            }
        }
        else if(input == 2) {
            int add = 0;
            int pick = 0;
            while (true) {
                cout << "Your wallet contains: " << Amount(acc) << " pln" << endl;
            cout << "1.add funds" << endl;
            cout << "2.Go back" << endl;
            cin >> pick;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (pick == 1) {
                    Payment pay;
                    cout << "How much money would you like to add? (Between 0 and 100 please) " << endl;
                    cout << "Enter here: " << endl;
                    while(true){
                    cin >> add;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    if(add > 0 && add < 100){
                    pay.addFund(add);
                    addAmount(pay.getFund(), acc);
                    break;
                    }
                    else{
                        cout <<"Value can't be added" << endl;
                    }
                }
                }

            else if (pick == 2) {Booking(acc);}
            else { cout << "Invalid service, try again\n" << endl; }
        }

        }
        else if(input == 3){
            showReservation(acc);
            Booking(acc);
        }
        else if(input == 4){
           mainscreen(acc);
        }
        else if(input == 5){
            exit(0);
        }
        else{
            cout<<"Invalid service, try again"<< endl;
        }

    }
}

void Ridesharing::mainscreen(User& user){
    string username,password;
    string name,pass;
    int n=0;

    while (true){
        cout<< "======|Welcome to Ridesharing system|======\n"<<endl;
        cout<< "Pick your service(use numbers)"<<endl;
        cout<< "1.Login"<< endl;
        cout<< "2.Register"<<endl;
        cout<< "3.Exit"<<endl;

        cin >> n;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if(n == 1){
            cout<<"\n\t==|Login Page|==\n" << endl;
            cout<<"Please enter your username"<< endl;
            cin>>username;
            user.setUsername(username);
            cout<< "Please enter your password"<<endl;
            cin >>password;
            user.setPassword(password);
            bool status = checkLogin(user);
            if (!status)
            {
                cout << "No account can be found, please register or use a valid account\n" << endl;
            }else{
                cout << "Welcome " << user.getUsername() << endl;
                cout<<endl;
                Booking(user);
            }
        }

        else if(n == 2)
        {

            cout << "Registration page" << endl;
            cout << "Enter a username" << endl;
            cin >> name;
            cout << "Enter a password" << endl;
            cin >> pass;
            bool taken = checkUser(name);
            if (!taken)
            {
                addUser(name,pass);
                cout << "Thank you for Registring" << endl;
            }else
            {
                cout << "Username already taken, pick another one \n" << endl;
            }
        }
        else if(n == 3){
            exit(0);
        }
        else{
            cout << "Invalid service, try again" << endl;
        }
    }
}

void Ridesharing::printUser(){
    for (unsigned int i = 0; i < profile.size(); i++)
    {
        cout << profile[i].getUsername() << " " << profile[i].getPassword() << endl;
    }
    
    
}

void Ridesharing::printCars(){
    for (unsigned int i = 0; i < cars.size(); i++)
    {
        cout << cars[i].getType() << " " <<cars[i].getModel() << " " << cars[i].getColor() << endl;
    }
    
}

void Ridesharing::printReservation(){
    for (unsigned int i = 0; i < trip_details.size(); i++)
    {
        cout << trip_details[i].getPickup() <<" "<< trip_details[i].getDropoff() <<" "<< trip_details[i].getHour() <<" "<< trip_details[i].getMin() << endl;
    }
    
}

void Ridesharing::sizeTrips(){
    cout << trip_details.size() <<endl;
}

void Ridesharing::addUser(const string& username, const string& password){
    User temp(username, password);
    profile.push_back(temp);
}

void Ridesharing::sizeProfile(){
    cout << profile.size() << endl;
}

void Ridesharing::sizeCar(){
    cout << cars.size() << endl;
}

bool Ridesharing::checkLogin(User& account){
    for(unsigned int i= 0; i < profile.size(); i++){ // search through the vector
    if(profile[i].getUsername() == account.getUsername() && profile[i].getPassword() == account.getPassword()){
        account.setId(i);
        return true;
    }
    }
    return false;
}

bool Ridesharing::checkUser(const string& username){
    for(unsigned int i= 0; i < profile.size(); i++){ // search through the vector
    if(profile[i].getUsername() == username){
        return true;
    }
}
return false;
}

void Ridesharing::saveCars(){
    addCar("Ford", "2016", "Grey");
    addCar("Kia", "2019", "Black");
    addCar("Honda", "2014", "White");
    addCar("Chevrolet", "2020", "Silver");
    addCar("BMW", "2018", "Blue");
}

void Ridesharing::addReservationLater(const string& pickup,const string& dropoff, int hour,int min,User& get){
    string name;
    name = get.getUsername();
    Reservation temp(name,pickup,dropoff,hour, min);
    trip_details.push_back(temp);

        //cout << "Username: "      << profile[get.getId()].getUsername() <<endl;
        //cout <<"Pickup location: "<< pickup <<endl;
        //cout << "Dropoff location: " <<dropoff <<endl;
        //cout <<"Starting time: "  << hour <<":"<<  min <<endl;
}

void Ridesharing::addReservationNow(){
    cars.clear();
    saveCars();
}

void Ridesharing::CarSearch(){
    int small = 1000000;
    int count = 0; 
    for (unsigned int i = 0; i < cars.size(); i++)
    {
        if (cars[i].getDistance() < small)
        {
            small = cars[i].getDistance();
            count = i;
        }
        
    }
    cout << "Your car is:" << endl;
    cout << "Driver name: " << cars[count].getDriver() << endl;
    cout << "Type: " << cars[count].getType() <<endl;
    cout << "Plate: " << cars[count].getPlate() << endl;
    cout << "Model: " << cars[count].getModel() << endl;
    cout << "Color: " << cars[count].getColor() <<"\n"<< endl;
}

void Ridesharing::showReservation(User& index){
bool no_ride = 0;
string choice;
    cout << "Your rides:" << endl;
    for (unsigned int i = 0; i < trip_details.size(); i++)
    {
        if(profile[index.getId()].getUsername() == trip_details[i].getName()){ 
        cout << "Username: "      << profile[index.getId()].getUsername() <<endl;
        cout <<"Pickup location: "<< trip_details[i].getPickup() <<endl;
        cout << "Dropoff location: " <<trip_details[i].getDropoff() <<endl;
        cout <<"Starting time: "  << trip_details[i].getHour() <<":"<<  trip_details[i].getMin() <<"\n"<<endl;
        cout<<endl;
        no_ride = 1;
        }
    }
        if(no_ride == 0){
        cout << "You don't have any ride" << endl;
        cout << "Press ENTER to go back" << endl;
        getline(cin,choice);
        }
    while(no_ride == 0){
        if(choice.length() != 0){
            cout << "PRESS ENTER!!" << endl;
            getline(cin,choice);
        }else{
            break;
        }
        
    }
}

void User::decreaseBalance(int remove){
    if (remove < 0 )
    {
        cout << "Value can't be negative" << endl;
    }else
    {
        balance -= remove;    
    }
    
}

int Ridesharing::Amount(User& amount){
    return profile[amount.getId()].getBalance();
}

void Ridesharing::removeAmount(int remove,User& amount){
    profile[amount.getId()].decreaseBalance(remove);
}

void Ridesharing::addAmount(int add_to, User& amount){
    profile[amount.getId()].increaseBalance(add_to);
}

bool Ridesharing::checkAmount(int price,User& amount){
    if (profile[amount.getId()].getBalance() - price < 0)
    {
        return true;
    }else
    {
        return false;
    }
    
    
}

User::User(){
    username = "";
    password = "";
    id = 0;
    balance = 0;
}

string User::getPassword(){
    return password;
}

string User::getUsername(){
    return username;
}

void User::setUsername(const string& name){
    username = name;
}

void User::setPassword(const string& pass){
    password = pass;
}

int User::getId()const{
    return id;
}

void User::setId(int x){
    id = x;
}

User::User(string name, string pass)
{
    username = name;
    password = pass;
}

int User::getBalance()const
{
    return balance;
}

void User::increaseBalance(int add){
    if(add < 0){
        cout << "Value can't be negative" << endl;
    }else
    {
        balance += add;
    }
    
}

Car::Car(){
    type = "";
    plate = "";
    model = "";
    color = "";
    distance = 0;
}

int Car::getDistance()const{
    return distance;
}

string Car::getType(){
    return type;
}

string Car::getModel(){
    return model;
}

string Car::getColor(){
    return color;
}

string Car::getPlate(){
    return plate;
}

string Car::getDriver(){
    return driver;
}

void Ridesharing::addCar(const string& new_type, const string& new_model,const string& new_color){
    int index,num,speed,t_time,r,distance;
    string names[] = {"James bond", "Micheal Jackson", "Josh Wilson", "Tobi Carson", "Emma Charlotte", "Ibraham Lincolin", "Noah James", "Will Smith", "Thomas Jefferson"};
    string plate_num,plate_let,plate;
    string name;
    for (unsigned int i=0; i<2; i++)
    {    r = rand() % 26;   // generate a random number
          plate_let  += 'A' + r;       // Convert to a character from a-z

    }
    index = rand()% 6;
    name = names[index];
    num = rand()% 90000 + 10000;
    stringstream s;
    s << num;
    s >> plate_num;
    plate = plate_let + " " + plate_num;
    t_time = rand()% 10+1;
    speed = rand()% 100+1;
    distance = t_time * speed;
    Car temp(name,new_type,plate,new_model,new_color, distance);
    cars.push_back(temp);
}

Car::Car(string driver,string type, string plate, string model, string color,int dis){
    this->driver = driver;
    this->type = type;
    this->plate = plate;
    this->model = model;
    this->color = color;
    distance = dis;
}

Reservation::Reservation(){
    name = "";
    hour = 0;
    min = 0;
    pickup = "";// pickup location
    dropoff = "";// dropoff location
}

Reservation::Reservation(string n,string start, string end,int h, int m){
    name = n;
    pickup = start;
    dropoff = end;
    hour = h;
    min = m;
}

string Reservation::getName(){
    return name;
}

string Reservation::getPickup(){
    return pickup;
}

string Reservation::getDropoff(){
    return dropoff;
}

int Reservation::getHour()const{
    return hour;
}

int Reservation::getMin()const{
    return min;
}

int Payment::getFund()const{
    return fund;
}

void Payment::setFund(int new_funds){
    fund = new_funds;
}

void Payment::addFund(int add_funds){
    int fund = this->getFund();
    if(fund < 0){
        cout << "Value can't be negative " << endl;
    }else{
    fund += add_funds;
    setFund(fund);
    }
}

Payment::~Payment(){}

User::~User(){}

Reservation::~Reservation(){}

Car::~Car(){}