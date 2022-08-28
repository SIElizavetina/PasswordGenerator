#include "password.h"
#include "ui_password.h"
#include "random"
Password::Password(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Password)
{
    ui->setupUi(this);

    this->setWindowIcon(QIcon(":/new/prefix1/icon.png"));

    srand(static_cast<unsigned int>(time(0)));

    connect( ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index){Changed_level(index);});
}

Password::~Password()
{
    delete ui;
}

void Password::Changed_level(int i)
{
    switch (i)
    {
    case 0: level=0;
        break;
    case 1: level=1;
        break;
    case 2: level=2;
    default:
        break;
    }
}

int Password::random(int min, int max)
{
    //равномерное распределение рандомных чисел в заданном диапазоне
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);

}

void Password::on_pushButton_clicked()
{
    result(level);
}

void Password::result(int level)
{
    switch (level)
    {
    case 0: light();
        break;
    case 1: middle();
        break;
    case 2: hard();
    default:
        break;
    }
}

void Password::light()
{
    int lenght = random(5, 8); //длина пароля
    std::vector <char> parol(lenght); //вектор пароля

    int count_num = random(2, 4); //количество цифр в пароле

    for (int i = 0; i < lenght; ++i) //заполняем весь пароль строчными буквами
    {
        parol[i]= random('a', 'z');
    }

    gener_num(parol, count_num); //заполняем пароль цифрами
    output_parol(parol);
}
void Password::middle()
{
    int lenght = random(8, 12); //длина пароля
    std::vector <char> parol(lenght); //вектор пароля

    int count_num = random(2, 4); //количество цифр в пароле

    for (int i = 0; i < lenght; ++i) //заполняем весь пароль строчными или заглавными буквами
    {
        if(random(0, 1)) parol[i] = random('a', 'z');
        else parol[i] = random('A', 'Z');
    }
    gener_num(parol, count_num); //заполняем пароль цифрами
    output_parol(parol);
}

void Password::hard()
{
    int lenght = random(12, 18); //длина пароля
    std::vector <char> parol(lenght); //вектор пароля

    //int count_num = random(2, 4); //количество цифр в пароле
    int count_simb = random(2, 7); //количество символов в пароле
    std::vector <char> simb = { '!','@', '#', '$', '&', '*', '+', '=', '?', '%', ';', ':'}; //символы, которые будут вписаны в пароль

    for (int i = 0; i < lenght; ++i) //заполняем весь пароль строчными или заглавными буквами
    {
        if (random(0, 1)) parol[i] = random('a', 'z');
        else parol[i] = random('A', 'Z');
    }

    std::vector <int> v(count_simb); //вектор, где хранятся индексы, на которых будут стоять цифры
    for (int i = 0; i < count_simb; ++i)
    {
        int index = random(0, parol.size() - 1); //выбирается индекс
        if (check_index(v, index, i)) //индекс проверяется на повторения
        {
            v[i] = index;
            if (random(0, 1))
            {//заполнение цифрами
                int num = random(0, 9);//выбирается цифра
                parol[index] = num + '0';//пароль заполняется цифрами
            }
            else
            {//заполнение символами
                int num = random(0, simb.size()-1);//выбирается цифра
                parol[index] = simb[num];//пароль заполняется цифрами
            }
        }
        else i--;
    }
    output_parol(parol);
}

void Password::gener_num(std::vector <char>& parol, int count_num)
{
    std::vector <int> v(count_num); //вектор, где хранятся индексы, на которых будут стоять цифры
    for (int i = 0; i < count_num; ++i)
    {
        int index = random(0, parol.size() - 1); //выбирается индекс
        if (check_index(v, index, i)) //индекс проверяется на повторения
        {
            v[i] = index;
            int num = random(0, 9);//выбирается цифра
            parol[index] = num + '0';//пароль заполняется цифрами
        }
        else i--;
    }
}

bool Password::check_index(std::vector <int>& v, int index, int i) //проверяет, есть ли уже такой индекс для заполнения
{
    for (int j = 0; j < i; ++j)
    {
        if (v[j] == index)
        {
            return false;
        }
    }

    return true;
}

void Password::output_parol(std::vector <char>& parol)
{
    str_parol.clear();
    str_parolClose.clear();

    for(int i=0; i<parol.size(); ++i)
    {
       str_parol.append(QString(parol[i]));
       str_parolClose.append("*");
    }
    ui->lineEdit->setText(str_parolClose);
    flag=0;
    ui->pushButtonOpen->setIcon(QIcon(":/new/prefix1/close.png"));
}

void Password::on_pushButtonOpen_clicked()
{
    if(flag)
    {
        ui->lineEdit->setText(str_parolClose);
        ui->pushButtonOpen->setIcon(QIcon(":/new/prefix1/close.png"));
        flag=0;
    }
    else
    {
        ui->lineEdit->setText(str_parol);
        ui->pushButtonOpen->setIcon(QIcon(":/new/prefix1/open.png"));
        flag=1;
    }
}
