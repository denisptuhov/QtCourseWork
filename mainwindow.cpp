#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    label = new DragableFrame;
    CreateCircleMenu();
    CreateRotateMenu();
    CreatePiecesMenu();
    SetIcons();

    label->getImg()->create();
    label->setPixmap(label->getImg()->toQPixmap(1));
    label->resize(label->getImg()->getWidth(),
                  label->getImg()->getHeight());
    label->getPnt()->LoadPixels(label->getImg()->getPixelsArr());
    label->getPnt()->LoadSize(label->getImg()->getWidth(),
                              label->getImg()->getHeight());
    Scroll();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete label;
}

void MainWindow::CreateCircleMenu()
{
    QMenu* menu = new QMenu;
    QAction* bt1 = new QAction("Radius and center coordinates");
    QAction* bt2 = new QAction("Square coordinates");
    bt1->setIcon(QIcon("D:/qt/course work/coursework/Icons/center_circle.png"));
    bt2->setIcon(QIcon("D:/qt/course work/coursework/Icons/square_and_circle.png"));
    menu->addAction(bt1);
    menu->addAction(bt2);
    connect(bt1, SIGNAL(triggered()), this, SLOT(on_actionRadius_and_center_coordinates_triggered()));
    connect(bt2, SIGNAL(triggered()), this, SLOT(on_actionSquare_coordinates_triggered()));
    ui->actionCircle_2->setMenu(menu);
}

void MainWindow::CreateRotateMenu()
{
    QMenu* menu = new QMenu;
    QAction* bt1 = new QAction("Full picture");
    QAction* bt2 = new QAction("Part of picture");
    bt1->setIcon(QIcon("D:/qt/course work/coursework/Icons/rotate_full.png"));
    bt2->setIcon(QIcon("D:/qt/course work/coursework/Icons/rotate_part.png"));
    menu->addAction(bt1);
    menu->addAction(bt2);
    connect(bt1, SIGNAL(triggered()), this, SLOT(on_RotateFullPicture_triggered()));
    connect(bt2, SIGNAL(triggered()), this, SLOT(on_RotatePartOfPicture_triggered()));
    ui->actionRotate->setMenu(menu);
}

void MainWindow::CreatePiecesMenu()
{
    QMenu* menu = new QMenu;
    QAction* bt1 = new QAction("Rectangle");
    QAction* bt2 = new QAction("Circle");
    bt1->setIcon(QIcon("D:/qt/course work/coursework/Icons/RectangleSwap.png"));
    bt2->setIcon(QIcon("D:/qt/course work/coursework/Icons/circle.png"));
    menu->addAction(bt1);
    menu->addAction(bt2);
    connect(bt1, SIGNAL(triggered()), this, SLOT(on_actionSwap_triggered()));
    connect(bt2, SIGNAL(triggered()), this, SLOT(on_actionSwap_4_pieces_in_circle_triggered()));
    ui->actionSwap_4_pieces_in_2->setMenu(menu);
}

void MainWindow::SetIcons()
{
    ui->actionRgb->setIcon(QIcon("D:/qt/course work/coursework/Icons/rgb.png"));
    ui->actionCircle_2->setIcon(QIcon("D:/qt/course work/coursework/Icons/circle.png"));
    ui->actionSquare->setIcon(QIcon("D:/qt/course work/coursework/Icons/square.png"));
    ui->actionStep_back_2->setIcon(QIcon("D:/qt/course work/coursework/Icons/step_back.png"));
    ui->actionRotate->setIcon(QIcon("D:/qt/course work/coursework/Icons/rotate.png"));
    ui->actionFill_color->setIcon(QIcon("D:/qt/course work/coursework/Icons/fill_color.jpg"));
    ui->actionLine_thickness->setIcon(QIcon("D:/qt/course work/coursework/Icons/thickness.png"));
    ui->actionChoosing_color->setIcon(QIcon("D:/qt/course work/coursework/Icons/line_color.jpg"));
    ui->actionOpen->setIcon(QIcon("D:/qt/course work/coursework/Icons/open_file.png"));
    ui->actionSave->setIcon(QIcon("D:/qt/course work/coursework/Icons/save_file.png"));
    ui->actionCreate->setIcon(QIcon("D:/qt/course work/coursework/Icons/create_file.png"));
    ui->actionInfo_about_File->setIcon(QIcon("D:/qt/course work/coursework/Icons/file_info.png"));
    ui->actionAbout_program_2->setIcon(QIcon("D:/qt/course work/coursework/Icons/info.png"));
    ui->actionBW_component->setIcon(QIcon("D:/qt/course work/coursework/Icons/bw.png"));
    ui->actionCollage->setIcon(QIcon("D:/qt/course work/coursework/Icons/collage.png"));
    ui->actionSwap->setIcon(QIcon("D:/qt/course work/coursework/Icons/RectangleSwap.png"));
    ui->actionSwap_4_pieces_in_2->setIcon(QIcon("D:/qt/course work/coursework/Icons/4.png"));
    ui->actionPentagramm_2->setIcon(QIcon("D:/qt/course work/coursework/Icons/pentagramm.png"));
}

