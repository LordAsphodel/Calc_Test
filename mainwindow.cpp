#include <QKeyEvent>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stdlib.h"
#include "math.h"
#include "stdio.h"
#include <limits>
#include "aboutwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

double temp_value;      //вспомогательное значение для считывания кнопок
QString temp_string;    //вспомогательная строка для считывания кнопок
int digits_count;       //количество цифр для ввода
int digit_to_append;    //какую цифру добавлять
int zeros_count;        //какое количество нулей добавить надо
bool dot_used;          //использовалась ли точка при вводе текущем
double memory_value;    //значение в памяти
double value_a, value_b;//величины, над которыми будут совершаться действия
double result_value;    //переменная для хранения результата
double last_value_a;
double last_value_b;

void MainWindow::ShowAboutWindow()
{
    AboutWindow* about_window = new AboutWindow();
    about_window->show();
}

enum CalculatorStates       //Состояния калькулятора
{
    normal,         //обычное
    dotted_state,   //режим ввода точки
    dot_zeros_input //режим ввода нулей
};
CalculatorStates current_calc_state = normal; //текущее состояние калькулятора

enum MathOperatoinList
{
    get_sum_value,      //суммировать
    get_difference,     //вычесть
    get_multiplication, //умножить
    get_division,       //поделить
    none                //отсутствует выбор
};
MathOperatoinList operation_chosen  = none;

enum ValueOrder
{
    first_value,
    second_value
};
ValueOrder current_value_order = first_value;

void MainWindow::SetInitValues()
{
    temp_value = 0;                 //вспомогательное значение для считывания кнопок
    temp_string = "";               //вспомогательная строка для считывания кнопок
    digits_count = 16;              //количество цифр для ввода
    digit_to_append = 0;            //какую цифру добавлять
    zeros_count = 0;                //какое количество нулей добавить надо
    dot_used = false;               //использовалась ли точка при вводе текущем
    ui->OutputField->display(0);    //занулить число в зоне вывода
    memory_value = 0;               //значение в памяти
    ui->MemoryStateIndicator->setText(""); //Убрать текст из индикатора памяти
    current_calc_state = normal;    //текущее состояние калькулятора
    ui->ClearMemoryButton->setDisabled(true); //Сделать недоступной кнопку очистки памяти
    ui->ShowMemoryButton->setDisabled(true); //Сделать недоступной кнопку показа памяти
    operation_chosen  = none;
    current_value_order = first_value;
}

void MainWindow::CheckMemory()
{
    if (memory_value != 0)
    {
        ui->MemoryStateIndicator->setText(" M");
        ui->ClearMemoryButton->setEnabled(true); //Сделать кнопку очистки памяти доступной
        ui->ShowMemoryButton->setEnabled(true); //Сделать кнопку показа памяти доступной
    }
    if (memory_value == 0)
    {
        ui->MemoryStateIndicator->setText("");
        ui->ClearMemoryButton->setDisabled(true); //Сделать недоступной кнопку очистки памяти
        ui->ShowMemoryButton->setDisabled(true); //Сделать недоступной кнопку показа памяти
    }
}

