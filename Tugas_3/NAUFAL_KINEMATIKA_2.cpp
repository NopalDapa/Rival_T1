#include <iostream>
#include <iomanip> // untuk bisa pake std::fixed dan std::setprecision
#include <cmath>
#include <array>

using namespace std;

// Fungsi untuk mengalikan dua matriks 4x4
array<array<double, 4>, 4> MMatriks(
    const array<array<double, 4>, 4>& A,
    const array<array<double, 4>, 4>& B) {
    
    array<array<double, 4>, 4> hasil = {0};
    
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            hasil[i][j] = 0;
            for (int k = 0; k < 4; ++k) {
                hasil[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    
    return hasil;
}

// Fungsi untuk membuat matriks transformasi D-H
array<array<double, 4>, 4> matriksDH(double theta, double d, double a, double alpha) {
    array<array<double, 4>, 4> matrix = {{
        {cos(theta), -sin(theta) * cos(alpha), sin(theta) * sin(alpha), a * cos(theta)},
        {sin(theta), cos(theta) * cos(alpha), -cos(theta) * sin(alpha), a * sin(theta)},
        {0, sin(alpha), cos(alpha), d},
        {0, 0, 0, 1}
    }};
    
    return matrix;
}

// fungsi untuk membulatkan ke 0 jika terlalu kecil
double bulatkan(double value, double threshold = 1e-6) {
    return fabs(value) < threshold ? 0.0 : value;
}

// fungsi untuk konversi derajat ke radian
double torad(double theta){
    return theta * M_PI / 180.0;
}

int main() {
    // Konversi derajat ke radian
    char robot;
    double theta1, theta2, theta3, d1, a2, a3;
    
    cin >> robot >> theta1 >> theta2 >> theta3;
    
    theta1 = torad(theta1);
    theta2 = torad(theta2);
    theta3 = torad(theta3);
    
    double alpha1 = 90 * M_PI / 180.0;

    if (robot == 'L') {  
        d1 = 5.0; a2 = 3.0; a3 = 2.0;
    } else if (robot == 'D') {  
        d1 = 6.0; a2 = 3.0; a3 = 2.0;
    } else {
        cout << "Robot Tidak Valid\n";
        return 0;
    }

    // Matriks transformasi A1, A2, dan A3
    auto A1 = matriksDH(theta1, d1, 0, alpha1);
    auto A2 = matriksDH(theta2, 0, a2, 0);
    auto A3 = matriksDH(theta3, 0, a3, 0);

    // Matriks transformasi total T = A1 * A2 * A3
    auto T = MMatriks(MMatriks(A1, A2), A3);

    // posisi end-effector arm robot
    double x = bulatkan(T[0][3]);
    double y = bulatkan(T[1][3]);
    double z = bulatkan(T[2][3]);

    // Output dengan 2 angka di belakang koma
    cout << fixed << setprecision(2);
    cout << x << "\n" << y << "\n" << z << endl;

    return 0;
}
