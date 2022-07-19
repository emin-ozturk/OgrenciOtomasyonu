#include "Ders.h"
#include "Ogrenci.h"
#include "Siralama.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <Windows.h>

using namespace std;
Ogrenci ogrenci;
Siralama siralama;

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

void Ders::dersBilgileriAl(struct ogrenci* ogrenciListesi, int no) {
	SetConsoleTitleA("Ders Ekle");
	struct ogrenci* gecisiListe = ogrenciListesi;
	char dersKodu[10];
	char dersAdi[50];
	int kredi, akts;
	secim = 0;
	int sonIndis;
	//ders eklemek istenilen ögrenci
	while (gecisiListe->ogrenciNo != no) {
		gecisiListe = gecisiListe->next;
	}
	while (secim != 2) {
		system("cls");
		cout << "Ders Kodu\t: ";
		cin >> dersKodu;
		cout << "Ders Adi\t: ";
		getchar();
		fgets(dersAdi, 50, stdin);
		sonIndis = strlen(dersAdi);
		dersAdi[sonIndis - 1] = '\0';
		cout << "Kredi\t\t: ";
		cin >> kredi;
		cout << "AKTS\t\t: ";
		cin >> akts;

		if (gecisiListe->dersListesi == NULL) {
			struct ders* dersListesi = NULL;
			dersListesi = dersEkle(dersListesi, (char*)dersKodu, (char*)dersAdi, kredi, akts);
			gecisiListe->dersListesi = dersListesi;
		}
		else {
			gecisiListe->dersListesi = dersEkle(gecisiListe->dersListesi, (char*)dersKodu, (char*)dersAdi, kredi, akts);
		}

		cout << "1-Yeni ders ekle" << endl;
		cout << "2-Ders eklemeyi bitir" << endl;
		dosyayaDersKaydet(ogrenciListesi);
		while (true) {
			cin >> secim;
			if (secim == 1 ||secim == 2) {
				break;
			} else {
				cout << "Hatali islem. Lutfen tekrar girin" << endl;
			}
		}
		if (secim == 2) {
			ogrenci.ogrenciBilgileri(ogrenciListesi, no);
		}
	}
}

struct ders* Ders::dersEkle(struct ders* dersListesi, char dersKodu[10], char dersAdi[50], int kredi, int akts) {
	struct ders* gecisiListe = (struct ders*)malloc(sizeof(struct ders));
	if (dersListesi == NULL) {
		for (i = 0; i < 10; i++) {
			gecisiListe->dersKodu[i] = dersKodu[i];
		}
		for (i = 0; i < 50; i++) {
			gecisiListe->dersAdi[i] = dersAdi[i];
		}
		gecisiListe->quiz1 = 0;
		gecisiListe->quiz2 = 0;
		gecisiListe->vize = 0;
		gecisiListe->final = 0;
		gecisiListe->ortalama = 0;
		gecisiListe->harfNotu[0] = '-';
		gecisiListe->harfNotu[1] = '-';
		gecisiListe->harfNotu[2] = '\0';
		gecisiListe->kredi = kredi;
		gecisiListe->akts = akts;
		gecisiListe->next = gecisiListe;
		gecisiListe->prev = gecisiListe;
		dersListesi = gecisiListe;
	}
	else {
		for (i = 0; i < 10; i++) {
			gecisiListe->dersKodu[i] = dersKodu[i];
		}
		for (i = 0; i < 50; i++) {
			gecisiListe->dersAdi[i] = dersAdi[i];
		}
		gecisiListe->quiz1 = 0;
		gecisiListe->quiz2 = 0;
		gecisiListe->vize = 0;
		gecisiListe->final = 0;
		gecisiListe->ortalama = 0;
		gecisiListe->harfNotu[0] = '-';
		gecisiListe->harfNotu[1] = '-';
		gecisiListe->harfNotu[2] = '\0';
		gecisiListe->kredi = kredi;
		gecisiListe->akts = akts;
		// liste çift bağlı ve dairesel olduğu için son eleman head->prev dir.
		dersListesi->prev->next = gecisiListe;
		gecisiListe->next = dersListesi;
		gecisiListe->prev = dersListesi->prev;
		dersListesi->prev = gecisiListe;
		dersListesi = gecisiListe;
	}
	cout << endl << "Ders Başarıyla Eklendi." << endl;
	return dersListesi;
}

