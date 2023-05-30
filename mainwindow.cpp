#include <fstream>
#include <Windows.h>
#include <string>
#include <QMessageBox>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include "graph.h"
#include <QFileDialog>
#include <vector>
#define edge pair<int,int>
using namespace std;


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->openButton, &QPushButton::clicked, this, &MainWindow::on_openButton_clicked);
    connect(ui->findTree, &QPushButton::clicked, this, &MainWindow::on_findSpanningTree_clicked);
    connect(ui->savButton, &QPushButton::clicked, this, &MainWindow::on_saveVutton_clicked);
}

void MainWindow::on_saveVutton_clicked()
{
    const QString fileName = QFileDialog::getOpenFileName(this, tr("Save file"), "", tr("Text Files (*.txt)"));

    if (fileName.isEmpty()) {
        QMessageBox::warning(this, tr("Error"), tr("File not found!"));
        return;
    }

    std::ofstream outfile(fileName.toStdString());
    if (!outfile.is_open()) {
        throw std::runtime_error("Error: Unable to open file for writing!");
    }
    outfile << "Edge :  Weight";
    outfile << '\n';
    for (const auto& component : MainWindow::grap.getT()) {

        outfile << component.second.first << " - " << component.second.second << " : "
                    << component.first;
        outfile << '\n';
    }
    outfile.close();
}

void MainWindow::on_openButton_clicked()
{
    const QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), "", tr("Text Files (*.txt)"));

    if (fileName.isEmpty()) {
        QMessageBox::warning(this, tr("Error"), tr("File not found!"));
        return;
    }

    std::ifstream file(fileName.toStdString());
    std::string line;

    while (getline(file, line)) {
        vector<int> nums = {};
        string delimiter = ",";
        size_t pos = 0;
        std::string token;
        while ((pos = line.find(delimiter)) != string::npos) {
            token = line.substr(0, pos);
            nums.push_back(stoi(token));
            line.erase(0, pos + delimiter.length());
        }
        MainWindow::edges.push_back(make_pair(nums[0], edge(nums[1],nums[2])));
    }

    MainWindow::grap = {(int)MainWindow::edges.size()};

    for(int i = 0; i < MainWindow::edges.size(); i++)
    {
        MainWindow::grap.AddWeightedEdge(
            MainWindow::edges[i].first,
            MainWindow::edges[i].second.first,
            MainWindow::edges[i].second.second
        );

    }
    MainWindow::send_text_on_field0(MainWindow::grap.getG());

    ui->findTree->setEnabled(true);
}

void MainWindow::send_text_on_field0(vector<pair<int, edge>> s) {

    ui->textEdit->append("Edge :  Weight");
    for(int i = 0; i < s.size() ;i++)
    {
        QString sd = QString("%1 - %2 : %3").arg(s[i].second.first)
                         .arg(s[i].second.second)
                         .arg(s[i].first);
        ui->textEdit->append(sd);
    }
}

void MainWindow::send_text_on_field1(vector<pair<int, edge>> s) {

    ui->textEdit_2->append("Edge :  Weight");
    for(int i = 0; i < s.size() ;i++)
    {
        QString sd = QString("%1 - %2 : %3").arg(s[i].second.first)
                         .arg(s[i].second.second)
                         .arg(s[i].first);
        ui->textEdit_2->append(sd);
    }
}

void MainWindow::on_findSpanningTree_clicked()
{
    MainWindow::grap.kruskal();
    MainWindow::send_text_on_field1(MainWindow::grap.getT());
    ui->savButton->setEnabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}


