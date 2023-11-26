#ifndef BOOKING_H
#define BOOKING_H


#include<iostream>
#include<string>
using namespace std;
class Booking {
private:
    string BookingID;
    string BookedDate;
    string Status;
    string ShowID;
    string CustomerID;
    string TicketID;
public:
    Booking(){

    }
    Booking(string BookedDate, string Status, string ShowID, string CustomerID, string TicketID) {
        this->BookingID = "";
        this->BookedDate = BookedDate;
        this->Status = Status;
        this->ShowID = ShowID;
        this->CustomerID = CustomerID;
        this->TicketID = TicketID;
    }
    Booking(string BookingID,string BookedDate, string Status, string ShowID, string CustomerID, string TicketID) {
        this->BookingID = BookingID;
        this->BookedDate = BookedDate;
        this->Status = Status;
        this->ShowID = ShowID;
        this->CustomerID = CustomerID;
        this->TicketID = TicketID;
    }
    void editInfo(const Booking& booking) {
        (*this )= booking;
    }
    string getBookingID() {
        return BookingID;
    }
    string getBookedDate() {
        return BookedDate;
    }
    string getStatus() {
        return Status;
    }
    string getShowID() {
        return ShowID;
    }
    string  getCustomerID(){
        return CustomerID;
    }
    string  getTicketID() {
        return TicketID;
    }


    void setBookingID(string bookingID) {
        BookingID = bookingID;
    }
    void setBookedDate(string bookedDate) {
        BookedDate = bookedDate;
    }
    void setStatus(string status) {
        Status = status;
    }
    void setShowID(string showID) {
        ShowID = showID;
    }
    void  setCustomerID(string customerID){
        CustomerID = customerID;
    }
    void  setTicketID(string ticketID) {
        TicketID = ticketID;
    }

    const Booking &operator =(const Booking &booking);
    bool operator == (const Booking &booking);


};



class BookingNode {
public:
    Booking booking;
    BookingNode* next;
    BookingNode(const Booking& booking) : booking(booking), next(nullptr) {}
    string operator [](const string& attributeName) {
        if (attributeName == "BookingID")
            return booking.getBookingID();
        else if (attributeName == "BookedDate")
            return booking.getBookedDate();
        else if (attributeName == "Status")
            return booking.getStatus();
        else if (attributeName == "ShowID")
            return booking.getShowID();
        else if (attributeName == "CustomerID")
            return booking.getCustomerID();
        else if (attributeName == "TicketID")
            return booking.getTicketID();
    }
};
class BookingManager {
private:
    BookingNode* head;
    int Next_Id ;
    int Load_Next_Id();
    void Save_Next_Id();

public:
    BookingManager(): head(nullptr) {
        Next_Id = Load_Next_Id();
    }
    ~BookingManager();
    string Generate_Id() {
        return to_string(Next_Id++);
    }
    void addBooking(const Booking& booking);
    void addBookingFromFile(const Booking& booking);
    int getSize();
    void removeBooking(const string& bookingID);
    void Save_Next_Id(int id);
    void Load_Bookings();
    void Update_Bookings();
};
#endif // BOOKING_H