void MainWindow::ClearDisplay()
{
    temp_value = 0;                 //вспомогательная строка для считывания кнопок
    temp_string = "";               //вспомогательная строка для считывания кнопок
    digits_count = 16;              //количество цифр для ввода
    digit_to_append = 0;            //какую цифру добавлять
    zeros_count = 0;                //какое количество нулей добавить надо
    dot_used = false;               //использовалась ли точка при вводе текущем
    ui->OutputField->display(0);    //занулить число в зоне вывода
    if(operation_chosen == none)
    {
        CheckMemory();
    }
    current_calc_state = normal; //текущее состояние калькулятора
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int key=event->key();//event->key() - целочисленный код клавиши
    //QString str = QString(QChar(key));
    if (key>=Qt::Key_0 && key<=Qt::Key_9)
    { //Цифровые клавиши 0..9
        switch (key)
        {
        case Qt::Key_0:
        {
            on_DigitButton_0_clicked();
            break;
        }
        case Qt::Key_1:
        {
            on_DigitButton_1_clicked();
            break;
        }
        case Qt::Key_2:
        {
            on_DigitButton_2_clicked();
            break;
        }
        case Qt::Key_3:
        {
            on_DigitButton_3_clicked();
            break;
        }
        case Qt::Key_4:
        {
            on_DigitButton_4_clicked();
            break;
        }
        case Qt::Key_5:
        {
            on_DigitButton_5_clicked();
            break;
        }
        case Qt::Key_6:
        {
            on_DigitButton_6_clicked();
            break;
        }
        case Qt::Key_7:
        {
            on_DigitButton_7_clicked();
            break;
        }
        case Qt::Key_8:
        {
            on_DigitButton_8_clicked();
            break;
        }
        case Qt::Key_9:
        {
            on_DigitButton_9_clicked();
            break;
        }
        default:
            break;
        }
    }
    else if (key==Qt::Key_Backspace)
    { //BackSpace стирает символ
        temp_value = ui->OutputField->value();
        temp_string.setNum(temp_value,'g',digits_count);
        if(current_calc_state == normal)
        {
            if(dot_used == false)
            {
                if(temp_string.length() >= 1)
                {
                    temp_string = temp_string.left(temp_string.length()-1);
                }
                if(temp_string.length() < 1)
                {
                    temp_string = temp_string = "0";
                }
            }
            if(dot_used == true)
            {
                if (temp_string[temp_string.length()-1] != '.')
                {
                    if(temp_string.length() >= 1)
                    {
                        temp_string = temp_string.left(temp_string.length()-1);
                    }
                    if(temp_string.length() < 1)
                    {
                        temp_string = temp_string = "0";
                        dot_used = 0;
                    }
                }
                if (temp_string[temp_string.length()-1] == '.')
                {
                    temp_string = temp_string.left(temp_string.length()-1);
                    dot_used = false;
                }
            }
        }
        if(current_calc_state == dotted_state)
        {
            current_calc_state = normal;
            if(operation_chosen == none)
            {
                CheckMemory();
            }
        }
        if(current_calc_state == dot_zeros_input)
        {
            if (zeros_count > 0)
            {
                zeros_count--;
            }
        }
        temp_value = temp_string.toDouble();
        ui->OutputField->display(temp_value);
        if(zeros_count == 0)
        {
            if(operation_chosen == none)
            {
                CheckMemory();
            }
            current_calc_state = normal;
        }
        if(zeros_count != 0)
        {
            ui->MemoryStateIndicator->setText("Z="+QString::number(zeros_count));
        }
        //        label1->setText();
    }
    else if (key==Qt::Key_Delete)
    { //Delete стирает всё
        on_ResetButton_clicked();
    }
    else if (key==Qt::Key_Plus)
    {
        on_SumButton_clicked();
    }
    else if (key==Qt::Key_Minus)
    {
        on_MinusButton_clicked();
    }
    else if (key==Qt::Key_Comma)
    {
        on_MultiplyButton_clicked();
    }
    else if (key==Qt::Key_Slash)
    {
        on_DivisionButton_clicked();
    }
    else if ((key == Qt::Key_Equal) || (key == Qt::Key_Enter))
    {
        on_ResultButton_clicked();
    }
    else if (key==Qt::Key_Period)
    {
        on_SetDotButton_clicked();
    }
    else if (key==Qt::Key_C)
    {
        ClearDisplay();
    }
    else if (key==Qt::Key_O)
    {
        ShowAboutWindow();
    }
}


