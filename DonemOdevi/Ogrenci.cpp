#include "Ogrenci.h"
#include "Ders.h"
#include "Filtre.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <Windows.h>

using namespace std;
Ders ders;
Filtre filtre;
struct kuyruk* k = NULL;

struct ogrenci {
	int ogrenciNo;
	char ogrenciAdi[20];
	char bolum[50];
	int sinif;
	float ano;
	struct ders* dersListesi;
	struct ogrenci* next;
};

struct ders {
	char dersKodu[10];
	char dersAdi[50];
	int quiz1;
	int quiz2;
	int vize;
	int final;
	float ortalama;
	char harfNotu[3];
	int akts;
	int kredi;
	struct ders* next;
	struct ders* prev;
};

void Ogrenci::baslat(struct ogrenci* ogrenciListesi) {
	ogrenciListesi = dosyaOku(ogrenciListesi);
	if (ogrenciListesi != NULL) {
		ogrenciListesi = ders.dosyaOku(ogrenciListesi);
	}
	anaSayfa(ogrenciListesi);
}

void Ogrenci::anaSayfa(struct ogrenci* ogrenciListesi) {
	SetConsoleTitleA("Okul Sistemi");
	system("cls");
	cout << "******Ogrenci Otomastonu******" << endl;
	while (true) {
		cout << "1-Ogrenci ekle" << endl;
		cout << "2-Ogrencileri listele" << endl;
		cin >> secim;
		if (secim == 1 || secim == 2) {
			break;
		}
		else {
			cout << "Hatali islem. Lutfen tekrar girin" << endl;
		}
	}
	switch (secim) {
	case 1:
		system("cls");
		ogrenciBilgileriAl(ogrenciListesi);
		break;
	case 2:
		ogrencileriListele(ogrenciListesi);
		break;
	default:
		break;
	}
}

void Ogrenci::ogrenciBilgileriAl(struct ogrenci* ogrenciListesi) {
	SetConsoleTitleA("Ogrenci Ekle");
	int ogrenciNo;
	char ogrenciAdi[20];
	char bolum[50];
	int sinif;
	float ano = 0;
	cout << "Okul Numarası\t: ";
	cin >> ogrenciNo;
	cout << "Adı\t\t: ";
	getchar();
	fgets(ogrenciAdi, 20, stdin);
	cout << "Bolumu\t\t: ";
	fgets(bolum, 50, stdin);
	cout << "Sinif\t\t: ";
	cin >> sinif;

	int sonIndis;
	sonIndis = strlen(ogrenciAdi);
	ogrenciAdi[sonIndis - 1] = '\0';
	sonIndis = strlen(bolum);
	bolum[sonIndis - 1] = '\0';
	if (ogrenciNoAra(ogrenciListesi, ogrenciNo)) {
		cout << "Bu okul numarasında bir ogrenci mevcut. Lutfen yeniden giriniz" << endl;
		ogrenciBilgileriAl(ogrenciListesi);
	}
	else {
		ogrenciListesi = ogrenciEkle(ogrenciListesi, ogrenciNo, ogrenciAdi, bolum, sinif, ano);
		dosyayaOgrenciKaydet(ogrenciListesi);
		ders.dosyayaDersKaydet(ogrenciListesi);
		cout << endl << "Ögrenci başarıyla eklendi" << endl;
		cout << "1-Yeni ogrenci ekle" << endl;
		cout << "2-Geri" << endl;
		cin >> secim;
		system("cls");
		switch (secim) {
		case 1:
			ogrenciBilgileriAl(ogrenciListesi);
			break;
		case 2:
			anaSayfa(ogrenciListesi);
			break;
		default:
			break;
		}
	}
}

bool Ogrenci::ogrenciNoAra(struct ogrenci* ogrenciListesi, int ogrenciNo) {
	struct ogrenci* gecisiListe = ogrenciListesi;
	if (ogrenciListesi == NULL) {
		return false;
	}
	do {
		if (gecisiListe->ogrenciNo != ogrenciNo) {
			gecisiListe = gecisiListe->next;
		}
		else {
			return true;
		}
	} while (ogrenciListesi != gecisiListe);
	return false;
}

