#ifndef MWINDOW_H
#define MWINDOW_H

#include <QWidget>
#include <QtWidgets>

#include "mydictionary.h"
#include "addingwindow.h"

class MWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MWindow(QWidget *parent = 0);

private:
    MyDictionary _dictionary;

    //--- UI
    //Виджет с словами
    QListWidget* _teWordsView;

    //Выпадающии списки языка с на
    QComboBox* _cbFromLenguage;
    QComboBox* _cbToLenguage;

    //Поле поиска
    QLineEdit* _leWordSearch;

    void loadWordsToView(MyWord::Language fromLanguage, MyWord::Language toLanguage, QString searchWord = "");

private slots:
    //При нажимании на кнопку "Удалить", будет вызвана эта ф-я - слот
    void btDeleteWordPressed();

    //При нажимании на кнопку "Добавить", будет вызвана эта ф-я - слот
    void btAddWordPressed();

    void reloadWordsView();

    void searchTextChanged(QString changedText); //Когда меняется текст в эдите, вызывается эта ф-я

public slots:
    void addTranslation(QString wordToAdd, QString translatedWordToAdd); //Вызывается, когда в окне добавления нажимают кнопку добавления
};

#endif // MWINDOW_H
