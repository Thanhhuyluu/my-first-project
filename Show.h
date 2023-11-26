
#ifndef SHOW_H
#define SHOW_H

#include<iostream>
#include<string>
using namespace std;
class Show {
private:
    string ShowID;
    string MovieID;
    string StartTime;
    string EndTime;
    string ShowDate;
    string CreatedDate;
public:
    Show(){

    }
    Show(string MovieID, string StartTime, string EndTime, string ShowDate, string CreatedDate) {
        this->ShowID = "";
        this->MovieID = MovieID;
        this->StartTime = StartTime;
        this->EndTime = EndTime;
        this->ShowDate = ShowDate;
        this->CreatedDate = CreatedDate;
    }
    Show(string ShowID,string MovieID, string StartTime, string EndTime, string ShowDate, string CreatedDate) {
        this->ShowID = ShowID;
        this->MovieID = MovieID;
        this->StartTime = StartTime;
        this->EndTime = EndTime;
        this->ShowDate = ShowDate;
        this->CreatedDate = CreatedDate;
    }
    void editInfo(const Show& show) {
        (*this )= show;

    }
    string getShowID() const {
        return ShowID;
    }
    string getMovieID() const{
        return MovieID;
    }
    string getStartTime() const{
        return StartTime;
    }
    string getEndTime() const{
        return EndTime;
    }
    string  getShowDate()const{
        return ShowDate;
    }
    string  getCreatedDate() const{
        return CreatedDate;
    }



    void setShowID(string showID) {
        ShowID = showID;
    }
    void setMovieID(string movieID) {
        MovieID = movieID;
    }
    void setStartTime(string startTime) {
        StartTime = startTime;
    }
    void setEndTime(string endTime) {
        EndTime = endTime;
    }
    void setShowDate(string showDate){
        ShowDate = showDate;
    }
    void setCreatedDate(string createdDate) {
        CreatedDate = createdDate;
    }


    const Show &operator =(const Show &show);
    bool operator == (const Show &show);


};



class ShowNode {
public:
    Show show;
    ShowNode* next;
    ShowNode(const Show& show) : show(show), next(nullptr) {}
    string ShowID;
    string MovieID;
    string StartTime;
    string EndTime;
    string ShowDate;
    string CreatedDate;
    string operator [](const string& attributeName) {
        if (attributeName == "ShowID")
            return show.getShowID();
        else if (attributeName == "MovieID")
            return show.getMovieID();
        else if (attributeName == "StartTime")
            return show.getStartTime();
        else if (attributeName == "EndTime")
            return show.getEndTime();
        else if (attributeName == "ShowDate")
            return show.getShowDate();
        else if (attributeName == "CreatedDate")
            return show.getCreatedDate();
    }
};
class ShowManager {
private:
    ShowNode* head;
    int Next_Id ;
    int Load_Next_Id();
    void Save_Next_Id();

public:
    ShowManager(): head(nullptr) {
        Next_Id = Load_Next_Id();
    }
    ~ShowManager();
    string Generate_Id() {
        return to_string(Next_Id++);
    }
    void addShow(const Show& show);
    void addShowFromFile(const Show& show);
    int getSize();
    void removeShow(const string& showID);
    void Save_Next_Id(int id);
    void Load_Shows();
    void Update_Shows();
    Show getShowByID(string ID) const;
    friend class App;
};





#endif // SHOW_H