void MainWindow::on_actionOpen_triggered()
{
    filename = QFileDialog::getOpenFileName(this, "Choose File", tr("C:/Users/denis/Desktop"), tr("*.bmp"));
    if (!filename.isEmpty() && !LoadFile(filename))
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Info",
                                                                  "Do you want to try again?");
        if (reply == QMessageBox::Yes)
            on_actionOpen_triggered();
    }
}

int MainWindow::LoadFile(QString filename)
{
    good_filename = new char[filename.length() + 1];
    std::strcpy(good_filename, filename.toLatin1().constData());

    int f = label->getImg()->load(good_filename);
    if (f <= 0)
    {
        QMessageBox::warning(this, "Error", "I can't open this file or his type is uncorrect!");
        return 0;
    }

    label->resize(label->getImg()->getWidth(), label->getImg()->getHeight());
    label->setPixmap(label->getImg()->toQPixmap(1));
    label->getPnt()->LoadSize(label->getImg()->getWidth(), label->getImg()->getHeight());
    label->getPnt()->LoadPixels(label->getImg()->getPixelsArr());
    label->disconnectOptions();

    delete [] good_filename;
    return 1;
}

void MainWindow::Scroll()
{
    label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    label->setScaledContents(true);

    scrollArea = new QScrollArea;
    scrollArea->setStyleSheet("background-color: grey");
    scrollArea->setWidget(label);
    setCentralWidget(scrollArea);
}

void MainWindow::on_actionCreate_triggered()
{
    if (!(label->getImg()->isNull()))
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Information",
                                                                  "Do you want to save current image?");
        if (reply == QMessageBox::Yes)
            on_actionSave_triggered();

    }

    label->getImg()->create();
    label->setPixmap(label->getImg()->toQPixmap(1));
    label->resize(label->getImg()->getWidth(),
                  label->getImg()->getHeight());
    label->getPnt()->LoadPixels(label->getImg()->getPixelsArr());
    label->getPnt()->LoadSize(label->getImg()->getWidth(),
                              label->getImg()->getHeight());
    label->disconnectOptions();
}

void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить как...", "./", "*.bmp");
    if (fileName.isNull()) return;

    good_filename = new char[fileName.length() + 1];
    std::strcpy(good_filename, fileName.toLatin1().constData());
    for (unsigned int i = 0; i < std::strlen(good_filename); i++) if (good_filename[i] == '\\') good_filename[i] = '/';
    label->getImg()->save(good_filename);
}

void MainWindow::on_actionAbout_program_2_triggered()
{
    QMessageBox::information(this, "Info", "This program was created by Denis Ptuhov using the QtCreator(v. 4.8.2)\n"
                                           "HotKeys:\n"
                                           "\t1) Ctrl + O - Open File\n"
                                           "\t2) Ctrl + S - Save File\n"
                                           "\t3) Ctrl + I - Information about file\n"
                                           "\t4) Ctrl + R - Create File");
}

void MainWindow::on_actionInfo_about_File_triggered()
{
    QMessageBox::information(this, "File info", label->getImg()->info());
}

void MainWindow::on_actionChoosing_color_triggered()
{
    chosen_color = QColorDialog::getColor(Qt::black, this, "Choosing color");
    if (chosen_color.isValid())
        label->getPnt()->UpdateColor(chosen_color);

}

void MainWindow::on_actionSquare_triggered()
{
    Dialog dialog(1);
    if (QDialog::Accepted == dialog.exec())
    {

        int n = dialog.getSquareLineSize();
        if (n <= 0)
        {
            QMessageBox::warning(this, "Wrong data", "Given coordinates is uncorrect");
            return;
        }
        label->activateDoingSquare(n);
    }
    else
        label->disconnectOptions();
}

void MainWindow::on_actionRgb_triggered()
{
    Dialog dialog(2);
    if (QDialog::Accepted == dialog.exec())
    {
        int n = dialog.getRgbNumber1();
        checkRgb(n, 0);
        n = dialog.getRgbNumber2();
        checkRgb(n, 1);
        n = dialog.getRgbNumber3();
        checkRgb(n, 2);

        label->setPixmap(label->getImg()->toQPixmap(1));
    }
    else
        label->disconnectOptions();
}

void MainWindow::checkRgb(int n, int n_color)
{
    if (n == 1)
        label->getPnt()->CreateRgb(n_color, 0);
    else if (n == 2)
        label->getPnt()->CreateRgb(n_color, 255);
}

void MainWindow::on_actionRadius_and_center_coordinates_triggered()
{
    Dialog dialog(3);
    if (QDialog::Accepted == dialog.exec())
    {
        int n = dialog.getCircleRadius();
        if (n <= 0)
        {
            QMessageBox::warning(this, "Wrong data", "Given coordinates is uncorrect");
            return;
        }

        label->activateDoingCircle(n);
    }
    else
        label->disconnectOptions();
}

