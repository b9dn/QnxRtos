#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double funkcja1(double x) {
    return 2 * x;
}

double funkcja2(double x) {
    return sin(x);
}

double funkcja3(double x) {
    return cos(x);
}

double funkcja4(double x) {
    return exp(x);
}

double funkcja5(double x) {
    return 1 / (1 + exp(-x));
}

double funkcja6(double x) {
    return pow(x, 3) + pow(x, 2) + x + 1;
}

double metoda_trapezow(double (*funkcja)(double), double a, double b, int n) {
    double h = (b - a) / n;
    double wynik = 0.0;
    int i;
    double x1, x2;

    for(i = 0; i < n; i++) {
        x1 = a + i * h;
        x2 = a + (i + 1) * h;
        wynik += funkcja(x1) + funkcja(x2);
    }
    wynik *= 0.5 * h;

    return wynik;
}

double metoda_prostokatow(double (*funkcja)(double), double a, double b, int n) {
    double h = (b - a) / n;
    double wynik = 0.0;
    int i;
    double x;

    for(i = 0; i < n; i++) {
        x = a + i * h;
        wynik += funkcja(x + 0.5 * h);
    }
    wynik *= h;

    return wynik;
}

double metoda_simpsona(double (*funkcja)(double), double a, double b, int n) {
    double h = (b - a) / n;
    double wynik = funkcja(a) + funkcja(b);
    int i;
    double x;

    for(i = 1; i < n; i++) {
        x = a + i * h;
        if (i % 2 == 0)
            wynik += 2 * funkcja(x);
        else
            wynik += 4 * funkcja(x);
    }
    wynik *= h / 3;

    return wynik;
}

int main(int argc, char *argv[]) {
    double a, b;
    int n, numer_funkcji, numer_metody;
    double (*funkcja)(double);
    double wynik;

    if(argc != 6) {
        printf("Sposob uzycia: %s <poczatek> <koniec> <liczba_przedzialow> <numer_funkcji> <numer_metody>\n", argv[0]);
        printf("Dostepne numery funkcji:\n");
        printf("1. 2x\n");
        printf("2. sin(x)\n");
        printf("3. cos(x)\n");
        printf("4. e^x\n");
        printf("5. 1 / (1 + e^(-x))\n");
        printf("6. x^3 + x^2 + x + 1\n");
        printf("Dostepne numery metod:\n");
        printf("1. Metoda trapezow\n");
        printf("2. Metoda prostokatow\n");
        printf("3. Metoda Simpsona\n");
        return 1;
    }

    a = atof(argv[1]);
    b = atof(argv[2]);
    n = atoi(argv[3]);
    numer_funkcji = atoi(argv[4]);
    numer_metody = atoi(argv[5]);

    if(a >= b) {
        printf("Bledne przedzialy calkowania\n");
        return 1;
    }
    if(n < 1) {
        printf("Liczba przedzialow nie moze byc mniejsza od 1");
        return 1;
    }

    switch (numer_funkcji) {
        case 1:
            funkcja = funkcja1;
            break;
        case 2:
            funkcja = funkcja2;
            break;
        case 3:
            funkcja = funkcja3;
            break;
        case 4:
            funkcja = funkcja4;
            break;
        case 5:
            funkcja = funkcja5;
            break;
        case 6:
            funkcja = funkcja6;
            break;
        default:
            printf("Nieznany numer funkcji.\n");
            return 1;
    }

    switch (numer_metody) {
        case 1:
            wynik = metoda_trapezow(funkcja, a, b, n);
            break;
        case 2:
            wynik = metoda_prostokatow(funkcja, a, b, n);
            break;
        case 3:
            if(n % 2 != 0) {
                printf("Dla metody Simpsona liczba przedzialow musi byc parzysta.\n");
                return 1;
            }
            wynik = metoda_simpsona(funkcja, a, b, n);
            break;
        default:
            printf("Nieznany numer metody.\n");
            return 1;
    }

    printf("Wynik calkowania: %lf\n", wynik);
    
    return 0;
}

