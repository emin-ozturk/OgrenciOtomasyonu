#include <iostream>
#include "Ogrenci.h"

using namespace std;
struct ogrenci* ogrenciListesi = NULL;

int main(int argc, char** argv) {
	Ogrenci ogrenci;
	ogrenci.baslat(ogrenciListesi);
	return 0;
}