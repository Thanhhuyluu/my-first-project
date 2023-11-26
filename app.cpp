#include "app.h"
#include "./ui_app.h"
#include <QMessageBox>
#include <sstream>
#include <QDate>
#include <QRadioButton>

App::App(QWidget *parent, UserManager *userManager, MovieManager *movieManager, ShowManager *showManager, TicketManager *ticketManager )
    : QMainWindow(parent)
    , ui(new Ui::App)
    , userManager(userManager)
    , movieManager(movieManager)
    , showManager(showManager)
    , ticketManager(ticketManager)


{
    ui->setupUi(this);
    // effect for logo
    ui->Main_Stacked_Widget->setCurrentIndex(0);
    Drop_Shadow_Effect = new QGraphicsDropShadowEffect();
    Drop_Shadow_Effect->setBlurRadius(4);
    Drop_Shadow_Effect->setColor(QColor(0,0,0,200));
    Drop_Shadow_Effect->setOffset(6,5);
    ui->Logo_label->setGraphicsEffect(Drop_Shadow_Effect);

    //effect for sign up form

    Drop_Shadow_Effect = new QGraphicsDropShadowEffect();
    Drop_Shadow_Effect->setBlurRadius(10);
    Drop_Shadow_Effect->setColor(qRgba(0,0,0,0.02));
    Drop_Shadow_Effect->setOffset(10,10);
    ui->Signup_Form_Wrapper->setGraphicsEffect(Drop_Shadow_Effect);

    //effect for login form
    Drop_Shadow_Effect = new QGraphicsDropShadowEffect();
    Drop_Shadow_Effect->setBlurRadius(10);
    Drop_Shadow_Effect->setColor(qRgba(0,0,0,0.02));
    Drop_Shadow_Effect->setOffset(10,10);
    ui->Login_Form_Wrapper->setGraphicsEffect(Drop_Shadow_Effect);
    ui->Login_PhoneNum_Inp->setFocus();


}

App::~App()
{
    delete ui;
}

void App::createNewWidgets(int row, int column,const  Movie& movie) {
    string newName = "frame" + std::to_string(row) + "_" + std::to_string(column);
    QFrame *frame = new QFrame(ui->Account_Discovery_List);
    frame->setObjectName(QString::fromStdString(newName));
    frame->setMinimumSize(QSize(280, 400));
    frame->setMaximumSize(QSize(280, 400));
    frame->setStyleSheet("#"+ QString::fromStdString(newName) +" {background-color: black; border-image: url("+  QString::fromStdString(movie.getMovieImage()) +") 0 0 0 0 stretch stretch;border-radius: 10px; margin: 20px 0; border: 5px solid black;}"     +"\n #"+ QString::fromStdString(newName) + ":hover {background-color: #fff}");
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setFrameShadow(QFrame::Raised);

    QVBoxLayout *layout = new QVBoxLayout(frame);
    QSpacerItem *verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    layout->addItem(verticalSpacer);
    QLabel *movieLabel = new QLabel(QString::fromStdString(movie.getMovieName()));
    movieLabel->setStyleSheet("font-size: 30px;color: #fff;font-weight: 900;");
    movieLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(movieLabel);


    QPushButton *button = new QPushButton("Chose");
    string newButtonName = "button" + std::to_string(row) + "_" + std::to_string(column);
    button->setObjectName(QString::fromStdString(newButtonName));
    button->setStyleSheet("#"+(button->objectName())+"{font-size: 18px;background-color:#e50914;font-weight: 700;color: #fff;border-radius: 5px;margin-bottom: 5px;}"+ "\n#"+button->objectName() + ":hover{background-color: #ff2f4e;;}");
    button->setMinimumSize(QSize(180,50));
    button->setMaximumSize(QSize(180, 50));
    connect(button, &QPushButton::clicked, [this,movie](){
        showShowOfMovie(movie);
    });
    layout->addWidget(button, 0, Qt::AlignHCenter);
    frame->setLayout(layout);

    // Thêm frame vào layout
    QGridLayout *gridLayout;
    if (!ui->Account_Discovery_List->layout()) {
        gridLayout = new QGridLayout(ui->Account_Discovery_List);
        ui->Account_Discovery_List->setLayout(gridLayout);
    } else {
        gridLayout = dynamic_cast<QGridLayout*>(ui->Account_Discovery_List->layout());
    }

    // Thêm frame vào grid layout
    gridLayout->addWidget(frame, row, column);
}

void App::createNewShowWidgets(const Show &show){
    string newName = "frame" + show.getShowID();
    QFrame *frame = new QFrame(ui->Movie_Show_List);
    frame->setObjectName(QString::fromStdString(newName));
    frame->setMinimumSize(QSize(0, 150));
    frame->setMaximumSize(QSize(16777215, 150));
    frame->setStyleSheet("#"+ QString::fromStdString(newName) +" {padding-left: 20px;color: #000;background-color: rgba(0,0,0,0.6);border-radius: 10px;}"     +"\n #"+ QString::fromStdString(newName) + ":hover {background-color: rgba(225,225,225,0.2); color: #fff;}");
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setFrameShadow(QFrame::Raised);

    QVBoxLayout *layout = new QVBoxLayout(frame);
    QLabel *showLabel = new QLabel(QString::fromStdString(show.getStartTime() + "-" +show.getEndTime() + "     " + show.getShowDate()));
    showLabel->setStyleSheet("font-size: 30px;color: #fff ;font-weight: 700;");
    showLabel->setAlignment(Qt::AlignLeft);
    layout->addWidget(showLabel);


    QPushButton *button = new QPushButton("Chose");
    button->setStyleSheet("font-size: 18px;background-color:#e50914;font-weight: 700;color: #fff;border-radius: 5px;margin-bottom: 5px;");
    button->setMinimumSize(QSize(180,50));
    button->setMaximumSize(QSize(180, 50));
    connect(button, &QPushButton::clicked, [this,show](){
        showHallOfShow(show);
    });
    layout->addWidget(button, 0, Qt::AlignRight);
    frame->setLayout(layout);

    // Thêm frame vào layout
    QGridLayout *gridLayout;
    if (!ui->Movie_Show_List->layout()) {
        gridLayout = new QGridLayout(ui->Movie_Show_List);
        ui->Movie_Show_List->setLayout(gridLayout);
    } else {
        gridLayout = dynamic_cast<QGridLayout*>(ui->Movie_Show_List->layout());
    }

    // Thêm frame vào grid layout
    gridLayout->addWidget(frame);

}

void App::editUserButtonHandle(const User&u,Admin &admin){
    ui->Admin_Main_StackWidget->setCurrentIndex(6);
    ui->Admin_User_Edit_Name_Input->setText(QString::fromStdString(u.getName()));
    ui->Admin_User_Edit_PhoneNum_Input->setText(QString::fromStdString(u.getPhoneNum()));
    ui->Admin_User_Edit_Password_Input->setText(QString::fromStdString(u.getPassword()));
    ui->Admin_User_Edit_Status_Input->setText(QString::fromStdString(u.getStatus()));
    QPushButton *AdminUserEditBtn = ui->Admin_User_Edit_Btn;
    connect(AdminUserEditBtn, &QPushButton::clicked,[this,&admin,&u](){
        string userName = ui->Admin_User_Edit_Name_Input->text().trimmed().toStdString();
        string userPhoneNum = ui->Admin_User_Edit_PhoneNum_Input->text().trimmed().toStdString();
        string userPassword = ui->Admin_User_Edit_Password_Input->text().trimmed().toStdString();
        string userStatus =  ui->Admin_User_Edit_Status_Input->text().trimmed().toStdString();
        User nu(userName,"Customer",userPhoneNum,userPassword,userStatus,u.getCreatedDate());
        nu.setID(u.getID());
        UserNode *temp = userManager->head;
        while(temp) {
            if(temp->user.getID() == u.getID()){
                temp->user = nu;
                ui->Admin_User_Edit_Name_Input->clear();
                ui->Admin_User_Edit_PhoneNum_Input->clear();
                ui->Admin_User_Edit_Password_Input->clear();
                ui->Admin_User_Edit_Status_Input->clear();
                break;
            }
            temp = temp->next;
        }

    });
}

