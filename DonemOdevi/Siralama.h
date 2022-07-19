#pragma once
class Siralama
{
public:
	struct agac* ekle(struct agac* kok, char dersKodu[10], char dersAdi[50], int quiz1, int quiz2, int vize, int final, float ortalama, char harfNotu[3]);
	void yazdir(struct agac* kok);

private:
	struct agac* yeni(char dersKodu[10], char dersAdi[50], int quiz1, int quiz2, int vize, int final, float ortalama, char harfNotu[3]);
	int i; //for dongusu icin
};
