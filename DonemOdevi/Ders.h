#pragma once
class Ders
{
public:
	void dosyayaDersKaydet(struct ogrenci* ogrenciListesi);
	void dersBilgileriAl(struct ogrenci* ogrenciListesi, int no);
	void notListele(struct ders* dersListesi, struct ogrenci* ogrenciListesi, int no);
	struct ogrenci* dosyaOku(struct ogrenci* ogrenciListesi);

private:
	struct ders* dersEkle(struct ders* dersListesi, char dersKodu[10], char dersAdi[50], int kredi, int akts);
	void notEkle(struct ders* dersListesi, struct ogrenci* ogrenciListesi, int no, char kod[10]);
	void notGuncelle(struct ders* dersListesi, struct ogrenci* ogrenciListesi, int no, char kod[10]);
	struct ders* dersSil(struct ders* dersListesi, struct ogrenci* ogrenciListesi, int no, char kod[10]);
	void dersGuncelle(struct ders* dersListesi, char kod[10], struct ogrenci* ogrenciListesi, int no);
	struct ders* dosyadanDersKaydet(struct ogrenci* ogrenciListesi, char dersKodu[10], char dersAdi[50], int quiz1, int quiz2, int vize, int final, float ortalama, char harfNotu[3], int akts, int kredi);
	bool dersVarmi(struct ders* dersListesi, char dersKodu[10]);
	void anoHesapla(struct ders* dersListesi, struct ogrenci* ogrenciListesi);
	void sirala(struct ders* dersListesi, struct ogrenci* ogrenciListesi, int no);
	void dersIslemleri(struct ders* dersListesi, struct ogrenci* ogrenciListesi, int no);
	int secim; //gidilecek sayfayı belirlemek için
	int i; //for döngüsü için
};