void App::createUserFrame(const User &u){
    string newName = "frame" + u.getID();
    QFrame *frame = new QFrame(ui->Admin_User_list);
    frame->setObjectName(QString::fromStdString(newName));
    frame->setMinimumSize(QSize(0, 220));
    frame->setMaximumSize(QSize(16777215, 220));
    frame->setStyleSheet("#"+ QString::fromStdString(newName) +" {padding-left: 20px;color: #000;background-color: rgba(0,0,0,0.6);border-radius: 10px;}"     +"\n #"+ QString::fromStdString(newName) + ":hover {background-color: rgba(225,225,225,0.2); color: #fff;}");
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setFrameShadow(QFrame::Raised);

    QVBoxLayout *layout = new QVBoxLayout(frame);
    QLabel *userLabel = new QLabel(QString::fromStdString("ID: " +u.getID() + "       Name: " +  u.getName()));
    QLabel *userJoinDate = new QLabel(QString::fromStdString("Joined in : " + u.getCreatedDate()));

    userLabel->setStyleSheet("font-size: 30px;color: #fff ;font-weight: 700;");
    userLabel->setAlignment(Qt::AlignLeft);
    layout->addWidget(userLabel);
    userJoinDate->setStyleSheet("font-size: 24px;color: #fff ;font-weight: 600;");
    userJoinDate->setAlignment(Qt::AlignLeft);
    layout->addWidget(userJoinDate);

    QPushButton *editUserButton = new QPushButton("Edit");
    editUserButton->setStyleSheet("font-size: 18px;background-color:#e50914;font-weight: 700;color: #fff;border-radius: 5px;margin-bottom: 5px;");
    editUserButton->setMinimumSize(QSize(180,50));
    editUserButton->setMaximumSize(QSize(180, 50));

    Admin *admin = new Admin(this->user->getName(),this->user->getPhoneNum(),this->user->getPassword(),this->user->getCreatedDate());
    admin->setID(this->user->getID());


    connect(editUserButton, &QPushButton::clicked, [this,u,&admin](){

        editUserButtonHandle(u,*admin);

    });


    layout->addWidget(editUserButton, 0, Qt::AlignRight);






    QPushButton *deleteUserButton = new QPushButton("Delete");
    deleteUserButton->setStyleSheet("font-size: 18px;background-color:#e50914;font-weight: 700;color: #fff;border-radius: 5px;margin-bottom: 5px;");
    deleteUserButton->setMinimumSize(QSize(180,50));
    deleteUserButton->setMaximumSize(QSize(180, 50));




    connect(deleteUserButton, &QPushButton::clicked, [this,u,&admin,frame,layout](){

        admin->removeUser(u.getID(),*userManager,*ticketManager);
        layout->removeWidget(frame);
        delete frame;

    });


    layout->addWidget(deleteUserButton, 0, Qt::AlignRight);
    frame->setLayout(layout);

    // Thêm frame vào layout
    QGridLayout *gridLayout;
    if (!ui->Admin_User_list->layout()) {
        gridLayout = new QGridLayout(ui->Admin_User_list);
        ui->Admin_User_list->setLayout(gridLayout);
    } else {
        gridLayout = dynamic_cast<QGridLayout*>(ui->Admin_User_list->layout());
    }

    // Thêm frame vào grid layout
    gridLayout->addWidget(frame);
}

void App::renderUserForAdminPage(){
    QLayout *layout = ui->Admin_User_list->layout();
    while (QLayoutItem *item = layout->takeAt(0)) {
        if (QWidget *widget = item->widget()) {
            widget->deleteLater();
        }
        delete item; // Xóa phần tử layout
    }
    UserNode *temp = userManager->head;
    while(temp ){
        if((*temp)["Role"] == "Customer"){
            createUserFrame(temp->user);
        }
        temp = temp->next;
    }
}

void App::showEditButtonHandle( Show &show, string movieID){
    ui->Admin_Show_Edit_error->clear();
    ui->Admin_Main_StackWidget->setCurrentIndex(4);
    QFrame *frame = ui->Admin_Show_Edit_Input_Field;
    QList<QRadioButton *> radioButtons = frame->findChildren<QRadioButton *>();


    for (QRadioButton *radio : radioButtons) {
        radio->setChecked(false);
    }
    QPushButton * button = ui->Admin_Show_Edit_Save_btn;
    QPushButton * SaveShowBtn = ui->Admin_Show_Edit_Btn;
    SaveShowBtn->hide();
    connect(button,&QPushButton::clicked,[this, &show, movieID,SaveShowBtn](){
        QFrame *frame = ui->Admin_Show_Edit_Input_Field;
        QList<QRadioButton *> radioButtons = frame->findChildren<QRadioButton *>();
        string showStartTime, showEndTime;
        for (QRadioButton *radio : radioButtons) {
            if(radio->isChecked()){
                string radioName = radio->objectName().toStdString();
                if(radioName[0] == 'M'){
                    if(radioName[1]== '1'){
                        showStartTime = "7:00";
                        showEndTime = "9:00";
                    }else if(radioName[1]=='2'){
                        showStartTime = "9:00";
                        showEndTime = "11:00";
                    }

                }else if(radioName[0] == 'A'){
                    if(radioName[1]== '1'){
                        showStartTime = "13:00";
                        showEndTime = "15:00";
                    }else if(radioName[1]=='2'){
                        showStartTime = "15:00";
                        showEndTime = "17:00";
                    }

                }else if(radioName[0] == 'E'){
                    if(radioName[1]== '1'){
                        showStartTime = "18:00";
                        showEndTime = "20:00";
                    }else if(radioName[1]=='2'){
                        showStartTime = "20:00";
                        showEndTime = "22:00";
                    }
                }

            }
        }
        QDate currentDate = QDate::currentDate();
        QString dateString = currentDate.toString("yyyy-dd-MM");
        string showDate = dateString.toStdString();
        ShowNode *temp = showManager->head;
        bool has_error = false;
        while(temp){
            if((*temp)["MovieID"] == movieID && (*temp)["StartTime"] == showStartTime && (*temp)["EndTime"] == showEndTime && (*temp)["ShowDate"] == showDate){
                ui->Admin_Show_Edit_error->setText("Show has been added");
                has_error = true;
                break;
            }
            temp = temp->next;

        }
        if(has_error == false){
            Admin admin(user->getName(),user->getPhoneNum(),user->getPassword(),user->getCreatedDate());
            admin.setID(to_string(userManager->getCurrentID()));
            Show anotherShow(show.getShowID(),movieID, showStartTime,  showEndTime, showDate,show.getCreatedDate());
            admin.editShow(show,anotherShow);
            ui->Admin_Show_Edit_error->clear();
            renderShowForAdminPage(movieID);
            SaveShowBtn->show();
            ui->Admin_Main_StackWidget->setCurrentIndex(3);

        }
    });
}

