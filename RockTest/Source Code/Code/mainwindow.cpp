#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "createquestion.h"
#include "editquestions.h"
#include "maketest.h"
#include <QDir>
#include <QMessageBox>

    QDir subjectsdire("E:/RockTestDatabase/Questions");
    QDir typeofexercisedire = subjectsdire;
    QDir diffdire = typeofexercisedire;
    QDir questiondire = diffdire;
    QDir     HeaderDir("E:/RockTestDatabase/Constructor/Header.docx");
    QDir     FooterDir("E:/RockTestDatabase/Constructor/Footer.docx");
    MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->treeWidget->setColumnCount(4);
    QStringList ColumnNames;
    ColumnNames << "Môn học" <<"Dạng bài tập"<<"Độ Khó" << "Số lượng câu hỏi trong thư viện";
    ui->treeWidget->setHeaderLabels(ColumnNames);
    int j=1;
    foreach (QFileInfo subject, subjectsdire.entryList())
    {
        if(j>=3)
        {
            if(!subject.isFile()) {
                QTreeWidgetItem *root = new QTreeWidgetItem(ui->treeWidget);
                root->setText(0,subject.fileName());
                ui->treeWidget->addTopLevelItem(root);
                typeofexercisedire = subjectsdire.filePath(subject.fileName());
                int i=1;
                foreach (QFileInfo type, typeofexercisedire.entryList())
                {
                    if(i>=3)
                    {
                        if(!type.isFile()) {
                            QTreeWidgetItem *branch1 = new QTreeWidgetItem();
                            branch1->setText(1,type.fileName());
                            root->addChild(branch1);
                            diffdire=typeofexercisedire.filePath(type.fileName());
                            int k=1;
                            foreach (QFileInfo diff, diffdire.entryList())
                            {
                                if(k>=3)
                                {
                                    if(!diff.isFile()) {
                                        QTreeWidgetItem *branch2 = new QTreeWidgetItem();
                                        branch2->setText(2,diff.fileName());
                                        branch1->addChild(branch2);
                                        questiondire = diffdire.filePath(diff.fileName());
                                        int l=1,dem=0;
                                        foreach (QFileInfo questiona, questiondire.entryList())
                                        {
                                            if(l>=3)
                                            {
                                                if(!questiona.isFile()) {
                                                dem++;
                                                }
                                            } else l++;
                                        }
                                        branch2->setText(3,"            " +QString::fromStdString(std::to_string(dem/2)));
                                    }
                                } else k++;
                            }
                        }
                    } else i++;
                }
            }
        } else j++;
    }
    ui->treeWidget->expandAll();
    ui->treeWidget->resizeColumnToContents(0);
    ui->treeWidget->resizeColumnToContents(1);
    ui->treeWidget->resizeColumnToContents(2);
    ui->treeWidget->resizeColumnToContents(3);
    showMaximized();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_CreateQuestion_clicked()
{
    QDir questionslocation("E:/RockTestDatabase/Questions");
    if (questionslocation.exists()) {
        CreateQuestion createquestionDialog;
        createquestionDialog.setModal(true);
        createquestionDialog.exec();
    }
    else    {
        questionslocation.mkpath("E:/RockTestDatabase/Questions");
        CreateQuestion createquestionDialog;
        createquestionDialog.setModal(true);
        createquestionDialog.exec();
    }
}

void MainWindow::on_pushButton_CreateTest_clicked()
{
    MakeTest maketestDialog;
    maketestDialog.setModal(true);
    maketestDialog.exec();
}

void MainWindow::on_pushButton_EditHeader_clicked()
{
    QFile question(HeaderDir.absolutePath());
    if(!question.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::critical(this,"Lỗi nghiêm trọng","    Chưa tạo đầu đề    ");
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
        text=HeaderDir.absolutePath();
        doc->dynamicCall("Open(QVariant)", QDir::toNativeSeparators(text));
    }
}

void MainWindow::on_pushButton_EditFooter_clicked()
{
    QFile question(FooterDir.absolutePath());
    if(!question.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::critical(this,"Lỗi nghiêm trọng","    Chưa tạo chân đề    ");
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
        text=FooterDir.absolutePath();
        doc->dynamicCall("Open(QVariant)", QDir::toNativeSeparators(text));
    }
}

