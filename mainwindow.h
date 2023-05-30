#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "graph.h"
#include <vector>
#include <QMainWindow>
#include <algorithm>
#define edge pair<int,int>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    vector<pair<int, edge>> edges = {};

    void send_text_on_field0(vector<pair<int, edge>> s);
    void send_text_on_field1(vector<pair<int, edge>> s);

    void on_openButton_clicked();

    void on_saveVutton_clicked();

    void on_findSpanningTree_clicked();

private:
    Graph grap;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
