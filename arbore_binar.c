#pragma warning(disable:4996)
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Farmacie
{
	char* denumire;
	short id;
	short personal;
};
typedef struct Farmacie Farmacie;

struct nodAB
{
	Farmacie info;
	struct nodAB *st, *dr;
};
typedef struct nodAB nodAB;

struct nodAB* inserare_arbBin(struct nodAB* rootAB, struct Farmacie k)
{
	if (rootAB)
	{
		if (k.id < rootAB->info.id)
			rootAB->st = inserare_arbBin(rootAB->st, k);
		else
			if (k.id > rootAB->info.id)
				rootAB->dr = inserare_arbBin(rootAB->dr, k);
			else
				printf("\nNodul %d deja exista", 666);
		return rootAB;
	}
	else
	{
		struct nodAB* nou = (struct nodAB*)malloc(sizeof(struct nodAB) * 1);
		nou->info = k;
		nou->st = NULL;
		nou->dr = NULL;
		return nou;
	}
}

void inpost_ordine(struct nodAB* root)
{
	if (root)
	{
		inpost_ordine(root->st);
		inpost_ordine(root->dr);
		printf("\n\t#ID%d %s cu %d angajati!", root->info.id, root->info.denumire, root->info.personal);
	}
}


void main()
{
	struct nodAB* root = NULL;

	const char* sep_list = ",\n";
	char* token; char fbuf[512];

	FILE* file = fopen("Date_Fisier_Text.txt", "r+");
	if (file)
	{
		struct Farmacie ff;
		while (fgets(fbuf, 512, file))
		{
			token = strtok(fbuf, sep_list);
			ff.denumire = (char*)malloc(sizeof(char) * strlen(token) + 1);
			strcpy_s(ff.denumire,(strlen(token) + 1) * sizeof(char), token);

			token = strtok(NULL, sep_list);
			ff.id = atoi(token);

			token = strtok(NULL, sep_list);
			ff.personal = atoi(token);

			root = inserare_arbBin(root, ff);
		}
		ff.denumire = NULL;
	}
	fclose(file);

	printf("\nArborele dupa creare:");
	inpost_ordine(root);
	printf("\n\n");
}
//
