#include "GUI_User.h"

#include <sstream>
GUI_User::GUI_User(GUI_Admin* adminGUI, Controller* controller)
{
	controller_ = controller;
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
	openFilterPageButton_ = new QPushButton("&Filter");
	verticalLayout->addWidget(playButton_);
	verticalLayout->addWidget(openFilterPageButton_);
	horizontalLayout->addWidget(myListPart);

}
void GUI_User::connectSignalsAndSlots()
{

	QObject::connect(this, &GUI_User::myListUpdatedSignal, this, &GUI_User::display);
	QObject::connect(saveButton_, &QPushButton::clicked, this, &GUI_User::saveButtonHandler);
	QObject::connect(openFilterPageButton_, &QPushButton::clicked, this, &GUI_User::openFilterPageButtonHandler);
	QObject::connect(playButton_, &QPushButton::clicked, this, &GUI_User::playButtonHandler);

	
}
void GUI_User::openFilterPageButtonHandler()
{
	QHBoxLayout* hLayout = new QHBoxLayout;
	QWidget* filterPage = new QWidget;
	filterPage->setLayout(hLayout);
	QWidget* filterWidget = new QWidget;
	QFormLayout* formLayout = new QFormLayout;
	filterWidget->setLayout(formLayout);
	QLabel* genreLabel = new QLabel("&Genre");
	QLabel* likesLabel = new QLabel("&Number of likes");
	genreLineEdit_ = new QLineEdit;
	likesLineEdit_ = new QLineEdit;
	genreLabel->setBuddy(genreLineEdit_);
	likesLabel->setBuddy(likesLineEdit_);
	filterButton_ = new QPushButton("&Filter");
	QObject::connect(filterButton_, &QPushButton::clicked, this, &GUI_User::filterButtonHandler);
	formLayout->addRow(genreLabel, genreLineEdit_);
	formLayout->addRow(likesLabel, likesLineEdit_);
	formLayout->addWidget(filterButton_);
	filterListWidget_ = new QListWidget;
	hLayout->addWidget(filterWidget);
	hLayout->addWidget(filterListWidget_);
	filterPage->show();
	
}
void GUI_User::filterButtonHandler()
{
	QString genre = genreLineEdit_->text();
	QString likes = likesLineEdit_->text();
	std::vector<Movie> filteredVector = controller_->filterByGenreAndLikes(genre.toStdString(), likes.toStdString());
	for (auto movie : filteredVector)
	{
		QListWidgetItem* item =  new QListWidgetItem;
		QString itemText = QString::fromStdString(movie.toString());
		item->setText(itemText);
		filterListWidget_->addItem(item);
	}
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
std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}
void GUI_User::playButtonHandler()
{
	QListWidgetItem* newItem = myListWidget_->currentItem();
	QString details = newItem->text();
	std::vector<std::string> tokens = tokenize(details.toStdString());
	if (tokens.size() != 5)
		throw std::exception("Invalid selection!\n");
	std::string path = "C:\\Users\\Tudor\\AppData\\Local\\Programs\\Opera\\launcher.exe ";
	path += tokens[4];
	ShellExecute(0, 0, s2ws(tokens[4]).c_str(), 0, 0, SW_SHOW);
	//system(path.c_str());
}