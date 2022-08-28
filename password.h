#ifndef PASSWORD_H
#define PASSWORD_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Password; }
QT_END_NAMESPACE

class Password : public QMainWindow
{
    Q_OBJECT

public:
    Password(QWidget *parent = nullptr);
    ~Password();

    QString str_parol, str_parolClose;
    bool flag=0;

    int level=0;
    void Changed_level(int i); //переопределения системы счисления выводимого числа
    int random(int min, int max);
    void result(int level);

    bool check_index(std::vector <int>& v, int index, int i);
    void gener_num(std::vector <char>& parol, int count_num);

    void output_parol(std::vector <char>& parol);

    void light();
    void middle();
    void hard();

private slots:

    void on_pushButton_clicked();
    void on_pushButtonOpen_clicked();

private:
    Ui::Password *ui;
};
#endif // PASSWORD_H
