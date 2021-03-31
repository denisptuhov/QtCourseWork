#ifndef DIALOG_H
#define DIALOG_H

#include <QColor>
#include <QString>
#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QColorDialog>
#include <QDialogButtonBox>
#include <QComboBox>
#include <QMessageBox>
#include <QFormLayout>
#include <QScrollBar>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(int term);
    ~Dialog();
    int getSquareLineSize();
    int getLineThickness();
    int getRgbNumber1();
    int getRgbNumber2();
    int getRgbNumber3();
    int getLeftXCoordinate();
    int getLeftYCoordinate();
    int getRightXCoordinate();
    int getRightYCoordinate();
    int getCircleRadius();
    int getDegree();
    int getN();
    int getM();
    int getSwapRecForm();
    int getSwapCirForm();
    void SquareDialog();
    void ThicknessDialog();
    void RgbDialog();
    void CircleAndSquareDialog();
    void CircleAndRadiusDialog();
    void RotateDialog(int f);
    void CollageDialog();
    void SwapRectangleDialog();
    void SwapCircleDialog();

private:
    QLineEdit* thickness;
    QLineEdit* line_size;
    QLineEdit* radius;
    QLineEdit* x_left_coord;
    QLineEdit* y_left_coord;
    QLineEdit* x_right_coord;
    QLineEdit* y_right_coord;
    QLineEdit* thick;
    QLineEdit* n_col;
    QLineEdit* m_col;
    QPushButton* pcmdOk;
    QPushButton* pcmdCancel;
    QGridLayout* layout;
    QComboBox* swapCir_box;
    QComboBox* red_box;
    QComboBox* green_box;
    QComboBox* blue_box;
    QComboBox* degree;
    QComboBox* swapRec_box;
};

#endif // DIALOG_H
