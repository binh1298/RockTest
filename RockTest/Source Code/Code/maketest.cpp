#include "maketest.h"
#include "ui_maketest.h"
#include <QDir>
#include <QList>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QAxWidget>
#include <ActiveQt>
#include <QtGui>
#include <string>
#include <QFileInfo>

    QDir subjectsdir("E:/RockTestDatabase/Questions");
    QDir typeofexercisedir = subjectsdir;
    QDir diffdir = typeofexercisedir;
    QDir questiondir = diffdir;
    QDir outlocation("E:/OutPut/");
    QDir AnswerCharIndexA("E:/RockTestDatabase/Constructor/A.docx");
    QDir AnswerCharIndexB("E:/RockTestDatabase/Constructor/B.docx");
    QDir AnswerCharIndexC("E:/RockTestDatabase/Constructor/C.docx");
    QDir AnswerCharIndexD("E:/RockTestDatabase/Constructor/D.docx");
    QDir Spacer("E:/RockTestDatabase/Constructor/Spacer.docx");
    QDir AnswerSheet("E:/RockTestDatabase/Constructor/AnswerSheet.docx");

    QString     outDir("E:/OutPut/");

    QDir     Header("E:/RockTestDatabase/Constructor/Header.docx");
    QDir     Footer("E:/RockTestDatabase/Constructor/Footer.docx");
    QDir     Questioner("E:/RockTestDatabase/Constructor/Questioner.docx");

    QList <QDir> AnswerCharIndex ;
    QList <QLineEdit *> lelist;
    QList <int> lemaxlist;
    QList <QDir> dirlist;
    QList <int> answersindex;
    int n=3,counter=0;

///////////////////////////////////////////////////////////////////////////////////////////////////////

    int treeCount(QTreeWidget *tree, QTreeWidgetItem *parent = 0)
    {
        int count = 0;
        if (parent == 0) {
            int topCount = tree->topLevelItemCount();
            for (int i = 0; i < topCount; i++) {
                QTreeWidgetItem *item = tree->topLevelItem(i);
                if (item->isExpanded()) {
                    count += treeCount(tree, item);
                }
            }
            count += topCount;
        } else {
            int childCount = parent->childCount();
            for (int i = 0; i < childCount; i++) {
                QTreeWidgetItem *item = parent->child(i);
                if (item->isExpanded()) {
                    count += treeCount(tree, item);
                }
            }
            count += childCount;
        }
        return count;
    }

    bool checkconstructors(QDir filename)
    {
        QFile constructor(filename.absolutePath());
        return constructor.exists();
    }

///////////////////////////////////////////////////////////////////////////////////////////////////////

void MakeTest::on_pushButton_CaculatetotalQuestion_clicked()
    {
        int total=0;
        foreach(QLineEdit* item, lelist)
        {
            if(item->text() != "")
            {
                total+=item->text().toInt();
            }
        }
        ui->label_TotalQuestion->setText("Tổng số câu hỏi: "+QString::fromStdString(std::to_string(total)));
    }

///////////////////////////////////////////////////////////////////////////////////////////////////////

    MakeTest::MakeTest(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MakeTest)
{
    ui->setupUi(this);
    // Checking essential constructive files. Default constructors can be found inside the project folder.
    if(!checkconstructors(Spacer)){
    QMessageBox::critical(this,"Thiếu tệp","Chưa có tệp khoảng cách giữa 2 câu");
    setModal(false);
    }
    if(!checkconstructors(Header)){
    QMessageBox::critical(this,"Thiếu tệp","Chưa có tệp Đầu đề");
    setModal(false);
    }
    if(!checkconstructors(Footer)){
    QMessageBox::critical(this,"Thiếu tệp","Chưa có tệp Cuối đề");
    setModal(false);
    }
    if(!checkconstructors(AnswerSheet)){
    QMessageBox::critical(this,"Thiếu tệp","Chưa có tệp Đầu đáp án");
    setModal(false);
    }
    ui->treeWidget->setColumnCount(4);
    QStringList ColumnNames;
    ColumnNames <<"Dạng bài tập"<<"Độ Khó" << "Số Lượng"<<"Tối đa";
    ui->treeWidget->setHeaderLabels(ColumnNames);
    int j=1;
    foreach (QFileInfo file, subjectsdir.entryList())
    {
        if(j>=3)
        {
            if(!file.isFile()) {
            ui->comboBox_Subject->addItem(file.fileName());
            }
        } else j++;
    }
    AnswerCharIndex.append(AnswerCharIndexA);
    AnswerCharIndex.append(AnswerCharIndexB);
    AnswerCharIndex.append(AnswerCharIndexC);
    AnswerCharIndex.append(AnswerCharIndexD);
    ui->label_ChosenOutDir->setText(outDir);
    showMaximized();
    setWindowFlags(Qt::Window);
    ui->progressBar->setValue(0);
    ui->progressBar->hide();
    setStyleSheet("QDialog {background: 'lightBlue';}");
}
MakeTest::~MakeTest()
{
    delete ui;
}
//////////////////// Build Tree //////////////////////////////////////////////////////////////
void MakeTest::AddRoot(QString typeofexercise) {
    QTreeWidgetItem *root = new QTreeWidgetItem(ui->treeWidget);
    root->setText(0,typeofexercise);
    ui->treeWidget->addTopLevelItem(root);
    diffdir = typeofexercisedir.filePath(typeofexercise);
    int j=1;
    foreach(QFileInfo diff, diffdir.entryList())
    {
        if (j>=3)
        {
            if(!diff.isFile()){
                AddChild(root,diff.fileName());
            }
        }
        else j++;
    }
}

