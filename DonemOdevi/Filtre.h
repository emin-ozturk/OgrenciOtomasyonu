#pragma once
class Filtre
{
public:
	struct kuyruk* baslat(struct kuyruk* k);
	void ekle(struct kuyruk* k, int ogrenciNo, char ogrenciAdi[20], char bolum[50]);
	void yazdir(struct kuyruk* k);
private:
	int bosMu(struct kuyruk* k);
	int i; //for döngüsü için
};
