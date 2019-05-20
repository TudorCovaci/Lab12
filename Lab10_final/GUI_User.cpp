#include "GUI_User.h"
//GUIMyListDisplay::GUIMyListDisplay(QLayout* parent)
//{
//
//	QVBoxLayout* verticalLayout = new QVBoxLayout;
//	this->setLayout(verticalLayout);
//	QLabel* myListLabel = new QLabel("&My list");
//	myListDisplay_ = new QListWidget;
//	myListLabel->setBuddy(myListDisplay_);
//	verticalLayout->addWidget(myListLabel);
//	verticalLayout->addWidget(myListDisplay_);
//	parent->addWidget(this);
//}
//GUI_User::GUI_User(Controller* controller)
//{
//	controller_ = controller;
//	myList_ = new MovieRepo;
//	
//	myListDisplay_ = new GUIMyListDisplay(this);
//	userButtons_ = new GUIUserButtons(this);
//}
//GUIUserButtons::GUIUserButtons(QLayout* parent)
//{
//	QHBoxLayout* horizontalLayout = new QHBoxLayout;
//	this->setLayout(horizontalLayout);
//	playButton_ = new QPushButton("Play");
//	nextButton_ = new QPushButton("Next");
//	horizontalLayout->addWidget(playButton_);
//	horizontalLayout->addWidget(nextButton_);
//	parent->addWidget(this);
//}
#include <sstream>
GUI_User::GUI_User(GUI_Admin* adminGUI)
{
	adminGUI_ = adminGUI;
	myList_ = new MovieRepo;
	Validator* validator = new Validator;
	myListController_ = new Controller(myList_, validator);
	myListController_->setFilePath("D:\\Facultate\\Semestrul 2\\OOP\\myList.csv");
	initGUI();
	connectSignalsAndSlots();
	display();
}
void GUI_User::initGUI()
{
	QHBoxLayout* horizontalLayout = new QHBoxLayout;
	this->setLayout(horizontalLayout);
	saveButton_ = new QPushButton("&>");
	horizontalLayout->addWidget(saveButton_);
	QWidget* myListPart = new QWidget;
	QVBoxLayout* verticalLayout = new QVBoxLayout;
	myListPart->setLayout(verticalLayout);
	QLabel* myListLabel = new QLabel("&My list");
	myListWidget_ = new QListWidget;
	myListLabel->setBuddy(myListWidget_);
	verticalLayout->addWidget(myListLabel);
	verticalLayout->addWidget(myListWidget_);
	playButton_ = new QPushButton("&Play");
	verticalLayout->addWidget(playButton_);
	horizontalLayout->addWidget(myListPart);

}
void GUI_User::connectSignalsAndSlots()
{
	QObject::connect(this, &GUI_User::myListUpdatedSignal, this, &GUI_User::display);
	QObject::connect(saveButton_, &QPushButton::clicked, this, &GUI_User::saveButtonHandler);

}
void GUI_User::display()
{
	if (myListWidget_->count() > 0)
		myListWidget_->clear();

	for (auto movie : myList_->getElements())
	{

		QListWidgetItem* newItem = new QListWidgetItem;
		QString newString = QString::fromStdString(movie.toString());
		newItem->setText(newString);
		myListWidget_->addItem(newItem);
	}
}
std::vector<std::string> GUI_User::tokenize(std::string line)
{
	std::vector<std::string> result;
	std::stringstream ss(line);
	std::string token;
	while (std::getline(ss, token, ','))
		result.push_back(token);
	return result;
}
void GUI_User::addMovieToMyList(std::string& title, std::string& genre,
	std::string& yearOfRelease, std::string& numberOfLikes,
	std::string& link)	
{
	
	myListController_->AddMovieToRepo(title, genre, yearOfRelease, numberOfLikes, link);
	
	emit myListUpdatedSignal();
}
void GUI_User::saveButtonHandler()
{
	QListWidgetItem* newItem = adminGUI_->getSelectedItem();
	QString details = newItem->text();
	std::vector<std::string> tokens = tokenize(details.toStdString());
	if (tokens.size() != 5)
		throw std::exception("Invalid selection!\n");
	emit addMovieToMyList(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4]);
}