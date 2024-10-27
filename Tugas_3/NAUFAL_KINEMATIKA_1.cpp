#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
using namespace std;

void Kec(double x, double y, double w, double R, double r, double theta[]) {
    double m[3];  // Array untuk menyimpan kecepatan roda

    for (int i = 0; i < 3; i++) {
        m[i] = (x * cos(theta[i] * M_PI / 180.0) + y * sin(theta[i] * M_PI / 180.0) + w * R) / r;
    }

    if (x != 0 && r == 0.0635) {
        m[2] *= -1;
    } else if (x != 0 && r == 0.024) {
        m[2] *= x;
    } else if (y != 0 && r == 0.0635) {
        m[1] *= -1;
    } else if (y != 0 && r == 0.024) {
        m[0] *= -1;
        m[2] = 0;
    }

    cout << m[0] << "\n" << m[1] << " \n" << m[2] << " \n";
}

int main() {
    string nama;
    cin >> nama;
    if (nama == "LILDAN") {
        double diameter = 0.127; // Diameter roda dalam meter
        double r = diameter / 2;  // Jari-jari roda
        double R = 0.15;          // Jarak roda ke pusat
        double theta[3] = {135.0, 90.0, 135.0}; // Sudut roda dalam derajat
        double on[100][4];
        double a, b, c;
        int i = 1;
        string input;

        // Loop untuk mengambil input
        while (true) {
            cin >> input;
            if (input == "GAS") {  // Cek jika input adalah "GAS"
                break;
            }

            // Konversi input menjadi angka jika bukan "GAS"
            a = stod(input); // Konversi input pertama menjadi a
            cin >> b >> c;   // Lanjutkan baca b dan c

            on[i][1] = a;
            on[i][2] = b;
            on[i][3] = c;
            i++;
        }

        cout << "▽" << endl;
        cout<<fixed<<setprecision(2);
        for (int j = 1; j < i; j++) {
            Kec(on[j][1], on[j][2], on[j][3], R, r, theta);
        }
    } else if (nama == "DHARMI") {
        double diameter = 0.048; // Diameter roda dalam meter
        double r = diameter / 2;  // Jari-jari roda
        double R = 0.15;          // Jarak roda ke pusat
        double theta[3] = {120,120,120}; // Sudut roda dalam derajat
        double on[100][4];
        double a, b, c;
        int i = 1;
        string input;

        // Loop untuk mengambil input
        while (true) {
            cin >> input;
            if (input == "GAS") {  // Cek jika input adalah "GAS"
                break;
            }

            // Konversi input menjadi angka jika bukan "GAS"
            a = stod(input); // Konversi input pertama menjadi a
            cin >> b >> c;   // Lanjutkan baca b dan c

            on[i][1] = b;
            on[i][2] = a;
            on[i][3] = c;
            i++;
        }
        cout << "△" << endl;
        cout<<fixed<<setprecision(2);
        for (int j = 1; j < i; j++) {
            Kec(on[j][1], on[j][2], on[j][3], R, r, theta);
        }
        
    } else {
        cout << "Nama robot tidak valid" << endl;
    }
    return 0;
} 