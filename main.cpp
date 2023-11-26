#include "app.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    UserManager userManager;
    ShowManager showManager;
    MovieManager movieManager;
    TicketManager ticketManager;
    userManager.Load_Users();
    showManager.Load_Shows();
    movieManager.Load_Movies();
    ticketManager.Load_Tickets();
    App w(nullptr, &userManager, &movieManager, &showManager, &ticketManager);

    w.showFullScreen();

    return a.exec();
}
