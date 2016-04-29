#ifndef MYDICTIONARY_H
#define MYDICTIONARY_H

#include <QObject>
#include "myword.h"

//В словаре мы будем хранить все наши слова с их переводами
class MyDictionary
{
public:
    MyDictionary();

    //Имя файла с дикшинарем, или его путь + название от текущей папки
    QString dictionaryFileName;

    //Загрузка словаря с файла "dictionaryFileName"
    bool load();

    //Сохранение словаря в файл "dictionaryFileName"
    bool save();

    //Вытаскиваем перевод слова "word" с языка "fromLanguage" на язык "toLanguage"
    QString getWordTranslation(QString word, MyWord::Language fromLanguage, MyWord::Language toLanguage);

    //Добавление слова
    void addWord(MyWord word);

    //Реплейс слова
    void replaceWordAt(int i, MyWord word);

    //Удаление слова
    void removeWordAt(int i);

    //Вытаскиваем слова
    QList<MyWord> getWords();
private:
    //Наши слова, List - это тот же вектор, но немножко удобней
    QList<MyWord> _words;

    //Вытягиваем слово с строки
    MyWord getWordFromString(QString string);
};

#endif // MYDICTIONARY_H
