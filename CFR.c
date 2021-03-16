#include <stdio.h>

int eValid(int x, int a, int b)
{
	return x >= a && x <= b;
}

void initializareTren(char spatii[50][8])
{
	int i, j;
	for (i = 0; i <= 49; i++)
		for (j = 0; j < 8; j++)
			spatii[i][j] = 0;
}

void initializareVagoane(int vagon[5])
{
	int i;
	for (i = 0; i < 5; i++)
		vagon[i] = 0;
}

void calcPasagVagon(char statii[50][8], int vagon[5])
{
	int i, j, k;
	for (k = 0; k < 5; k++)
		for (i = 0; i < 10; i++)
			for (j = 0; j < 8; j++)
				if (statii[10 * k + i][j] != 0)
					vagon[k]++;

}

int nrCalatCompart(char statii[50][8], int k, int l) // l = indice de compartiment
{
	int nr = 0, i;
	for (i = 0; i < 8; i++)
		if (statii[10 * k + l][i] != 0)
			nr++;
	return nr;
}

int CompartMaxLocuriLibere(char statii[50][8], int k)
{
	int N, i, max = 0, p;
	for (i = 0; i < 10; i++)
	{
		N = 8 - nrCalatCompart(statii, k, i);
		if (max < N)
		{
			max = N;
			p = 10 * k + i;
		}
	}
	return p;
}

int minVag(int vagon[5])
{
	int min = vagon[0], i, j = 0;
	for (i = 0; i < 5; i++)
		if (vagon[i] < min)
		{
			min = vagon[i];
			j = i;
		}

	return j;
}

void afisare(char statii[50][8])
{
	int i, j;
	for (i = 0; i < 50; i++)
	{
		for (j = 0; j < 8; j++)
			printf("%d ", statii[i][j]);
		printf("\n");
	}
}

void initalizareGrup(int grup[2][60])
{
	int i, j;
	for (i = 0; i < 2; i++)
		for (j = 0; j < 60; j++)
			grup[i][j] = 0;
}

int main()
{
	char statii[50][8];
	int vagon[5], i, j, k, m, t, l, p;
	int grup[2][60], aux[2];

	initializareTren(statii);
	initializareVagoane(vagon);
	initalizareGrup(grup);

	for (m = 0; m < 6; m++) // indexarea statiilor
	{
		int count = 0;
		initalizareGrup(grup);
		while (scanf("%d %d", &grup[0][count], &grup[1][count]) == 2) // citire
		{
			if (!eValid(grup[0][count], 1, 5) || !eValid(grup[1][count], 1, 6))
			{
				printf("Mai inceara!\n");
				continue;
			}

			count++;
		}

		// sortarea dupa numarul de persoane din grupuri
		for (i = 0; i < count - 1; i++)
			for (j = 0; j < count; j++)
				if (grup[0][i] < grup[0][j])
				{
					aux[0] = grup[0][i]; aux[1] = grup[1][i];
					grup[0][i] = grup[0][j]; grup[1][i] = grup[1][j];
					grup[0][j] = aux[0]; grup[1][j] = aux[1];
				}

		for (i = 0; i < count; i++) // parcurge lista de grupuri
		{

			calcPasagVagon(statii, vagon);
			l = minVag(vagon); // l = indicele vagonului cu cele mai putine locuri ocupate
			for (k = 0; k < 5; k++)
			{
				if (k == l) // daca s-a gasit vagonul minim
					p = CompartMaxLocuriLibere(statii, l); // p = indicele compartimentului cu cele mai putine locuri ocupate
			}

			int count2 = 0; // cate locuri ocupate din grupul i
			for (j = 0; j < 8 && count2 < grup[0][i]; j++)
			{
				if (statii[p][j] == 0) // daca locurile din compart p sunt libere
				{
					statii[p][j] = grup[1][i]; // se ocupa locuri
					vagon[k] -= grup[0][i]; // se scad locuri din vagoane
					count2++;
				}
			}
		}

		afisare(statii); // afiseaza situatia
		// Trecerea la urmatoarea statie
		for (i = 0; i < 50; i++)
			for (j = 0; j < 8; j++)
				if (statii[i][j] >= 1)
					statii[i][j]--; // oamenii se apropie de destinatie

		printf("\n\n############################################################################\n\n");
	}

	afisare(statii);
	printf("Trenul a ajuns la Bucuresti!! VA MULTUMIM PENTRU CA ATI ALES SA CALATORITI CU CFR CALATORI!\n");
	return 0;
}