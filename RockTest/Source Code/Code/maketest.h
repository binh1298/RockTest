#ifndef MAKETEST_H
#define MAKETEST_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QTreeWidgetItem>
#include <QAxObject>
#include <QDir>

namespace Ui {
class MakeTest;
}

class MakeTest : public QDialog
{
    Q_OBJECT

    void AddRoot(QString typeofexercise);
    void AddChild (QTreeWidgetItem *parent,QString difficulty);
    void addanswers (QAxObject *selection, QDir AnswersLocation);
    void addquestiontotest (QAxObject   *selection, QDir Question);
    void openfile(QDir Filename);

public:
    explicit MakeTest(QWidget *parent = 0);
    ~MakeTest();

private slots:
    void on_comboBox_Subject_currentTextChanged(const QString &arg1);

    void on_pushButton_Done_clicked();

    void on_pushButton_CaculatetotalQuestion_clicked();

    void addingquestions();

    void on_pushButton_ChooseOutDir_clicked();

private:

    Ui::MakeTest *ui;
};

#endif // MAKETEST_H
