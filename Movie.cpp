#include"Movie.h"
#include<iostream>
#include<fstream>
#include<QDebug>
#include<sstream>
#include<QDate>
#include<QMessageBox>
const Movie &Movie::operator =(const Movie &m) {
    if(this != &m) {
        ID = m.ID;
        movieName = m.movieName;
        movieType = m.movieType;
        movieDuration = m.movieDuration;
        movieImage = m.movieImage;
        movieDescription = m.movieDescription;
    }
    return *this;
}


bool Movie::operator != (const Movie &m) {
    if(( movieName != m.movieName) || (movieType != m.movieType) || (movieDuration != m.movieDuration) || (movieImage != m.movieImage) || (movieDescription != m.movieDescription)){
        return true;
    }
    return false;
}
int MovieManager::Load_Next_Id(){
    int id;
    ifstream Next_Id_File("C:\\Users\\ADMIN\\Desktop\\PBL2\\data\\Next_Movie_Id.txt");
    if(Next_Id_File.is_open()){
        Next_Id_File >> id;
        Next_Id_File.close();
    } else {
        id = 1;

    }
    return id;

}
void MovieManager::Save_Next_Id(int id) {
    ofstream Next_Id_File("C:\\Users\\ADMIN\\Desktop\\PBL2\\data\\Next_Movie_Id.txt");
    if(Next_Id_File.is_open()) {
        Next_Id_File << id;
        Next_Id_File.close();
    }
}
void MovieManager::addMovieFromFile(const Movie& movie) {

    MovieNode* newNode = new MovieNode(movie);
    if (!head) {
        head = newNode;
        return;
    }

    MovieNode* current = head;
    while (current->next) {
        current = current->next;
    }
    current->next = newNode;
}

int MovieManager::getCurrentID(){
    return Next_Id - 1;
}

void MovieManager::addMovie(const Movie& movie){
    qDebug()<< "oke";
    MovieNode* newNode = new MovieNode(movie);
    newNode->movie.ID = MovieManager::Generate_Id();
    if (!head) {
        head = newNode;
        return;
    }

    MovieNode* current = head;
    while (current->next) {
        current = current->next;
    }
    current->next = newNode;
}


void MovieManager::Load_Movies() {
    ifstream Movie_File("C:\\Users\\ADMIN\\Desktop\\PBL2\\data\\Movie.txt");
    if(Movie_File.is_open()) {
        string line;

        while(getline(Movie_File, line)) {
            Movie movie;
            stringstream ss(line);
            getline(ss,movie.ID, ',');
            getline(ss,movie.movieName, ',');
            getline(ss,movie.movieType, ',');
            getline(ss,movie.movieDuration, ',');
            getline(ss,movie.movieImage, ',');
            getline(ss,movie.movieDescription, ',');
            addMovieFromFile(movie);
        }
       Movie_File.close();
    } else {
        qDebug("failed to open file");
    }
}
void MovieManager::Update_Movies() {
    ofstream Movie_File("C:\\Users\\ADMIN\\Desktop\\PBL2\\data\\Movie.txt");
    if(!Movie_File.is_open()) {
        qDebug("Failed to write file");
        return;
    }else {

        MovieNode* current = head;
        while (current) {
            Movie_File  << (*current)["ID"]<< "," << (*current)["movieName"] << "," << (*current)["movieType"] << "," << (*current)["movieDuration"] << "," << (*current)["movieImage"] << "," << (*current)["movieDescription"] << "\n";
            current = current->next;
        }

        Movie_File.close();
    }
}

void MovieManager::removeMovie(const Movie& movie){
    if (!head) {
        std::cout << "The list is empty. Cannot remove a ticket.\n";
        return;
    }
    if (head->movie.getID() == movie.getID()) {
        MovieNode* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    MovieNode* prev = nullptr;
    MovieNode* current = head;

    while (current && current->movie.getID() != movie.getID() && current->movie != movie) {
        prev = current;
        current = current->next;
    }

    if (!current) {
        std::cout << "Movie with ID " << movie.getID() << " not found in the list.\n";
        return;
    }
    prev->next = current->next;
    delete current;
}

Movie MovieManager::getMovie( string movieID) {
    MovieNode *temp = head;
    while(temp) {
        if((*temp)["ID"] == movieID) {
            return temp->movie;
        }
        temp = temp->next;
    }
    Movie movie;
    if(temp == NULL) return movie;
}
MovieManager::~MovieManager() {
    MovieNode* current = head;
    while (current) {
        MovieNode* temp = current;
        current = current->next;
        delete temp;
    }
    Save_Next_Id(Next_Id);
}

int MovieManager::getSize(){
    int count = 0;
    MovieNode *temp = head;
    while(temp){
        count++;
        temp = temp->next;
    }
    return count;
}

Movie MovieManager::getMovieByID(string ID) const{
    MovieNode *temp = head;
    while(temp){
        if(temp->movie.getID() == ID){
            return temp->movie;
        }
        temp = temp->next;
    }
}