void App::createShowWidgetsForAdminPage( Show &show, string movieID){
    string newName = "frame" + show.getShowID();
    QFrame *frame = new QFrame(ui->Admin_Show_list);
    frame->setObjectName(QString::fromStdString(newName));
    frame->setMinimumSize(QSize(0, 200));
    frame->setMaximumSize(QSize(16777215, 200));
    frame->setStyleSheet("#"+ QString::fromStdString(newName) +" {padding-left: 20px;color: #000;background-color: rgba(0,0,0,0.6);border-radius: 10px;}"     +"\n #"+ QString::fromStdString(newName) + ":hover {background-color: rgba(225,225,225,0.2); color: #fff;}");
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setFrameShadow(QFrame::Raised);

    QVBoxLayout *layout = new QVBoxLayout(frame);
    QLabel *showLabel = new QLabel(QString::fromStdString(show.getStartTime() + "-"+show.getEndTime() +  "     " + show.getShowDate()));
    showLabel->setStyleSheet("font-size: 30px;color: #fff ;font-weight: 700;");
    showLabel->setAlignment(Qt::AlignLeft);
    layout->addWidget(showLabel);


    QPushButton *showEditButton = new QPushButton("Edit");
    showEditButton->setStyleSheet("font-size: 18px;background-color:#e50914;font-weight: 700;color: #fff;border-radius: 5px;margin-bottom: 5px;");
    showEditButton->setMinimumSize(QSize(180,50));
    showEditButton->setMaximumSize(QSize(180, 50));
    connect(showEditButton, &QPushButton::clicked, [this,&show, movieID](){
        showEditButtonHandle(show, movieID);
    });
    layout->addWidget(showEditButton, 0, Qt::AlignRight);
    QPushButton *showDeleteButton = new QPushButton("Delete");
    showDeleteButton->setStyleSheet("font-size: 18px;background-color:#e50914;font-weight: 700;color: #fff;border-radius: 5px;margin-bottom: 5px;");
    showDeleteButton->setMinimumSize(QSize(180,50));
    showDeleteButton->setMaximumSize(QSize(180, 50));
        connect(showDeleteButton, &QPushButton::clicked, [this,&show,frame,layout](){
        Admin admin(user->getName(),user->getPhoneNum(),user->getPassword(),user->getCreatedDate());
        admin.setID(to_string(userManager->getCurrentID()));
        admin.removeShow(*showManager,show, *ticketManager);

        layout->removeWidget(frame);
        delete frame;

        });
    layout->addWidget(showDeleteButton, 0, Qt::AlignRight);

    frame->setLayout(layout);

    // Thêm frame vào layout
    QGridLayout *gridLayout;
    if (!ui->Admin_Show_list->layout()) {
        gridLayout = new QGridLayout(ui->Admin_Show_list);
        ui->Admin_Show_list->setLayout(gridLayout);
    } else {
        gridLayout = dynamic_cast<QGridLayout*>(ui->Admin_Show_list->layout());
    }

    // Thêm frame vào grid layout
    gridLayout->addWidget(frame);

}

void App::showShowOfMovie(const Movie &movie) {
    renderShow(movie.getID());

}

void App::renderSeat(int row, int column, bool booked, const Show &show) {

    string newName = "seat_" + to_string(row) + "_" + to_string(column) + "_" + show.getShowID();
    QPushButton *seat= new QPushButton(ui->Book_Ticket_Show_Hall_Seat);
    seat->setObjectName(QString::fromStdString(newName));
    seat->setMinimumSize(QSize(50, 50));
    seat->setMaximumSize(QSize(50, 50));
    seat->setText(QString::number(row) +"-"+QString::number(column));
    seat->setCheckable(true);
    seat->setChecked(false);
    if(booked ){
        seat->setDisabled(true);
        seat->setStyleSheet(
            "#" + QString::fromStdString(newName) + " {background-color: rgba(104,94,94,0.9); border-radius: 2px;}"
                                                    "\n #" + QString::fromStdString(newName) + ":hover {background-color: rgba(104,94,94,0.9);}"
            );
    }else {

        seat->setStyleSheet(
            "#" + QString::fromStdString(newName) + " {background-color: #eef0ef; border-radius: 2px;}"
                                                    "\n #" + QString::fromStdString(newName) + ":hover {background-color: rgba(238,240,239,0.8)}"
            );


    }

    connect(seat, &QPushButton::toggled, [seat](){
        if(seat->isChecked()){
            seat->setStyleSheet("#" + seat->objectName() + " {background-color: red; border-radius: 2px;}");

        }else {
            seat->setStyleSheet("#" + seat->objectName() + " {background-color: #eef0ef; border-radius: 2px;}");
        }
    });
    // Thêm frame vào layout
    QGridLayout *gridLayout;
    if (!ui->Book_Ticket_Show_Hall_Seat->layout()) {
        gridLayout = new QGridLayout(ui->Book_Ticket_Show_Hall_Seat);
        ui->Book_Ticket_Show_Hall_Seat->setLayout(gridLayout);
    } else {
        gridLayout = dynamic_cast<QGridLayout*>(ui->Book_Ticket_Show_Hall_Seat->layout());
    }

    // Thêm frame vào grid layout
    gridLayout->addWidget(seat,row,column);

}

void App::removeMovie(const Movie& movie, QFrame *frame){

    QLayout *layout = ui->Admin_Edit_Page_Movie_list->layout();
    if (layout) {
        layout->removeWidget(frame);
        delete frame;
    }
    Admin admin(user->getName(),user->getPhoneNum(),user->getPassword(),user->getCreatedDate());
    admin.setID(to_string(userManager->getCurrentID()));
    admin.removeMovie(*movieManager,movie);
}

void App::editMovieBtnHandle(Movie &movie){
    ui->Admin_Main_StackWidget->setCurrentIndex(2);
    ui->Admin_Movie_Des_Input->setText(QString::fromStdString(movie.getMovieDescription()));
    ui->Admin_Movie_Duration_Input->setText(QString::fromStdString(movie.getMovieDuration()));
    ui->Admin_Movie_Img_Input->setText(QString::fromStdString(movie.getMovieImage()));
    ui->Admin_Movie_MovieType_Input->setText(QString::fromStdString(movie.getMovieType()));
    ui->Admin_Movie_Name_Input->setText(QString::fromStdString(movie.getMovieName()));
    QPushButton* editBtn = ui->Admin_Movie_Edit_Save_btn;
    connect(editBtn, &QPushButton::clicked, [this,&movie](){

        AdminEditMovie(movie);
    });
}

void App::AdminEditMovie(Movie &movie){
    Admin admin(user->getName(),user->getPhoneNum(),user->getPassword(), user->getCreatedDate());
    string newMovieName = ui->Admin_Movie_Name_Input->text().trimmed().toStdString();
    string newMovieType = ui->Admin_Movie_MovieType_Input->text().trimmed().toStdString();
    string newMovieDuration = ui->Admin_Movie_Duration_Input->text().trimmed().toStdString();
    string newMovieDescription = ui->Admin_Movie_Des_Input->text().trimmed().toStdString();
    string newMovieImg = ui->Admin_Movie_Img_Input->text().trimmed().toStdString();
    Movie newEdit(newMovieName,newMovieType,newMovieDuration,newMovieImg,newMovieDescription);
    newEdit.setID(movie.getID());
    admin.editMovie(movie,newEdit);
    ui->Admin_Main_StackWidget->setCurrentIndex(1);
    renderMovieAdminPage();
}

void App::renderShowForAdminPage(string movieID){
    QLayout *layout = ui->Admin_Show_list->layout();
    while (QLayoutItem *item = layout->takeAt(0)) {
        if (QWidget *widget = item->widget()) {
            widget->deleteLater();
        }
        delete item; // Xóa phần tử layout
    }
    ShowNode *temp = showManager->head;
    while(temp!= NULL) {
        if((*temp)["MovieID"] == movieID) {
            createShowWidgetsForAdminPage(temp->show, movieID);
        }
        temp = temp->next;
    }
    QPushButton * addShowBtn = ui->Admin_Add_Show_btn;
    connect(addShowBtn,&QPushButton::clicked,[this,movieID](){
        addShowAdminBtnHandle(movieID);
    });
}