struct ogrenci* Ogrenci::ogrenciEkle(struct ogrenci* ogrenciListesi, int ogrenciNo, char ogrenciAdi[20], char bolum[50], int sinif, float ano) {
	struct ogrenci* gecisiListe = (struct ogrenci*)malloc(sizeof(struct ogrenci));
	if (ogrenciListesi == NULL) {
		gecisiListe->ogrenciNo = ogrenciNo;
		for (i = 0; i < 20; i++) {
			gecisiListe->ogrenciAdi[i] = ogrenciAdi[i];
		}
		for (i = 0; i < 50; i++) {
			gecisiListe->bolum[i] = bolum[i];
		}
		gecisiListe->sinif = sinif;
		gecisiListe->ano = ano;
		gecisiListe->dersListesi = NULL;
		gecisiListe->next = gecisiListe;
		ogrenciListesi = gecisiListe;
	}
	else {
		gecisiListe->ogrenciNo = ogrenciNo;
		for (i = 0; i < 20; i++) {
			gecisiListe->ogrenciAdi[i] = ogrenciAdi[i];
		}
		for (i = 0; i < 50; i++) {
			gecisiListe->bolum[i] = bolum[i];
		}
		gecisiListe->sinif = sinif;
		gecisiListe->ano = ano;
		gecisiListe->dersListesi = NULL;

		struct ogrenci* gecisiListe2 = ogrenciListesi;
		while (gecisiListe2->next != ogrenciListesi) {
			gecisiListe2 = gecisiListe2->next;
		}
		gecisiListe2->next = gecisiListe;
		gecisiListe->next = ogrenciListesi;
		ogrenciListesi = gecisiListe;
	}
	return ogrenciListesi;
}

void Ogrenci::ogrencileriListele(struct ogrenci* ogrenciListesi) {
	SetConsoleTitleA("Mevcut Ogrenciler");
	system("cls");
	if (ogrenciListesi == NULL) {
		cout << "Mevcut ogrenci bulunmamaktadir. Lutfen ogrenci ekleyin." << endl;
		cout << "1-Ogrenci ekle" << endl;
		cout << "2-Geri" << endl;
		cin >> secim;
		system("cls");
		switch (secim) {
		case 1:
			ogrenciBilgileriAl(ogrenciListesi);
			break;
		case 2:
			anaSayfa(ogrenciListesi);
			break;
		default:
			break;
		}
		return;
	}
	struct ogrenci* gecisiListe = ogrenciListesi;
	do {
		printf("Ogrenci No: %-20d\tAd: %-20s\tBolum: %s\n", gecisiListe->ogrenciNo, gecisiListe->ogrenciAdi, gecisiListe->bolum);
		gecisiListe = gecisiListe->next;
	} while (gecisiListe != ogrenciListesi);
	ogrencileriListeleIslemleri(ogrenciListesi, gecisiListe);
}

void Ogrenci::ogrencileriListeleIslemleri(struct ogrenci* ogrenciListesi, struct ogrenci* gecisiListe) {
	char bolum[50];
	int sonIndis;
	cout << endl << "Islemler" << endl;
	while (true) {
		cout << "1-Ogrenci sec" << endl;
		cout << "2-Bolume gore filtrele" << endl;
		cout << "3-Geri" << endl;
		cin >> secim;
		if (secim == 1 || secim == 2 || secim == 3) {
			break;
		}
		else {
			cout << "Hatali islem. Lutfen tekrar girin" << endl;
		}
	}
	switch (secim) {
	case 1:
		cout << "Islem yapmak istediginiz ogrencinin ogrenci numarasını girin" << endl;
		cin >> secim;
		while (true) {
			if (ogrenciNoAra(ogrenciListesi, secim)) {
				break;
			}
			else {
				cout << "Bu okul numarasında bir ogrenci mevcut degil. Lutfen yeniden giriniz" << endl;
				cin >> secim;
			}
		}
		ogrenciBilgileri(gecisiListe, secim);
		break;
	case 2:
		cout << "Filtrelemek istediginiz bolumu girin" << endl;
		getchar();
		fgets(bolum, 50, stdin);
		sonIndis = strlen(bolum);
		bolum[sonIndis - 1] = '\0';
		while (true) {
			if (bolumAra(ogrenciListesi, bolum)) {
				break;
			}
			else {
				cout << "Bu isimde bir bolum mevcut degil. Lutfen yeniden giriniz" << endl;
				fgets(bolum, 50, stdin);
				sonIndis = strlen(bolum);
				bolum[sonIndis - 1] = '\0';
			}
		}
		filtrele(ogrenciListesi, gecisiListe, bolum);
		break;
	case 3:
		anaSayfa(ogrenciListesi);
		break;
	default:
		break;
	}
}

bool Ogrenci::bolumAra(struct ogrenci* ogrenciListesi, char bolum[50]) {
	struct ogrenci* gecisiListe = ogrenciListesi;
	if (ogrenciListesi == NULL) {
		return false;
	}
	do {
		if ((strcmp(gecisiListe->bolum, bolum) == 0)) {
			return true;
		}
		gecisiListe = gecisiListe->next;
	} while (ogrenciListesi != gecisiListe);
	return false;
}

