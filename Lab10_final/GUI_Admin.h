#pragma once
#include <QtWidgets>
#include "Controller.h"

class GUI_Admin :public QWidget
{
	Q_OBJECT
private:
	QListWidget* moviesList_;
	QLineEdit* titleTextBox_;
	QLineEdit* genreTextBox_;
	QLineEdit* yearTextBox_;
	QLineEdit* likesTextBox_;
	QLineEdit* trailerTextBox_;
	QLineEdit* newTitleTextBox_;
	QLineEdit* newGenreTextBox_;
	QLineEdit* newYearTextBox_;
	QLineEdit* newLikesTextBox_;
	QLineEdit* newTrailerTextBox_;
	QPushButton* addButton_;
	QPushButton* deleteButton_;
	QPushButton* updateButton_;
	QPushButton* updateMovieButton_;
	QPushButton* cancelButton_;
	
	Controller* controller_;
	QWidget* updateWindow_;
public:
	GUI_Admin(QWidget* parent = Q_NULLPTR) {}
	GUI_Admin(const GUI_Admin& admin) {}
	GUI_Admin(Controller* controller);
	QListWidgetItem* getSelectedItem();

private:
	std::vector<std::string> tokenize(std::string line);
	void display();
	void connectSignalsAndSlots();
	void addMovieButtonHandler();
	void deleteMovieButtonHandler();
	void updateMovieButtonHandler();
	void updateButtonHandler();
	void initGUI();

signals:
	void moviesUpdatedSignal();
	void addMovieSignal(std::string& title, std::string& genre,
		std::string& yearOfRelease, std::string& numberOfLikes,
		std::string& link);
public slots:
	void addMovie(std::string& title, std::string& genre,
		std::string& yearOfRelease, std::string& numberOfLikes,
		std::string& link);
	void updateMovie(std::string& title, std::string& newGenre,
		std::string& newYearOfRelease, std::string& newNumberOfLikes,
		std::string& newLink);
};