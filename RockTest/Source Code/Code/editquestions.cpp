#include "editquestions.h"
#include "ui_editquestions.h"

EditQuestions::EditQuestions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditQuestions)
{
    ui->setupUi(this);
}

EditQuestions::~EditQuestions()
{
    delete ui;
}