struct ogrenci* Ders::dosyaOku(struct ogrenci* ogrenciListesi) {
	ifstream dosyaoku("bilgiler\\ders.txt", ios::in);
	//dosyadan alınan veriler
	string dDersKodu;
	string dDersAdi;
	int dQuiz1;
	int dQuiz2;
	int dVize;
	int dFinal;
	float dOrtalama;
	string dHarfNotu;
	int akts;
	int kredi;

	string oku; //dosya satırları oku
	int satir = 1;// okunan satır

	char dersKodu[10], dersAdi[50], harfNotu[3];

	struct ogrenci* gecisiListe = ogrenciListesi;
	if (gecisiListe == NULL) {
		return ogrenciListesi;
	}
	struct ders* gecisiListe2 = gecisiListe->dersListesi;
	while (getline(dosyaoku, oku)) {
		if (oku == "@") {
			gecisiListe = gecisiListe->next;
			continue;
		}
		else {
			if (satir == 1) {
				dDersKodu = oku;
				for (i = 0; i < oku.length(); i++) {
					dersKodu[i] = dDersKodu[i];
				}
				dersKodu[i] = '\0';
			}
			else if (satir == 2) {
				dDersAdi = oku;
				for (i = 0; i < oku.length(); i++) {
					dersAdi[i] = dDersAdi[i];
				}
				dersAdi[i] = '\0';
			}
			else if (satir == 3) {
				stringstream ss;
				ss << oku;
				ss >> dQuiz1;
			}
			else if (satir == 4) {
				stringstream ss;
				ss << oku;
				ss >> dQuiz2;
			}
			else if (satir == 5) {
				stringstream ss;
				ss << oku;
				ss >> dVize;
			}
			else if (satir == 6) {
				stringstream ss;
				ss << oku;
				ss >> dFinal;
			}
			else if (satir == 7) {
				stringstream ss;
				ss << oku;
				ss >> dOrtalama;
			}
			else if (satir == 8) {
				dHarfNotu = oku;
				for (i = 0; i < oku.length(); i++) {
					harfNotu[i] = dHarfNotu[i];
				}
				harfNotu[i] = '\0';
			}
			else if (satir == 9) {
				stringstream ss;
				ss << oku;
				ss >> akts;
			}
			else if (satir == 10) {
				stringstream ss;
				ss << oku;
				ss >> kredi;
				satir = 0;
				gecisiListe->dersListesi = dosyadanDersKaydet(gecisiListe, dersKodu, dersAdi, dQuiz1, dQuiz2, dVize, dFinal, dOrtalama, harfNotu, akts, kredi);
			}
		}
		satir++;
	}
	return ogrenciListesi;
}

struct ders* Ders::dosyadanDersKaydet(struct ogrenci* ogrenciListesi, char dersKodu[10], char dersAdi[50], int quiz1, int quiz2, int vize, int final, float ortalama, char harfNotu[3], int akts, int kredi) {
	struct ders* dersListesi = ogrenciListesi->dersListesi;
	struct ders* gecisiListe = (struct ders*)malloc(sizeof(struct ders));
	if (dersListesi == NULL) {
		for (i = 0; i < 10; i++) {
			gecisiListe->dersKodu[i] = dersKodu[i];
		}
		for (i = 0; i < 50; i++) {
			gecisiListe->dersAdi[i] = dersAdi[i];
		}
		gecisiListe->quiz1 = quiz1;
		gecisiListe->quiz2 = quiz2;
		gecisiListe->vize = vize;
		gecisiListe->final = final;
		gecisiListe->ortalama = ortalama;
		for (i = 0; i < 3; i++) {
			gecisiListe->harfNotu[i] = harfNotu[i];
		}
		gecisiListe->kredi = kredi;
		gecisiListe->akts = akts;
		gecisiListe->next = gecisiListe;
		gecisiListe->prev = gecisiListe;
		dersListesi = gecisiListe;
	}
	else {
		for (i = 0; i < 10; i++) {
			gecisiListe->dersKodu[i] = dersKodu[i];
		}
		for (i = 0; i < 50; i++) {
			gecisiListe->dersAdi[i] = dersAdi[i];
		}
		gecisiListe->quiz1 = quiz1;
		gecisiListe->quiz2 = quiz2;
		gecisiListe->vize = vize;
		gecisiListe->final = final;
		gecisiListe->ortalama = ortalama;
		for (i = 0; i < 3; i++) {
			gecisiListe->harfNotu[i] = harfNotu[i];
		}
		gecisiListe->kredi = kredi;
		gecisiListe->akts = akts;
		dersListesi->prev->next = gecisiListe; //son dugum
		gecisiListe->next = dersListesi;
		gecisiListe->prev = dersListesi->prev;
		dersListesi->prev = gecisiListe;
		dersListesi = gecisiListe;
	}
	return dersListesi;
}

