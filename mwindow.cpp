#include "mwindow.h"

MWindow::MWindow(QWidget *parent) :
    QWidget(parent)
{
    //Грузим словарь
    _dictionary.load();

    //--- UI
    //Мейновый лайаут
    QHBoxLayout* mainLayout = new QHBoxLayout();
    this->setLayout(mainLayout);

    //Левый лайаут
    QVBoxLayout* leftLayout = new QVBoxLayout();
    mainLayout->addLayout(leftLayout);

    //Правый лайаут
    QVBoxLayout* rightLayout = new QVBoxLayout();
    mainLayout->addLayout(rightLayout);

    //Лайаут с комбо боксами
    QHBoxLayout* comboBoxesLayout = new QHBoxLayout();
    rightLayout->addLayout(comboBoxesLayout);

    _cbFromLenguage = new QComboBox();
    _cbFromLenguage->addItem(MyWord::getLenguageString(MyWord::Ukrainian));
    _cbFromLenguage->addItem(MyWord::getLenguageString(MyWord::English));
    _cbFromLenguage->addItem(MyWord::getLenguageString(MyWord::Italian));
    comboBoxesLayout->addWidget(_cbFromLenguage);
    connect(_cbFromLenguage, SIGNAL(currentIndexChanged(QString)), this, SLOT(reloadWordsView()));

    _cbToLenguage = new QComboBox();
    _cbToLenguage->addItem(MyWord::getLenguageString(MyWord::English));
    _cbToLenguage->addItem(MyWord::getLenguageString(MyWord::Ukrainian));
    _cbToLenguage->addItem(MyWord::getLenguageString(MyWord::Italian));
    comboBoxesLayout->addWidget(_cbToLenguage);
    connect(_cbToLenguage, SIGNAL(currentIndexChanged(QString)), this, SLOT(reloadWordsView()));

    //Строка поиска
    _leWordSearch = new QLineEdit();
    rightLayout->addWidget(_leWordSearch);
    connect(_leWordSearch, SIGNAL(textChanged(QString)), this, SLOT(searchTextChanged(QString)));

    //Наша вьюха со словами
    _teWordsView = new QListWidget();
    rightLayout->addWidget(_teWordsView);
    loadWordsToView(MyWord::Ukrainian, MyWord::English); //Языки по умолчанию

    //Кнопка удаления слова
    QPushButton* pbDeleteWord = new QPushButton("Удалить");
    connect(pbDeleteWord, SIGNAL(pressed()), this, SLOT(btDeleteWordPressed())); //Конекшн сигнала со слотом
    rightLayout->addWidget(pbDeleteWord);

    //Кнопка добавления слова
    QPushButton* pbAddWord = new QPushButton("Добавить");
    connect(pbAddWord, SIGNAL(pressed()), this, SLOT(btAddWordPressed())); //Конекшн сигнала со слотом
    rightLayout->addWidget(pbAddWord);
}
void MWindow::btDeleteWordPressed()
{
    //Ели ничего не выбрано, то не удаляем слово
    if (_teWordsView->currentItem() == NULL)
        return;

    for (int i = 0; i < _dictionary.getWords().length(); i++)
        if(_dictionary.getWords().at(i).getTranlationByLanguage(MyWord::getLenguageByString(_cbFromLenguage->currentText())) == _teWordsView->currentItem()->text().section(" ",0,0))
            _dictionary.removeWordAt(i);

    _dictionary.save();
    _leWordSearch->setText("");
    reloadWordsView();
}
//Реализация события нажима кнопки "Добавить"
void MWindow::btAddWordPressed()
{
    AddingWindow* addingWindow = new AddingWindow;
    connect(addingWindow, SIGNAL(translationToAddSend(QString,QString)), this, SLOT(addTranslation(QString,QString))); //Соидиняем, что бы при нажатии кнопки в диалоге, слово добавлялось
    addingWindow->setAttribute(Qt::WA_DeleteOnClose); //При закрытии будет удалятся полностью
    addingWindow->exec(); //Открываем диалог
}

void MWindow::addTranslation(QString wordToAdd, QString translatedWordToAdd)
{
    for (int i = 0; i < _dictionary.getWords().length(); i++)
    {
        if (_dictionary.getWords().at(i).getTranlationByLanguage(MyWord::getLenguageByString(_cbFromLenguage->currentText())) == wordToAdd)
        {
            MyWord word = _dictionary.getWords().at(i);
            word.addTranlation(MyWord::getLenguageByString(_cbToLenguage->currentText()), translatedWordToAdd);
            _dictionary.replaceWordAt(i, word);

            _dictionary.save();
            _leWordSearch->setText("");
            reloadWordsView();

            return;
        }
    }

    MyWord word;

    word.addTranlation(MyWord::getLenguageByString(_cbFromLenguage->currentText()), wordToAdd);
    word.addTranlation(MyWord::getLenguageByString(_cbToLenguage->currentText()), translatedWordToAdd);

    _dictionary.addWord(word);

    _dictionary.save();
    _leWordSearch->setText("");
    reloadWordsView();
}

void MWindow::searchTextChanged(QString changedText)
{
    loadWordsToView(MyWord::getLenguageByString(_cbFromLenguage->currentText()), MyWord::getLenguageByString(_cbToLenguage->currentText()), changedText);
}

void MWindow::loadWordsToView(MyWord::Language fromLanguage, MyWord::Language toLanguage, QString searchWord)
{
    //Стираем все
    _teWordsView->clear();

    //Записываем переводы
    for (int i = 0; i < _dictionary.getWords().length(); i++)
    {
        if (searchWord == "") //Если не ищем, грузим все слова
        {
             QListWidgetItem *item = new QListWidgetItem(_dictionary.getWords().at(i).getTranlationByLanguage(fromLanguage) + "            "
                                                        + _dictionary.getWords().at(i).getTranlationByLanguage(toLanguage));
             item->setTextAlignment(Qt::AlignHCenter); //Делаем текст по центру
            _teWordsView->addItem(item);
        }
        else //Иначе фильтруем по префиксу
            if(_dictionary.getWords().at(i).getTranlationByLanguage(fromLanguage).left(searchWord.count()).toLower() == searchWord.toLower()) //Капс не влияет на поиск, так как переводим в ловеркейс
            {
                QListWidgetItem *item = new QListWidgetItem(_dictionary.getWords().at(i).getTranlationByLanguage(fromLanguage) + "            "
                                                           + _dictionary.getWords().at(i).getTranlationByLanguage(toLanguage));
                item->setTextAlignment(Qt::AlignHCenter); //Делаем текст по центру
               _teWordsView->addItem(item);
            }
    }
}

void MWindow::reloadWordsView()
{
    loadWordsToView(MyWord::getLenguageByString(_cbFromLenguage->currentText()), MyWord::getLenguageByString(_cbToLenguage->currentText()));
}
