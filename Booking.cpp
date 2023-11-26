#include"Booking.h"
#include<iostream>
#include<fstream>
#include<QDebug>
#include<sstream>
#include<QDate>


const Booking &Booking::operator =(const Booking &booking) {
    if(this != &booking) {
        BookingID = booking.BookingID;
        BookedDate = booking.BookedDate;
        Status = booking.Status;
        ShowID = booking.ShowID;
        CustomerID = booking.CustomerID;
        TicketID = booking.TicketID;
    }
    return *this;
}
bool Booking::operator == (const Booking &booking) {
    return (BookedDate == booking.BookedDate) && (Status == booking.Status) && (ShowID == booking.ShowID) && (CustomerID == booking.CustomerID) && (TicketID == booking.TicketID);
}
int BookingManager::Load_Next_Id(){
    int id;
    ifstream Next_Id_File("C:\\Users\\ADMIN\\Desktop\\PBL2\\data\\Next_Booking_Id.txt");
    if(Next_Id_File.is_open()){
        Next_Id_File >> id;
        Next_Id_File.close();
    } else {
        id = 1;

    }
    return id;

}
void BookingManager::Save_Next_Id(int id) {
    ofstream Next_Id_File("C:\\Users\\ADMIN\\Desktop\\PBL2\\data\\Next_Booking_Id.txt");
    if(Next_Id_File.is_open()) {
        Next_Id_File << id;
        Next_Id_File.close();
    }
}
void BookingManager::addBookingFromFile(const Booking& booking) {
    BookingNode* newNode = new BookingNode(booking);
    newNode->booking.setBookingID( BookingManager::Generate_Id());
    if (!head) {
        head = newNode;
        return;
    }

    BookingNode* current = head;
    while (current->next) {
        current = current->next;
    }
    current->next = newNode;
}
void BookingManager::addBooking(const Booking& booking) {
    BookingNode* newNode = new BookingNode(booking);
    newNode->booking.setBookingID(BookingManager::Generate_Id());
    QDate currentDate = QDate::currentDate();
    QString dateString = currentDate.toString("yyyy-dd-MM");
    newNode->booking.setBookedDate( dateString.toStdString());
    if (!head) {
        head = newNode;
        return;
    }

    BookingNode* current = head;
    while (current->next) {
        current = current->next;
    }
    current->next = newNode;
}
int BookingManager::getSize() {
    int count = 0;
    while(head != NULL) {
        ++count;
        head = head->next;
    }
    return count;
}

void BookingManager::Load_Bookings() {
    ifstream Booking_File("C:\\Users\\ADMIN\\Desktop\\PBL2\\data\\Booking.txt");
    if(Booking_File.is_open()) {
        string line;
        while(getline(Booking_File, line)) {
            string BookingID,BookedDate,Status, ShowID,CustomerID,TicketID;
            stringstream ss(line);
            getline(ss,BookingID, ',');
            getline(ss,BookedDate, ',');
            getline(ss,Status, ',');
            getline(ss,ShowID, ',');
            getline(ss,CustomerID, ',');
            getline(ss,TicketID, ',');
            Booking booking(BookingID,BookedDate,Status,ShowID,CustomerID,TicketID);
            addBookingFromFile(booking);
        }
        Booking_File.close();
    } else {
        qDebug("failed to open file");
    }
}
void BookingManager::Update_Bookings() {
    ofstream Booking_File("C:\\Users\\ADMIN\\Desktop\\PBL2\\data\\Booking.txt");
    if(!Booking_File.is_open()) {
        qDebug("Failed to write file");
        return;
    }else {

        BookingNode* current = head;
        while (current) {
            Booking_File  << (*current)["BookingID"]<< "," << (*current)["BookedDate"] << "," << (*current)["Status"] << "," << (*current)["ShowID"] << "," << (*current)["CustomerID"] <<"," << (*current)["TicketID"] << "\n";
            current = current->next;
        }
        Booking_File.close();
    }
}
void BookingManager::removeBooking(const string& bookingID) {
    if (!head) {
        std::cout << "The list is empty. Cannot remove a booking.\n";
        return;
    }
    if (head->booking.getBookingID() == bookingID) {
        BookingNode* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    BookingNode* prev = nullptr;
    BookingNode* current = head;

    while (current && current->booking.getBookingID() != bookingID) {
        prev = current;
        current = current->next;
    }

    if (!current) {
        std::cout << "Booking with ID " << bookingID << " not found in the list.\n";
        return;
    }
    prev->next = current->next;
    delete current;
}
BookingManager::~BookingManager() {
    BookingNode* current = head;
    while (current) {
        BookingNode* temp = current;
        current = current->next;
        delete temp;
    }
}
