#ifndef EDITQUESTIONS_H
#define EDITQUESTIONS_H

#include <QDialog>

namespace Ui {
class EditQuestions;
}

class EditQuestions : public QDialog
{
    Q_OBJECT

public:
    explicit EditQuestions(QWidget *parent = 0);
    ~EditQuestions();

private:
    Ui::EditQuestions *ui;
};

#endif // EDITQUESTIONS_H
