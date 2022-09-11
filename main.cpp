#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <time.h>

using namespace std;

enum Operasyon {
    Toplama,
    Cikarma,
    Carpma,
    Bolme
};

string operasyonIsareti(Operasyon operasyon) {
    switch (operasyon) {
        case Operasyon::Toplama:
            return " + ";
        case Operasyon::Cikarma:
            return " - ";
        case Operasyon::Carpma:
            return " * ";
        case Operasyon::Bolme:
            return " / ";
    }
}

double operasyonUygula(Operasyon operasyon, double sayi1, double sayi2) {
    switch (operasyon) {
        case Operasyon::Toplama:
            return sayi1 + sayi2;
        case Operasyon::Cikarma:
            return sayi1 - sayi2;
        case Operasyon::Carpma:
            return sayi1 * sayi2;
        case Operasyon::Bolme:
            if (sayi2 == 0.0)
                return 0.0;
            else
                return sayi1 / sayi2;
    }
}

void sayiAtama(vector<double>& list, int& hedef) {
    srand(time(NULL));
    cout <<"\n\tIslem Cozucu Arayuzune Hos Geldiniz!" << endl;
    for(int i = 0; i < 5; i++){
        int x;
        x = rand() % 9 + 1;
        cout << "\n\tUretilen " << i + 1 << ". tek haneli sayimiz =\t" << x << endl;
        list.push_back((double)x);
    }
    int x = (rand() % 9 + 1) * 10;
    cout << "\n\t10'nun kati olan cift haneli sayimiz =  " << x <<endl;
    list.push_back((double)x);
    cout << "\n\tUlasilmasini istediginiz 3 basamakli sayiyi giriniz: ";
    cin >> hedef;
    sort(list.begin(), list.end());
    cout << "\n\t*----------------------------\n\n";
}

void hesapla(vector<double>& list, int hedef, vector<Operasyon>& operasyonlar, int& sayac, set<string>& cozumler) {
    if(operasyonlar.size() + 1 < list.size()) {
        for(int i = 0; i < 4; i++) {
            operasyonlar.push_back((Operasyon)i);
            hesapla(list, hedef, operasyonlar, sayac, cozumler);
            operasyonlar.pop_back();
        }
        //return;
    }

    double araDeger = list[0];
    for(int i = 0; i < operasyonlar.size(); i++) {
        araDeger = operasyonUygula(operasyonlar[i], araDeger, list[i+1]);
    }

    if(abs(araDeger - hedef) < .00000000001) {
        string cozum = std::to_string((int)list[0]);

        for(int i = 0; i < operasyonlar.size(); i++){
            cozum += operasyonIsareti(operasyonlar[i]);
            cozum += std::to_string((int)list[i+1]);
        }

        if (cozumler.count(cozum) == 0) {
            cozumler.insert(cozum);
            sayac++;
            cout << "\t\t" << sayac << ". cozum  " << cozum << " = " << hedef << endl << endl;
        }
    }
}

int main() {
    set<string> cozumler;
    int hedef;
    int sayac = 0;
    while(true) {
        vector<Operasyon> operasyonlar;
        vector<double> list;
        sayiAtama(list, hedef);
        do {
            hesapla(list, hedef, operasyonlar, sayac, cozumler);
        } while(next_permutation(list.begin(), list.end()));
        sayac = 0;
        cout << "\tOlasi tum cozumler listelenmistir.\n\tEger bir cozum goremiyorsaniz, verilen degerler ile hedefe ulasan bir cozum bulunmamaktadir.\n";
        cout << "\tBaska uretilen degerlerle denemek icin \"ENTER\" tusuna basiniz...\n";
        getchar();
        getchar();
    }
    return 0;
}