void App::getShowButtonHandle(const Movie &movie){

    ui->Admin_Main_StackWidget->setCurrentIndex(3);
    renderShowForAdminPage(movie.getID());
}

void App::createMovieFrame( Movie &movie){
    string newName = "movie" + movie.getID();
    QFrame *frame = new QFrame(ui->Admin_Edit_Page_Movie_list);
    frame->setObjectName(QString::fromStdString(newName));
    frame->setMinimumSize(QSize(0, 250));
    frame->setMaximumSize(QSize(16777215, 250));
    frame->setStyleSheet("#"+ QString::fromStdString(newName) +" {padding-left: 30px; padding-top: 10px;background-color: rgba(0,0,0,0.6);border-radius: 10px;}"     +"\n #"+ QString::fromStdString(newName) + ":hover {background-color:rgba(225,225,225,0.2)}");
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setFrameShadow(QFrame::Raised);

    QVBoxLayout *layout = new QVBoxLayout(frame);
    QString movieName =  QString::fromStdString(movie.getMovieName());
    QLabel *movieNameLabel = new QLabel(movieName);
    movieNameLabel->setStyleSheet("font-size: 35px;color: #fff;font-weight: 700;");
    movieNameLabel->setAlignment(Qt::AlignLeft);
    layout->addWidget(movieNameLabel);
    QString movieDuration =  QString::fromStdString("Duration: "+movie.getMovieDuration() + " minutes");
    QLabel *movieDurationLabel = new QLabel(movieDuration);
    movieDurationLabel->setStyleSheet("font-size: 20px;color: #fff ;font-weight: 400;");
    movieDurationLabel->setAlignment(Qt::AlignLeft);
    layout->addWidget(movieDurationLabel);


    QPushButton *deleteButton = new QPushButton("Delete");
    deleteButton->setStyleSheet("font-size: 18px;background-color:#e50914;font-weight: 700;color: #fff;border-radius: 5px;margin-bottom: 5px;");
    deleteButton->setMinimumSize(QSize(180,50));
    deleteButton->setMaximumSize(QSize(180, 50));

    connect(deleteButton, &QPushButton::clicked, [this,movie, frame](){

        removeMovie(movie, frame);

    });
    layout->addWidget(deleteButton, 0, Qt::AlignRight);

    QPushButton *editButton = new QPushButton("Edit");
    editButton->setStyleSheet("font-size: 18px;background-color:#e50914;font-weight: 700;color: #fff;border-radius: 5px;margin-bottom: 5px;");
    editButton->setMinimumSize(QSize(180,50));
    editButton->setMaximumSize(QSize(180, 50));

    connect(editButton, &QPushButton::clicked, [this,&movie](){

        editMovieBtnHandle(movie);

    });
    layout->addWidget(editButton, 0, Qt::AlignRight);

    QPushButton *getShowButton = new QPushButton("Get show");
    getShowButton->setStyleSheet("font-size: 18px;background-color:#e50914;font-weight: 700;color: #fff;border-radius: 5px;margin-bottom: 5px;");
    getShowButton->setMinimumSize(QSize(180,50));
    getShowButton->setMaximumSize(QSize(180, 50));

    connect(getShowButton, &QPushButton::clicked, [this,movie](){
        getShowButtonHandle(movie);
    });
    layout->addWidget(getShowButton, 0, Qt::AlignRight);

    frame->setLayout(layout);
    QGridLayout *gridLayout;
    if (!ui->Admin_Edit_Page_Movie_list->layout()) {
        gridLayout = new QGridLayout(ui->Admin_Edit_Page_Movie_list);
        ui->Admin_Edit_Page_Movie_list->setLayout(gridLayout);
    } else {
        gridLayout = dynamic_cast<QGridLayout*>(ui->Admin_Edit_Page_Movie_list->layout());
    }

    // Thêm frame vào grid layout
    gridLayout->addWidget(frame);

}

Show App::getShowByTicket(const Ticket& ticket){
    ShowNode *temp = showManager->head;
    string showID = ticket.getShowID();
    while(temp) {
        if( (*temp)["ShowID"] == showID){
            Show show((*temp)["ShowID"],(*temp)["MovieID"],(*temp)["StartTime"],(*temp)["EndTime"],(*temp)["ShowDate"],(*temp)["CreatedDate"]);
            return show;
        }
        temp = temp->next;
    }
}

void App::removeTicket(const Ticket &ticket, QFrame *frame){
    ticketManager->removeTicket(ticket);
    QLayout *layout = ui->My_Booking_List->layout();
    if (layout) {
        layout->removeWidget(frame);
        delete frame;
    }

}

void App::createTicketFrame(const Ticket &ticket){
    string newName = "frame" + ticket.getTicketID();
    QFrame *frame = new QFrame(ui->My_Booking_List);
    frame->setObjectName(QString::fromStdString(newName));
    frame->setMinimumSize(QSize(0, 180));
    frame->setMaximumSize(QSize(16777215, 180));
    frame->setStyleSheet("#"+ QString::fromStdString(newName) +" {background-color: rgba(0,0,0,0.4); border-radius: 10px;padding-left: 30px;}"     +"\n #"+ QString::fromStdString(newName) + ":hover {background-color:rgba(225,225,225,0.4);}");
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setFrameShadow(QFrame::Raised);   
    QVBoxLayout *layout = new QVBoxLayout(frame);
    Show show = getShowByTicket(ticket);
    Movie movie = movieManager->getMovieByID(show.getMovieID());
    QString movieName = QString::fromStdString(movie.getMovieName());
    QLabel *movieNameLabel = new QLabel(movieName);
    movieNameLabel->setStyleSheet("font-size: 34px;color: #fff ;font-weight: 800;");
    movieNameLabel->setAlignment(Qt::AlignLeft);
    QString showTime =  QString::fromStdString(show.getShowDate() + "    " +show.getStartTime() + "-" + show.getEndTime());
    QLabel *bookingLabel = new QLabel(showTime);
    bookingLabel->setStyleSheet("font-size: 24px;color: #c8c8c8 ;font-weight: 600;");
    bookingLabel->setAlignment(Qt::AlignLeft);
    QString seatPosition =  QString::fromStdString("Seat: " + ticket.getSeatRow()+ ticket.getSeatCol());
    QLabel *seatLabel = new QLabel(seatPosition);
    seatLabel->setStyleSheet("font-size: 24px;color: #c8c8c8 ;font-weight: 600;");
    seatLabel->setAlignment(Qt::AlignLeft);
    layout->addWidget(movieNameLabel);
    layout->addWidget(bookingLabel);
    layout->addWidget(seatLabel);


    QPushButton *button = new QPushButton("Delete");
    button->setStyleSheet("font-size: 18px;background-color:#e50914;font-weight: 700;color: #fff;border-radius: 5px;margin-bottom: 5px;");
    button->setMinimumSize(QSize(180,50));
    button->setMaximumSize(QSize(180, 50));

    connect(button, &QPushButton::clicked, [this,ticket, frame](){

        removeTicket(ticket, frame);

    });
    layout->addWidget(button, 0, Qt::AlignRight);
    frame->setLayout(layout);
    // Thêm frame vào layout
    QGridLayout *gridLayout;
    if (!ui->My_Booking_List->layout()) {
        gridLayout = new QGridLayout(ui->My_Booking_List);
        ui->My_Booking_List->setLayout(gridLayout);
    } else {
        gridLayout = dynamic_cast<QGridLayout*>(ui->My_Booking_List->layout());
    }

    // Thêm frame vào grid layout
    gridLayout->addWidget(frame);
}

