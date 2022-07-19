#include "Siralama.h"
#include <stdio.h>
#include <conio.h>
#include <iostream>

using namespace std;

struct agac {
	char dersKodu[10];
	char dersAdi[50];
	int quiz1;
	int quiz2;
	int vize;
	int final;
	float ortalama;
	char harfNotu[3];
	struct agac* sol;
	struct agac* sag;
};

struct agac* Siralama::yeni(char dersKodu[10], char dersAdi[50], int quiz1, int quiz2, int vize, int final, float ortalama, char harfNotu[3]) {
	struct agac* p = new agac();
	for (i = 0; i < 10; i++) {
		p->dersKodu[i] = dersKodu[i];
	}
	for (i = 0; i < 50; i++) {
		p->dersAdi[i] = dersAdi[i];
	}
	p->quiz1 = quiz1;
	p->quiz2 = quiz2;
	p->vize = vize;
	p->final = final;
	p->ortalama = ortalama;
	for (i = 0; i < 3; i++) {
		p->harfNotu[i] = harfNotu[i];
	}
	p->sol = NULL;
	p->sag = NULL;
	return p;
}

struct agac* Siralama::ekle(struct agac* kok, char dersKodu[10], char dersAdi[50], int quiz1, int quiz2, int vize, int final, float ortalama, char harfNotu[3]) {
	if (kok != NULL) {
		if (ortalama < kok->ortalama) {
			kok->sol = ekle(kok->sol, dersKodu, dersAdi, quiz1, quiz2, vize, final, ortalama, harfNotu);
		}
		else {
			kok->sag = ekle(kok->sag, dersKodu, dersAdi, quiz1, quiz2, vize, final, ortalama, harfNotu);
		}
	}
	else {
		kok = yeni(dersKodu, dersAdi, quiz1, quiz2, vize, final, ortalama, harfNotu);
	}
	return kok;
}

void Siralama::yazdir(struct agac* kok) {
	if (kok != NULL) {
		yazdir(kok->sol);
		printf("%s\t%s\nQuiz1: %d\tQuiz2: %d\tVize: %d\tFinal: %d\tOrtalama: %.2f\t\tHarf: %s\n",
			kok->dersKodu, kok->dersAdi, kok->quiz1, kok->quiz2, kok->vize, kok->final, kok->ortalama, kok->harfNotu);
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		yazdir(kok->sag);
	}
}