void MainWindow::AppendDigitToLCD(int input_digit)
{
    if(operation_chosen != none && current_value_order == first_value)
    {
        ClearDisplay();
        current_value_order = second_value;
    }
    //если вводятся цифры от 1 до 9
    for(int i = 1; i <= 9; i++)
    {
        if (i == input_digit)
        {
            temp_value = ui->OutputField->value();
            temp_string.setNum(temp_value,'g',digits_count);
            if(temp_string.length() <= digits_count)
            {
                if(current_calc_state == normal)
                {
                    temp_string.append(QString::number(input_digit));
                }
                if(current_calc_state == dotted_state)
                {
                    temp_string.append(".");
                    temp_string.append(QString::number(input_digit));
                    dot_used = true;
                    current_calc_state = normal;
                }
                if(current_calc_state == dot_zeros_input)
                {
                    if(dot_used != true)
                    {
                        temp_string.append(".");
                    }
                    for(int j = 1; j <= zeros_count; j++)
                    {
                        temp_string.append("0");
                    }
                    temp_string.append(QString::number(input_digit));
                    dot_used = true;
                    current_calc_state = normal;
                    zeros_count = 0;
                }
            }
            temp_value = temp_string.toDouble();
            ui->OutputField->display(temp_value);
            if(operation_chosen == none)
            {
                CheckMemory();
            }
        }
    }
    //если вводятся нули
    if(input_digit == 0)
    {
        temp_value = ui->OutputField->value();
        temp_string.setNum(temp_value);
        temp_string.setNum(temp_value,'g',digits_count);
        if(temp_string.length() <= digits_count)
        {
            if(current_calc_state == normal)
            {
                temp_string.append("0");
            }
            if(current_calc_state == dotted_state)
            {
                //temp_string.append(".0");
                //dot_used = true;
                //current_calc_state = normal;
                current_calc_state = dot_zeros_input;
            }
            if (dot_used == true)
            {
                current_calc_state = dot_zeros_input;
            }
            if((current_calc_state == dot_zeros_input))
            {
                if(zeros_count <= digits_count - 3 - temp_string.length())
                {
                    zeros_count++;
                    ui->MemoryStateIndicator->setText("Z="+QString::number(zeros_count));
                }
            }
        }
        temp_value = temp_string.toDouble();
        ui->OutputField->display(temp_value);
    }
    temp_string = "";
    temp_value = 0;
}

void MainWindow::on_DigitButton_1_clicked()
{
    digit_to_append = 1;
    AppendDigitToLCD(digit_to_append);
}

void MainWindow::on_DigitButton_2_clicked()
{
    digit_to_append = 2;
    AppendDigitToLCD(digit_to_append);
}

void MainWindow::on_DigitButton_3_clicked()
{
    digit_to_append = 3;
    AppendDigitToLCD(digit_to_append);
}

void MainWindow::on_DigitButton_4_clicked()
{
    digit_to_append = 4;
    AppendDigitToLCD(digit_to_append);
}

void MainWindow::on_DigitButton_5_clicked()
{
    digit_to_append = 5;
    AppendDigitToLCD(digit_to_append);
}

void MainWindow::on_DigitButton_6_clicked()
{
    digit_to_append = 6;
    AppendDigitToLCD(digit_to_append);
}

void MainWindow::on_DigitButton_7_clicked()
{
    digit_to_append = 7;
    AppendDigitToLCD(digit_to_append);
}

void MainWindow::on_DigitButton_8_clicked()
{
    digit_to_append = 8;
    AppendDigitToLCD(digit_to_append);
}

void MainWindow::on_DigitButton_9_clicked()
{
    digit_to_append = 9;
    AppendDigitToLCD(digit_to_append);
}

void MainWindow::on_DigitButton_0_clicked()
{
    digit_to_append = 0;
    AppendDigitToLCD(digit_to_append);
}

void MainWindow::on_SetDotButton_clicked()
{
    temp_value = ui->OutputField->value();
    temp_string.setNum(temp_value,'g',digits_count);
    if(temp_string.length() <= digits_count - 2)
    {
        if(dot_used == false)
        {
            current_calc_state = dotted_state;
            ui->MemoryStateIndicator->setText("Dot.");
        }
    }
    temp_string = "";
    temp_value = 0;
}

void MainWindow::on_ResetButton_clicked()
{
    SetInitValues();
}