void App::renderMyBooking(string userID){

    TicketNode *temp = ticketManager->head;
    while(temp){
        if((*temp)["CustomerID"] == userID){
            createTicketFrame(temp->ticket);
        }
        temp = temp->next;
    }

}

void App::showHallOfShow(const Show &show) {


    ui->Account_Main_Widget->setCurrentIndex(4);
    on_Account_Menu_Btn_clicked();
    Movie movie = movieManager->getMovie(show.getMovieID());
    ui->Book_Ticket_Movie_Img->setStyleSheet("border-image: url("+ QString::fromStdString(movie.getMovieImage())   +") 0 0 0 0 stretch stretch;");
    ui->Ticket_Movie_Description->setText(QString::fromStdString(movie.getMovieDescription()));
    ui->Ticket_Movie_Duration->setText(QString::fromStdString(movieManager->getMovie(show.getMovieID()).getMovieDuration()));
    ui->Ticket_Show_Start_End_Time->setText(QString::fromStdString(show.getStartTime() + " - " + show.getEndTime()));
    ui->Ticket_Show_Date->setText(QString::fromStdString(show.getShowDate()));
    ui->Book_Ticket_Movie_Name->setText(QString::fromStdString(movie.getMovieName()));
    bool booked[6][12];
    for(int i = 0; i < 6; i ++){
        for(int j = 0; j < 12; j++){
            booked[i][j] = false;
        }
    }
    TicketNode *temp = ticketManager->head;
    while(temp){
        if(temp->ticket.getShowID() == show.getShowID()) {
            booked[stoi(temp->ticket.getSeatRow())][stoi(temp->ticket.getSeatCol())] = true;
        }
        temp = temp->next;
    }
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 12; j++){
            renderSeat(i,j,booked[i][j],show);
        }
    }
    ui->Book_Ticket_Btn->setDisabled(false);
    ui->Book_Ticket_Btn->setStyleSheet("font-size: 18px;background-color:#e50914;font-weight: 700;color: #fff;border-radius: 5px;margin-bottom: 5px;");
}

void App::on_Signup_Switch_Btn_clicked()
{

    ui->Signup_Password_Error_Label->clear();
    ui->Signup_PhoneNum_Error_Label->clear();
    ui->Login_PhoneNum_Inp->clear();
    ui->Login_Password_Inp->clear();
    ui->Signup_Name_Error_Label->clear();
    ui->Signup_Comfirm_Password_Error_Label->clear();
    ui->Signup_Error_Main_Label->clear();
    ui->Signup_Password_Inp->clear();
    ui->Signup_PhoneNum_Inp->clear();
    ui->Signup_Comfirm_Password_Inp->clear();
    ui->Signup_Password_Inp->clear();
    ui->Signup_FirstName_Inp->clear();
    ui->Signup_LastName_Inp->clear();
    ui->Main_Stacked_Widget->setCurrentIndex(1);
}

void App::on_Login_Switch_Btn_clicked()
{

    ui->Signup_Password_Inp->clear();
    ui->Signup_PhoneNum_Inp->clear();
    ui->Login_Error->clear();
    ui->Login_Password_Error->clear();
    ui->Login_PhoneNum_Error->clear();
    ui->Main_Stacked_Widget->setCurrentIndex(0);
    Drop_Shadow_Effect = new QGraphicsDropShadowEffect();
    Drop_Shadow_Effect->setBlurRadius(10);
    Drop_Shadow_Effect->setColor(qRgba(0,0,0,0.02));
    Drop_Shadow_Effect->setOffset(10,10);
    ui->Signup_Form_Wrapper->setGraphicsEffect(Drop_Shadow_Effect);

}

void App::on_Login_Btn_clicked()
{
    string PhoneNum_Inp = ui->Login_PhoneNum_Inp->text().trimmed().toStdString();
    string Password_Inp = ui->Login_Password_Inp->text().trimmed().toStdString();
    ui->Login_PhoneNum_Error->clear();
    ui->Login_Password_Error->clear();
    int has_error = 0;
    if(PhoneNum_Inp.size() != 10 && PhoneNum_Inp.size() != 0) {
        ui->Login_PhoneNum_Error->setText("Phone Number is not valid");
        has_error = 1;
    }else {
        for(int i = 0; i < PhoneNum_Inp.size(); i++) {
            int j = PhoneNum_Inp[i];
            if(!(j >= 48 && j <= 57)) {
                ui->Login_PhoneNum_Error->setText("Field Phone Number must be Numberic");
                has_error = 1;
                break;
            }
        }
    }
    if(ui->Login_PhoneNum_Inp->text().trimmed().isEmpty()) {
        ui->Login_PhoneNum_Error->setText("Please fill out this field");
        has_error = 1;
    }
    if( ui->Login_Password_Inp->text().trimmed().isEmpty()) {
        has_error = 1;
        ui->Login_Password_Error->setText("Please fill out this field");
    }
    if(has_error != 1) {
        UserNode *temp = userManager->head;
        while(temp) {
            if(PhoneNum_Inp.compare((*temp)["PhoneNum"]) == 0 && Password_Inp.compare((*temp)["Password"]) == 0) {
                QMessageBox::information(this, "info",QString::fromStdString((*temp)["Name"]));
                User *u = new User((*temp)["ID"],(*temp)["Name"], (*temp)["Role"], (*temp)["PhoneNum"],(*temp)["Password"], (*temp)["Status"],(*temp)["CreatedDate"]);
                this->user = u;
                this->user->setID(u->getID());

                if(user->getRole() == "Customer"){
                    ui->Main_Stacked_Widget->setCurrentIndex(2);
                    ui->Account_Main_Widget->setCurrentIndex(0);
                    renderMovie();
                }else if(user->getRole() == "Admin"){
                    renderAdminTicketsChart();
                    ui->Main_Stacked_Widget->setCurrentIndex(3);

                }
                break;
            }
            temp = temp->next;
        }
        if(temp == NULL) {
            ui->Login_Error->setText("Account not found");
        }
    }
}