void MakeTest::AddChild (QTreeWidgetItem *parent, QString difficulty)
{
    QTreeWidgetItem *branch = new QTreeWidgetItem(ui->treeWidget);
    auto le = new QLineEdit();
    branch->setText(1,difficulty);
    questiondir = diffdir.filePath(difficulty);
    int i=0,j=1;
    foreach(QFileInfo questions, questiondir.entryList())
    {
        if (j>=3)
        {
            if(!questions.isFile()){
                i++;
            }
        }
        else j++;
    }
    QString tmp = QString::fromStdString(std::to_string(i/2));
    branch->setText(3,tmp);
    ui->treeWidget->setItemWidget(branch,2,le);
    parent-> addChild(branch);
    dirlist.append(questiondir);
    lemaxlist.append(i/2);
    lelist.append(le);
}

void MakeTest::on_comboBox_Subject_currentTextChanged(const QString &arg1)
{
    ui->treeWidget->clear();
    lelist.clear();
    lemaxlist.clear();
    dirlist.clear();
    AnswerCharIndex.clear();
    answersindex.clear();
    typeofexercisedir = subjectsdir.filePath(arg1);
    int j=1;
    foreach (QFileInfo file, typeofexercisedir.entryList())
    {
        if(j>=3)
        {
            if(!file.isFile()) {
                AddRoot(file.fileName());
            }
        }
        else j++;
    }
    ui->treeWidget->resizeColumnToContents(0);
    ui->treeWidget->resizeColumnToContents(1);
    ui->treeWidget->resizeColumnToContents(2);
    ui->treeWidget->resizeColumnToContents(3);
}


/////////////////////  Make Test  ////////////////////////////////////////////////////////////////

int getc(int i)
{
    int need=lelist[i]->text().toInt();
    int ma=lemaxlist[i];
    if(n*need <= ma) return 0;
   // if(n==1) return 0;
    int c=need;
    int r=(ma-need)/n;
    while(r+c> need && c>0)
    {
        c--;
        r=(ma-c)/n;
    }
    return c;
}

void addCharindextotest (QAxObject   *selection, int questionindex)
{
   // selection->dynamicCall("EndKey(QVarient&)", 6); // WdStoryType::wdStory=6
    selection->dynamicCall("InsertFile(QString&)", AnswerCharIndex[questionindex].absolutePath());
}

void MakeTest::openfile(QDir Filename)
{
    QFile question(Filename.absolutePath());
    if(!question.open(QFile::ReadOnly | QFile::Text))
    {
        //QMessageBox::warning(this,"Lỗi","File Chưa Được Tạo (có thể do tên chứa các kí tự không phù hợp)");
    }
    else
    {
        QString text= "";
        QAxObject *word;
        QAxObject *doc;
        word = new QAxObject("Word.Application", this);
        word->setProperty("DisplayAlerts", true);
        word->setProperty("Visible", true);
        doc = word->querySubObject("Documents");
        text=Filename.absolutePath();
        doc->dynamicCall("Open(QVariant)", QDir::toNativeSeparators(text));
    }
}

