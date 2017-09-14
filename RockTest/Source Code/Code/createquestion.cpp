#include "createquestion.h"
#include "ui_createquestion.h"
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include <QAxWidget>
#include <ActiveQt>

    QDir SubjectsLocation("E:/RockTestDatabase/Questions");
    QDir TypeofExerciseLocation = SubjectsLocation;
    QDir DifficultyLocation = TypeofExerciseLocation;
    QDir QuestionLocation = TypeofExerciseLocation;
    QDir FinalLocation = QuestionLocation;
    QDir AnswerLocation = FinalLocation;
    QDir FinalAnswerLocation = AnswerLocation;
    bool finishedquestion = false;
    bool finishedA = false;
    bool finishedB = false;
    bool finishedC = false;
    bool finishedD = false;
    int currentindex_Subject,currentindex_TypeofExercise, currentindex_Difficulty;
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void CreateQuestion::ResetAnswers() //Turn all the EditAnswer Button into their default states
{
    if (finishedA && finishedB && finishedC && finishedD)
    {
    ui->pushButton_EditAnswerA->setText("Đáp án đúng");
    ui->pushButton_EditAnswerB->setText("Đáp án sai 1");
    ui->pushButton_EditAnswerC->setText("Đáp án sai 2");
    ui->pushButton_EditAnswerD->setText("Đáp án sai 3");
    finishedA=false;
    finishedB=false;
    finishedC=false;
    finishedD=false;
    ui->comboBox_Difficulty->setEnabled(true);
    ui->comboBox_Subject->setEnabled(true);
    ui->comboBox_TypeofExercise->setEnabled(true);
    }
    else QMessageBox::critical(this,"Lỗi Nghiêm Trọng","    Chưa chỉnh sửa câu hỏi xong    ");

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////

    CreateQuestion::CreateQuestion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateQuestion)
{
    ui->setupUi(this);
    int j=1;
    foreach (QFileInfo file, SubjectsLocation.entryList())
    {
        if (j>=3) // I use this a lot because i have no idea how to avoid the "." and the ".." folder.
        {
            if(!file.isFile()) {
            ui->comboBox_Subject->addItem(file.fileName());
            }
        } else j++;
    }
    setWindowFlags(Qt::Window);
    setStyleSheet("QDialog {background: 'lightBlue';}");
    setWindowFlags(this->windowFlags() & ~Qt::WindowCloseButtonHint); /* the users have to follow the steps to make questions (use the "Xong" or Finish button to close the dialog)
                                                                         in order to avoid missing files later when creating tests.
                                                                      */
}