void Ders::dosyayaDersKaydet(struct ogrenci* ogrenciListesi) {
	struct ogrenci* gecisiListe = ogrenciListesi;
	struct ders* gecisiListe2;
	struct ders* gecisiListe3;
	ofstream dosyaYaz("bilgiler\\ders.txt");

	if (dosyaYaz.is_open()) {
		if (ogrenciListesi == NULL) {
			return;
		}
		do {
			gecisiListe2 = gecisiListe->dersListesi;
			gecisiListe3 = gecisiListe->dersListesi;

			if (gecisiListe2 == NULL) {
				dosyaYaz << "@" << endl;
				gecisiListe = gecisiListe->next;
				continue;
			}
			do {
				dosyaYaz << gecisiListe2->dersKodu << endl;
				dosyaYaz << gecisiListe2->dersAdi << endl;
				dosyaYaz << gecisiListe2->quiz1 << endl;
				dosyaYaz << gecisiListe2->quiz2 << endl;
				dosyaYaz << gecisiListe2->vize << endl;
				dosyaYaz << gecisiListe2->final << endl;
				dosyaYaz << gecisiListe2->ortalama << endl;
				dosyaYaz << gecisiListe2->harfNotu << endl;
				dosyaYaz << gecisiListe2->akts << endl;
				dosyaYaz << gecisiListe2->kredi << endl;
				gecisiListe2 = gecisiListe2->next;
			} while (gecisiListe2 != gecisiListe3);
			dosyaYaz << "@" << endl;
			gecisiListe = gecisiListe->next;
		} while (gecisiListe != ogrenciListesi);
		dosyaYaz.close();
	}
}

void Ders::notListele(struct ders* dersListesi, struct ogrenci* ogrenciListesi, int no) {
	SetConsoleTitleA("Not Listesi");
	system("cls");
	if (dersListesi == NULL) {
		cout << "Ders kaydı bulunamadı. Lutfen ders ekleyin." << endl;
		cout << "1-Geri" << endl;
		cin >> secim;
		system("cls");
		switch (secim) {
		case 1:
			ogrenci.ogrenciBilgileri(ogrenciListesi, no);
			break;
		default:
			break;
		}
		return;
	}
	struct ders* gecisiListe = dersListesi;
	do {
		printf("%s\t%s\nQuiz1: %-3d\tQuiz2: %-3d\tVize: %-3d\tFinal: %-3d\tOrtalama: %.2f\t\tHarf: %s",
			gecisiListe->dersKodu, gecisiListe->dersAdi, gecisiListe->quiz1, gecisiListe->quiz2, gecisiListe->vize, gecisiListe->final, gecisiListe->ortalama, gecisiListe->harfNotu);
		cout << endl << "-------------------------------------------------------------------------------------------------" << endl;
		gecisiListe = gecisiListe->next;
	} while (gecisiListe != dersListesi);
	dersIslemleri(dersListesi, ogrenciListesi, no);
}

