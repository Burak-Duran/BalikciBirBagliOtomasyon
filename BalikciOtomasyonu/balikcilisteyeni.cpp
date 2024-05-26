#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <fstream>
#include <iomanip>
#include <locale.h>
using namespace std;



//BURAK DURAN
//2312721019
//BALIKCI OTOMASYONU



struct balikBilgileri {
    char balikIsmi[50];  
    float stok;
    float fiyat;
};

struct BalikNode {
    balikBilgileri balik;
    BalikNode* link;
};


struct satisBilgileri {
    balikBilgileri satilanBalik;
    float toplam;
    int adet;
};

struct SatisNode {
    satisBilgileri satis;
    SatisNode* link;
};

BalikNode* balikHead = NULL;
SatisNode* satisHead = NULL;

void dosyadanBalikYukle();
void dosyayaBalikKaydet();
void dosyadanSatisYukle();
void dosyayaSatisKaydet();

void balikEkle() {
    char secim;
    int sayi = 0;
    BalikNode* newNode;
    do {
        newNode = new BalikNode();

        cout << "Bal�k ismi giriniz: ";
        cin >> newNode->balik.balikIsmi;

        cout << "L�tfen " << newNode->balik.balikIsmi << " bal���n�n sto�unu giriniz: ";
        cin >> newNode->balik.stok;

        cout << "L�tfen " << newNode->balik.balikIsmi << " bal���n�n fiyat�n� giriniz: ";
        cin >> newNode->balik.fiyat;

        newNode->link = balikHead;
        balikHead = newNode;

        cout << "Ba�ka bal�k girisi yapmak ister misiniz? (E/H): ";
        secim = getche();
        cout << endl;
        sayi++;
    } while (secim == 'e' || secim == 'E');
    cout << sayi << " Adet bal�k girisi yap�ld�." << endl;
    dosyayaBalikKaydet();
}

void balikListeleme() {
    dosyadanBalikYukle();
    BalikNode* secili = balikHead;
    cout << setw(10) << "BALIK" << setw(10) << "STOK" << setw(10) << "FIYAT" << endl;
    while (secili != NULL) {
        cout << setw(10) << secili->balik.balikIsmi << setw(10) << secili->balik.stok << setw(10) << secili->balik.fiyat << endl;
        secili = secili->link;
    }
}

void balikArama() {
    dosyadanBalikYukle();
    BalikNode* secili = balikHead;
    cout << "Hangi bal��� g�rmek istiyorsunuz?: ";
    string isim;
    cin >> isim;
    int sayac = 0;
    cout << setw(10) << "BALIK" << setw(10) << "STOK" << setw(10) << "FIYAT" << endl;
    while (secili != NULL) {
        if (isim == secili->balik.balikIsmi) {
            cout << setw(10) << secili->balik.balikIsmi << setw(10) << secili->balik.stok << setw(10) << secili->balik.fiyat << endl;
            sayac++;
        }
        secili = secili->link;
    }
    if (sayac == 0) {
        cout << "B�yle bir bal�k yoktur" << endl;
    }
}

void balikSilme() {
    dosyadanBalikYukle();
    BalikNode* secili = balikHead;
    BalikNode* onceki = NULL;
    int sayac = 0;
    while (secili != NULL) {
        if (secili->balik.stok == 0) {
            cout << setw(10) << secili->balik.balikIsmi << setw(10) << secili->balik.stok << setw(10) << secili->balik.fiyat << endl;
            if (onceki == NULL) {
                balikHead = secili->link;
            } else {
                onceki->link = secili->link;
            }
            BalikNode* temp = secili;
            secili = secili->link;
            delete temp;
            sayac++;
        } else {
            onceki = secili;
            secili = secili->link;
        }
    }
    if (sayac > 0) {
        cout << sayac << " Adet Bal�k Silindi" << endl;
    } else {
        cout << "Bal�k silinmedi" << endl;
    }
    dosyayaBalikKaydet();
}

void balikGuncelleme() {
    dosyadanBalikYukle();
    BalikNode* secili = balikHead;
    char secim;
    do {
        cout << "><(((�>   EL�M�ZDE OLAN BALIKLAR   <�)))><" << endl;
        balikListeleme();

        cout << "Hangi Bal��� G�ncellemek �stiyorsunuz?" << endl;
        string isim;
        cin >> isim;

        while (secili != NULL) {
            if (isim == secili->balik.balikIsmi) {
                cout << "Bal�k �smi Giriniz: ";
                cin >> secili->balik.balikIsmi;

                cout << "L�tfen " << secili->balik.balikIsmi << " Bal���n�n Sto�unu Giriniz: ";
                cin >> secili->balik.stok;

                cout << "L�tfen " << secili->balik.balikIsmi << " Bal���n�n Fiyat�n� Giriniz: ";
                cin >> secili->balik.fiyat;
                break;
            }
            secili = secili->link;
        }

        cout << "Ba�ka Bal�k G�ncellemek �ster misiniz? (E/H)" << endl;
        secim = getche();
    } while (secim == 'e' || secim == 'E');
    dosyayaBalikKaydet();
}

void satisListeleme() {
    dosyadanSatisYukle();
    float toplam = 0;
    SatisNode* secili = satisHead;
    cout << setw(10) << "Bal�k" << setw(10) << "Fiyat" << setw(10) << "Adet" << setw(15) << "Toplam fiyat" << endl;
    while (secili != NULL) {
        cout << setw(10) << secili->satis.satilanBalik.balikIsmi << setw(10) << secili->satis.satilanBalik.fiyat << setw(10) << secili->satis.adet << setw(15) << secili->satis.toplam << endl;
        toplam += secili->satis.toplam;
        secili = secili->link;
    }
    cout << endl;
    cout << "G�nl�k Kazan�: " << toplam << endl;
}