void addanswertotest (QAxObject   *selection, QDir Answer,int questionindex)
{
    //addCharindextotest(selection,questionindex);
    QString charindex;
    if(questionindex == 0) charindex="A.";
    if(questionindex == 1) charindex="B.";
    if(questionindex == 2) charindex="C.";
    if(questionindex == 3) charindex="D.";
    selection->dynamicCall("EndKey(QVariant&)", 6); // WdUnits::wdLine=6
    selection->dynamicCall("TypeText(const QString&)",charindex);
    selection->dynamicCall("InsertFile(QString&)", Answer.absolutePath());
}
void MakeTest::addanswers(QAxObject *selection, QDir AnswersLocation)
{
    QDir CorrectAnswer;
    QList <QDir> WrongAnswers;
    int j=1,countaz=0;
    foreach (QFileInfo file, AnswersLocation.entryList())
    {
        if(j>=3)
        {
            if(!file.isFile() && ( file.fileName().endsWith(".docx") ) ) {
                countaz++;
                if(file.fileName().endsWith("Ans.docx"))
                {
                    CorrectAnswer=AnswersLocation.filePath(file.fileName());
                }
                else
                WrongAnswers.append(AnswersLocation.filePath(file.fileName()));
            }
        }
        else j++;
    }
    std::random_shuffle(WrongAnswers.begin(), WrongAnswers.end());
    if(countaz<4)
    {
        QMessageBox::information(this,"Câu hỏi thiếu đáp án","Câu hỏi tại: " + AnswersLocation.absolutePath() + " bị thiếu đáp án");
    }
    for(int i=0;i<4;i++)
    {
        //QMessageBox::information(this,"In đáp án",QString::fromStdString(std::to_string(i)));
        if(answersindex[counter-1]==i)
        {
            addanswertotest(selection,CorrectAnswer,i);
           // QMessageBox::information(this,"Correct Ans",CorrectAnswer.absolutePath());
        }
        else
        if(!WrongAnswers.empty())
        {
            addanswertotest(selection,WrongAnswers.front(),i);
           // QMessageBox::information(this,"Wrong Ans",WrongAnswers.front().absolutePath());
            WrongAnswers.pop_front();
        }
    }
    selection->dynamicCall("InsertFile(QString&)", Spacer.absolutePath());
}
void MakeTest::addquestiontotest (QAxObject   *selection, QDir Question)
{
    counter++;
    selection->dynamicCall("EndKey(QVarient&)", 6); // WdStoryType::wdStory=6
    selection->dynamicCall("TypeText(const QString&)","Câu "+ QString::fromStdString(std::to_string(counter)) +": ");
    selection->dynamicCall("InsertFile(QString&)", Question.absolutePath());
    QDir AnswersLocation(Question.absolutePath().section(".",0,0)+"_Answers");
    //QMessageBox::information(this,"tit",AnswersLocation.absolutePath());
    addanswers(selection,AnswersLocation);

}

void MakeQuestionLinkSheeet(QString FileName, QList<QDir> QuestionLinks,int index)
{
    QAxObject   axObject("Word.Application");
    QAxObject   *documents = axObject.querySubObject("Documents");
    QAxObject   *document = documents->querySubObject("Open(const QString&, bool)", AnswerSheet.absolutePath(), true);
    QAxObject   *selection = axObject.querySubObject("Selection");
    selection->dynamicCall("TypeText(const QString&)","------------------------------------------------------------------");
    selection->dynamicCall("InsertFile(QString&)", Spacer.absolutePath());
    selection->dynamicCall("TypeText(const QString&)","Danh sách câu hỏi đã sử dụng:");
    selection->dynamicCall("InsertFile(QString&)", Spacer.absolutePath());
    selection->dynamicCall("InsertFile(QString&)", Spacer.absolutePath());
    int i=0;
    while(!QuestionLinks.empty())
    {
        i++;
        selection->dynamicCall("TypeText(const QString&)","Câu "+ QString::fromStdString(std::to_string(i)) + ": ");
        selection->dynamicCall("TypeText(const QString&)",QuestionLinks.front().absolutePath());
        selection->dynamicCall("InsertFile(QString&)", Spacer.absolutePath());
        QuestionLinks.pop_front();
    }
    document->dynamicCall("SaveAs(const QString&)", outDir + FileName + "_" + QString::fromStdString(std::to_string(index)) +"_ĐƯỜNG DẪN" );
    document->dynamicCall("Close()");
    axObject.dynamicCall("Quit()");
}