void Ders::dersIslemleri(struct ders* dersListesi, struct ogrenci* ogrenciListesi, int no) {
	cout << endl << "Islemler" << endl;
	while (true) {
		cout << "1-Not girisi" << endl;
		cout << "2-Not guncelle" << endl;
		cout << "3-Ders sil" << endl;
		cout << "4-Ders guncelle" << endl;
		cout << "5-Ortalamaya gore listele" << endl;
		cout << "6-Geri" << endl;
		cin >> secim;
		if (secim == 1 || secim == 2 || secim == 3 || secim == 4 || secim == 5 || secim == 6) {
			break;
		}
		else {
			cout << "Hatali islem. Lutfen tekrar girin" << endl;
		}
	}
	char kod[10];
	switch (secim) {
	case 1:
		cout << "Not eklemek istediginiz dersin kodunu girin" << endl;
		while (true) {
			cin >> kod;
			if (!dersVarmi(dersListesi, kod)) {
				cout << "Girdiginiz koda ait ders bulunamadi. Lutfen tekrar giriniz" << endl;
			}
			else {
				break;
			}
		}
		SetConsoleTitleA("Not Girisi");
		system("cls");
		notEkle(dersListesi, ogrenciListesi, no, kod);
		cout << endl << "Not girisi tamamlandi" << endl;
		cout << "1-Geri" << endl;
		cin >> secim;
		if (secim) {
			notListele(dersListesi, ogrenciListesi, no);
		}
		break;
	case 2:
		cout << "Not guncellemek istediginiz dersin kodunu girin" << endl;
		while (true) {
			cin >> kod;
			if (!dersVarmi(dersListesi, kod)) {
				cout << "Girdiginiz koda ait ders bulunamadi. Lutfen tekrar giriniz" << endl;
			}
			else {
				break;
			}
		}
		notGuncelle(dersListesi, ogrenciListesi, no, kod); 
		cout << endl << "Not basarıyla guncellendi" << endl;
		cout << "1-Geri" << endl;
		cin >> secim;
		if (secim) {
			notListele(dersListesi, ogrenciListesi, no);
		}
		break;
	case 3:
		cout << "Silmek istediginiz dersin kodunu girin" << endl;
		while (true) {
			cin >> kod;
			if (!dersVarmi(dersListesi, kod)) {
				cout << "Girdiginiz koda ait ders bulunamadi. Lutfen tekrar giriniz" << endl;
			}
			else {
				break;
			}
		}
		dersListesi = dersSil(dersListesi, ogrenciListesi, no, kod);
		ogrenciListesi->dersListesi = dersListesi;
		dosyayaDersKaydet(ogrenciListesi);
		anoHesapla(dersListesi, ogrenciListesi);

		ogrenci.dosyadaOgrenciGuncelle(ogrenciListesi);
		ogrenciListesi = NULL;
		ogrenciListesi = ogrenci.dosyaOku(ogrenciListesi);
		ogrenci.dosyadaOgrenciGuncelle(ogrenciListesi);
		ogrenciListesi = NULL;
		ogrenciListesi = ogrenci.dosyaOku(ogrenciListesi);
		ogrenciListesi = dosyaOku(ogrenciListesi);

		SetConsoleTitleA("Ders Sil");
		system("cls");
		cout << "Ders silme tamamlandi" << endl;
		cout << "1-Geri" << endl;
		cin >> secim;
		if (secim) {
			notListele(dersListesi, ogrenciListesi, no);
		}
		break;
	case 4:
		cout << "Guncellemek istediginiz dersin kodunu girin" << endl;
		while (true) {
			cin >> kod;
			if (!dersVarmi(dersListesi, kod)) {
				cout << "Girdiginiz koda ait ders bulunamadi. Lutfen tekrar giriniz" << endl;
			}
			else {
				break;
			}
		}
		SetConsoleTitleA("Ders Guncelle");
		dersGuncelle(dersListesi, kod, ogrenciListesi, no);
		break;
	case 5:
		sirala(dersListesi, ogrenciListesi, no);
		break;
	case 6:
		ogrenci.ogrenciBilgileri(ogrenciListesi, no);
		break;
	default:
		break;
	}
}

