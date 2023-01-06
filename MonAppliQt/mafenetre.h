#ifndef MAFENETRE_H
#define MAFENETRE_H

#include <QWidget>
#include <QmainWindow>

namespace Ui {
    class MaFenetre;}

class MaFenetre : public QMainWindow{
        Q_OBJECT
public:
        explicit MaFenetre(QWidget *parent = 0);
        ~MaFenetre();

private slots:
    void on_Connect_clicked();
    void on_Deconnection_clicked();
    void on_Quitter_clicked();
    void on_Selectionner_clicked();
    void on_Maj_clicked();
    void on_spinBoxincr_clicked();
    void on_spinBoxdecr_clicked();




private:
    Ui::MaFenetre *ui;
};

#endif // MAFENETRE_H