CreateQuestion::~CreateQuestion()
{
    delete ui;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void CreateQuestion::on_pushButton_CreateSubject_clicked()
{
    bool ok=false;
    if (ui->lineEdit_NewSubject->text() == "" )
    {
      QMessageBox::critical(this,"Lỗi","Chưa nhập tên môn học");
    }
    else {
      ok=true;
      for (int i = 0; i < ui->comboBox_Subject->count(); ++i) // Checks if the Subject folder already exists
      {
          if (ui->comboBox_Subject->itemText(i) == ui->lineEdit_NewSubject->text())
                {
                QMessageBox::critical(this,"Lỗi","Môn học đã tồn tại");
                ok=false;
                break;
                }
      }
    }
    if (ok)
    {
        SubjectsLocation.mkdir(ui->lineEdit_NewSubject->text());
        ui->comboBox_Subject->addItem(ui->lineEdit_NewSubject->text());
        ui->comboBox_Subject->setCurrentIndex(ui->comboBox_Subject->count()-1);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

void CreateQuestion::on_pushButton_CreateTypeofExercise_clicked()
{
    bool ok=false;
    if (ui->lineEdit_NewTypeofExercise->text() == "" )
    {
      QMessageBox::critical(this,"Lỗi","Chưa nhập tên dạng bài tập");
    }
    else {
        ok=true;
        for (int i = 0; i < ui->comboBox_TypeofExercise->count(); ++i) // Checks if the TypeofExercise folder already exists
        {
            if (ui->comboBox_TypeofExercise->itemText(i) == ui->lineEdit_NewTypeofExercise->text())
                  {
                  QMessageBox::critical(this,"Lỗi","Dạng bài tập đã tồn tại");
                  ok=false;
                  break;
                  }
        }
    }
    if (ok)
    {
        TypeofExerciseLocation.mkdir(ui->lineEdit_NewTypeofExercise->text());
        ui->comboBox_TypeofExercise->addItem(ui->lineEdit_NewTypeofExercise->text());
        ui->comboBox_TypeofExercise->setCurrentIndex(ui->comboBox_TypeofExercise->count()-1);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

void CreateQuestion::on_pushButton_CreateDifficulty_clicked()
{
    bool ok=false;
    if (ui->lineEdit_NewDifficulty->text() == "" )
    {
      QMessageBox::critical(this,"Lỗi","Chưa nhập độ khó");
    }
    else {
        ok=true;
        for (int i = 0; i < ui->comboBox_Difficulty->count(); ++i) // Checks if the Difficulty folder already exists
        {
            if (ui->comboBox_Difficulty->itemText(i) == ui->lineEdit_NewDifficulty->text())
                  {
                  QMessageBox::critical(this,"Lỗi","Độ khó đã tồn tại");
                  ok=false;
                  break;
                  }
        }
    }
    if (ok)
    {
        DifficultyLocation.mkdir(ui->lineEdit_NewDifficulty->text());
        ui->comboBox_Difficulty->addItem(ui->lineEdit_NewDifficulty->text());
        ui->comboBox_Difficulty->setCurrentIndex(ui->comboBox_Difficulty->count()-1);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

void CreateQuestion::on_comboBox_Subject_currentTextChanged(const QString &subj)
{
    TypeofExerciseLocation=SubjectsLocation.filePath(subj);
    ui->comboBox_TypeofExercise->clear();
    int j=1;
    foreach (QFileInfo file, TypeofExerciseLocation.entryList())
    {
        if(j>=3)
        {
            if(!file.isFile()) {
            ui->comboBox_TypeofExercise->addItem(file.fileName());
            }
        } else j++;
    }
    currentindex_Subject = ui->comboBox_Subject->currentIndex();
    DifficultyLocation = TypeofExerciseLocation.filePath(ui->comboBox_TypeofExercise->currentText());
    QuestionLocation = DifficultyLocation.filePath(ui->comboBox_Difficulty->currentText());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

void CreateQuestion::on_comboBox_TypeofExercise_currentTextChanged(const QString &typy)
{
    DifficultyLocation=TypeofExerciseLocation.filePath(typy);
    ui->comboBox_Difficulty->clear();
    int j=1;
    foreach (QFileInfo file, DifficultyLocation.entryList())
    {
        if(j>=3)
        {
            if(!file.isFile()) {
            ui->comboBox_Difficulty->addItem(file.fileName());
            }
        } else j++;
    }
    currentindex_TypeofExercise = ui->comboBox_TypeofExercise->currentIndex();
    QuestionLocation = DifficultyLocation.filePath(ui->comboBox_Difficulty->currentText());

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

void CreateQuestion::on_comboBox_Difficulty_currentTextChanged(const QString &diffy)
{
    currentindex_Difficulty = ui->comboBox_Difficulty->currentIndex();
    QuestionLocation=DifficultyLocation.filePath(diffy);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

void CreateQuestion::on_pushButton_EditQuestion_clicked()
{
    int j=1;
    foreach (QFileInfo file, QuestionLocation.entryList())
    {
        if (j>=3)
        {
            if(!file.isFile()) {
            if(ui->lineEdit_QuestionName->text()+".docx" == file.fileName())
                {
                QMessageBox::critical(this,"Lỗi","Câu đã có trong thư viện, sử dụng tên câu hỏi khác");
                return;
                }
            }
        } else j++;
    }
    if(ui->lineEdit_QuestionName->text() != "")
    {
        FinalLocation=QuestionLocation.filePath(ui->lineEdit_QuestionName->text()+".docx");
        QuestionLocation.mkdir(ui->lineEdit_QuestionName->text()+"_Answers");
        AnswerLocation=QuestionLocation.filePath(ui->lineEdit_QuestionName->text()+"_Answers");
        QFile question(FinalLocation.absolutePath());
        if(!question.open(QFile::WriteOnly | QFile::Text))
        {
            QMessageBox::warning(this,"Lỗi","File Chưa Được Tạo (có thể do tên chứa các kí tự không phù hợp)");
        }
        else
        {
            QTextStream out(&question);
            QString text= "";
            out <<text;
            question.flush();
            question.close();
            QAxObject *word;
            QAxObject *doc;
            word = new QAxObject("Word.Application", this);
            word->setProperty("DisplayAlerts", true);
            word->setProperty("Visible", true);
            doc = word->querySubObject("Documents");
            text=FinalLocation.absolutePath();;
            doc->dynamicCall("Open(QVariant)", QDir::toNativeSeparators(text));
            finishedquestion=true;
            // incase the user misclick when editing the questions
            ui->comboBox_Difficulty->setEnabled(false);
            ui->comboBox_Subject->setEnabled(false);
            ui->comboBox_TypeofExercise->setEnabled(false);
        }
    }
    else {
        QMessageBox::information(this,"Sai Cú Pháp","Bạn chưa nhập tên câu hỏi");
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

void CreateQuestion::on_pushButton_Finish_clicked()
{
    if ((finishedquestion && finishedA && finishedB && finishedC && finishedD )
         ||(!finishedquestion && !finishedA && !finishedB && !finishedC && !finishedD ))
    this->close();
    else QMessageBox::information(this,"Sai Cú Pháp","Nhập Thiếu Dữ Liệu Hoặc Chưa Chỉnh Sửa Câu Hỏi");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

void CreateQuestion::on_pushButton_Continue_clicked()
{
    if(finishedA && finishedB && finishedC && finishedD)
    {
    ui->lineEdit_NewDifficulty->clear();
    ui->lineEdit_NewSubject->clear();
    ui->lineEdit_NewTypeofExercise->clear();
    ui->lineEdit_QuestionName->clear();
    ResetAnswers();
    finishedquestion=false;
    }
    else QMessageBox::critical(this, "Sai cú pháp","Bạn nhập thiếu đáp án");
}

//////////////////// Input Answers //////////////////////////////////////////////////////////////////////

void CreateQuestion::on_pushButton_EditAnswerA_clicked()
{
    if(finishedquestion)
    {
    //QMessageBox::information(this,"tit",AnswerLocation.absolutePath());
    ui->pushButton_EditAnswerA->setText(ui->pushButton_EditAnswerA->text() + "( Đã chỉnh sửa )");
    FinalAnswerLocation = AnswerLocation.filePath(ui->lineEdit_QuestionName->text()+"_Ans"+".docx");
    QFile question(FinalAnswerLocation.absolutePath());
    if(!question.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this,"Lỗi","File Chưa Được Tạo (có thể do tên chứa các kí tự không phù hợp)");
    }
    QTextStream out(&question);
    QString text= "";
    out <<text;
    question.flush();
    question.close();
    QAxObject *word;
    QAxObject *doc;
    word = new QAxObject("Word.Application", this);
    word->setProperty("DisplayAlerts", false);
    word->setProperty("Visible", true);
    doc = word->querySubObject("Documents");
    text=FinalAnswerLocation.absolutePath();
    doc->dynamicCall("Open(QVariant)", QDir::toNativeSeparators(text));
    finishedA=true;
    }
    else
    {
        QMessageBox::critical(this,"Sai cú pháp","Chưa chỉnh sửa câu hỏi");
    }
}

void CreateQuestion::on_pushButton_EditAnswerB_clicked()
{
    if(finishedquestion)
    {
    ui->pushButton_EditAnswerB->setText(ui->pushButton_EditAnswerB->text() + " ( Đã chỉnh sửa )");
    FinalAnswerLocation = AnswerLocation.filePath(ui->lineEdit_QuestionName->text()+"_1"+".docx");
    QFile question(FinalAnswerLocation.absolutePath());
    if(!question.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this,"Lỗi","File Chưa Được Tạo (có thể do tên chứa các kí tự không phù hợp)");
    }
    QTextStream out(&question);
    QString text= "";
    out <<text;
    question.flush();
    question.close();
    QAxObject *word;
    QAxObject *doc;
    word = new QAxObject("Word.Application", this);
    word->setProperty("DisplayAlerts", false);
    word->setProperty("Visible", true);
    doc = word->querySubObject("Documents");
    text=FinalAnswerLocation.absolutePath();
    doc->dynamicCall("Open(QVariant)", QDir::toNativeSeparators(text));
    finishedB=true;
    }
    else
    {
        QMessageBox::critical(this,"Sai cú pháp","Chưa chỉnh sửa câu hỏi");
    }
}

void CreateQuestion::on_pushButton_EditAnswerC_clicked()
{
    if(finishedquestion)
    {
    ui->pushButton_EditAnswerC->setText(ui->pushButton_EditAnswerC->text() + " ( Đã chỉnh sửa )");
    FinalAnswerLocation = AnswerLocation.filePath(ui->lineEdit_QuestionName->text()+"_2"+".docx");
    QFile question(FinalAnswerLocation.absolutePath());
    if(!question.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this,"Lỗi","File Chưa Được Tạo (có thể do tên chứa các kí tự không phù hợp)");
    }
    QTextStream out(&question);
    QString text= "";
    out <<text;
    question.flush();
    question.close();
    QAxObject *word;
    QAxObject *doc;
    word = new QAxObject("Word.Application", this);
    word->setProperty("DisplayAlerts", false);
    word->setProperty("Visible", true);
    doc = word->querySubObject("Documents");
    text=FinalAnswerLocation.absolutePath();
    doc->dynamicCall("Open(QVariant)", QDir::toNativeSeparators(text));
    finishedC = true;
    }
    else
    {
        QMessageBox::critical(this,"Sai cú pháp","Chưa chỉnh sửa câu hỏi");
    }
}

void CreateQuestion::on_pushButton_EditAnswerD_clicked()
{
    if(finishedquestion)
    {
    ui->pushButton_EditAnswerD->setText(ui->pushButton_EditAnswerD->text()+ " ( Đã chỉnh sửa )");
    FinalAnswerLocation = AnswerLocation.filePath(ui->lineEdit_QuestionName->text()+"_3"+".docx");
    QFile question(FinalAnswerLocation.absolutePath());
    if(!question.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this,"Lỗi","File Chưa Được Tạo (có thể do tên chứa các kí tự không phù hợp)");
    }
    QTextStream out(&question);
    QString text= "";
    out <<text;
    question.flush();
    question.close();
    QAxObject *word;
    QAxObject *doc;
    word = new QAxObject("Word.Application", this);
    word->setProperty("DisplayAlerts", false);
    word->setProperty("Visible", true);
    doc = word->querySubObject("Documents");
    text=FinalAnswerLocation.absolutePath();
    doc->dynamicCall("Open(QVariant)", QDir::toNativeSeparators(text));
    finishedD = true;
    }
    else
    {
        QMessageBox::critical(this,"Sai cú pháp","Chưa chỉnh sửa câu hỏi");
    }
}
