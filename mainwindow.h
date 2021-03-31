#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QColorDialog>
#include <QColor>
#include <QPixmap>
#include <cstring>
#include <QScrollArea>
#include "dragableframe.h"
#include "dialog.h"
#include "rotate.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();
    void on_actionCreate_triggered();
    void on_actionSave_triggered();
    void Scroll();
    void checkRgb(int n, int n_color);
    int LoadFile(QString filename);
    void CreateCircleMenu();
    void CreateRotateMenu();
    void CreatePiecesMenu();
    void SetIcons();
    void on_actionAbout_program_2_triggered();
    void on_actionInfo_about_File_triggered();
    void on_actionChoosing_color_triggered();
    void on_actionSquare_triggered();
    void on_actionLine_thickness_triggered();
    void on_actionFill_color_triggered();
    void on_actionRgb_triggered();
    void on_actionRadius_and_center_coordinates_triggered();
    void on_actionSquare_coordinates_triggered();
    void on_RotateFullPicture_triggered();
    void on_RotatePartOfPicture_triggered();
    void on_actionStep_back_2_triggered();
    void on_actionBW_component_triggered();
    void on_actionCollage_triggered();
    void on_actionSwap_triggered();
    void on_actionSwap_4_pieces_in_circle_triggered();
    void on_actionPentagramm_2_triggered();

private:
    Ui::MainWindow *ui;
    QString filename;
    QColor chosen_color;
    DragableFrame* label;
    QScrollArea* scrollArea;
    char* good_filename;
    Rotate rt;
};

#endif // MAINWINDOW_H
