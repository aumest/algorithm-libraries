#ifndef __FFT_H__
#define __FFT_H__
#include <cmath>
#include <complex>
#include <vector>
namespace exalg {
	const double PI = std::acos(-1);	
	static void FastFourierTransform(std::vector<std::complex<double>> &v) {
        int n = (int)v.size();
        for (int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1;
            while (!((j ^= bit) & bit)) bit >>= 1;
            if (i < j) swap(v[i], v[j]);
        }
        for (int i = 1; i < n; i <<= 1) {
            double x = -PI / i;
            std::complex<double> w = { cos(x), sin(x) };
            for (int j = 0; j < n; j += i << 1) {
                std::complex<double> th(1);
                for (int k = 0; k < i; k++) {
                    std::complex<double> tmp = v[i + j + k] * th;
                    v[i + j + k] = v[j + k] - tmp;
                    v[j + k] += tmp;
                    th *= w;
                }
            }
        }
	}
    static void InverseFastFourierTransform(std::vector<std::complex<double>>& v) {
        int n = (int)v.size();
        for (int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1;
            while (!((j ^= bit) & bit)) bit >>= 1;
            if (i < j) swap(v[i], v[j]);
        }
        for (int i = 1; i < n; i <<= 1) {
            double x = PI / i;
            std::complex<double> w = { cos(x), sin(x) };
            for (int j = 0; j < n; j += i << 1) {
                std::complex<double> th(1);
                for (int k = 0; k < i; k++) {
                    std::complex<double> tmp = v[i + j + k] * th;
                    v[i + j + k] = v[j + k] - tmp;
                    v[j + k] += tmp;
                    th *= w;
                }
            }
        }
        for (int i = 0; i < n; i++)
            v[i] /= n;
    }
}
#endif
