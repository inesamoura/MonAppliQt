
#include "mafenetre.h"
#include "ui_mafenetre.h"

#include"MfErrNo.h"
#include"Sw_Device.h"
#include"Sw_Mf_Classic.h"
#include"Sw_ISO14443A-3.h"
#include"TypeDefs.h"
#include"Tools.h"
#include <QtGui>



MaFenetre::MaFenetre(QWidget *parent) : QMainWindow(parent),
ui(new Ui::MaFenetre){
    ui->setupUi(this);
}

MaFenetre::~MaFenetre()
{
    delete ui;
}

ReaderName MonLecteur;
//on declare status pour tout le code
int16_t status = MI_OK;

//fonction pour connecter la carte
void MaFenetre::on_Connect_clicked()
{
    //type de lecteur
    MonLecteur.Type = ReaderCDC;
    MonLecteur.device = 0;
    //connection de la carte
    status = OpenCOM(&MonLecteur);
    qDebug() << "OpenCOM" << status;

    //Action de la led et du buzzer
    status = LEDBuzzer(&MonLecteur, LED_GREEN_ON+LED_YELLOW_ON+LED_RED_ON+LED_GREEN_ON);
    DELAYS_MS(300);
    status = LEDBuzzer(&MonLecteur, LED_GREEN_ON);
    DELAYS_MS(100);
    status = LEDBuzzer(&MonLecteur, LED_GREEN_ON+LED_YELLOW_ON+LED_RED_ON+LED_GREEN_ON);
    DELAYS_MS(100);
    status = LEDBuzzer(&MonLecteur, LED_GREEN_ON);
    DELAYS_MS(150);
    status = LEDBuzzer(&MonLecteur, LED_GREEN_ON+LED_YELLOW_ON+LED_RED_ON+LED_GREEN_ON);
    DELAYS_MS(100);
    status = LEDBuzzer(&MonLecteur, LED_GREEN_ON);
    status = LEDBuzzer(&MonLecteur, LED_RED_ON);

}


//fonction pour deconnecter la carte
void MaFenetre::on_Deconnection_clicked()
{
    status = 0;
    //fonction qui permet de fermer la connexion
    status = CloseCOM(&MonLecteur);
    //afficher close dans la console
    qDebug() << "CloseCOM" << status;
    //Recuperation de version du lecteur
    status = Version(&MonLecteur);

    //Action de la led et du buzzer
    status = LEDBuzzer(&MonLecteur, LED_GREEN_ON+LED_YELLOW_ON+LED_RED_ON+LED_GREEN_ON);
    DELAYS_MS(5);
    status = LEDBuzzer(&MonLecteur, LED_GREEN_ON);
    DELAYS_MS(50);
    status = LEDBuzzer(&MonLecteur, LED_GREEN_ON+LED_YELLOW_ON+LED_RED_ON+LED_GREEN_ON);
    DELAYS_MS(5);
    status = LEDBuzzer(&MonLecteur, LED_GREEN_ON);
    status = LEDBuzzer(&MonLecteur, LED_GREEN_ON);

}

//fonction pour quitter
void MaFenetre::on_Quitter_clicked()
{
    RF_Power_Control(&MonLecteur, FALSE, 0);
    //les led sont off
    status = LEDBuzzer(&MonLecteur, LED_OFF);
    //fonction qui permet de se deconnecter du lecteur
     status = CloseCOM(&MonLecteur);
    //fonction pour fermer l'interface et arreter le programme
    qApp->quit();
}

//fonction pour selectionner
void MaFenetre::on_Selectionner_clicked()
{

    //pour bien verifier qu'il y a une carte sur le lecteur
    status = ISO14443_3_A_PollCard(&MonLecteur, atq, sak, uid, &uid_len);
    uint8_t Data2[16];
    //fonction qui permet de lire le block 9 qui contient le prenom e utilisant la cle A
    status = Mf_Classic_Read_Block(&MonLecteur, TRUE, 9, Data2, AuthKeyA, 2);
    uint8_t Data1[16];
    //fonction qui permet de lire le block 10 qui contient le nom en utilisant la cle A
    status = Mf_Classic_Read_Block(&MonLecteur, TRUE, 10, Data1, AuthKeyA, 2);

    //afficher les données dans notre interface graphique
    ui ->Nom->setText((char*)Data1);
    ui -> Nom->update();
    ui -> Nom->setText((char*)Data2);
    ui -> Nom->update();

    //afficher le nombre d'unite de la carte

    //declaration de notre compteur
    uint32_t Compteur = 0;
    //fonction qui permet de lire la valeur de notre compteur qui se trouve das le block14 secteur 3 avec la cle A
    status = Mf_Classic_Read_Value(&MonLecteur, TRUE, 14, &Compteur, AuthKeyA, 3);
    //affciher la valeur de notre compteur dans l'interface
    ui -> Compteur->setPlainText(QString::number(Compteur));
    ui -> Compteur->update();

}

