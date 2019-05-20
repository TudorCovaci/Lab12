#include "GUI_Admin.h"
#include <sstream>
#include "qdialog.h"
std::vector<std::string> GUI_Admin::tokenize(std::string line)
{
	std::vector<std::string> result;
	std::stringstream ss(line);
	std::string token;
	while (std::getline(ss, token, ','))
		result.push_back(token);
	return result;
}
GUI_Admin::GUI_Admin(Controller* controller)
{
	controller_ = controller;
	initGUI();
	connectSignalsAndSlots();
	display();

}
void GUI_Admin::initGUI()
{
	//movie list
	QVBoxLayout* vertLayout = new QVBoxLayout;
	this->setLayout(vertLayout);
	QLabel* moviesLabel = new QLabel("&Movies");
	moviesList_ = new QListWidget;
	moviesLabel->setBuddy(moviesList_);
	vertLayout->addWidget(moviesLabel);
	vertLayout->addWidget(moviesList_);

	//text boxes
	QFormLayout* formLayout = new QFormLayout;
	QWidget* textBoxes = new QWidget;
	textBoxes->setLayout(formLayout);
	titleTextBox_ = new QLineEdit;
	genreTextBox_ = new QLineEdit;
	yearTextBox_ = new QLineEdit;
	likesTextBox_ = new QLineEdit;
	trailerTextBox_ = new QLineEdit;
	QLabel* titleLabel = new QLabel("&Title");
	titleLabel->setBuddy(titleTextBox_);
	QLabel* genreLabel = new QLabel("&Genre");
	genreLabel->setBuddy(genreTextBox_);
	QLabel* yearLabel = new QLabel("&Year of release");
	yearLabel->setBuddy(yearTextBox_);
	QLabel* likesLabel = new QLabel("&Number of likes");
	likesLabel->setBuddy(likesTextBox_);
	QLabel* trailerLabel = new QLabel("&Trailer");
	trailerLabel->setBuddy(trailerTextBox_);
	formLayout->addRow(titleLabel, titleTextBox_);
	formLayout->addRow(genreLabel, genreTextBox_);
	formLayout->addRow(yearLabel, yearTextBox_);
	formLayout->addRow(likesLabel, likesTextBox_);
	formLayout->addRow(trailerLabel, trailerTextBox_);
	vertLayout->addWidget(textBoxes);

	//buttons
	QGridLayout* gridLayout = new QGridLayout;
	QWidget* buttons = new QWidget;
	buttons->setLayout(gridLayout);
	addButton_ = new QPushButton("&Add");
	deleteButton_ = new QPushButton("&Delete");
	updateButton_ = new QPushButton("&Update");	
	gridLayout->addWidget(addButton_);
	gridLayout->addWidget(deleteButton_);
	gridLayout->addWidget(updateButton_);
	vertLayout->addWidget(buttons);
}
void GUI_Admin::display()
{
	if (moviesList_->count() > 0)
		moviesList_->clear();

	for (auto movie: controller_->getRepo()->getElements())
	{
		
		
		QListWidgetItem* newItem = new QListWidgetItem;
		QString newString = QString::fromStdString(movie.toString());
		newItem->setText(newString);
		moviesList_->addItem(newItem);
	}


}
void GUI_Admin::connectSignalsAndSlots()
{
	QObject::connect(this, &GUI_Admin::moviesUpdatedSignal, this, &GUI_Admin::display);
	QObject::connect(addButton_, &QPushButton::clicked, this, &GUI_Admin::addMovieButtonHandler);
	QObject::connect(deleteButton_, &QPushButton::clicked, this, &GUI_Admin::deleteMovieButtonHandler);
	QObject::connect(updateButton_, &QPushButton::clicked, this, &GUI_Admin::updateMovieButtonHandler);
}
void GUI_Admin::addMovie(std::string& title, std::string& genre,
	std::string& yearOfRelease, std::string& numberOfLikes,
	std::string& link)
{
	controller_->AddMovieToRepo(title, genre, yearOfRelease, numberOfLikes, link);
	emit moviesUpdatedSignal();
}
void GUI_Admin::updateMovie(std::string& title, std::string& newGenre,
	std::string& newYearOfRelease, std::string& newNumberOfLikes,
	std::string& newLink)
{
	bool response;
	response = controller_->UpdateMovie(title, newGenre, newYearOfRelease, newNumberOfLikes, newLink);
	QMessageBox* dialog = new QMessageBox;
	if (response == true)
	{
		dialog->setText("Movie updated");
		dialog->show();
		emit moviesUpdatedSignal();
	}
	else {
		dialog->setText("Update failed");
		dialog->show();
	}
	updateWindow_->close();
}
void GUI_Admin::addMovieButtonHandler()
{
	QString title = titleTextBox_->text();
	
	QString genre = genreTextBox_->text();
	QString yearOfRelease = yearTextBox_->text();
	QString numberOfLikes = likesTextBox_->text();
	QString link = trailerTextBox_->text();
	titleTextBox_->clear();
	genreTextBox_->clear();
	yearTextBox_->clear();
	likesTextBox_->clear();
	trailerTextBox_->clear();
	emit addMovie(title.toStdString(), genre.toStdString()
		, yearOfRelease.toStdString(), numberOfLikes.toStdString()
		, link.toStdString());
}
void GUI_Admin::deleteMovieButtonHandler()
{
	QListWidgetItem* newItem = moviesList_->currentItem();
	QString details = newItem->text();
	std::vector<std::string> tokens = tokenize(details.toStdString());
	controller_->RemoveMovie(tokens[0]);
	emit moviesUpdatedSignal();
}
void GUI_Admin::updateMovieButtonHandler()
{
	updateWindow_ = new QWidget;
	QFormLayout* formLayout = new QFormLayout;
	updateWindow_->setLayout(formLayout);
	QLabel* titleLabel = new QLabel("&Title");
	QLabel* genreLabel = new QLabel("&New genre");
	QLabel* yearLabel = new QLabel("&New year of release");
	QLabel* likesLabel = new QLabel("&New number of likes");
	QLabel* trailerLabel = new QLabel("&New trailer link");
	newTitleTextBox_ = new QLineEdit;
	newGenreTextBox_ = new QLineEdit;
	newYearTextBox_ = new QLineEdit;
	newLikesTextBox_ = new QLineEdit;
	newTrailerTextBox_ = new QLineEdit;
	updateMovieButton_ = new QPushButton("&Update");
	cancelButton_ = new QPushButton("&Cancel");
	QObject::connect(updateMovieButton_, &QPushButton::clicked, this, &GUI_Admin::updateButtonHandler);
	QObject::connect(cancelButton_, &QPushButton::clicked, updateWindow_, &QWidget::close);
	titleLabel->setBuddy(newTitleTextBox_);
	genreLabel->setBuddy(newGenreTextBox_);
	yearLabel->setBuddy(newYearTextBox_);
	likesLabel->setBuddy(newLikesTextBox_);
	trailerLabel->setBuddy(newTrailerTextBox_);
	formLayout->addRow(titleLabel,newTitleTextBox_);
	formLayout->addRow(genreLabel, newGenreTextBox_);
	formLayout->addRow(yearLabel, newYearTextBox_);
	formLayout->addRow(likesLabel, newLikesTextBox_);
	formLayout->addRow(trailerLabel, newTrailerTextBox_);
	formLayout->addRow(updateMovieButton_, cancelButton_);
	updateWindow_->show();
}
void GUI_Admin::updateButtonHandler()
{
	QString title = newTitleTextBox_->text();
	QString newGenre = newGenreTextBox_->text();
	QString newYear = newYearTextBox_->text();
	QString newLikes = newLikesTextBox_->text();
	QString newTrailer = newTrailerTextBox_->text();
	emit updateMovie(title.toStdString(), newGenre.toStdString(),
		newYear.toStdString(), newLikes.toStdString(),
		newTrailer.toStdString());

}
QListWidgetItem*  GUI_Admin::getSelectedItem()
{
	return moviesList_->currentItem();
}