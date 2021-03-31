#include "dialog.h"

Dialog::Dialog(int temp)
{
    layout = new QGridLayout;
    pcmdOk = new QPushButton("&Ok");
    pcmdCancel = new QPushButton("&Cancel");
    connect(pcmdOk, SIGNAL(clicked()), SLOT(accept()));
    connect(pcmdCancel, SIGNAL(clicked()), SLOT(reject()));
    pcmdOk->setStyleSheet("background-color: green; "
                          "border-style: outset; "
                          "border-radius: 10px; "
                          "font: bold 14px; "
                          "min-width: 10em; "
                          "padding: 6px;");
    pcmdCancel->setStyleSheet("background-color: red; "
                              "border-style: outset; "
                              "border-radius: 10px; "
                              "font: bold 14px; "
                              "min-width: 10em; "
                              "padding: 6px;");

    switch (temp) {
        case 1:
            SquareDialog();
            break;
        case 2:
            RgbDialog();
            break;
        case 3:
            CircleAndRadiusDialog();
            break;
        case 4:
            CircleAndSquareDialog();
            break;
        case 5:
            ThicknessDialog();
            break;
        case 6:
            RotateDialog(1);
            break;
        case 7:
            RotateDialog(0);
            break;
        case 8:
            CollageDialog();
            break;
        case 9:
            SwapRectangleDialog();
            break;
        case 10:
            SwapCircleDialog();
            break;
    }

    setLayout(layout);
}

Dialog::~Dialog()
{
    delete layout;
    delete pcmdOk;
    delete pcmdCancel;
}

void Dialog::SquareDialog()
{
    line_size = new QLineEdit;
    QLabel* side_size = new QLabel("Side size: ");

    QLabel* info_about_point = new QLabel("The coordinates of the upper left corner\n"
                                          "are determined by the first click on the image.\n"
                                          "Other characteristics you can change\nby clicking on the Line format button");
    info_about_point->setStyleSheet("color: red");

    layout->addWidget(side_size, 0, 0);
    layout->addWidget(line_size, 0, 1);
    layout->addWidget(info_about_point, 1, 0);
    layout->addWidget(pcmdOk, 2, 0);
    layout->addWidget(pcmdCancel, 2, 1);
}

void Dialog::ThicknessDialog()
{
    thick = new QLineEdit;
    QLabel* set_thickness = new QLabel("Set thickness: ");

    layout->addWidget(set_thickness, 0, 0);
    layout->addWidget(thick, 0, 1);
    layout->addWidget(pcmdOk, 2, 0);
    layout->addWidget(pcmdCancel, 2, 1);
}

void Dialog::RgbDialog()
{
      red_box = new QComboBox;
      green_box = new QComboBox;
      blue_box = new QComboBox;
      QStringList list;
      list << "Select number" << "0" << "255";

      red_box->addItems(list);
      green_box->addItems(list);
      blue_box->addItems(list);

      QLabel* red_cmp = new QLabel("Select the value of the red component: ");
      QLabel* green_cmp = new QLabel("Select the value of the green component: ");
      QLabel* blue_cmp = new QLabel("Select the value of the blut component: ");

      layout->addWidget(red_cmp, 0, 0);
      layout->addWidget(red_box, 0, 1);
      layout->addWidget(green_cmp, 1, 0);
      layout->addWidget(green_box, 1, 1);
      layout->addWidget(blue_cmp, 2, 0);
      layout->addWidget(blue_box, 2, 1);
      layout->addWidget(pcmdOk, 3, 0);
      layout->addWidget(pcmdCancel, 3, 1);
}

void Dialog::CircleAndRadiusDialog()
{
    QLabel* enter_radius = new QLabel("Enter radius: ");
    QLabel* info_label = new QLabel("Сenter coordinates are determined\nby clicking on the picture");
    info_label->setStyleSheet("color: red;");
    radius = new QLineEdit;

    layout->addWidget(enter_radius, 0, 0);
    layout->addWidget(radius, 0, 1);
    layout->addWidget(info_label, 1, 0);
    layout->addWidget(pcmdOk, 3, 0);
    layout->addWidget(pcmdCancel, 3, 1);
}

void Dialog::CircleAndSquareDialog()
{
     QLabel* up_crd = new QLabel("Enter the coordinates of the upper left corner: ");
     QLabel* down_crd = new QLabel("Enter the coordinates of the lower right corner: ");

     x_left_coord = new QLineEdit;
     y_left_coord = new QLineEdit;
     x_right_coord = new QLineEdit;
     y_right_coord = new QLineEdit;

     layout->addWidget(up_crd, 0, 0);
     layout->addWidget(x_left_coord, 0, 1);
     layout->addWidget(y_left_coord, 0, 2);
     layout->addWidget(down_crd, 1, 0);
     layout->addWidget(x_right_coord, 1, 1);
     layout->addWidget(y_right_coord, 1, 2);
     layout->addWidget(pcmdOk, 2, 1);
     layout->addWidget(pcmdCancel, 2, 2);
}

