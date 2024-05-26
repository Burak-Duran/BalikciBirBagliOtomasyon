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

        cout << "Balýk ismi giriniz: ";
        cin >> newNode->balik.balikIsmi;

        cout << "Lütfen " << newNode->balik.balikIsmi << " balýðýnýn stoðunu giriniz: ";
        cin >> newNode->balik.stok;

        cout << "Lütfen " << newNode->balik.balikIsmi << " balýðýnýn fiyatýný giriniz: ";
        cin >> newNode->balik.fiyat;

        newNode->link = balikHead;
        balikHead = newNode;

        cout << "Baþka balýk girisi yapmak ister misiniz? (E/H): ";
        secim = getche();
        cout << endl;
        sayi++;
    } while (secim == 'e' || secim == 'E');
    cout << sayi << " Adet balýk girisi yapýldý." << endl;
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
    cout << "Hangi balýðý görmek istiyorsunuz?: ";
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
        cout << "Böyle bir balýk yoktur" << endl;
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
        cout << sayac << " Adet Balýk Silindi" << endl;
    } else {
        cout << "Balýk silinmedi" << endl;
    }
    dosyayaBalikKaydet();
}

void balikGuncelleme() {
    dosyadanBalikYukle();
    BalikNode* secili = balikHead;
    char secim;
    do {
        cout << "><(((º>   ELÝMÝZDE OLAN BALIKLAR   <º)))><" << endl;
        balikListeleme();

        cout << "Hangi Balýðý Güncellemek Ýstiyorsunuz?" << endl;
        string isim;
        cin >> isim;

        while (secili != NULL) {
            if (isim == secili->balik.balikIsmi) {
                cout << "Balýk Ýsmi Giriniz: ";
                cin >> secili->balik.balikIsmi;

                cout << "Lütfen " << secili->balik.balikIsmi << " Balýðýnýn Stoðunu Giriniz: ";
                cin >> secili->balik.stok;

                cout << "Lütfen " << secili->balik.balikIsmi << " Balýðýnýn Fiyatýný Giriniz: ";
                cin >> secili->balik.fiyat;
                break;
            }
            secili = secili->link;
        }

        cout << "Baþka Balýk Güncellemek Ýster misiniz? (E/H)" << endl;
        secim = getche();
    } while (secim == 'e' || secim == 'E');
    dosyayaBalikKaydet();
}

void satisListeleme() {
    dosyadanSatisYukle();
    float toplam = 0;
    SatisNode* secili = satisHead;
    cout << setw(10) << "Balýk" << setw(10) << "Fiyat" << setw(10) << "Adet" << setw(15) << "Toplam fiyat" << endl;
    while (secili != NULL) {
        cout << setw(10) << secili->satis.satilanBalik.balikIsmi << setw(10) << secili->satis.satilanBalik.fiyat << setw(10) << secili->satis.adet << setw(15) << secili->satis.toplam << endl;
        toplam += secili->satis.toplam;
        secili = secili->link;
    }
    cout << endl;
    cout << "Günlük Kazanç: " << toplam << endl;
}

void balikSatis() {
    dosyadanBalikYukle();
    dosyadanSatisYukle();
    BalikNode* secili = balikHead;
    cout << "><(((º>   ELÝMÝZDE OLAN BALIKLAR   <º)))><" << endl;
    balikListeleme();
    char secim;
    do {
        cout << "Hangi balýðý satmak istiyorsunuz?" << endl;
        string isim;
        cin >> isim;
        int sayi;
        float odenecekUcret;
        secili = balikHead;

        while (secili != NULL) {
            if (isim == secili->balik.balikIsmi) {
                cout << "Kaç tane satmak istiyorsunuz?" << endl;
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
                    cout << "Ödemeniz Gereken Ücret: " << odenecekUcret << endl;
                } else {
                    cout << "Elimizde " << secili->balik.stok << " kg " << secili->balik.balikIsmi << " balýðý bulunmaktadýr." << endl;
                }
                break;
            }
            secili = secili->link;
        }

        cout << "Baþka balýk satýþý yapmak ister misiniz? (E/H)" << endl;
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

        cout << " ><(((º> *BALIKCI OTOMASYONU* <º)))>< " << endl;
        cout << " /*            Ana Menü           *\\ " << endl;
        cout << " \\*        1.Balýk Ekleme         */ " << endl;
        cout << " /*       2.Balýk Güncelleme      *\\ " << endl;
        cout << " \\*      3.Stok Görüntüleme       */ " << endl;
        cout << " /*         4.Balýk Satýþý        *\\ " << endl;
        cout << " \\*         5.Balýk Arama         */ " << endl;
        cout << " /*        6.Satýþ Listeleme      *\\ " << endl;
        cout << " \\*         7.Balýk Silme         */ " << endl;
        cout << " /*             8.Çýkýþ           *\\ " << endl;

        cout << "\nLütfen yapmak istediðiniz iþlemi girin: ";
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
                cout << "Hatalý Seçim Yaptýnýz! 1-8" << endl;
        }
        if (secim != '8' ) {
        	
            cout << "Ana menuye donmek ister misin?(E/H)" << endl;
            secim = getche();
        }
    } while (secim == 'e' || secim == 'E');
    cout << "Programdan Çýktýnýz!" << endl;

    system("pause");
    return 0;
}