void Ders::sirala(struct ders* dersListesi, struct ogrenci* ogrenciListesi, int no) {
	system("cls");
	struct agac* kok = NULL;
	struct ders* gecisiListe = dersListesi;
	do {
		kok = siralama.ekle(kok, gecisiListe->dersKodu, gecisiListe->dersAdi, gecisiListe->quiz1, gecisiListe->quiz2, gecisiListe->vize, gecisiListe->final, gecisiListe->ortalama, gecisiListe->harfNotu);
		gecisiListe = gecisiListe->next;
	} while (gecisiListe != dersListesi);
	siralama.yazdir(kok);
	dersIslemleri(dersListesi, ogrenciListesi, no);
}

void Ders::dersGuncelle(struct ders* dersListesi, char kod[10], struct ogrenci* ogrenciListesi, int no) {
	system("cls");
	char dersKodu[10];
	char dersAdi[50];
	int kredi, akts;
	int sonIndis;
	struct ders* gecisiListe = dersListesi;
	struct ogrenci* gecisiListe2 = ogrenciListesi;
	do {
		if ((strcmp(gecisiListe->dersKodu, kod) == 0)) {
			break;
		}
		gecisiListe = gecisiListe->next;
	} while (gecisiListe != dersListesi);

	do {
		if (gecisiListe2->dersListesi == gecisiListe) {
			break;
		}
		gecisiListe2 = gecisiListe2->next;
	} while (gecisiListe2 != ogrenciListesi);

	cout << "Mevcut bilgiler" << endl;
	cout << "Ders kodu\t: ";
	cout << gecisiListe->dersKodu << endl;
	cout << "Ders adi\t: ";
	cout << gecisiListe->dersAdi << endl;
	cout << "Kredi\t\t: ";
	cout << gecisiListe->kredi << endl;
	cout << "AKTS\t\t: ";
	cout << gecisiListe->akts << endl;

	cout << endl << "Ders Kodu\t: ";
	cin >> dersKodu;
	cout << "Ders Adi\t: ";
	getchar();
	fgets(dersAdi, 50, stdin);
	cout << "Kredi\t\t: ";
	cin >> kredi;
	cout << "AKTS\t\t: ";
	cin >> akts;

	sonIndis = strlen(dersAdi);
	dersAdi[sonIndis - 1] = '\0';

	for (i = 0; i < 10; i++) {
		gecisiListe->dersKodu[i] = dersKodu[i];
	}

	for (i = 0; i < 50; i++) {
		gecisiListe->dersAdi[i] = dersAdi[i];
	}
	gecisiListe->kredi = kredi;
	gecisiListe->akts = akts;
	gecisiListe2->dersListesi = gecisiListe;
	ogrenciListesi = gecisiListe2;

	dosyayaDersKaydet(ogrenciListesi);
	anoHesapla(dersListesi, ogrenciListesi);

	ogrenci.dosyadaOgrenciGuncelle(ogrenciListesi);
	ogrenciListesi = NULL;
	ogrenciListesi = ogrenci.dosyaOku(ogrenciListesi);
	ogrenci.dosyadaOgrenciGuncelle(ogrenciListesi);
	ogrenciListesi = NULL;
	ogrenciListesi = ogrenci.dosyaOku(ogrenciListesi);
	ogrenciListesi = dosyaOku(ogrenciListesi);

	cout << endl << "Ders başarıyla guncellendi." << endl;
	cout << "1-Geri" << endl;
	cin >> secim;
	if (secim == 1) {
		notListele(dersListesi, ogrenciListesi, no);
	}
}

