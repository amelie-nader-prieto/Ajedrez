#include "GLTablero.h"

void GLTablero::dibuja() {
	int sum = 0;
	for (int i = 0; i < Columnas; i++) {
		for (int j = 0; j < Filas; j++) {
			sum = i + j;
			switch (j)
			{
			case 0: if (sum > 3 && sum < 7) cas.dibuja(i, j); break;
			case 1: if (sum > 3 && sum < 9) cas.dibuja(i, j); break;
			case 2: if (sum > 3 && sum < 11) cas.dibuja(i, j); break;
			case 3: if (sum > 3 && sum < 13) cas.dibuja(i, j); break;
			case 4: if (sum > 3 && sum <= 14) cas.dibuja(i, j); break;
			case 5: if (sum > 4 && sum <= 15) cas.dibuja(i, j); break;
			case 6: if (sum > 6 && sum < 16) cas.dibuja(i, j); break;
			case 7: if (sum > 8 && sum < 16) cas.dibuja(i, j); break;
			case 8: if (sum > 10 && sum < 16) cas.dibuja(i, j); break;
			case 9: if (sum > 12 && sum < 16) cas.dibuja(i, j); break;
			default:
				break;
			}
		}
	}
}