void MainWindow::on_actionSquare_coordinates_triggered()
{
    Dialog dialog(4);
    if (QDialog::Accepted == dialog.exec())
    {
        QPoint start_point(dialog.getLeftXCoordinate(), dialog.getLeftYCoordinate());
        QPoint current_point(dialog.getRightXCoordinate(), dialog.getRightYCoordinate());

        if (current_point.y() - start_point.y() != current_point.x() - start_point.x() ||
            start_point.x() > label->getImg()->getWidth() || start_point.x() <= 0 ||
            start_point.y() > label->getImg()->getHeight() || start_point.y() <= 0 ||
            current_point.x() > label->getImg()->getWidth() || current_point.x() <= 0 ||
            current_point.y() > label->getImg()->getHeight() || current_point.y() <= 0)
        {
            QMessageBox::warning(this, "Wrong data", "Given coordinates is uncorrect");
            return;
        }
        label->getPnt()->CreateCircleUsingSquare(start_point, current_point);
        label->setPixmap(label->getImg()->toQPixmap(1));

    }
    else
        label->disconnectOptions();
}

void MainWindow::on_actionLine_thickness_triggered()
{
    Dialog dialog(5);
    if (QDialog::Accepted == dialog.exec())
    {
        int n = dialog.getLineThickness();
        if (n <= 0)
        {
            QMessageBox::warning(this, "Wrong data", "Given value is uncorrect");
            return;
        }
        label->getPnt()->UpdateThickness(n);
    }
    else
        label->disconnectOptions();
}

void MainWindow::on_actionFill_color_triggered()
{
    QColor fill_color = QColorDialog::getColor(Qt::white, this, "Choosing fill color");

    if (!fill_color.isValid())
        label->getPnt()->disconnectFill();
    else
        label->getPnt()->UpdateFillColor(fill_color);
}

void MainWindow::on_RotateFullPicture_triggered()
{
    Dialog dialog(6);
    if (dialog.exec() == QDialog::Accepted)
    {
        rt.LoadPixels(label->getImg()->getPixelsArr());
        rt.LoadSize(label->getImg()->getWidth(),
                    label->getImg()->getHeight());

        int n = dialog.getDegree();
        switch(n)
        {
            case 1:
                rt.RotateOn90Full();
                label->getImg()->SwapCoordinates();
                label->resize(label->getImg()->getWidth(),
                              label->getImg()->getHeight());
                break;
            case 2:
                rt.RotateOn180Full();
                break;
            case 3:
                rt.RotateOn270Full();
                label->getImg()->SwapCoordinates();
                label->resize(label->getImg()->getWidth(),
                              label->getImg()->getHeight());
                break;
        }
    }

    label->getPnt()->LoadSize(label->getImg()->getWidth(),
                              label->getImg()->getHeight());
    label->setPixmap(label->getImg()->toQPixmap(1));
}

void MainWindow::on_RotatePartOfPicture_triggered()
{
    Dialog dialog(7);
    if (dialog.exec() == QDialog::Accepted)
        label->activateDoingRotate(dialog.getDegree());

}

void MainWindow::on_actionStep_back_2_triggered()
{
    QPixmap tmp = label->getImg()->toOldQPixmap();
    label->resize(label->getImg()->getWidth(),
                  label->getImg()->getHeight());
    if (!tmp.isNull())
         label->setPixmap(tmp);
    label->disconnectOptions();
}

void MainWindow::on_actionBW_component_triggered()
{
    label->getPnt()->CreateBW();
    label->setPixmap(label->getImg()->toQPixmap(1));
}

void MainWindow::on_actionCollage_triggered()
{
    Dialog dialog(8);
    if (dialog.exec() == QDialog::Accepted)
    {
        int n = dialog.getN(),
            m = dialog.getM();
        if (n <= 0 || m <= 0)
        {
            QMessageBox::warning(this, "Error", "Uncorrect value!");
            return;
        }

        label->getPnt()->CreateCollage(n, m);
        label->setPixmap(label->getImg()->toQPixmap(1));
    }
    else
        label->disconnectOptions();
}

void MainWindow::on_actionSwap_triggered()
{
    Dialog dialog(9);
    if (dialog.exec() == QDialog::Accepted)
    {
        int n = dialog.getSwapRecForm();
        if (n)
            label->activateDoingRecSwap(n);
    }
    else
        label->disconnectOptions();
}

void MainWindow::on_actionSwap_4_pieces_in_circle_triggered()
{
    Dialog dialog(10);
    if (dialog.exec() == QDialog::Accepted)
    {
        int n = dialog.getSwapCirForm();
        if (n)
            label->activateDoingCirSwap(n, dialog.getCircleRadius());
    }
    else
        label->disconnectOptions();
}

void MainWindow::on_actionPentagramm_2_triggered()
{
    Dialog dialog(3);
    if (dialog.exec() == QDialog::Accepted)
    {
        int r = dialog.getCircleRadius();
        if (r <= 0)
        {
            QMessageBox::warning(this, "Error", "Uncorrect value!");
            return;
        }
        label->activateDoingPentagramm(r);
    }
}
