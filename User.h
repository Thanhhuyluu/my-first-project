#ifndef USER_H
#define USER_H
#include<iostream>
#include<string>
#include "Ticket.h"
#include "Movie.h"
using namespace std;
class User {
private:
    string ID;
    string Name;
    string Role;
    string PhoneNum;
    string Password;
    string Status;
    string CreatedDate;
public:
    User(){

    }
    User(string Name, string Role, string PhoneNum, string Password, string Status, string CreatedDate) {
        this->ID = "";
        this->Name = Name;
        this->Role = Role;
        this->PhoneNum = PhoneNum;
        this->Password = Password;
        this->Status = Status;
        this->CreatedDate = CreatedDate;
    }
    User(string  ID,string Name, string Role, string PhoneNum, string Password, string Status, string CreatedDate) {
        this->ID = ID;
        this->Name = Name;
        this->Role = Role;
        this->PhoneNum = PhoneNum;
        this->Password = Password;
        this->Status = Status;
        this->CreatedDate = CreatedDate;
    }

    string getID() const {
        return ID;
    }
    string getName()const {
        return Name;
    }
    string getRole()const {
        return Role;
    }
    string getPhoneNum()const {
        return PhoneNum;
    }
    string  getPassword()const{
        return Password;
    }
    string  getStatus()const {
        return Status;
    }
    string  getCreatedDate() const{
        return CreatedDate;
    }



    void setID(string id) {
        ID = id;
    }
    void setName(string name) {
        Name = name;
    }
    void setRole(string role) {
        Role = role;
    }
    void setPhoneNum(string phoneNum) {
        PhoneNum = phoneNum;
    }
    void setPassword(string password){
        Password = password;
    }
    void setStatus(string status) {
        Status = status;
    }
    void setCreatedDate(string createdDate) {
        CreatedDate = createdDate;
    }
    const User &operator =(const User &u);
    bool operator == (const User &u);
    friend class UserManager;
    virtual void BookTicket(TicketManager &ticketManager, const Ticket &ticket) {

    }
    virtual void editInfo(const User& user) {
        (*this )= user;
    }
    void BookTicket(){

    }
};
class Customer:public User {
public:
    Customer( string Name, string PhoneNum, string Password, string CreatedDate):User(Name,"Customer",PhoneNum,Password,"Active", CreatedDate){}
    void BookTicket( TicketManager &ticketManager, const Ticket &ticket) ;
};
class UserManager;
class Admin:public User {
public:
    Admin( string Name, string PhoneNum, string Password, string CreatedDate):User(Name,"Admin",PhoneNum,Password,"Active", CreatedDate){}
    void editMovie( Movie &movie,const  Movie &newEdit);
    void addMovie( MovieManager &movieManager, const Movie& movie);
    void removeMovie(MovieManager &movieManager, const Movie& movie);
    void removeShow(ShowManager &showManager, const Show &show, TicketManager &ticketManager);
    void editShow(Show &show, const Show &newShow);
    void addShow(ShowManager& showManager, const Show& show);
    void BookTicket(string customerID, TicketManager &ticketManager, Ticket &ticket);
    void removeUser(string userID, UserManager & userManager, TicketManager &ticketManager);
    virtual void editInfo(const User& newChange, User &u);
};






class UserNode {
public:
    User user;
    UserNode* next;
    UserNode(const User& user) : user(user), next(nullptr) {}

    string operator [](const string& attributeName) {
        if (attributeName == "ID")
            return user.getID();
        else if (attributeName == "Name")
            return user.getName();
        else if (attributeName == "Role")
            return user.getRole();
        else if (attributeName == "PhoneNum")
            return user.getPhoneNum();
        else if (attributeName == "Password")
            return user.getPassword();
        else if (attributeName == "Status")
            return user.getStatus();
        else if (attributeName == "CreatedDate")
            return user.getCreatedDate();
    }
};
class UserManager {
private:
    UserNode* head;
    int Next_Id ;
    int Load_Next_Id();
    void Save_Next_Id();

public:
    UserManager(): head(nullptr) {
        Next_Id = Load_Next_Id();
    }
    ~UserManager();
    string Generate_Id() {
        return to_string(Next_Id++);
    }
    void addUser(const User& user);
    void addUserFromFile(const User& user);
    int getSize();
    void removeUser(const string& userID);
    void Save_Next_Id(int id);
    void Load_Users();
    void Update_Users();
    int getCurrentID();
    int getQuantityOfDay(string date);
    friend class App;
};



#endif // USER_H
