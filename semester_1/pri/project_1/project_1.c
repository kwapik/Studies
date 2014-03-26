/* PRI - Podstawy Programowania
 * Zadanie 1.6
 *
 * @author Krzysztof Kwapisiewicz <krzysztof.kwapisiewicz@gmail.com>
 */

#include <math.h>
#include <stdio.h>

void printProgramInfo();
int getPrecision();
double getX();
double calculateArctgWithTaylor(double x, int precision);
double calculateAbsoluteError(double arctgTaylor, double arctgCLibrary);
void printResults(double arctgTaylor, double arctgCLibrary, double absoluteError);

int main() {
	printProgramInfo();
	int precision = getPrecision();
	double x = getX();
	double arctgTaylor = calculateArctgWithTaylor(x, precision);
	double arctgCLibrary = atan(x);
	double absoluteError = calculateAbsoluteError(arctgTaylor, arctgCLibrary);
	printResults(arctgTaylor, arctgCLibrary, absoluteError);
	return 0;
}

void printProgramInfo() {
	printf("PRI - Podstawy Programowania\n");
	printf("Zadanie 1.6\n\n");
	printf("Program oblicza wartosc funkcji arctg(x) dla zadanej wartosci x przy pomocy dwóch metod:\n");
	printf("  - szeregu Taylora, dla n pierwszych wyrazow\n");
	printf("  - funkcji bibliotecznej jezyka C - atan\n");
	printf("Wynikiem programu jest obliczenie bledu bezwzglednego pierwszej z metod.\n\n");
}

int getPrecision() {
	printf("Podaj dokladnosc n (ilosc wyrazow szeregu Taylora: ");
	int precision;
	scanf("%d", &precision);
	return precision;
}

double getX() {
	printf("Podaj wartosc argumentu x: ");
	double x;
	scanf("%lf", &x);
	return x;
}

double calculateArctgWithTaylor(double x, int precision) {
	double arctgTaylor = 0;
	int i;
	for (i = 0; i < precision; ++i) {
		arctgTaylor += pow(-1, i) * pow(x, 2 * i + 1) / (2 * i + 1);
	}
	return arctgTaylor;
}

double calculateAbsoluteError(double arctgTaylor, double arctgCLibrary) {
	return (arctgTaylor - arctgCLibrary) * 100 / arctgCLibrary;
}

void printResults(double arctgTaylor, double arctgCLibrary, double absoluteError) {
	printf("\nObliczone wartości:\n");
	printf("  - przy pomocy szeregu Taylora: %le\n", arctgTaylor);
	printf("  - przy pomocy funkcji bibliotecznej: %le\n", arctgCLibrary);
	printf("  - blad bezwzgledny [%%]: %le\n", absoluteError);
}
