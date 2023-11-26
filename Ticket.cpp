
#include"Ticket.h"
#include<iostream>
#include<fstream>
#include<QDebug>
#include<sstream>
#include<QDate>


const Ticket &Ticket::operator =(const Ticket &ticket) {
    if(this != &ticket) {
        TicketID = ticket.TicketID;
        TicketPrice = ticket.TicketPrice;
        Hall = ticket.Hall;
        ShowID = ticket.ShowID;
        TicketType = ticket.TicketType;
        CreatedDate = ticket.CreatedDate;
        SeatRow = ticket.SeatRow;
        SeatCol = ticket.SeatCol;
        CustomerID = ticket.CustomerID;
    }
    return *this;
}
bool Ticket::operator == (const Ticket &ticket) {
    return (TicketPrice == ticket.getTicketPrice()) && (Hall == ticket.getHall()) && (ShowID == ticket.getShowID()) && (TicketType == ticket.getTicketType()) && (SeatRow == ticket.getSeatRow()) && (SeatCol == ticket.getSeatCol()) && (CustomerID == ticket.getCustomerID());
}

bool Ticket::operator != (const Ticket &ticket) {
    if((TicketPrice != ticket.getTicketPrice()) ||(Hall != ticket.getHall()) || (ShowID != ticket.getShowID())|| (TicketType != ticket.getTicketType()) || (SeatRow != ticket.getSeatRow()) || (SeatCol != ticket.getSeatCol()) || (CustomerID != ticket.getCustomerID())) return true;

    return false;
}
int TicketManager::Load_Next_Id(){
    int id;
    ifstream Next_Id_File("C:\\Users\\ADMIN\\Desktop\\PBL2\\data\\Next_Ticket_Id.txt");
    if(Next_Id_File.is_open()){
        Next_Id_File >> id;
        Next_Id_File.close();
    } else {
        id = 1;

    }
    return id;

}
void TicketManager::Save_Next_Id(int id) {
//    ofstream Next_Id_File("C:\\Users\\ADMIN\\Desktop\\PBL2\\data\\Next_Ticket_Id.txt");
//    if(Next_Id_File.is_open()) {
//        Next_Id_File << id;
//        Next_Id_File.close();
//    }else {
//       std::cout  << "ID ticket has not opened";
//    }

    std::ofstream Next_Id_File("C:\\Users\\ADMIN\\Desktop\\PBL2\\data\\Next_Ticket_Id.txt"); // Mở tệp "ID.txt" để ghi đè
    if (!Next_Id_File.is_open()) {
       std::cerr << "can't open" << std::endl;
        return;
    }

    Next_Id_File << id; // Ghi ID vào tệp

    Next_Id_File.close(); // Đóng tệp sau khi ghi xong
}
void TicketManager::addTicketFromFile(const Ticket& ticket) {
    TicketNode* newNode = new TicketNode(ticket);

    if (!head) {
        head = newNode;
        return;
    }

    TicketNode* current = head;
    while (current->next) {
        current = current->next;
    }
    current->next = newNode;
}

void TicketManager::addTicket(const Ticket& ticket) {
    TicketNode* newNode = new TicketNode(ticket);
    newNode->ticket.setTicketID(TicketManager::Generate_Id());
    QDate currentDate = QDate::currentDate();
    QString dateString = currentDate.toString("yyyy-dd-MM");
    newNode->ticket.setCreatedDate( dateString.toStdString());
    if (!head) {
        head = newNode;
        return;
    }

    TicketNode* current = head;
    while (current->next) {
        current = current->next;
    }
    current->next = newNode;
}

int TicketManager::getSize() {
    int count = 0;
    TicketNode *temp = head;
    while(temp != NULL) {
        ++count;
        temp = temp->next;
    }
    return count;
}

int TicketManager::getTodayTickets(){
    QDate currentDate = QDate::currentDate();
    string dateString = currentDate.toString("yyyy-dd-MM").toStdString();
    int count = 0;
    TicketNode *temp = head;
    while(temp){
        if((*temp)["CreatedDate"] == dateString){
            count++;
        }
        temp = temp->next;
    }
    return count;
}

void TicketManager::Load_Tickets() {
    ifstream Ticket_File("C:\\Users\\ADMIN\\Desktop\\PBL2\\data\\Ticket.txt");
    if(Ticket_File.is_open()) {
        string line;
        while(getline(Ticket_File, line)) {

            string TicketID,TicketPrice,Hall, ShowID,TicketType,CreatedDate,SeatRow,SeatCol, CustomerID;
            stringstream ss(line);
            getline(ss,TicketID, ',');
            getline(ss,TicketPrice, ',');
            getline(ss,Hall, ',');
            getline(ss,ShowID, ',');
            getline(ss,TicketType, ',');
            getline(ss,CreatedDate, ',');
            getline(ss,SeatRow, ',');
            getline(ss,SeatCol, ',');
            getline(ss,CustomerID,',');
            Ticket ticket(TicketID,TicketPrice,Hall,ShowID,TicketType,CreatedDate,SeatRow, SeatCol, CustomerID);
            addTicketFromFile(ticket);
        }
        Ticket_File.close();
    } else {
        qDebug("failed to open file");
    }
}

void TicketManager::Update_Tickets() {
    ofstream Ticket_File("C:\\Users\\ADMIN\\Desktop\\PBL2\\data\\Ticket.txt");
    if(!Ticket_File.is_open()) {
        qDebug("Failed to write file");
        return;
    }else {

        TicketNode* current = head;
        while (current) {
            Ticket_File  << (*current)["TicketID"]<< "," << (*current)["TicketPrice"] << "," << (*current)["Hall"] << "," << (*current)["ShowID"] << "," << (*current)["TicketType"] <<"," << (*current)["CreatedDate"]<<"," << (*current)["SeatRow"]<<"," << (*current)["SeatCol"] << "," << (*current)["CustomerID"] <<"\n";
            current = current->next;
        }
        Ticket_File.close();
    }
}
void TicketManager::removeTicket(const Ticket& ticket) {
    if (!head) {
        std::cout << "The list is empty. Cannot remove a ticket.\n";
        return;
    }
    if (head->ticket.getTicketID() == ticket.getTicketID() && head->ticket == ticket) {
        TicketNode* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    TicketNode* prev = nullptr;
    TicketNode* current = head;

    while (current && current->ticket.getTicketID() != ticket.getTicketID() && current->ticket != ticket) {
        prev = current;
        current = current->next;
    }

    if (!current) {
        std::cout << "Ticket with ID " << ticket.getTicketID() << " not found in the list.\n";
        return;
    }
    prev->next = current->next;
    delete current;

}

void TicketManager::removeTicketByShowID(string showID){
    TicketNode *temp = head;
    while(temp){
        if((*temp)["ShowID"] == showID){
            removeTicket(temp->ticket);
        }
        temp = temp->next;
    }
}


void TicketManager::removeTicketByCustomerID(string customerID){
    TicketNode *temp = head;
    while(temp){
        if((*temp)["CustomerID"] == customerID){
            removeTicket(temp->ticket);
        }
        temp = temp->next;
    }
}
int TicketManager::getQuantityOfDay(string date){
    TicketNode *temp = head;
    int count = 0;
    while(temp){
        if((*temp)["CreatedDate"] == date){
            count ++;
        }
        temp = temp->next;
    }
    return count;
}


TicketManager::~TicketManager() {
    TicketNode* current = head;
    while (current) {
        TicketNode* temp = current;
        current = current->next;
        delete temp;
    }
    Save_Next_Id(Next_Id);
}
