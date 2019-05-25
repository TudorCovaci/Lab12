#include <QtWidgets>
#include "Controller.h"
#include "GUI_User.h"
#include "GUI_Admin.h"
void DisplayMovies(QLayout* adminWindow)
{
	QWidget* listAll = new QWidget;
	QVBoxLayout* vLayout = new QVBoxLayout;
	listAll->setLayout(vLayout);
	QLabel* moviesLabel = new QLabel("&Movies");
	QListWidget* moviesList = new QListWidget;
	moviesLabel->setBuddy(moviesList);
	vLayout->addWidget(moviesLabel);
	vLayout->addWidget(moviesList);
	
	adminWindow->addWidget(listAll);

}
void MovieInfoInput(QLayout* adminWindow)
{
	QWidget* inputWidget = new QWidget();
	
	QFormLayout* formLayout = new QFormLayout;
	QLabel* titleLabel = new QLabel("&Title");
	QLineEdit* titleTextBox = new QLineEdit();
	titleLabel->setBuddy(titleTextBox);
	QLabel* genreLabel = new QLabel("&Genre");
	QLineEdit* genreTextBox = new QLineEdit();
	genreLabel->setBuddy(genreTextBox);
	QLabel* yearLabel = new QLabel("&Year of Release");
	QLineEdit* yearTextBox = new QLineEdit();
	yearLabel->setBuddy(yearTextBox);
	QLabel* likesLabel = new QLabel("&Number of likes");
	QLineEdit* likesTextBox = new QLineEdit();
	likesLabel->setBuddy(likesTextBox);
	QLabel* trailerLabel = new QLabel("&Trailer");
	QLineEdit* trailerTextBox = new QLineEdit();
	trailerLabel->setBuddy(trailerTextBox);
	formLayout->addRow(titleLabel, titleTextBox);
	formLayout->addRow(genreLabel, genreTextBox);
	formLayout->addRow(yearLabel, yearTextBox);
	formLayout->addRow(likesLabel, likesTextBox);
	formLayout->addRow(trailerLabel, trailerTextBox);
	formLayout->addRow(titleLabel, titleTextBox);
	inputWidget->setLayout(formLayout);
	adminWindow->addWidget(inputWidget);

}
void AdminButtons(QLayout* adminWindow)
{
	QGridLayout* gridLayout = new QGridLayout;
	QWidget* buttonsWidget = new QWidget;
	buttonsWidget->setLayout(gridLayout);
	QPushButton* addButton = new QPushButton("&Add");
	QPushButton* deleteButton = new QPushButton("&Delete");
	QPushButton* updateButton = new QPushButton("&Update");
	QPushButton* filterButton = new QPushButton("&Filter");
	gridLayout->addWidget(addButton);
	gridLayout->addWidget(deleteButton);
	gridLayout->addWidget(updateButton);
	gridLayout->addWidget(filterButton);
	adminWindow->addWidget(buttonsWidget);

}


void MyList(QLayout* userWindow)
{
	QVBoxLayout* hLayout = new QVBoxLayout;
	QWidget* myListWidget = new QWidget;
	myListWidget->setLayout(hLayout);
	QListWidget* myList = new QListWidget;
	QLabel* myListLabel = new QLabel("My list");
	myListLabel->setBuddy(myList);
	hLayout->addWidget(myListLabel);
	hLayout->addWidget(myList);
	userWindow->addWidget(myListWidget);

}
void AddToMyListButton(QLayout* layout)
{
	QPushButton* addToMyListButton = new QPushButton(">");
	layout->addWidget(addToMyListButton);
}
void UserButtons(QLayout* layout)
{
	QGridLayout* gridLayout = new QGridLayout;
	QWidget* userButtons = new QWidget;
	userButtons->setLayout(gridLayout);
	QPushButton* nextButton = new QPushButton("&Next");
	QPushButton* playButton = new QPushButton("&Play Trailer");
	gridLayout->addWidget(playButton);
	gridLayout->addWidget(nextButton);
	layout->addWidget(userButtons);
	
}


int main(int argc, char** argv)
{
	
	
	MovieRepo* repo = new MovieRepo;;
	Validator* validator = new Validator();
	Controller* controller = new Controller(repo,validator);
	controller->setFilePath("D:\\Facultate\\Semestrul 2\\OOP\\movies.txt");
	controller->readFromFile();
	QApplication app(argc, argv);
	QWidget* mainWindow = new QWidget;
	QHBoxLayout* mainLayout = new QHBoxLayout;
	mainWindow->setLayout(mainLayout);
	app.setApplicationName("Movie Database");
	GUI_Admin* adminHalf = new GUI_Admin(controller);
	GUI_User* userHalf = new GUI_User(adminHalf, controller);
	mainLayout->addWidget(adminHalf);
	mainLayout->addWidget(userHalf);	
	mainWindow->show();
	return app.exec();

}