void Ogrenci::filtrele(struct ogrenci* ogrenciListesi, struct ogrenci* gecisi, char bolum[50]) {
	SetConsoleTitleA("Bolume gore filtrele");
	system("cls");
	struct ogrenci* gecisiListe = ogrenciListesi;
	k = filtre.baslat(k);
	do {
		if ((strcmp(gecisiListe->bolum, bolum) == 0)) {
			filtre.ekle(k, gecisiListe->ogrenciNo, gecisiListe->ogrenciAdi, gecisiListe->bolum);
		}
		gecisiListe = gecisiListe->next;
	} while (gecisiListe != ogrenciListesi);
	filtre.yazdir(k);
	ogrencileriListeleIslemleri(ogrenciListesi, gecisi);
}

void Ogrenci::ogrenciBilgileri(struct ogrenci* ogrenciListesi, int no) {
	SetConsoleTitleA("Ogrenci Bilgileri");
	system("cls");
	struct ogrenci* gecisiListe = ogrenciListesi;
	while (1) {
		if (gecisiListe->ogrenciNo == no) {
			cout << "Ogrenci No\t: ";
			cout << gecisiListe->ogrenciNo;
			cout << endl << "Adi\t\t: ";
			puts(gecisiListe->ogrenciAdi);
			cout << "Bolumu\t\t: ";
			puts(gecisiListe->bolum);
			cout << "Sinif\t\t: ";
			cout << gecisiListe->sinif << endl;
			printf("ANO\t\t: %.2f", gecisiListe->ano);
			break;
		}
		gecisiListe = gecisiListe->next;
	}
	cout << endl << endl << "Islemler:" << endl;
	while (true) {
		cout << "1-Ogrenci sil" << endl;
		cout << "2-Ders ekle" << endl;
		cout << "3-Not listesi" << endl;
		cout << "4-Ogrenci bilgileri kaydet" << endl;
		cout << "5-Ogrenci guncelle" << endl;
		cout << "6-Geri" << endl;
		cin >> secim;
		if (secim == 1 || secim == 2 || secim == 3 || secim == 4 || secim == 5 || secim == 6) {
			break;
		}
		else {
			cout << "Hatali islem. Lutfen tekrar girin" << endl;
		}
	}
	switch (secim) {
	case 1:
		ogrenciListesi = ogrenciSil(ogrenciListesi, no);
		dosyadaOgrenciGuncelle(ogrenciListesi);
		ders.dosyayaDersKaydet(ogrenciListesi);
		ogrenciListesi = NULL;
		ogrenciListesi = dosyaOku(ogrenciListesi);
		dosyadaOgrenciGuncelle(ogrenciListesi);
		ogrenciListesi = NULL;
		ogrenciListesi = dosyaOku(ogrenciListesi);
		ogrenciListesi = ders.dosyaOku(ogrenciListesi);
		SetConsoleTitleA("Ogrenci Sil");
		system("cls");
		cout << "Ogrenci basarıyla silindi" << endl;
		cout << "1-Geri" << endl;
		cin >> secim;
		if (secim == 1) {
			ogrencileriListele(ogrenciListesi);
		}
		break;
	case 2:
		ders.dersBilgileriAl(ogrenciListesi, no);
		break;
	case 3:
		system("cls");
		gecisiListe = ogrenciListesi;
		while (gecisiListe->ogrenciNo != no) {
			gecisiListe = gecisiListe->next;
		}
		ders.notListele(gecisiListe->dersListesi, ogrenciListesi, no);
		break;
	case 4:
		ogrenciBilgileriniKaydet(gecisiListe);
		cout << "Bilgiler kaydedildi" << endl;
		cout << "1-Geri" << endl;;
		cin >> secim;
		if (secim == 1) {
			ogrencileriListele(ogrenciListesi);
		}
		break;
	case 5:
		ogrenciGuncelle(ogrenciListesi, no);
		break;
	case 6:
		ogrencileriListele(ogrenciListesi);
		break;
	default:
		anaSayfa(ogrenciListesi);
		break;
	}
}

