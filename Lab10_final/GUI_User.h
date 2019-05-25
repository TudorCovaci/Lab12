#pragma once
#include <QtWidgets>
#include "Controller.h"
//class GUIMyListDisplay : public QWidget
//{
//private:
//	QListWidget* myListDisplay_;
//public:
//	GUIMyListDisplay(QWidget* parent = Q_NULLPTR) {}
//	GUIMyListDisplay(const GUIMyListDisplay& myListDisplay) {}
//	GUIMyListDisplay(QLayout* parent);
//	void Display(Controller* myListController);
//};
//class GUIUserButtons : public QWidget
//{
//private:
//	QPushButton* playButton_;
//	QPushButton* nextButton_;
//public:
//	GUIUserButtons(QWidget* parent = Q_NULLPTR) {}
//	GUIUserButtons(const GUIUserButtons& userButtons) {}
//	GUIUserButtons(QLayout* parent);
//
//};
//class GUI_User :public QVBoxLayout
//{
//private:
//	Controller* controller_;
//	Controller* myListController_;
//	MovieRepo* myList_;
//	GUIMyListDisplay* myListDisplay_;
//	GUIUserButtons* userButtons_;
//public:
//	GUI_User(QWidget* parent = Q_NULLPTR) {}
//	GUI_User(const GUI_User& guiUser) {}
//	GUI_User(Controller* controller);
//};
#include "GUI_Admin.h"
class GUI_User : public QWidget
{
	Q_OBJECT
private:
	MovieRepo* myList_;
	QListWidget* myListWidget_;
	QListWidget* filterListWidget_;
	QPushButton* saveButton_;
	QPushButton* playButton_;
	QPushButton* openFilterPageButton_;
	QPushButton* filterButton_;
	Controller* myListController_;
	QLineEdit* genreLineEdit_;
	QLineEdit* likesLineEdit_;
	GUI_Admin* adminGUI_;
	Controller* controller_;
public:
	GUI_User(QWidget* parent = Q_NULLPTR) {}
	GUI_User(const GUI_User& guiUser) {}
	GUI_User(GUI_Admin* adminGUI, Controller* controller);
private:
	void display();
	void connectSignalsAndSlots();
	void initGUI();
	void saveButtonHandler();
	void openFilterPageButtonHandler();
	void filterButtonHandler();
	void playButtonHandler();
	std::vector<std::string> tokenize(std::string line);
signals:
	void myListUpdatedSignal();
	void addMovieToMyListSignal(std::string& title, std::string& genre,
		std::string& yearOfRelease, std::string& numberOfLikes,
		std::string& link);
public slots:
	void addMovieToMyList(std::string& title, std::string& genre,
		std::string& yearOfRelease, std::string& numberOfLikes,
		std::string& link);


};