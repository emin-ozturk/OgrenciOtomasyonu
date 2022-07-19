#pragma once
class Ogrenci
{
public:
	void baslat(struct ogrenci* ogrenciListesi);
	void ogrenciBilgileri(struct ogrenci* ogrenciListesi, int no);
	void dosyadaOgrenciGuncelle(struct ogrenci* ogrenciListesi);
	struct ogrenci* dosyaOku(struct ogrenci* ogrenciListesi);

private:
	void anaSayfa(struct ogrenci* ogrenciListesi);
	void ogrenciBilgileriAl(struct ogrenci* ogrenciListesi);
	struct ogrenci* ogrenciEkle(struct ogrenci* ogrenciListesi, int ogrenciNo, char ogrenciAdi[20], char bolum[50], int sinif, float ano);
	void ogrenciGuncelle(struct ogrenci* ogrenciListesi, int no);
	void ogrencileriListeleIslemleri(struct ogrenci* ogrenciListesi, struct ogrenci* gecisiListe);
	void ogrencileriListele(struct ogrenci* ogrenciListesi);
	struct ogrenci* ogrenciSil(struct ogrenci* ogrenciListesi, int no);
	void dosyayaOgrenciKaydet(struct ogrenci* ogrenciListesi);
	void ogrenciBilgileriniKaydet(struct ogrenci* ogrenciListesi);
	bool ogrenciNoAra(struct ogrenci* ogrenciListesi, int ogrenciNo);
	bool bolumAra(struct ogrenci* ogrenciListesi, char bolum[50]);
	void filtrele(struct ogrenci* ogrenciListesi, struct ogrenci* gecisi, char bolum[50]);
	int secim; //gidilecek sayfayı belirlemek için
	int i; //for döngüsü için
};