void Dialog::RotateDialog(int f)
{
    QLabel* select_degree = new QLabel("Select the degree of rotation:");
    degree = new QComboBox;
    degree->addItem("Select number");
    degree->addItem("90");
    degree->addItem("180");
    degree->addItem("270");

    layout->addWidget(select_degree, 0, 0);
    layout->addWidget(degree, 0, 1);
    layout->addWidget(pcmdOk, 2, 0);
    layout->addWidget(pcmdCancel, 2, 1);
    if (!f)
    {
        QLabel* label = new QLabel("Coordinates of upper left corner\n"
                                   "are determined by press on the picture\n"
                                   "Coordinates of bottom right corner\n"
                                   "are determined by mouse release");
        label->setStyleSheet("color: red;");
        layout->addWidget(label, 1, 0);
    }
}

void Dialog::CollageDialog()
{
    n_col = new QLineEdit;
    m_col = new QLineEdit;
    QLabel* lb1 = new QLabel("Number of pictures in 1 line:");
    QLabel* lb2 = new QLabel("Number of pictures in 1 column:");

    layout->addWidget(lb1, 0, 0);
    layout->addWidget(n_col, 0, 1);
    layout->addWidget(lb2, 1, 0);
    layout->addWidget(m_col, 1, 1);
    layout->addWidget(pcmdOk, 2, 0);
    layout->addWidget(pcmdCancel, 2, 1);

}

void Dialog::SwapRectangleDialog()
{
    QLabel* lb1 = new QLabel("Choose the way of swaping:");
    QLabel* lb2 = new QLabel("Coordinates of upper left corner\n"
                             "are determined by press on the picture\n"
                             "Coordinates of bottom right corner\n"
                             "are determined by mouse release");
    lb2->setStyleSheet("color: red;");
    swapRec_box = new QComboBox;
    swapRec_box->addItem("Select way");
    swapRec_box->addItem("Diagonally");
    swapRec_box->addItem("By circle");

    layout->addWidget(lb1, 0, 0);
    layout->addWidget(swapRec_box, 0, 1);
    layout->addWidget(lb2, 1, 0);
    layout->addWidget(pcmdOk, 2, 0);
    layout->addWidget(pcmdCancel, 2, 1);
}

void Dialog::SwapCircleDialog()
{
    QLabel* lb1 = new QLabel("Choose the way of swaping:");
    QLabel* enter_radius = new QLabel("Enter radius: ");
    QLabel* info_label = new QLabel("Сenter coordinates are determined\nby clicking on the picture");
    info_label->setStyleSheet("color: red;");
    radius = new QLineEdit;
    swapCir_box = new QComboBox;
    swapCir_box->addItem("Select way");
    swapCir_box->addItem("Diagonally");
    swapCir_box->addItem("By circle");

    layout->addWidget(enter_radius, 0, 0);
    layout->addWidget(radius, 0, 1);
    layout->addWidget(lb1, 1, 0);
    layout->addWidget(swapCir_box, 1, 1);
    layout->addWidget(info_label, 2, 0);
    layout->addWidget(pcmdOk, 3, 0);
    layout->addWidget(pcmdCancel, 3, 1);
}

int Dialog::getSquareLineSize()
{
    return line_size->text().toInt();
}

int Dialog::getLineThickness()
{
    return thick->text().toInt();
}

int Dialog::getRgbNumber1()
{
    return red_box->currentIndex();
}

int Dialog::getRgbNumber2()
{
    return green_box->currentIndex();
}

int Dialog::getRgbNumber3()
{
    return blue_box->currentIndex();
}

int Dialog::getLeftXCoordinate()
{
    return x_left_coord->text().toInt();
}

int Dialog::getLeftYCoordinate()
{
    return y_left_coord->text().toInt();
}

int Dialog::getRightXCoordinate()
{
    return x_right_coord->text().toInt();
}

int Dialog::getRightYCoordinate()
{
    return y_right_coord->text().toInt();
}

int Dialog::getCircleRadius()
{
    return radius->text().toInt();
}

int Dialog::getDegree()
{
    return degree->currentIndex();
}

int Dialog::getN()
{
    return n_col->text().toInt();
}

int Dialog::getM()
{
    return m_col->text().toInt();
}

int Dialog::getSwapRecForm()
{
    return swapRec_box->currentIndex();
}

int Dialog::getSwapCirForm()
{
    return swapCir_box->currentIndex();
}

