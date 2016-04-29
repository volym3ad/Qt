#ifndef ADDINGWINDOW_H
#define ADDINGWINDOW_H

#include <QDialog>
#include <QtWidgets>

class AddingWindow : public QDialog
{
    Q_OBJECT
public:
    AddingWindow();

private:
    //Поле ввода слова на добавление
    QLineEdit* _leWordToAdd;
    QLineEdit* _leTranslatedWordToAdd;

private slots:
    //При нажимании на кнопку "Добавить перевод", будет вызвана эта ф-я - слот
    void btAddTranslationPressed();

signals:
    void translationToAddSend(QString wordToAdd, QString translatedWordToAdd);
};

#endif // ADDINGWINDOW_H
