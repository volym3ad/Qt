#ifndef MYWORD_H
#define MYWORD_H

#include <QObject>
#include <QtGui>

//Слово - это одно и то же значение на разных языках,
//так и тут, у одного слова - одно значение, но на множестве языков

//Класс слова
class MyWord
{
public:
    MyWord();

    //Список языков
    enum Language
    {
        Ukrainian,
        English,
        Italian
    };

    //Извлекаем значение слова на языке language
    QString getTranlationByLanguage(MyWord::Language language) const;

    //Добавление перевода
    void addTranlation(MyWord::Language language, QString tranlation);

    //Язык из энума в стринг
    static QString getLenguageString(MyWord::Language language);

    //Язык из стринга в энум
    static MyWord::Language getLenguageByString(QString languageString);
private:

    //Мапа, это тот же двумерный массив, грубо говоря. Ключ - это язык (или [1] как в массивах, 1 - ключ,
    //тут это Word::Language ), и по этому ключу мы можем достать перевод слова на этом языке
    QMap<MyWord::Language, QString> _translations;
};

#endif // MYWORD_H