void App::on_Signup_Btn_clicked()
{
    string firstName_Inp = ui->Signup_FirstName_Inp->text().trimmed().toStdString();
    string lastName_Inp = ui->Signup_LastName_Inp->text().trimmed().toStdString();
    string PhoneNum_Inp = ui->Signup_PhoneNum_Inp->text().trimmed().toStdString();
    string Password_Inp = ui->Signup_Password_Inp->text().trimmed().toStdString();
    string Comfirm_Password_Inp = ui->Signup_Comfirm_Password_Inp->text().trimmed().toStdString();
    int has_error = 0;

    // Validate signup form
    ui->Signup_Name_Error_Label->clear();
    ui->Signup_PhoneNum_Error_Label->clear();
    ui->Signup_Password_Error_Label->clear();
    ui->Signup_Comfirm_Password_Error_Label->clear();
    ui->Signup_Error_Main_Label->clear();
    if(ui->Signup_FirstName_Inp->text().trimmed().isEmpty()|| ui->Signup_LastName_Inp->text().trimmed().isEmpty()) {
        ui->Signup_Name_Error_Label->setText("Please fill out this field");
        has_error = 1;
        ui->Signup_FirstName_Inp->clear();
        ui->Signup_LastName_Inp->clear();
    }
    if(ui->Signup_PhoneNum_Inp->text().trimmed().isEmpty()) {
        ui->Signup_PhoneNum_Error_Label->setText("Please fill out this field");
        has_error = 1;
    }
    if( ui->Signup_Password_Inp->text().trimmed().isEmpty()) {
        has_error = 1;
        ui->Signup_Password_Error_Label->setText("Please fill out this field");
    }
    if(ui->Signup_Comfirm_Password_Inp->text().trimmed().isEmpty()) {
        ui->Signup_Comfirm_Password_Error_Label->setText("Please fill out this field");
        has_error = 1;

    }
    if(Password_Inp.compare(Comfirm_Password_Inp) != 0) {
        ui->Signup_Comfirm_Password_Inp->clear();
        ui->Signup_Comfirm_Password_Error_Label->setText("Passwords don't match");
        has_error = 1;
    }
    //Regex Name:
    string nameTemp = firstName_Inp+ lastName_Inp;
    for(int i = 0; i < nameTemp.size(); i++)  {
        if(!((nameTemp[i] >= 65 && nameTemp[i] <= 90) || (nameTemp[i] >= 97 && nameTemp[i] <= 122))) {
            ui->Signup_Name_Error_Label->setText(("First name, last name must contain alpha characters"));
        }
    }
    // Regex PhoneNum:
    if(PhoneNum_Inp.size() != 10 && PhoneNum_Inp.size() != 0) {
        ui->Signup_PhoneNum_Error_Label->setText("Phone Number is not valid");
        has_error = 1;
    }else {
        for(int i = 0; i < PhoneNum_Inp.size(); i++) {
            int j = PhoneNum_Inp[i];
            if(!(j >= 48 && j <= 57)) {
                ui->Signup_PhoneNum_Error_Label->setText("Field Phone Number must be Numberic");
                has_error = 1;
                break;
            }
        }
    }
    // Regex Password
    if(((Password_Inp.size() <6 || Password_Inp.size() >12)&& Password_Inp.size()!= 0)) {
        ui->Signup_Password_Error_Label->setText("Password must contain between 6 and 12 characters");
        has_error = 1;
    }
    for(int i = 0; i < Password_Inp.size();i ++) {
        int j = Password_Inp[i];
        if(!((j >= 33 && j <= 125))) {
            ui->Signup_Password_Error_Label->setText("Password must contain between 6 and 12 characters");
            has_error = 1;
            break;
        }
    }
    if(has_error != 1) {

        UserNode *Nodetemp = userManager->head;
        string Name = firstName_Inp + " " + lastName_Inp;
        User *u = new Customer(Name, PhoneNum_Inp, Password_Inp, "01/01/2023");

        while(Nodetemp) {
            int oke = 0;
            if(((*Nodetemp)["Name"] == u->getName()) && (((*Nodetemp)["Role"]) == u->getRole()) &&(((*Nodetemp)["PhoneNum"]) == u->getPhoneNum()) && (((*Nodetemp)["Password"]) == u->getPassword())) {
                ui->Signup_Error_Main_Label->setText("Account Already Exists");
                oke = 1;
            }else if(((*Nodetemp)["PhoneNum"] == u->getPhoneNum())||((*Nodetemp)["Password"] == u->getPassword())) {

                if((*Nodetemp)["PhoneNum"] == u->getPhoneNum()) {
                    ui->Signup_PhoneNum_Error_Label->setText("Phone number has already been taken");
                    oke = 1;
                }
                if((*Nodetemp)["Password"] == u->getPassword()) {
                    ui->Signup_Password_Error_Label->setText(("Password has already been taken"));
                    oke = 1;
                }

            }
            if(oke == 1) break;
            else {
                Nodetemp = Nodetemp->next;
            }
        }
        if(Nodetemp == NULL) {
            userManager->addUser(*u);
            this->user = u;

            this->user->setID(to_string(userManager->getCurrentID()));

            QMessageBox::information(this,"info",QString::fromStdString(user->getID()));
            ui->Main_Stacked_Widget->setCurrentIndex(2);
            ui->Account_Main_Widget->setCurrentIndex(0);
            renderMovie();
        }

    }
}

void App::on_Account_Menu_Btn_clicked()
{
    int width = ui->Account_Menu_Widget->width();
    int newWidth;
    if(width == 57) {
        newWidth = 180;
    }else {
        newWidth = 57;
    }
    QPropertyAnimation *animation= new QPropertyAnimation(ui->Account_Menu_Widget, "minimumWidth");
    animation->setDuration(250);
    animation->setStartValue(width);
    animation->setEndValue(newWidth);
    animation->setEasingCurve(QEasingCurve::InOutQuart);
    animation->start();
}

void App::on_Account_Setting_btn_clicked()
{
    ui->Account_Main_Widget->setCurrentIndex(3);
}

void App::renderMovie() {
    ui->Discovery_UserName_label->setText(QString::fromStdString(user->getName()));
    QLayout *layout = ui->Account_Discovery_List->layout();
    while (QLayoutItem *item = layout->takeAt(0)) {
        if (QWidget *widget = item->widget()) {
            widget->deleteLater();
        }
        delete item; // Xóa phần tử layout
    }
    ui->Account_Main_Widget->setCurrentIndex(0);
    MovieNode *temp = movieManager->head;
    int i = 0, j = 0;
    while(temp!= NULL) {
        this->createNewWidgets(i,j, temp->movie);
        if(j > 2) {
            j = 0;
            i++;

        } else {
            j++;
        }
        temp = temp->next;
    }
}

void App::renderMovieAdminPage(){
    QLayout *layout = ui->Admin_Edit_Page_Movie_list->layout();
    while (QLayoutItem *item = layout->takeAt(0)) {
        if (QWidget *widget = item->widget()) {
            widget->deleteLater();
        }
        delete item; // Xóa phần tử layout
    }
    MovieNode *temp = movieManager->head;
    while(temp){
        createMovieFrame(temp->movie);
        temp = temp->next;
    }
}

void App::renderShow(string movieID) {

    QLayout *layout = ui->Movie_Show_List->layout();
    while (QLayoutItem *item = layout->takeAt(0)) {
        if (QWidget *widget = item->widget()) {
            widget->deleteLater();
        }
        delete item; // Xóa phần tử layout
    }
    ui->Account_Main_Widget->setCurrentIndex(1);
    ShowNode *temp = showManager->head;
    while(temp!= NULL) {
        if((*temp)["MovieID"] == movieID) {
            createNewShowWidgets(temp->show);
        }
        temp = temp->next;
    }
}

void App::on_Account_Discovery_btn_clicked()
{
    renderMovie();
    ui->Discovery_UserName_label->setText(QString::fromStdString(user->getName()));

}

