#include "Filtre.h"
#include <iostream>

struct filtre {
	int ogrenciNo;
	char ogrenciAdi[20];
	char bolum[50];
	struct filtre* next;
};

struct kuyruk {
	int cnt;
	filtre* front;
	filtre* rear;
};


struct kuyruk* Filtre::baslat(struct kuyruk* k) {
	k = (kuyruk*)malloc(sizeof(kuyruk));
	k->cnt = 0;
	k->front = NULL;
	k->rear = NULL;
	return k;
}

int Filtre::bosMu(struct kuyruk* k) {
	return(k->cnt == 0);
}

void Filtre::ekle(struct kuyruk* k, int ogrenciNo, char ogrenciAdi[20], char bolum[50]) {
	struct filtre* gecisiListe = (struct filtre*)malloc(sizeof(struct filtre));
	gecisiListe->ogrenciNo = ogrenciNo;
	for (i = 0; i < 20; i++) {
		gecisiListe->ogrenciAdi[i] = ogrenciAdi[i];
	}
	for (i = 0; i < 50; i++) {
		gecisiListe->bolum[i] = bolum[i];
	}
	gecisiListe->next = NULL;
	if (bosMu(k)) {
		k->front = k->rear = gecisiListe;
	}
	else {
		k->rear->next = gecisiListe;
		k->rear = gecisiListe;
	}
	k->cnt++;
}

void Filtre::yazdir(struct kuyruk* k) {
	if (!bosMu(k)) {
		struct filtre* gecisiListe = k->front;
		do {
			printf("Ogrenci No: %-20d\tAd: %-20s\tBolum: %s\n", gecisiListe->ogrenciNo, gecisiListe->ogrenciAdi, gecisiListe->bolum);
			gecisiListe = gecisiListe->next;
		} while (gecisiListe != NULL);
	}
}
