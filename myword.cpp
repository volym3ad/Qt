#include "myword.h"

MyWord::MyWord()
{
}

//Реализация метода добавления перевода
void MyWord::addTranlation(MyWord::Language language, QString tranlation)
{
    //Не может быть одинаковых ключей
    if (_translations.contains(language))
        _translations.remove(language);

    //Добавляем tranlation слова на язык language
    _translations.insert(language, tranlation);
}

QString MyWord::getTranlationByLanguage(MyWord::Language language) const
{
    // Второй аргумент - это дефоулт и если нету перевода слова на язык language, тогда возвращаем ноль (Null)
    return _translations.value(language, "Нет_перевода");
}

QString MyWord::getLenguageString(MyWord::Language language)
{
    switch (language) {
    case Ukrainian :
        return "Украинский";
        break;
    case English :
        return "Английский";
        break;
    case Italian :
        return "Италийский";
        break;
    default:
        return "Украинский";
        break;
    }
}

MyWord::Language MyWord::getLenguageByString(QString languageString)
{
    if (languageString == "Украинский")
        return Ukrainian;

    else if (languageString == "Английский")
        return English;

    else if (languageString == "Италийский")
        return Italian;

    return Ukrainian;
}