void App::on_Account_Setting_Btn_clicked()
{

    UserNode *temp = userManager->head;
    ui->Account_Setting_Old_Setting_Error->clear();

    string PhoneNum_Inp = ui->Account_Setting_User_PhoneNum->text().trimmed().toStdString();
    string Password_Inp = ui->Account_Setting_User_Password->text().trimmed().toStdString();
    string newPhoneNum_Inp = ui->Account_Setting_User_PhoneNum_2->text().trimmed().toStdString();
    string newName_Inp = ui->Account_Setting_User_Name->text().trimmed().toStdString();
    string newPassword_Inp = ui->Account_Setting_User_Password_2->text().trimmed().toStdString();
    string oldPhoneNum = user->getPhoneNum();
    string oldPassword = user->getPassword();
    int has_error = 0;

    if(newPhoneNum_Inp.empty()||newName_Inp.empty() ||newPassword_Inp.empty() ) {
        ui->Account_Setting_New_Setting_Error->setText("Please fill out all the field");
        has_error = 1;
        ui->Account_Setting_User_PhoneNum_2->clear();
        ui->Account_Setting_User_Name->clear();
        ui->Account_Setting_User_Password_2->clear();
    }


    //Regex Name:

    for(int i = 0; i < newName_Inp.size(); i++)  {
        if((!((newName_Inp[i] >= 65 && newName_Inp[i] <= 90) || (newName_Inp[i] >= 97 && newName_Inp[i] <= 122))) && (newName_Inp[i]!= 32)) {
            ui->Account_Setting_New_Setting_Error->setText(("Name must contain alpha characters"));
            has_error = 1;
            break;
        }
    }
    // Regex PhoneNum:
    if(newPhoneNum_Inp.size() != 10 && newPhoneNum_Inp.size() != 0) {
        ui->Account_Setting_New_Setting_Error->setText("Phone Number is not valid");
        has_error = 1;
    }else {
        for(int i = 0; i < newPhoneNum_Inp.size(); i++) {
            int j = newPhoneNum_Inp[i];
            if(!(j >= 48 && j <= 57)) {
                ui->Account_Setting_New_Setting_Error->setText("Field Phone Number must be Numberic");
                has_error = 1;
                break;
            }
        }
    }
    // Regex Password
    if(((newPassword_Inp.size() <6 || newPassword_Inp.size() >12)&& newPassword_Inp.size()!= 0)) {
        ui->Account_Setting_New_Setting_Error->setText("Password must contain between 6 and 12 characters");
        has_error = 1;
    }
    for(int i = 0; i < newPassword_Inp.size();i ++) {
        int j = newPassword_Inp[i];
        if(!((j >= 33 && j <= 125))) {
            ui->Account_Setting_New_Setting_Error->setText("Password must contain between 6 and 12 characters");
            has_error = 1;
            break;
        }
    }
    if(has_error != 1) {

        UserNode *Nodetemp = userManager->head;
        string Name = newName_Inp;
        User *u = new Customer(Name, newPhoneNum_Inp, newPassword_Inp, "01/01/2023");

        while(Nodetemp) {
            int oke = 0;
            if(((*Nodetemp)["Name"] == u->getName()) && (((*Nodetemp)["Role"]) == u->getRole()) &&(((*Nodetemp)["PhoneNum"]) == u->getPhoneNum()) && (((*Nodetemp)["Password"]) == u->getPassword())) {
                ui->Account_Setting_New_Setting_Error->setText("Account Already Exists");
                oke = 1;
            }else if(((*Nodetemp)["PhoneNum"] == u->getPhoneNum())||((*Nodetemp)["Password"] == u->getPassword())) {

                if(((*Nodetemp)["PhoneNum"] == u->getPhoneNum()) &&( (*Nodetemp)["PhoneNum"] != oldPhoneNum)) {
                    ui->Account_Setting_New_Setting_Error->setText("Phone number has already been taken");
                    oke = 1;
                }
                if(((*Nodetemp)["Password"] == u->getPassword()) &&((*Nodetemp)["Password"] != oldPassword) ) {
                    ui->Account_Setting_New_Setting_Error->setText(("Password has already been taken"));
                    oke = 1;
                }

            }
            if(oke == 1) break;
            else {
                Nodetemp = Nodetemp->next;
            }
        }
        if(Nodetemp == NULL) {
            while(temp!= NULL) {
                if((*temp)["PhoneNum"] == oldPhoneNum && (*temp)["Password"] == oldPassword) {
                    User newSetting((*temp)["ID"],newName_Inp, (*temp)["Role"], newPhoneNum_Inp,newPassword_Inp,(*temp)["Status"], (*temp)["CreatedDate"]);
                    (*temp).user.editInfo(newSetting);
                    *user = (*temp).user;
                    ui->Account_Setting_User_Password_2->clear();
                    ui->Account_Setting_User_Name->clear();
                    ui->Account_Setting_User_PhoneNum_2->clear();
                    ui->Account_Setting_User_Password->clear();
                    ui->Account_Setting_User_PhoneNum->clear();
                    ui->Account_Setting_New_Setting_Error->clear();
                    break;
                }
                temp = temp->next;
            }
            if(temp == NULL)  QMessageBox::information(this, "info", "Your info hasn't been edited!");
        }


    }





    if(oldPhoneNum != PhoneNum_Inp || oldPassword != Password_Inp) {
        ui->Account_Setting_Old_Setting_Error->setText("Your informations are not match");

    }

}

void App::on_Book_Ticket_Btn_clicked()
{
    QFrame *frame = ui->Book_Ticket_Show_Hall_Seat;
    for(QObject *child : frame->children()) {
        if(QPushButton *button = qobject_cast<QPushButton*> (child)){
            if(button->isChecked()){
                std::string seatName = button->objectName().toStdString();
                std::istringstream  s(seatName);
                std::string temp;
                getline(s,temp, '_' );
                getline(s,temp, '_' );
                string sRow = temp;
                getline(s,temp,'_');
                string sCol = temp;
                getline(s,temp,'_');
                string showID = temp;

                QDate currentDate = QDate::currentDate();
                QString dateString = currentDate.toString("yyyy-dd-MM");
                string bookedDate = dateString.toStdString();

                Ticket newTicket("100.000","1",showID,"normal",bookedDate,sRow,sCol,this->user->getID());
                User *u = new Customer(this->user->getName(),this->user->getPhoneNum(),this->user->getPassword(),this->user->getCreatedDate());
                u->BookTicket(*ticketManager,newTicket);
                ui->Book_Ticket_Btn->setDisabled(true);
                ui->Book_Ticket_Btn->setStyleSheet("font-size: 18px;background-color:#ae0922;font-weight: 700;color: #fff;border-radius: 5px;margin-bottom: 5px;");
                button->setChecked(false);
            }
        }
    }
}

void App::on_Account_My_Booking_btn_clicked()
{
    ui->Account_Main_Widget->setCurrentIndex(2);
    QLayout *layout = ui->My_Booking_List->layout();
    while (QLayoutItem *item = layout->takeAt(0)) {
        if (QWidget *widget = item->widget()) {
            widget->deleteLater();
        }
        delete item; // Xóa phần tử layout
    }
    renderMyBooking(user->getID());


}

void App::on_Account_Logout_btn_clicked()
{
    ui->Login_Password_Inp->clear();
    ui->Login_PhoneNum_Inp->clear();
    ui->Login_Error->clear();
    ui->Main_Stacked_Widget->setCurrentIndex(0);
}

void App::on_Admin_Menu_btn_clicked()
{
    int width = ui->Admin_Menu_Widget->width();
    int newWidth;
    if(width == 57) {
        newWidth = 180;
    }else {
        newWidth = 57;
    }
    QPropertyAnimation *animation= new QPropertyAnimation(ui->Admin_Menu_Widget, "minimumWidth");
    animation->setDuration(250);
    animation->setStartValue(width);
    animation->setEndValue(newWidth);
    animation->setEasingCurve(QEasingCurve::InOutQuart);
    animation->start();
}

void App::on_Admin_My_Movie_btn_clicked()
{
    ui->Admin_Main_StackWidget->setCurrentIndex(1);
    ui->Admin_Show_Edit_Btn->show();
    ui->Admin_Show_Edit_Save_btn->show();
    renderMovieAdminPage();
}

void App::on_Admin_Logout_btn_clicked()
{
    ui->Login_Password_Inp->clear();
    ui->Login_PhoneNum_Inp->clear();
    ui->Login_Error->clear();
    ui->Main_Stacked_Widget->setCurrentIndex(0);
}

void App::on_Admin_Add_Movie_btn_clicked()
{
    ui->Admin_Main_StackWidget->setCurrentIndex(2);
    ui->Admin_Movie_MovieType_Input->clear();
    ui->Admin_Movie_Name_Input->clear();
    ui->Admin_Movie_Img_Input->clear();
    ui->Admin_Movie_Duration_Input->clear();
    ui->Admin_Movie_Des_Input->clear();

    QPushButton* editBtn = ui->Admin_Movie_Edit_Save_btn;
    connect(editBtn, &QPushButton::clicked, [this](){
        Admin admin(user->getName(),user->getPhoneNum(),user->getPassword(), user->getCreatedDate());
        string newMovieTypeName = ui->Admin_Movie_MovieType_Input->text().trimmed().toStdString();
        string newMovieName = ui->Admin_Movie_Name_Input->text().trimmed().toStdString();
        string newMovieDuration = ui->Admin_Movie_Duration_Input->text().trimmed().toStdString();
        string newMovieDes = ui->Admin_Movie_Des_Input->text().trimmed().toStdString();
        string newMovieImg = ui->Admin_Movie_Img_Input->text().trimmed().toStdString();
        Movie movie(to_string(movieManager->getCurrentID()),newMovieName,newMovieTypeName,newMovieDuration,newMovieImg, newMovieDes);
        admin.addMovie(*movieManager, movie);
        ui->Admin_Main_StackWidget->setCurrentIndex(1);
        renderMovieAdminPage();
    });

}

