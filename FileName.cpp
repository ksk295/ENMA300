#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    cout << fixed << setprecision(3);

    // Initial intensity
    double I0 = 10.0;
    double I = I0;

    // Refractive indices
    double n_air = 1.000;
    double n_PMMA = 1.489;
    double n_water = 1.333;
    double n_polymer = 1.460;

    // Absorption coefficients (m^-1)
    double alpha_PMMA = 0.132;
    double alpha_water = 0.097;
    double alpha_polymer = 0.132;

    // Thicknesses (m)
    double t_PMMA_front = 0.002;
    double t_water = 0.010;
    double t_polymer = 0.002;
    double t_PMMA_back = 0.020;

    // Variables for reflection, transmission, absorption
    double R, T_interface, T_abs;

    cout << "Initial intensity = " << I << " W/m^2" << endl << endl;

    // 1. air -> PMMA(front)
    R = pow((n_air - n_PMMA) / (n_air + n_PMMA), 2);
    T_interface = 1 - R;
    T_abs = exp(-alpha_PMMA * t_PMMA_front);
    I = I * T_interface * T_abs;

    cout << "After air -> PMMA(front): " << I << " W/m^2" << endl;

    // 2. PMMA -> water
    R = pow((n_PMMA - n_water) / (n_PMMA + n_water), 2);
    T_interface = 1 - R;
    T_abs = exp(-alpha_water * t_water);
    I = I * T_interface * T_abs;

    cout << "After PMMA -> After water interface + absorption: " << I << " W/m^2" << endl;

    // 3. water -> new polymer
    R = pow((n_water - n_polymer) / (n_water + n_polymer), 2);
    T_interface = 1 - R;
    T_abs = exp(-alpha_polymer * t_polymer);
    I = I * T_interface * T_abs;

    cout << "After water -> new polymer: " << I << " W/m^2" << endl;

    // 4. new polymer -> PMMA(back)
    R = pow((n_polymer - n_PMMA) / (n_polymer + n_PMMA), 2);
    T_interface = 1 - R;
    T_abs = exp(-alpha_PMMA * t_PMMA_back);
    I = I * T_interface * T_abs;

    cout << "After new polymer -> PMMA(back): " << I << " W/m^2" << endl;

    // 5. PMMA(back) -> air
    R = pow((n_PMMA - n_air) / (n_PMMA + n_air), 2);
    T_interface = 1 - R;
    I = I * T_interface;

    cout << "Final transmitted intensity = " << I << " W/m^2" << endl;

    // Percent transmitted
    double percentT = (I / I0) * 100.0;
    cout << "Percent transmitted = " << percentT << " %" << endl;

    return 0;
}