bool Ders::dersVarmi(struct ders* dersListesi, char dersKodu[10]) {
	struct ders* gecisiListe = dersListesi;
	if (dersListesi == NULL) {
		return false;
	}
	do {
		if ((strcmp(gecisiListe->dersKodu, dersKodu) == 0)) {
			return true;
		}
		else {
			gecisiListe = gecisiListe->next;
		}
	} while (gecisiListe != dersListesi);
	return false;
}

	struct ders* Ders::dersSil(struct ders* dersListesi, struct ogrenci* ogrenciListesi, int no, char kod[10]) {
		struct ders* gecisiListe = dersListesi;
		if ((gecisiListe->next == dersListesi) && (strcmp(gecisiListe->dersKodu, kod) == 0)) { //bir dugum varsa
			free(dersListesi);
			dersListesi = NULL;
		}
		else if ((gecisiListe->prev->next == dersListesi) && (strcmp(gecisiListe->prev->dersKodu, kod) == 0)) { //silinecek ders ilk dugum ise
			gecisiListe = dersListesi->prev;
			struct ders* gecisiListe2 = gecisiListe->prev;
			free(gecisiListe);
			gecisiListe2->next = dersListesi;
			dersListesi->prev = gecisiListe2;
		}
		else if ((gecisiListe->next != dersListesi) && (strcmp(gecisiListe->dersKodu, kod) == 0)) { //silinecek ders son dugum ise
			struct ders* gecisiListe2 = dersListesi->next;
			gecisiListe = dersListesi->prev;//son dugum
			gecisiListe2 = dersListesi->next;
			free(dersListesi);
			gecisiListe->next = gecisiListe2;
			gecisiListe2->prev = gecisiListe;
			dersListesi = gecisiListe2;
		}
		else { //silinecek ders orta dugum ise
			while (strcmp(gecisiListe->dersKodu, kod) != 0) {
				if (gecisiListe->next == dersListesi) {
					cout << "Silmek istediginiz ders bulunamadı" << endl;
					return dersListesi;
				}
				gecisiListe = gecisiListe->next;
			}
			struct ders* gecisiListe2 = gecisiListe->next;
			gecisiListe2->prev = gecisiListe->prev;
			gecisiListe->prev->next = gecisiListe2;
			free(gecisiListe);
		}
		return dersListesi;
	}

void Ders::notGuncelle(struct ders* dersListesi, struct ogrenci* ogrenciListesi, int no, char kod[10]) {
	SetConsoleTitleA("Not Guncelle");
	system("cls");
	struct ders* gecisiListe = dersListesi;
	do {
		if ((strcmp(gecisiListe->dersKodu, kod) == 0)) {
			break;
		}
		else {
			gecisiListe = gecisiListe->next;
		}
	} while (gecisiListe != dersListesi);
	
	cout << "Mevcut bilgiler" << endl;
	cout << "Ders Adi: ";
	cout << gecisiListe->dersAdi << endl;
	cout << "Quiz1\t: ";
	cout << gecisiListe->quiz1 << endl;
	cout << "Quiz2\t: ";
	cout << gecisiListe->quiz2 << endl;
	cout << "Vize\t: ";
	cout << gecisiListe->vize << endl;
	cout << "Final\t: ";
	cout << gecisiListe->final << endl << endl;
	notEkle(dersListesi, ogrenciListesi, no, kod);
}

