#ifndef MOVIE_H
#define MOVIE_H
#include<iostream>
#include<string>
using namespace std;
class Movie {
private:
    string ID;
    string movieType;
    string movieName;
    string movieDuration;
    string movieImage;
    string movieDescription;
public:
    Movie(){

    }
    Movie(string movieName, string movieType, string movieDuration, string movieImage, string movieDescription) {
        this->ID = "";
        this->movieName = movieName;
        this->movieType = movieType;
        this->movieDuration = movieDuration;
        this->movieImage = movieImage;
        this->movieDescription = movieDescription;
    }
    Movie(string ID,string movieName, string movieType, string movieDuration, string movieImage, string movieDescription) {
        this->ID = ID;
        this->movieName = movieName;
        this->movieType = movieType;
        this->movieDuration = movieDuration;
        this->movieImage = movieImage;
        this->movieDescription = movieDescription;
    }
    void editInfo(const Movie &another){
        (*this) = another;
    }
    string getID() const{
        return ID;
    }
    string getMovieName() const{
        return movieName;
    }
    string getMovieType() const{
        return movieType;
    }
    string getMovieDuration() const{
        return movieDuration;
    }
    string  getMovieImage()const{
        return movieImage;
    }
    string  getMovieDescription() const{
        return movieDescription;
    }
    void setID(string id) {
        ID = id;
    }
    void setMovieName(string MovieName) {
        movieName = MovieName;
    }
    void setMovieType(string MovieType){
        movieType = MovieType;
    }
    void setMovieDuration(string MovieDuration) {
        movieDuration =MovieDuration;
    }
    void setMovieImage(string MovieImage){
        movieImage = MovieImage;
    }
    void setMovieDescription(string MovieDescription) {
        movieDescription = MovieDescription;
    }
    const Movie &operator =(const Movie &m);
    bool operator == (const Movie &m);
    bool operator != (const Movie &m);
    friend class MovieManager;
    friend class App;
};


class MovieNode {
public:
    Movie movie;
    MovieNode* next;
    MovieNode(const Movie& movie) : movie(movie), next(nullptr) {}

    string operator [](const string& attributeName) {
        if (attributeName == "ID")
            return movie.getID();
        else if (attributeName == "movieName")
            return movie.getMovieName();
        else if (attributeName == "movieType")
            return movie.getMovieType();
        else if (attributeName == "movieDuration")
            return movie.getMovieDuration();
        else if (attributeName == "movieImage")
            return movie.getMovieImage();
        else if (attributeName == "movieDescription")
            return movie.getMovieDescription();
    }

};
class MovieManager {
private:
    MovieNode* head;
    int Next_Id ;
    int Load_Next_Id();
    void Save_Next_Id();

public:
    MovieManager(): head(nullptr) {
        Next_Id = Load_Next_Id();
    }
    ~MovieManager();
    string Generate_Id() {
        return to_string(Next_Id++);
    }
    Movie getMovie( string movieID)  ;
    void addMovie(const Movie& movie);
    void addMovieFromFile(const Movie& movie);
    void Save_Next_Id(int id);
    void removeMovie(const Movie& movie);
    void Load_Movies();
    void Update_Movies();
    int getCurrentID();
    int getSize();
    Movie getMovieByID(string ticketID) const;
    friend class App;
};







#endif // MOVIE_H





