void App::addShowAdminBtnHandle(string movieID){
    ui->Admin_Show_Edit_error->clear();
    ui->Admin_Main_StackWidget->setCurrentIndex(4);
    QFrame *frame = ui->Admin_Show_Edit_Input_Field;
    QList<QRadioButton *> radioButtons = frame->findChildren<QRadioButton *>();
    for (QRadioButton *radio : radioButtons) {
        radio->setChecked(false);
    }
    QPushButton * showSaveBtn = ui->Admin_Show_Edit_Btn;
    QPushButton * button = ui->Admin_Show_Edit_Save_btn;
    button->hide();
    connect(showSaveBtn,&QPushButton::clicked,[this, movieID,button](){
        ui->Admin_Show_Edit_error->clear();
        QFrame *frame = ui->Admin_Show_Edit_Input_Field;
        QList<QRadioButton *> radioButtons = frame->findChildren<QRadioButton *>();
        string showStartTime, showEndTime;
        for (QRadioButton *radio : radioButtons) {
            if(radio->isChecked()){
                string radioName = radio->objectName().toStdString();
                if(radioName[0] == 'M'){
                    if(radioName[1]== '1'){
                        showStartTime = "7:00";
                        showEndTime = "9:00";
                    }else if(radioName[1]=='2'){
                        showStartTime = "9:00";
                        showEndTime = "11:00";
                    }

                }else if(radioName[0] == 'A'){
                    if(radioName[1]== '1'){
                        showStartTime = "13:00";
                        showEndTime = "15:00";
                    }else if(radioName[1]=='2'){
                        showStartTime = "15:00";
                        showEndTime = "17:00";
                    }

                }else if(radioName[0] == 'E'){
                    if(radioName[1]== '1'){
                        showStartTime = "18:00";
                        showEndTime = "20:00";
                    }else if(radioName[1]=='2'){
                        showStartTime = "20:00";
                        showEndTime = "22:00";
                    }
                }
            }
        }
        QDate currentDate = QDate::currentDate();
        QString dateString = currentDate.toString("yyyy-dd-MM");
        string showDate = dateString.toStdString();
        Show newShow(movieID,showStartTime,showEndTime,showDate,showDate);
        ShowNode *temp = showManager->head;
        bool has_error = false;
        while(temp){
            if(temp->show == newShow){
                ui->Admin_Show_Edit_error->setText("Show has been added");
                has_error = true;
                break;
            }
            temp = temp->next;
        }
        if(has_error == false){
            Admin admin(user->getName(),user->getPhoneNum(),user->getPassword(),user->getCreatedDate());
            admin.setID(to_string(userManager->getCurrentID()));
            admin.addShow(*showManager,newShow);
            ui->Admin_Show_Edit_error->clear();
            renderShowForAdminPage(movieID);
            button->show();
            ui->Admin_Main_StackWidget->setCurrentIndex(3);

        }
    });
}

void App::renderAdminTicketsChart(){
    QDate currentDate = QDate::currentDate();
    QString dateString = currentDate.toString("yyyy-dd-MM");
    string date5 = dateString.toStdString();

    string date4 = currentDate.addDays(-1).toString("yyyy-dd-MM").toStdString();
    string date3 = currentDate.addDays(-2).toString("yyyy-dd-MM").toStdString();
    string date2 = currentDate.addDays(-3).toString("yyyy-dd-MM").toStdString();
    string date1 = currentDate.addDays(-4).toString("yyyy-dd-MM").toStdString();

    QBarSet *set0 = new QBarSet ("New Customer");
    QBarSet *set2 = new QBarSet ("New Booking");
    *set0 << ticketManager->getQuantityOfDay(date1) << ticketManager->getQuantityOfDay(date2) << ticketManager->getQuantityOfDay(date3) << ticketManager->getQuantityOfDay(date4) << ticketManager->getQuantityOfDay(date5);
    *set2 << userManager->getQuantityOfDay(date1) << userManager->getQuantityOfDay(date2) << userManager->getQuantityOfDay(date3) << userManager->getQuantityOfDay(date4) << userManager->getQuantityOfDay(date5);
    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set2);
    QChart *chart  = new QChart();
    chart->addSeries(series);
    chart->setTitle("Cinema Analytics");
    chart->setAnimationOptions(QChart::AllAnimations);
    QStringList categories;
    categories << QString::fromStdString(date1) << QString::fromStdString(date2) << QString::fromStdString(date3) << QString::fromStdString(date4) << QString::fromStdString(date5);
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);

    QChartView *chartView = new QChartView(chart);


    // Đặt kích thước của QChartView
    chartView->resize(994, 576);
    chartView->setParent(ui->Admin_Dashboard_Chart);
    ui->Admin_Quatity_Movie_Count->setText(QString::number(movieManager->getSize()));
    ui->Admin_Quatity_Show_Count->setText(QString::number(showManager->getSize()));
    ui->Admin_Quatity_User_Count->setText(QString::number(userManager->getSize()));
    ui->Admin_Quatity_Ticket_Count->setText(QString::number(ticketManager->getSize()));
    ui->Admin_Current_Number_Booking_Count->setText(QString::number(ticketManager->getTodayTickets()));
    ui->Admin_Current_Money->setText(QString::number(ticketManager->getTodayTickets()*100000) + "đ");
    QCalendarWidget * calendar = ui->Admin_Calendar;

    connect(calendar,&QCalendarWidget::selectionChanged,[this,calendar](){
        string selectedDate = calendar->selectedDate().toString("yyyy-dd-MM").toStdString();
        int TicketCounter = ticketManager->getQuantityOfDay(selectedDate);
        ui->Admin_Current_Number_Booking_Count->setText(QString::number(TicketCounter));
        ui->Admin_Current_Money->setText(QString::number(TicketCounter *100000) + "đ");

    });
}

void App::on_Admin_Analystic_btn_clicked()
{
    renderAdminTicketsChart();
    ui->Admin_Main_StackWidget->setCurrentIndex(0);
}

void App::on_Account_Search_btn_clicked()
{
    ui->Discovery_UserName_label->setText(QString::fromStdString(user->getName()));
    QLayout *layout = ui->Account_Discovery_List->layout();
    while (QLayoutItem *item = layout->takeAt(0)) {
        if (QWidget *widget = item->widget()) {
            widget->deleteLater();
        }
        delete item; // Xóa phần tử layout
    }
    ui->Account_Main_Widget->setCurrentIndex(0);
    string input = toLower(ui->Account_Search_Inp->text().trimmed().toStdString());
    MovieNode* temp = movieManager->head;
    int i = 0, j = 0;
    while(temp){
        if(toLower((*temp)["movieName"]) == input){
            this->createNewWidgets(i,j,temp->movie);
            if(j > 2) {
                j = 0;
                i++;

            } else {
                j++;
            }
        }
        temp = temp->next;
    }


}

void App::on_Admin_My_User_btn_clicked()
{
    ui->Admin_Main_StackWidget->setCurrentIndex(5);
    renderUserForAdminPage();
}