void Ders::notEkle(struct ders* dersListesi, struct ogrenci* ogrenciListesi, int no, char kod[5]) {
	struct ders* gecisiListe = dersListesi;
	int quiz1, quiz2, vize, final;
	float ortalama;
	while (true) {
		if (strcmp(gecisiListe->dersKodu, kod) == 0)
			break;
		gecisiListe = gecisiListe->next;
	}
	cout << "Ders Adi: ";
	puts(gecisiListe->dersAdi);
	cout << "Quiz1\t: ";
	cin >> quiz1;
	cout << "Quiz2\t: ";
	cin >> quiz2;
	cout << "Vize\t: ";
	cin >> vize;
	cout << "Final\t: ";
	cin >> final;
	ortalama = (float)quiz1 * 0.1 + (float)quiz2 * 0.1 + (float)vize * 0.3 + (float)final * 0.5;
	gecisiListe->quiz1 = quiz1;
	gecisiListe->quiz2 = quiz2;
	gecisiListe->vize = vize;
	gecisiListe->final = final;
	gecisiListe->ortalama = ortalama;
	if (ortalama >= 0 && ortalama <= 39.99999) {
		gecisiListe->harfNotu[0] = 'F';
		gecisiListe->harfNotu[1] = 'F';
		gecisiListe->harfNotu[2] = '\0';
	}
	else if (ortalama >= 40 && ortalama <= 49.99999) {
		gecisiListe->harfNotu[0] = 'F';
		gecisiListe->harfNotu[1] = 'D';
		gecisiListe->harfNotu[2] = '\0';
	}
	else if (ortalama >= 50 && ortalama <= 54.99999) {
		gecisiListe->harfNotu[0] = 'D';
		gecisiListe->harfNotu[1] = 'D';
		gecisiListe->harfNotu[2] = '\0';
	}
	else if (ortalama >= 55 && ortalama <= 59.99999) {
		gecisiListe->harfNotu[0] = 'D';
		gecisiListe->harfNotu[1] = 'C';
		gecisiListe->harfNotu[2] = '\0';
	}
	else if (ortalama >= 60 && ortalama <= 69.99999) {
		gecisiListe->harfNotu[0] = 'C';
		gecisiListe->harfNotu[1] = 'C';
		gecisiListe->harfNotu[2] = '\0';
	}
	else if (ortalama >= 70 && ortalama <= 79.99999) {
		gecisiListe->harfNotu[0] = 'C';
		gecisiListe->harfNotu[1] = 'B';
		gecisiListe->harfNotu[2] = '\0';
	}
	else if (ortalama >= 80 && ortalama <= 84.99999) {
		gecisiListe->harfNotu[0] = 'B';
		gecisiListe->harfNotu[1] = 'B';
		gecisiListe->harfNotu[2] = '\0';
	}
	else if (ortalama >= 85 && ortalama <= 89.99999) {
		gecisiListe->harfNotu[0] = 'B';
		gecisiListe->harfNotu[1] = 'A';
		gecisiListe->harfNotu[2] = '\0';
	}
	else if (ortalama >= 90 && ortalama <= 100) {
		gecisiListe->harfNotu[0] = 'A';
		gecisiListe->harfNotu[1] = 'A';
		gecisiListe->harfNotu[2] = '\0';
	}
	dosyayaDersKaydet(ogrenciListesi);
	anoHesapla(dersListesi, ogrenciListesi);

	ogrenci.dosyadaOgrenciGuncelle(ogrenciListesi);
	ogrenciListesi = NULL;
	ogrenciListesi = ogrenci.dosyaOku(ogrenciListesi);
	ogrenci.dosyadaOgrenciGuncelle(ogrenciListesi);
	ogrenciListesi = NULL;
	ogrenciListesi = ogrenci.dosyaOku(ogrenciListesi);
	ogrenciListesi = dosyaOku(ogrenciListesi);
}

void Ders::anoHesapla(struct ders* dersListesi, struct ogrenci* ogrenciListesi) {
	struct ders* gecisiListe = dersListesi;
	struct ogrenci* gecisiListe2 = ogrenciListesi;
	float ano = 0;
	int toplamKredi = 0;
	float toplam = 0;
	char harf[9][2] = { {'A','A'}, {'B','A'}, {'B','B'}, {'C','B'}, {'C','C'}, {'D','C'}, {'D','D'}, {'F','D'}, {'F','F'} };
	float puan[] = { 4.00, 3.50, 3.25, 3.00, 2.50, 2.25, 2.00, 1.50, 0.0 };

	if (gecisiListe == NULL) {
		gecisiListe2->ano = 0;
		return;
	}
	
	do {
		if (gecisiListe->harfNotu[0] == '-') {
			gecisiListe = gecisiListe->next;
			continue;
		}

		for (i = 0; i < 9; i++) {
			if (gecisiListe->harfNotu[0] == harf[i][0] && gecisiListe->harfNotu[1] == harf[i][1]) {
				toplam += (float)gecisiListe->kredi * puan[i];
				toplamKredi += gecisiListe->kredi;
				break;
			}
		}
		gecisiListe = gecisiListe->next;
	} while (gecisiListe != dersListesi);
	ano = toplam / (float)toplamKredi;

	//ano hesaplanan ogrenci
	do {
		if (gecisiListe2->dersListesi == gecisiListe) {
			break;
		}
		gecisiListe2 = gecisiListe2->next;
	} while (gecisiListe2 != ogrenciListesi);

	gecisiListe2->ano = ano;
	ogrenciListesi = gecisiListe2;
}