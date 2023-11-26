#include"User.h"
#include<iostream>
#include<fstream>
#include<QDebug>
#include<sstream>
#include<QDate>


const User &User::operator =(const User &u) {
    if(this != &u) {
        ID = u.ID;
        Name = u.Name;
        Role = u.Role;
        PhoneNum = u.PhoneNum;
        Password = u.Password;
        Status = u.Status;
    }
    return *this;
}
bool User::operator == (const User &u) {
    return (Name == u.Name) && (Role == u.Role) && (Password == u.Password) && (PhoneNum == u.PhoneNum);
}

void Customer::BookTicket( TicketManager &ticketManager, const Ticket &ticket) {
    ticketManager.addTicket(ticket);
}

void Admin::editMovie( Movie &movie,const Movie &newEdit){
    movie.editInfo(newEdit);
}

void Admin::addMovie(MovieManager &movieManager, const Movie &movie) {
    movieManager.addMovie(movie);
}

void Admin::removeMovie(MovieManager &movieManager, const Movie & movie){
    movieManager.removeMovie(movie);
}

void Admin::removeShow(ShowManager &showManager, const Show &show, TicketManager & ticketManager){
    ticketManager.removeTicketByShowID(show.getShowID());

    showManager.removeShow(show.getShowID());
}
void Admin::editShow( Show &show,const Show &newShow){
    show.editInfo(newShow);
}


void Admin::addShow(ShowManager& showManager, const Show& show){
    showManager.addShow(show);
}

void Admin::BookTicket(string customerID, TicketManager &ticketManager, Ticket &ticket){
    ticket.setCustomerID(customerID);
    ticketManager.addTicket(ticket);
}

void Admin::removeUser(string userID, UserManager & userManager, TicketManager &ticketManager){
    ticketManager.removeTicketByCustomerID(userID);
    userManager.removeUser(userID);
}


void Admin::editInfo(const User &newChange, User &u){
    u = newChange;
}

int UserManager::Load_Next_Id(){
    int id;
    ifstream Next_Id_File("C:\\Users\\ADMIN\\Desktop\\PBL2\\data\\Next_User_Id.txt");
    if(Next_Id_File.is_open()){
        Next_Id_File >> id;
        Next_Id_File.close();
    } else {
        id = 1;
    }
    return id;
}
void UserManager::Save_Next_Id(int id) {
    ofstream Next_Id_File("C:\\Users\\ADMIN\\Desktop\\PBL2\\data\\Next_User_Id.txt");
    if(Next_Id_File.is_open()) {
        Next_Id_File << id;
        Next_Id_File.close();
    }
}
void UserManager::addUserFromFile(const User& user) {
    UserNode* newNode = new UserNode(user);
    if (!head) {
        head = newNode;
        return;
    }

    UserNode* current = head;
    while (current->next) {
        current = current->next;
    }
    current->next = newNode;
}
void UserManager::addUser(const User& user) {
    UserNode* newNode = new UserNode(user);
    newNode->user.ID = UserManager::Generate_Id();
    QDate currentDate = QDate::currentDate();
    QString dateString = currentDate.toString("yyyy-dd-MM");
    newNode->user.CreatedDate = dateString.toStdString();
    if (!head) {
        head = newNode;
        return;
    }

    UserNode* current = head;
    while (current->next) {
        current = current->next;
    }
    current->next = newNode;
}
int UserManager::getSize(){
    UserNode *temp = head;
    int count = 0;
    while(temp){
        count++;
        temp = temp->next;
    }
    return count;
}
int UserManager::getCurrentID(){
    return Next_Id - 1;
}
void UserManager::Load_Users() {
    ifstream User_File("C:\\Users\\ADMIN\\Desktop\\PBL2\\data\\person.txt");
    if(User_File.is_open()) {
        string line;

        while(getline(User_File, line)) {
            User user;
            stringstream ss(line);
            getline(ss,user.ID, ',');
            getline(ss,user.Role, ',');
            getline(ss,user.Name, ',');
            getline(ss,user.Password, ',');
            getline(ss,user.PhoneNum, ',');
            getline(ss,user.Status, ',');
            getline(ss,user.CreatedDate, ',');
            addUserFromFile(user);
        }
        User_File.close();
    } else {
        qDebug("failed to open file");
    }
}
void UserManager::Update_Users() {
    ofstream User_File("C:\\Users\\ADMIN\\Desktop\\PBL2\\data\\person.txt");
    if(!User_File.is_open()) {
        qDebug("Failed to write file");
        return;
    }else {

        UserNode* current = head;
        while (current) {
            User_File  << (*current)["ID"]<< "," << (*current)["Role"] << "," << (*current)["Name"] << "," << (*current)["Password"] << "," << (*current)["PhoneNum"] << "," << (*current)["Status"] << "," << (*current)["CreatedDate"] << "\n";
            current = current->next;
        }
        User_File.close();
    }
}
void UserManager::removeUser(const string& userID) {
    if (!head) {
        std::cout << "The list is empty. Cannot remove a user.\n";
        return;
    }
    if (head->user.ID == userID) {
        UserNode* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    UserNode* prev = nullptr;
    UserNode* current = head;

    while (current && current->user.ID != userID) {
        prev = current;
        current = current->next;
    }

    if (!current) {
        std::cout << "User with ID " << userID << " not found in the list.\n";
        return;
    }
    prev->next = current->next;
    delete current;
}

int UserManager::getQuantityOfDay(string date){
    UserNode *temp = head;
    int count = 0;
    while(temp){
        if((*temp)["CreatedDate"] == date){
            count ++;
        }
        temp = temp->next;
    }
    return count;
}

UserManager::~UserManager() {
    UserNode* current = head;
    while (current) {
        UserNode* temp = current;
        current = current->next;
        delete temp;
    }
    Save_Next_Id(Next_Id);
}


