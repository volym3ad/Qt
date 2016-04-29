#include "mydictionary.h"

MyDictionary::MyDictionary()
{
   dictionaryFileName = "dictionary.txt";
}

QString MyDictionary::getWordTranslation(QString word, MyWord::Language fromLanguage, MyWord::Language toLanguage)
{
    //Перебераем все элементы списка со словами
    for (int i = 0; i < _words.length(); i++)
    {
        //Если перевод текущего слова с языка fromLanguage совпадает с word,
        //тогда возвращаем его же перевод с языка toLanguage
        if(_words.at(i).getTranlationByLanguage(fromLanguage) == word)
            return _words.at(i).getTranlationByLanguage(toLanguage);
    }

    //Если не нашли, возвращаем ноль
    return "Нету перевода";
}

void MyDictionary::addWord(MyWord word)
{
    _words.append(word); //Добавляем в конец
}

//Возвращает булл, true - все ок, false - ошибка
bool MyDictionary::load()
{
    QFile file(dictionaryFileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return false;

    QTextStream in(&file);
    QString line = in.readLine();
    while (!line.isNull())
    {
        _words.append(getWordFromString(line));   //Добавляем слово с считанной строки

        //Переходим к некст строке
        line = in.readLine();
    }

    return true;
}

//Возвращает булл, true - все ок, false - ошибка
bool MyDictionary::save()
{
    QFile file(dictionaryFileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&file);

    for (int i = 0; i < _words.length(); i++)
    {
        out << _words.at(i).getTranlationByLanguage(MyWord::Ukrainian) << " "
            << _words.at(i).getTranlationByLanguage(MyWord::English) << " "
            << _words.at(i).getTranlationByLanguage(MyWord::Italian) << " "
            << "\n";
    }

    return true;
}

MyWord MyDictionary::getWordFromString(QString string)
{
    MyWord word;

    word.addTranlation(MyWord::Ukrainian, string.section(" ",0,0)); //Ф-я section вытаскивает с стринга секцию, ограниченную пробелом под 1 номером
    word.addTranlation(MyWord::English, string.section(" ",1,1));
    word.addTranlation(MyWord::Italian, string.section(" ",2,2));

    return word;
}
QList<MyWord> MyDictionary::getWords()
{
    return _words;
}
void MyDictionary::replaceWordAt(int i, MyWord word)
{
    _words.replace(i, word);
}
void MyDictionary::removeWordAt(int i)
{
    _words.removeAt(i);
}