void MakeAnswerSheet(QString FileName, int index)
{
    QAxObject   axObject("Word.Application");
    QAxObject   *documents = axObject.querySubObject("Documents");
    QAxObject   *document = documents->querySubObject("Open(const QString&, bool)", AnswerSheet.absolutePath(), true);
    QAxObject   *selection = axObject.querySubObject("Selection");
    for(int i=0;i<answersindex.count();i++)
    {
        QString charindex;
        if(answersindex[i] == 0) charindex="A";
        if(answersindex[i] == 1) charindex="B";
        if(answersindex[i] == 2) charindex="C";
        if(answersindex[i] == 3) charindex="D";
        selection->dynamicCall("EndKey(QVariant&)", 6);
        selection->dynamicCall("TypeText(const QString&)","Câu " + QString::fromStdString(std::to_string(i+1)) + ": " + charindex);
        selection->dynamicCall("InsertFile(QString&)", Spacer.absolutePath());
    }
    document->dynamicCall("SaveAs(const QString&)", outDir + FileName + "_" + QString::fromStdString(std::to_string(index)) +"_ĐÁP ÁN" );
    document->dynamicCall("Close()");
    axObject.dynamicCall("Quit()");
}

void MakeTest::addingquestions()
{
    QList <QDir> QuestionList;
    QList <QDir> SmallConstQuestionList;
    QList <QDir> SmallRandomQuestionList;
    QList < QList<QDir> > FullRandomQuestionList;
    QList < QList<QDir> > FullConstQuestionList;
    QList <QDir> FinalQuestionList;
    for(int j=0;j<lelist.count();j++)
    if(lelist[j]->text() != "" && lelist[j]->text() !="0")
    {
        //QMessageBox::information(this,"tit","Getting Questions");
        int fj=1;
        foreach (QFileInfo file, dirlist[j].entryList()) // Get Questions from Library
        {
            if(fj>=3)
            {
                if(!file.isFile() && ( file.fileName().endsWith(".docx") ) ) {
                    QuestionList.append(dirlist[j].filePath(file.fileName()));
                }
            }
            else fj++;
        }

        //QMessageBox::information(this,"tit","Adding Constant Questions");
        if(ui->checkBox_PartialShuffle->isChecked())
        {
        for(int k=1;k<=rand()%5+1;k++)
        std::random_shuffle(QuestionList.begin(), QuestionList.end());
        std::random_shuffle(QuestionList.begin(), QuestionList.end());
        }
        SmallConstQuestionList.clear();
        for(int k=1;k<=getc(j);k++) // Get Const questions
        {
            if(!QuestionList.empty())
            {
            SmallConstQuestionList.append(QuestionList.front());
//            QMessageBox::critical(this,"Constant",QuestionList.front().absolutePath());
            QuestionList.pop_front();
            }
        }

        FullConstQuestionList.append(SmallConstQuestionList);
        SmallRandomQuestionList.clear();
        //QMessageBox::information(this,"tit","Adding Random Questions");
        while(!QuestionList.empty())
        {
            SmallRandomQuestionList.append(QuestionList.front());
//            QMessageBox::critical(this,"Random",QuestionList.front().absolutePath());
            QuestionList.pop_front();
        }
        FullRandomQuestionList.append(SmallRandomQuestionList);
    }
    else
    {
        SmallConstQuestionList.clear();
        FullConstQuestionList.append(SmallConstQuestionList);
        SmallRandomQuestionList.clear();
        FullRandomQuestionList.append(SmallRandomQuestionList);
    }

    QString     FileName(ui->lineEdit_TestName->text());
    for(int i=0;i<n;i++)
    {
    ui->progressBar->setValue(ui->progressBar->value() + (float)(0.1/n)*100);
    counter = 0;
    for(int i=1;i<=rand()%5+1;i++) std::random_shuffle(answersindex.begin(),answersindex.end());
    std::random_shuffle(answersindex.begin(),answersindex.end());
    FinalQuestionList.clear();
    //QMessageBox::information(this,"tit","Creating Test: "+ QString::fromStdString(std::to_string(i)));
    QAxObject   axObject("Word.Application");
    QAxObject   *documents = axObject.querySubObject("Documents");
    QAxObject   *document = documents->querySubObject("Open(const QString&, bool)", Header.absolutePath(), true);
    QAxObject   *selection = axObject.querySubObject("Selection");
    for(int k=0;k<lelist.count();k++)
    if(lelist[k]->text() != "" && lelist[k]->text() !="0")
    {
        int c=getc(k);
        int r=lelist[k]->text().toInt()-c;
        //QMessageBox::information(this,"k",QString::fromStdString(std::to_string(c)));
        for(int j=0;j<c;j++)
        if(!FullConstQuestionList[k].empty())
        {
            //QMessageBox::information(this,"FinalConstant",FullConstQuestionList[k][j].absolutePath());
            FinalQuestionList.append(FullConstQuestionList[k][j]);
        }
        for(int j=0;j<r;j++)
        if(!FullRandomQuestionList[k].empty())
        {
            //QMessageBox::information(this,"FinalRandom",FullRandomQuestionList[k].front().absolutePath());
            FinalQuestionList.append(FullRandomQuestionList[k].front());
            FullRandomQuestionList[k].pop_front();
        }
    }
    //QMessageBox::information(this,"Tit","Start Adding Questions To Test");
    ui->progressBar->setValue(ui->progressBar->value() + (float)(0.3/n)*100);
    if(ui->checkBox_Shuffle->isChecked())
        std::random_shuffle(FinalQuestionList.begin(), FinalQuestionList.end());
    QList <QDir> QuestionLinks = FinalQuestionList;
    while(!FinalQuestionList.empty())
    {
        addquestiontotest(selection,FinalQuestionList.front());
        FinalQuestionList.pop_front();
    }
    ui->progressBar->setValue(ui->progressBar->value() + (float)(0.3/n)*100);
    selection->dynamicCall("EndKey(QVarient&)", 6); // WdStoryType::wdStory=6
    selection->dynamicCall("InsertFile(QString&)", Footer.absolutePath());
    document->dynamicCall("SaveAs(const QString&)", outDir + FileName+ "_" + QString::fromStdString(std::to_string(i+1)));
    document->dynamicCall("Close()");
    if(ui->checkBox_Opener->isChecked())
        openfile(outlocation.filePath(outDir + FileName+ "_" + QString::fromStdString(std::to_string(i+1)) + ".docx"));
    axObject.dynamicCall("Quit()");
    //QMessageBox::information(this,"Tit","Make AnswerSheet");
    ui->progressBar->setValue(ui->progressBar->value() + (float)(0.3/n)*100);
    MakeAnswerSheet(FileName,i+1);
    MakeQuestionLinkSheeet(FileName,QuestionLinks,i+1);
    }
}