void Ogrenci::ogrenciGuncelle(struct ogrenci* ogrenciListesi, int no) {
	SetConsoleTitleA("Ogrenci Guncelle");
	system("cls");
	struct ogrenci* gecisiListe = ogrenciListesi;
	int ogrenciNo;
	char ogrenciAdi[20];
	char bolum[50];
	int sinif;
	do {
		if (gecisiListe->ogrenciNo == no) {
			break;
		}
		gecisiListe = gecisiListe->next;
	} while (gecisiListe != ogrenciListesi);
	cout << "Mevcut bilgiler" << endl;
	cout << "Ogrenci No\t: ";
	cout << gecisiListe->ogrenciNo << endl;
	cout << "Ad\t\t: ";
	cout << gecisiListe->ogrenciAdi << endl;
	cout << "Bolum\t\t: ";
	cout << gecisiListe->bolum << endl;
	cout << "Sinif\t\t: ";
	cout << gecisiListe->sinif << endl << endl;

	cout << "Okul Numarası\t: ";
	cin >> ogrenciNo;
	cout << "Adı\t\t: ";
	getchar();
	fgets(ogrenciAdi, 20, stdin);
	cout << "Bolumu\t\t: ";
	fgets(bolum, 50, stdin);
	cout << "Sinif\t\t: ";
	cin >> sinif;

	int sonIndis;
	sonIndis = strlen(ogrenciAdi);
	ogrenciAdi[sonIndis - 1] = '\0';
	sonIndis = strlen(bolum);
	bolum[sonIndis - 1] = '\0';

	gecisiListe->ogrenciNo = ogrenciNo;
	for (i = 0; i < 20; i++) {
		gecisiListe->ogrenciAdi[i] = ogrenciAdi[i];
	}
	for (i = 0; i < 50; i++) {
		gecisiListe->bolum[i] = bolum[i];
	}
	gecisiListe->sinif = sinif;
	dosyadaOgrenciGuncelle(ogrenciListesi);
	ogrenciListesi = NULL;
	ogrenciListesi = dosyaOku(ogrenciListesi);
	dosyadaOgrenciGuncelle(ogrenciListesi);
	ogrenciListesi = NULL;
	ogrenciListesi = dosyaOku(ogrenciListesi);
	ogrenciListesi = ders.dosyaOku(ogrenciListesi);
	cout << endl << "Ogrenci basariyla guncellendi." << endl;
	cout << "1-Geri" << endl;
	cin >> secim;
	if (secim == 1) {
		ogrenciBilgileri(ogrenciListesi, ogrenciNo);
	}
}

void Ogrenci::ogrenciBilgileriniKaydet(struct ogrenci* ogrenciListesi) {
	struct ogrenci* gecisiListe = ogrenciListesi;
	ofstream dosyaYaz("bilgiler\\Transkript.txt");

	if (dosyaYaz.is_open()) {
		dosyaYaz << "\t\t\t\t******Ögrenci Bilgileri******" << endl;
		dosyaYaz << endl << "-------------------------------------------------------------------------------------------------" << endl;
		dosyaYaz << "Ögrenci No\t:";
		dosyaYaz << gecisiListe->ogrenciNo;
		dosyaYaz << endl << "Ögrenci Adı\t:";
		dosyaYaz << gecisiListe->ogrenciAdi;
		dosyaYaz << endl << "Bölümü\t\t:";
		dosyaYaz << gecisiListe->bolum;
		dosyaYaz << endl << "Sinif\t\t:";
		dosyaYaz << gecisiListe->sinif;
		dosyaYaz << endl << "ANO\t\t:";
		dosyaYaz << gecisiListe->ano;
		dosyaYaz << endl << "-------------------------------------------------------------------------------------------------" << endl;
		struct ders* gecisiListe2 = gecisiListe->dersListesi;

		if (gecisiListe2 != NULL) {
			dosyaYaz << "Dersler" << endl << endl;
			do {
				dosyaYaz << gecisiListe2->dersKodu;
				dosyaYaz << "\t";
				dosyaYaz << gecisiListe2->dersAdi << endl;
				dosyaYaz << "Quiz1: ";
				dosyaYaz << gecisiListe2->quiz1;
				dosyaYaz << "\tQuiz2: ";
				dosyaYaz << gecisiListe2->quiz2;
				dosyaYaz << "\tVize: ";
				dosyaYaz << gecisiListe2->vize;
				dosyaYaz << "\tFinal: ";
				dosyaYaz << gecisiListe2->final;
				dosyaYaz << "\tOrtalama: ";
				dosyaYaz << gecisiListe2->ortalama;
				dosyaYaz << "\t\tHarf: ";
				dosyaYaz << gecisiListe2->harfNotu;
				dosyaYaz << endl << "-------------------------------------------------------------------------------------------------" << endl;
				gecisiListe2 = gecisiListe2->next;
			} while (gecisiListe2 != gecisiListe->dersListesi);
		}
		dosyaYaz.close();
	}
}

