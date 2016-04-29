#include "addingwindow.h"

AddingWindow::AddingWindow()
{
    //Мейновый лайаут
    QVBoxLayout* mainLayout = new QVBoxLayout();
    this->setLayout(mainLayout);

    //Слово
    QLabel* lWord = new QLabel("Слово:");
    mainLayout->addWidget(lWord);

    //Строка ввода нового слова
    _leWordToAdd = new QLineEdit();
    mainLayout->addWidget(_leWordToAdd);

    //Перевод
    QLabel* lWordTranslation = new QLabel("Перевод:");
    mainLayout->addWidget(lWordTranslation);

    //Строка ввода перевода нового слова
    _leTranslatedWordToAdd = new QLineEdit();
    mainLayout->addWidget(_leTranslatedWordToAdd);

    QPushButton* pbAddWord = new QPushButton("Добавить перевод");
    connect(pbAddWord, SIGNAL(pressed()), this, SLOT(btAddTranslationPressed())); //Конекшн сигнала со слотом
    mainLayout->addWidget(pbAddWord);
}
void AddingWindow::btAddTranslationPressed()
{
    emit translationToAddSend(_leWordToAdd->text(), _leTranslatedWordToAdd->text());

    close(); //Закрываем окно
}