void MakeTest::on_pushButton_Done_clicked()
{

    if(ui->lineEdit_ND->text() == "" || ui->lineEdit_TestName->text() == "")
    {
        QMessageBox::critical(this,"Sai cú pháp","Bạn nhập thiếu dữ liệu");
    }
    else
    {
    bool ok=true;
    for(int j=0;j<lelist.count();j++)
    {
        if (lelist[j]->text().toInt()>lemaxlist[j])
        {
            QMessageBox::critical(this,"Sai cú pháp","Số lượng câu hỏi mỗi đề không được vượt quá số lượng câu hỏi trong thư viện");
            ok=false;
            break;
        }
    }
    int j=1;
    foreach (QFileInfo file, outlocation.entryList())
    {
        if (j>=3)
        {
            if(!file.isFile()) {
            if(ui->lineEdit_TestName->text()+"_0"+".docx" == file.fileName() ||
               ui->lineEdit_TestName->text()+"_0"+".doc" == file.fileName() )
            {
            QMessageBox::critical(this,"Lỗi","Đề thi đã có, sử dụng tên đề thi khác");
            ok=false;
            break;
            }
            }
        } else j++;
    }
    if(ok)
        {
        n = ui->lineEdit_ND->text().toInt();
        int total=0;
        foreach(QLineEdit* item, lelist)
        {
            if(item->text() != "")
            {
                total+=item->text().toInt();
            }
        }
        answersindex.clear();
        if(ui->checkBox_AnswerRatio->isChecked())
        {
            int x=total/4;
            for(int i=1;i<=x;i++) answersindex.append(1);
            for(int i=x+1;i<=2*x;i++) answersindex.append(2);
            for(int i=2*x+1;i<=3*x;i++) answersindex.append(3);
            for(int i=3*x+1;i<=total;i++) answersindex.append(0);
        }
        else
        {
            for(int i=1;i<=total;i++) answersindex.append(rand()%4);
        }
        ui->progressBar->setValue(0);
        ui->progressBar->show();
        addingquestions();
        ui->progressBar->setValue(100);
        QMessageBox::information(this,"Thông báo","Đã trộn xong");
        ui->progressBar->hide();
        }
    }
}



void MakeTest::on_pushButton_ChooseOutDir_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,"Chọn thư mục lưu", outlocation.absolutePath());
    QDir Newoutlocation(filename);
    outlocation = Newoutlocation;
    outDir = outlocation.absolutePath();
    ui->label_ChosenOutDir->setText(outDir);
    QFileInfo AnswerFile(outDir);

}