struct ogrenci* Ogrenci::dosyaOku(struct ogrenci* ogrenciListesi) {
	ifstream dosyaoku("bilgiler\\ogrenci.txt", ios::in);
	char ogrenciAdi[20], bolum[50];
	//dosyadan alınan veriler
	int dOgrenciNo;
	string dOgrenciAdi;
	string dBolum;
	int dSinif;
	float dAno;

	string oku; //dosya satırları oku
	int satir = 1;// okunan satır

	while (getline(dosyaoku, oku)) {
		if (satir == 1) {
			stringstream ss;
			ss << oku;
			ss >> dOgrenciNo;
		}
		else if (satir == 2) {
			dOgrenciAdi = oku;
			for (i = 0; i < oku.length(); i++) {
				ogrenciAdi[i] = dOgrenciAdi[i];
			}
			ogrenciAdi[i] = '\0';
		}
		else if (satir == 3) {
			dBolum = oku;
			for (i = 0; i < oku.length(); i++) {
				bolum[i] = dBolum[i];
			}
			bolum[i] = '\0';
		}
		else if (satir == 4) {
			stringstream ss;
			ss << oku;
			ss >> dSinif;
		}
		else if (satir == 5) {
			stringstream ss;
			ss << oku;
			ss >> dAno;
			satir = 0;
			ogrenciListesi = ogrenciEkle(ogrenciListesi, dOgrenciNo, ogrenciAdi, bolum, dSinif, dAno);
		}
		satir++;
	}
	return ogrenciListesi;
}

void Ogrenci::dosyayaOgrenciKaydet(struct ogrenci* ogrenciListesi) {
	struct ogrenci* gecisiListe = ogrenciListesi;
	ofstream dosyaYaz("bilgiler\\ogrenci.txt", ios::app);
	if (dosyaYaz.is_open()) {
		dosyaYaz << gecisiListe->ogrenciNo << endl;
		dosyaYaz << gecisiListe->ogrenciAdi << endl;
		dosyaYaz << gecisiListe->bolum << endl;
		dosyaYaz << gecisiListe->sinif << endl;
		dosyaYaz << gecisiListe->ano << endl;
		dosyaYaz.close();
	}
}

void Ogrenci::dosyadaOgrenciGuncelle(struct ogrenci* ogrenciListesi) {
	struct ogrenci* gecisiListe = ogrenciListesi;
	ofstream dosyaYaz("bilgiler\\ogrenci.txt");

	if (dosyaYaz.is_open()) {
		if (ogrenciListesi == NULL) {
			dosyaYaz << "";
		}
		else {
			do {
				dosyaYaz << gecisiListe->ogrenciNo << endl;
				dosyaYaz << gecisiListe->ogrenciAdi << endl;
				dosyaYaz << gecisiListe->bolum << endl;
				dosyaYaz << gecisiListe->sinif << endl;
				dosyaYaz << gecisiListe->ano << endl;
				gecisiListe = gecisiListe->next;
			} while (gecisiListe != ogrenciListesi);
		}
	}
	dosyaYaz.close();
}

struct ogrenci* Ogrenci::ogrenciSil(struct ogrenci* ogrenciListesi, int no) {
	struct ogrenci* gecisiListe = ogrenciListesi;
	if (ogrenciListesi->next == NULL) {
		cout << "Listede ogrenci yok" << endl;
		return ogrenciListesi;
	}

	if (ogrenciListesi->ogrenciNo == no && ogrenciListesi->next == ogrenciListesi) {
		free(ogrenciListesi);
		ogrenciListesi = NULL;
	}

	else if (ogrenciListesi->ogrenciNo == no) {
		struct ogrenci* last = ogrenciListesi;
		while (last->next != ogrenciListesi)
			last = last->next;
		ogrenciListesi = ogrenciListesi->next;
		last->next = ogrenciListesi;
		free(gecisiListe);
	}
	else if (gecisiListe->next == NULL) {
		cout << "Silmek istediginiz ogrenci bulunamadi" << endl;
	}
	else {
		while (gecisiListe->next->ogrenciNo != no) {
			if (gecisiListe->next->next == NULL) {
				cout << "Silmek istediginiz ogrenci bulunamadi." << endl;
				return ogrenciListesi;
			}
			gecisiListe = gecisiListe->next;
		}
		struct ogrenci* gecisiListe2 = gecisiListe->next;
		gecisiListe->next = gecisiListe->next->next;
		free(gecisiListe2);
	}
	return ogrenciListesi;
}