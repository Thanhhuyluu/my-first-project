#ifndef APP_H
#define APP_H

#include <QMainWindow>
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QApplication>
#include <QWidget>
#include <QPropertyAnimation>
#include<QScreen>
#include <QHBoxLayout>
#include <QFrame>
#include <QPushButton>
#include <QKeyEvent>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QChartView>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QHorizontalStackedBarSeries>
#include "User.h"
#include "Movie.h"
#include "Ticket.h"
#include "Show.h"
QT_BEGIN_NAMESPACE

namespace Ui { class App; }
QT_END_NAMESPACE

class App : public QMainWindow
{
    Q_OBJECT

public:
    App(QWidget *parent = nullptr, UserManager *userManager = nullptr, MovieManager *movieManager = nullptr, ShowManager *showManager = nullptr, TicketManager *ticketManager = nullptr);
    ~App();
protected:
    void keyPressEvent(QKeyEvent *event) override
    {
        if (event->key() == Qt::Key_Escape)
        {
            (*userManager).Update_Users();
            (*ticketManager).Update_Tickets();
            (*movieManager).Update_Movies();
            (*showManager).Update_Shows();
            this->close(); // Thoát ứng dụng
        }
    }
private slots:
    string toLower(const string& str) {
        string result = str;
        for (char& c : result) {
            c = tolower(c);
        }
        return result;
    }

    void on_Signup_Switch_Btn_clicked();

    void on_Login_Switch_Btn_clicked();

    void on_Login_Btn_clicked();

    void on_Signup_Btn_clicked();

    void on_Account_Menu_Btn_clicked();

    void createNewWidgets(int row, int column,const Movie& movie);

    void renderSeat(int row, int column,bool booked, const Show &show);

    void createNewShowWidgets(const Show &show);

    void createShowWidgetsForAdminPage( Show &show, string movieID);

    void showShowOfMovie(const Movie &movie);

    void showHallOfShow(const Show &show);

    void renderMovie();

    void renderShow(string movieID);

    void renderShowForAdminPage(string movieID);

    void createUserFrame(const User &user);

    void renderUserForAdminPage();

    void getShowButtonHandle(const Movie &movie);

    void createTicketFrame(const Ticket &ticket);

    void renderMyBooking(string userID);

    void removeTicket(const Ticket &ticket, QFrame *frame);

    void showEditButtonHandle( Show &show, string movieID);

    Show getShowByTicket(const Ticket& ticket);

    void on_Account_Setting_btn_clicked();

    void on_Account_Discovery_btn_clicked();

    void on_Account_Setting_Btn_clicked();

    void on_Book_Ticket_Btn_clicked();


    void on_Account_My_Booking_btn_clicked();

    void on_Account_Logout_btn_clicked();

    void on_Admin_Menu_btn_clicked();

    void removeMovie(const Movie& movie, QFrame *frame);

    void editMovieBtnHandle( Movie &movie);

    void createMovieFrame( Movie &movie);

    void renderMovieAdminPage();

    void on_Admin_My_Movie_btn_clicked();

    void AdminEditMovie( Movie & movie);


    void on_Admin_Logout_btn_clicked();

    void on_Admin_Add_Movie_btn_clicked();

    void addShowAdminBtnHandle(string movieID);

    void renderAdminTicketsChart();
    void on_Admin_Analystic_btn_clicked();

    void on_Account_Search_btn_clicked();

    void on_Admin_My_User_btn_clicked();

    void editUserButtonHandle(const User &u, Admin &admin);

private:
    Ui::App *ui;
    UserManager *userManager;
    MovieManager *movieManager;
    ShowManager *showManager;
    TicketManager *ticketManager;
    User *user;
    QGraphicsDropShadowEffect *Drop_Shadow_Effect;
    QPropertyAnimation *animation;
};
#endif // APP_H