void MainWindow::on_ClearMemoryButton_clicked()
{
    memory_value = 0;
    CheckMemory();
}

void MainWindow::on_AddMemoryButton_clicked()
{
    temp_value = ui->OutputField->value();
    memory_value += temp_value;
    CheckMemory();
    temp_value = 0;
}

void MainWindow::on_MinusMemoryButton_clicked()
{
    temp_value = ui->OutputField->value();
    memory_value -= temp_value;
    CheckMemory();
    temp_value = 0;
}

void MainWindow::on_InvertSignButton_clicked()
{
    temp_value = ui->OutputField->value();
    ui->OutputField->display(-temp_value);
}

void MainWindow::on_ShowMemoryButton_clicked()
{
    ui->OutputField->display(memory_value);
}

void MainWindow::on_ReplaceMemoryButton_clicked()
{
    temp_value = ui->OutputField->value();
    memory_value = temp_value;
    CheckMemory();
}

void MainWindow::on_SumButton_clicked()
{
    if(current_value_order == second_value)
    {
        on_ResultButton_clicked();
    }
    operation_chosen = get_sum_value;
    ui->MemoryStateIndicator->setText("Sum");
    current_calc_state = normal;
    value_a = ui->OutputField->value();
    //current_value_order = first_value;
}

void MainWindow::on_MinusButton_clicked()
{
    if(current_value_order == second_value)
    {
        on_ResultButton_clicked();
    }
    operation_chosen = get_difference;
    ui->MemoryStateIndicator->setText("Min");
    current_calc_state = normal;
    value_a = ui->OutputField->value();
    //current_value_order = first_value;
}

void MainWindow::on_MultiplyButton_clicked()
{
    if(current_value_order == second_value)
    {
        on_ResultButton_clicked();
    }
    operation_chosen = get_multiplication;
    ui->MemoryStateIndicator->setText("Mul");
    current_calc_state = normal;
    value_a = ui->OutputField->value();
    //current_value_order = first_value;

}

void MainWindow::on_DivisionButton_clicked()
{
    if(current_value_order == second_value)
    {
        on_ResultButton_clicked();
    }
    operation_chosen = get_division;
    ui->MemoryStateIndicator->setText("Div");
    current_calc_state = normal;
    value_a = ui->OutputField->value();
    //current_value_order = first_value;

}

void MainWindow::on_ResultButton_clicked()
{
    if(current_value_order == first_value)
    {
        value_b = value_a;
        value_a = ui->OutputField->value();
    }
    if(current_value_order == second_value)
    {
        value_b = ui->OutputField->value();
    }

    switch (operation_chosen)
    {
    case get_sum_value:
    {
        result_value = value_a + value_b;
        break;
    }
    case get_difference:
    {
        result_value = value_a - value_b;
        break;
    }
    case get_multiplication:
    {
        result_value = value_a * value_b;
        break;
    }
    case get_division:
    {
        if(value_b != 0)
        {
            result_value = value_a / value_b;
        }
        if(value_b == 0)
        {
            result_value = std::numeric_limits<double>::max();
        }
        break;
    }
    default:
        break;
    }

    ui->OutputField->display(result_value);
    current_value_order = first_value;
    if(current_value_order == first_value)
    {
        value_a = value_b;
    }
}

void MainWindow::on_SquareButton_clicked()
{
    value_a = ui->OutputField->value();
    result_value = pow(value_a,2);
    ui->OutputField->display(result_value);
}

void MainWindow::on_SquareRootButton_clicked()
{
    value_a = ui->OutputField->value();
    if (value_a >= 0)
    {
        result_value = sqrt(value_a);
    }
    if (value_a < 0)
    {
        result_value = sqrt(-value_a);
    }
    ui->OutputField->display(result_value);
}

void MainWindow::on_menu_action_About_triggered()
{
    ShowAboutWindow();
}

void MainWindow::on_menu_action_Exit_triggered()
{
    this->close();
}
