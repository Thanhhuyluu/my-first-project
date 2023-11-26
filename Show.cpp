#include"Show.h"
#include<iostream>
#include<fstream>
#include<QDebug>
#include<sstream>
#include<QDate>


const Show &Show::operator =(const Show &show) {
    if(this != &show) {
        ShowID = show.ShowID;
        MovieID = show.MovieID;
        StartTime = show.StartTime;
        EndTime = show.EndTime;
        ShowDate = show.ShowDate;
        CreatedDate = show.CreatedDate;
    }
    return *this;
}
bool Show::operator == (const Show &show) {
    if((MovieID == show.MovieID) && (StartTime == show.StartTime) && (EndTime == show.EndTime) && (ShowDate == show.ShowDate))
    return true ;
    else return false;
}
int ShowManager::Load_Next_Id(){
    int id;
    ifstream Next_Id_File("C:\\Users\\ADMIN\\Desktop\\PBL2\\data\\Next_Show_Id.txt");
    if(Next_Id_File.is_open()){
        Next_Id_File >> id;
        Next_Id_File.close();
    } else {
        id = 1;

    }
    return id;

}
void ShowManager::Save_Next_Id(int id) {
    ofstream Next_Id_File("C:\\Users\\ADMIN\\Desktop\\PBL2\\data\\Next_Show_Id.txt");
    if(Next_Id_File.is_open()) {
        Next_Id_File << id;
        Next_Id_File.close();
    }
}
void ShowManager::addShowFromFile(const Show& show) {
    ShowNode* newNode = new ShowNode(show);
    if (!head) {
        head = newNode;
        return;
    }

    ShowNode* current = head;
    while (current->next) {
        current = current->next;
    }
    current->next = newNode;
}
void ShowManager::addShow(const Show& show) {
    ShowNode* newNode = new ShowNode(show);
    newNode->show.setShowID(ShowManager::Generate_Id());
    QDate currentDate = QDate::currentDate();
    QString dateString = currentDate.toString("yyyy-dd-MM");
    newNode->show.setCreatedDate( dateString.toStdString());
    if (!head) {
        head = newNode;
        return;
    }

    ShowNode* current = head;
    while (current->next) {
        current = current->next;
    }
    current->next = newNode;
}
int ShowManager::getSize(){
    int count = 0;
    ShowNode *temp = head;
    while(temp){
        count++;
        temp = temp->next;
    }
    return count;
}

void ShowManager::Load_Shows() {
    ifstream Show_File("C:\\Users\\ADMIN\\Desktop\\PBL2\\data\\Show.txt");
    if(Show_File.is_open()) {
        string line;
        while(getline(Show_File, line)) {

            string ShowID,MovieID,StartTime, EndTime,ShowDate,CreatedDate;
            stringstream ss(line);
            getline(ss,ShowID, ',');
            getline(ss,MovieID, ',');
            getline(ss,StartTime, ',');
            getline(ss,EndTime, ',');
            getline(ss,ShowDate, ',');
            getline(ss,CreatedDate, ',');
            Show show(ShowID,MovieID,StartTime,EndTime,ShowDate,CreatedDate);
            addShowFromFile(show);
        }
        Show_File.close();
    } else {
        qDebug("failed to open file");
    }
}
void ShowManager::Update_Shows() {
    ofstream Show_File("C:\\Users\\ADMIN\\Desktop\\PBL2\\data\\Show.txt");
    if(!Show_File.is_open()) {
        qDebug("Failed to write file");
        return;
    }else {
        ShowNode* current = head;
        while (current) {
            Show_File  << (*current)["ShowID"]<< "," << (*current)["MovieID"] << "," << (*current)["StartTime"] << "," << (*current)["EndTime"] << "," << (*current)["ShowDate"] <<"," << (*current)["CreatedDate"] << "\n";
            current = current->next;
        }
        Show_File.close();
    }
}
void ShowManager::removeShow(const string& showID) {
    if (!head) {
        std::cout << "The list is empty. Cannot remove a show.\n";
        return;
    }
    if (head->show.getShowID() == showID) {
        ShowNode* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    ShowNode* prev = nullptr;
    ShowNode* current = head;

    while (current && current->show.getShowID() != showID) {
        prev = current;
        current = current->next;
    }

    if (!current) {
        std::cout << "Show with ID " << showID << " not found in the list.\n";
        return;
    }
    prev->next = current->next;
    delete current;
}
ShowManager::~ShowManager() {
    ShowNode* current = head;
    while (current) {
        ShowNode* temp = current;
        current = current->next;
        delete temp;
    }
    Save_Next_Id(Next_Id);
}
Show ShowManager::getShowByID(string ID) const{
    ShowNode *temp = head;
    while(temp){
        if(temp->show.getShowID() == ID) {
            return temp->show;
        }
        temp =temp->next;
    }
}