void balikSatis() {
    dosyadanBalikYukle();
    dosyadanSatisYukle();
    BalikNode* secili = balikHead;
    cout << "><(((�>   EL�M�ZDE OLAN BALIKLAR   <�)))><" << endl;
    balikListeleme();
    char secim;
    do {
        cout << "Hangi bal��� satmak istiyorsunuz?" << endl;
        string isim;
        cin >> isim;
        int sayi;
        float odenecekUcret;
        secili = balikHead;

        while (secili != NULL) {
            if (isim == secili->balik.balikIsmi) {
                cout << "Ka� tane satmak istiyorsunuz?" << endl;
                cin >> sayi;
                if (sayi <= secili->balik.stok) {
                    secili->balik.stok -= sayi;

                    SatisNode* newSatis = new SatisNode();
                    newSatis->satis.satilanBalik = secili->balik;
                    newSatis->satis.adet = sayi;
                    newSatis->satis.toplam = sayi * secili->balik.fiyat;

                    newSatis->link = satisHead;
                    satisHead = newSatis;

                    odenecekUcret = newSatis->satis.toplam;
                    cout << "�demeniz Gereken �cret: " << odenecekUcret << endl;
                } else {
                    cout << "Elimizde " << secili->balik.stok << " kg " << secili->balik.balikIsmi << " bal��� bulunmaktad�r." << endl;
                }
                break;
            }
            secili = secili->link;
        }

        cout << "Ba�ka bal�k sat��� yapmak ister misiniz? (E/H)" << endl;
        cin >> secim;
    } while (secim == 'e' || secim == 'E');
    dosyayaBalikKaydet();
    dosyayaSatisKaydet();
}

void dosyadanBalikYukle() {
    ifstream file("stok.dat", ios::binary);
    if (!file.is_open()) return;

    BalikNode* onceki = NULL;
    while (true) {
        BalikNode* yeni = new BalikNode();
        file.read((char*)&yeni->balik, sizeof(balikBilgileri));
        if (file.eof()) {
            delete yeni;
            break;
        }
        yeni->link = NULL;
        if (onceki == NULL) {
            balikHead = yeni;
        } else {
            onceki->link = yeni;
        }
        onceki = yeni;
    }
    file.close();
}

void dosyayaBalikKaydet() {
    ofstream file("stok.dat", ios::binary | ios::trunc);
    BalikNode* secili = balikHead;
    while (secili != NULL) {
        file.write((char*)&secili->balik, sizeof(balikBilgileri));
        secili = secili->link;
    }
    file.close();
}

void dosyadanSatisYukle() {
    ifstream file("satis.dat", ios::binary);
    if (!file.is_open()) return;

    SatisNode* onceki = NULL;
    while (true) {
        SatisNode* yeni = new SatisNode();
        file.read((char*)&yeni->satis, sizeof(satisBilgileri));
        if (file.eof()) {
            delete yeni;
            break;
        }
        yeni->link = NULL;
        if (onceki == NULL) {
            satisHead = yeni;
        } else {
            onceki->link = yeni;
        }
        onceki = yeni;
    }
    file.close();
}

void dosyayaSatisKaydet() {
    ofstream file("satis.dat", ios::binary | ios::trunc);
    SatisNode* secili = satisHead;
    while (secili != NULL) {
        file.write((char*)&secili->satis, sizeof(satisBilgileri));
        secili = secili->link;
    }
    file.close();
}

int main() {
    setlocale(LC_ALL, "Turkish");
    char secim = ' ';
    do {
        system("cls");

        cout << " ><(((�> *BALIKCI OTOMASYONU* <�)))>< " << endl;
        cout << " /*            Ana Men�           *\\ " << endl;
        cout << " \\*        1.Bal�k Ekleme         */ " << endl;
        cout << " /*       2.Bal�k G�ncelleme      *\\ " << endl;
        cout << " \\*      3.Stok G�r�nt�leme       */ " << endl;
        cout << " /*         4.Bal�k Sat���        *\\ " << endl;
        cout << " \\*         5.Bal�k Arama         */ " << endl;
        cout << " /*        6.Sat�� Listeleme      *\\ " << endl;
        cout << " \\*         7.Bal�k Silme         */ " << endl;
        cout << " /*             8.��k��           *\\ " << endl;

        cout << "\nL�tfen yapmak istedi�iniz i�lemi girin: ";
        secim = getch();
        cout << endl;
        switch (secim) {
            case '1': {
                balikEkle();
                break;
            }
            case '2': {
                balikGuncelleme();
                break;
            }
            case '3': {
                balikListeleme();
                break;
            }
            case '4': {
                balikSatis();
                break;
            }
            case '5': {
                balikArama();
                break;
            }
            case '6': {
                satisListeleme();
                break;
            }
            case '7': {
                balikSilme();
                break;
            }
            case '8': {
                break;
            }
            default:
                cout << "Hatal� Se�im Yapt�n�z! 1-8" << endl;
        }
        if (secim != '8' ) {
        	
            cout << "Ana menuye donmek ister misin?(E/H)" << endl;
            secim = getche();
        }
    } while (secim == 'e' || secim == 'E');
    cout << "Programdan ��kt�n�z!" << endl;

    system("pause");
    return 0;
}