//fonction pour mettre à jour
void MaFenetre::on_Maj_clicked()
{
    //ecrire dans la console:

    //declaration d'une chaine de caractère prenant la valeur de saisi nom
    QString Text = ui-> Nom -> toPlainText();
    //afficher dans la console
    qDebug() << "Text : " << Text;
    //delcaration d'une chaine de caractère qui prend la valeur se saisi prenom
    QString Text1 = ui->Prenom->toPlainText();
    //afficher dans la console
    qDebug() << "Text : " << Text1;


    //ecrire le nom sur la carte:

    //declaration d'une chaine de caractere pour ecrire le nm sur la carte
    char Data1[16];
    //pour convertir une table en caractère
    sprintf(Data1, TRext/toUtf8().data(), 16);
    auto datanom = (uint8_t*)Data1;
    //fonction qui permet d'ecrire sur la carte le nom dans le block 10 secteur 2 avec la cle B
    status = Mf_Classic_Write_Block(&MonLecteur, TRUE, 10, datanom, AuthKeyB, 2);


    //ecrire le prenom sur la carte:

    //declaration d'une chaine de cara pour ecrire le prenom sur la carte
    char Data2[16];
    //pour convertir une table en caractère
    sprintf(Data2, TRext/toUtf8().data(), 16);
    auto dataprenom = (uint8_t*)Data2;
    //fonction qui permet d'ecrire sur la carte le nom dans le block 10 secteur 2 avec la cle B
    status = Mf_Classic_Write_Block(&MonLecteur, TRUE, 9, dataprenom, AuthKeyB, 2);

}

//fonction qui s'occupe de l'incrementation
void MaFenetre::on_spinBoxincr_clicked()
{
    //recuperation de la valeur de nb qu'il faut ajouter
    auto Compteur= ui -> Compteur -> value();
    //focntion qui permet d'incrementer la valeur de mon compteur qui se trouve dans 14 j'ajoute le nb d'unite demandé
    //et je stock dans 13 (la memoire) en utilisant la cle B
    status = Mf_Classic_Increment_Value(&MonLecteur, TRUE, 14, Compteur, 13, AuthKeyB, 3);
    //fonction qui permet d'ecrire la nouvelle valeur qui se trouve dans 13 en 14
    status = Mf_Classic_Restore_Value(&MonLecteur, TRUE, 13, 14, AuthKeyB, 3);

    //lire la nouvelle valeur

    //declaration du compteur1 où je veux stocker la nouvelle valeur du compteur (valeur incrementer)
    uint32_t Compteur1 = 0;
    //fonction qui permets de lire la nouvelle valeur du compteur qui se trouve dans le block 14 secteur 3 ) l'aide de la cle A
    status = Mf_Classic_Read_Value(&MonLecteur, TRUE, 14, &Compteur1, AuthKeyA, 3);
    //conversion de la valeur de compteur en string  pour l'afficher dans l'interface graphique
    auto text_compteur = QString::number(Compteur1);
    //affichage de la nouvelle valeur dans l'interface
    ui -> Compteur->setPlainText(text_compteur);
    ui -> Compteur->update();

}

//fonction qui s'occupe de la decrementation
void MaFenetre::on_spinBoxdecr_clicked()
{

    //recuperation de la valeur de nb qu'il faut ajouter
    auto Compteur= ui -> spinBoxdecr -> value();
    //focntion qui permet d'incrementer la valeur de mon compteur qui se trouve dans 14 j'ajoute le nb d'unite demandé
    //et je stock dans 13 (la memoire) en utilisant la cle A
    status = Mf_Classic_Decrement_Value(&MonLecteur, TRUE, 14, Compteur, 13, AuthKeyA, 3);
    //fonction qui permet d'ecrire la nouvelle valeur qui se trouve dans 13 en 14
    status = Mf_Classic_Restore_Value(&MonLecteur, TRUE, 13, 14, AuthKeyA, 3);

    //lire la nouvelle valeur

    //declaration du compteur1 où je veux stocker la nouvelle valeur du compteur (valeur incrementer)
    uint32_t Compteur1 = 0;
    //fonction qui permets de lire la nouvelle valeur du compteur qui se trouve dans le block 14 secteur 3 ) l'aide de la cle A
    status = Mf_Classic_Read_Value(&MonLecteur, TRUE, 14, &Compteur1, AuthKeyA, 3);
    //conversion de la valeur de compteur en string  pour l'afficher dans l'interface graphique
    auto text_compteur = QString::number(Compteur1);
    //affichage de la nouvelle valeur dans l'interface
    ui -> Compteur->setPlainText(text_compteur);
    ui -> Compteur->update();

    //Action de la led et du buzzer
    status = LEDBuzzer(&MonLecteur, LED_GREEN_ON+LED_YELLOW_ON+LED_RED_ON+LED_GREEN_ON);
    DELAYS_MS(10);
    status = LEDBuzzer(&MonLecteur, LED_GREEN_ON+LED_YELLOW_ON+LED_RED_ON+LED_GREEN_ON);
    DELAYS_MS(5);
    status = LEDBuzzer(&MonLecteur, LED_GREEN_ON);
    status = LEDBuzzer(&MonLecteur, LED_YELLOW_ON);
    DELAYS_MS(100);
    status = LEDBuzzer(&MonLecteur, LED_YELLOW_ON);
    status = LEDBuzzer(&MonLecteur, LED_RED_ON);



}
