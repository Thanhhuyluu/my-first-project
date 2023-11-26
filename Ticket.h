#ifndef TICKET_H
#define TICKET_H

#include<iostream>
#include<string>
#include "Show.h"

using namespace std;
class Ticket {
private:
    string TicketID;
    string TicketPrice;
    string Hall;
    string ShowID;
    string TicketType;
    string CreatedDate;
    string SeatRow;
    string SeatCol;
    string CustomerID;
public:
    Ticket(){

    }

    Ticket(string TicketPrice, string Hall, string ShowID, string TicketType, string CreatedDate, string SeatRow, string SeatCol,string CustomerID) {
        this->TicketID = "";
        this->TicketPrice = TicketPrice;
        this->Hall = Hall;
        this->ShowID = ShowID;
        this->TicketType = TicketType;
        this->CreatedDate = CreatedDate;
        this->SeatRow = SeatRow;
        this->SeatCol = SeatCol;
        this->CustomerID = CustomerID;
    }
    Ticket(string TicketID,string TicketPrice, string Hall, string ShowID, string TicketType, string CreatedDate,string SeatRow, string SeatCol, string CustomerID) {
        this->TicketID = TicketID;
        this->TicketPrice = TicketPrice;
        this->Hall = Hall;
        this->ShowID = ShowID;
        this->TicketType = TicketType;
        this->CreatedDate = CreatedDate;
        this->SeatRow = SeatRow;
        this->SeatCol = SeatCol;
        this->CustomerID = CustomerID;
    }
    void editInfo(const Ticket& ticket) {
        (*this )= ticket;
    }
    string getTicketID() const{
        return TicketID;
    }
    string getTicketPrice()const {
        return TicketPrice;
    }
    string getHall() const{
        return Hall;
    }
    string getShowID()const {
        return ShowID;
    }
    string  getTicketType()const{
        return TicketType;
    }
    string  getCreatedDate()const {
        return CreatedDate;
    }
    string getSeatRow()const {
        return SeatRow;
    }
    string getSeatCol()const{
        return SeatCol;
    }

    string getCustomerID()const{
        return CustomerID;
    }

    void setTicketID(string ticketID) {
        TicketID = ticketID;
    }
    void setTicketPrice(string ticketPrice) {
        TicketPrice = ticketPrice;
    }
    void setHall(string hall) {
        Hall = hall;
    }
    void setShowID(string showID) {
        ShowID = showID;
    }
    void  setTicketType(string ticketType){
        TicketType = ticketType;
    }
    void  setCreatedDate(string createdDate) {
        CreatedDate = createdDate;
    }
    void setSeatRow(string seatRow) {
        SeatRow = seatRow;
    }
    void setSeatCol(string seatCol){
        SeatCol = seatCol;
    }
    void setCustomerID(string customerID){
        CustomerID = customerID;
    }

    const Ticket &operator =(const Ticket &ticket);
    bool operator == (const Ticket &ticket);
    bool operator != (const Ticket &ticket);

};



class TicketNode {
public:
    Ticket ticket;
    TicketNode* next;
    TicketNode(const Ticket& ticket) : ticket(ticket), next(nullptr) {}

    string operator [](const string& attributeName) {
        if (attributeName == "TicketID")
            return ticket.getTicketID();
        else if (attributeName == "TicketPrice")
            return ticket.getTicketPrice();
        else if (attributeName == "Hall")
            return ticket.getHall();
        else if (attributeName == "ShowID")
            return ticket.getShowID();
        else if (attributeName == "TicketType")
            return ticket.getTicketType();
        else if (attributeName == "CreatedDate")
            return ticket.getCreatedDate();
        else if(attributeName == "SeatRow")
            return ticket.getSeatRow();
        else if(attributeName == "SeatCol")
            return ticket.getSeatCol();
        else if(attributeName == "CustomerID")
            return ticket.getCustomerID();
        return "";
    }

};
class TicketManager {
private:
    TicketNode* head;
    int Next_Id ;
    int Load_Next_Id();
    void Save_Next_Id();

public:
    TicketManager(): head(nullptr) {
        Next_Id = Load_Next_Id();
    }
    ~TicketManager();
    string Generate_Id() {
        return to_string(Next_Id++);
    }
    void addTicket(const Ticket& ticket);
    void addTicketFromFile(const Ticket& ticket);
    int getSize();
    int getTodayTickets();
    void removeTicket(const Ticket &ticket);
    void Save_Next_Id(int id);
    void Load_Tickets();
    void Update_Tickets();
    int getQuantityOfDay(string date);
    void removeTicketByShowID(string showID);
    void removeTicketByCustomerID(string customerID);
    friend class App;
};





#endif // TICKET_H
