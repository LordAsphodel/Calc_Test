#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <Qt>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_DigitButton_1_clicked();

    void on_DigitButton_2_clicked();

    void on_DigitButton_3_clicked();

    void on_DigitButton_4_clicked();

    void on_DigitButton_5_clicked();

    void on_DigitButton_6_clicked();

    void on_DigitButton_7_clicked();

    void on_DigitButton_8_clicked();

    void on_DigitButton_9_clicked();

    void on_DigitButton_0_clicked();

    void on_SetDotButton_clicked();

    void on_ResetButton_clicked();

    void AppendDigitToLCD(int input_digit);

    void on_ClearMemoryButton_clicked();

    void on_AddMemoryButton_clicked();

    void on_MinusMemoryButton_clicked();

    void on_InvertSignButton_clicked();

    void ClearDisplay();

    void on_ShowMemoryButton_clicked();

    void on_ReplaceMemoryButton_clicked();

    void CheckMemory();

    void on_SumButton_clicked();

    void on_MinusButton_clicked();

    void on_MultiplyButton_clicked();

    void on_DivisionButton_clicked();

    void on_ResultButton_clicked();

    void on_SquareButton_clicked();

    void on_SquareRootButton_clicked();

    void ShowAboutWindow();

    void on_menu_action_About_triggered();

    void on_menu_action_Exit_triggered();

public slots:

    void SetInitValues();

private:
    Ui::MainWindow *ui;

protected:
   virtual void keyPressEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H
