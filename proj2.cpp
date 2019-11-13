#include <iostream>
#include <cstdio>
#include <cstring>

#include <vector>

using std::vector;

template <class it>
void printi(it cont, int siz);
void selection(int& current, int& cnt, vector<char*>& pwords, fpos_t start, FILE* f, int mem);
void mysort(vector <char*>& strings, int len);

int main()
{
	char test[12];
	vector <char*> best;
	printf("Give me a password:\n");
	scanf("%11s", test);
	printf("You provided a password of %s\n", test);
	printf("The most similar passwords to %s are:\n", test);

	int count = (int)strlen(test);
	const int tsize = count;

	FILE* pfile = fopen("common_passwords.txt", "r");
	if (!pfile) { printf("Error"); exit(1); }

	int matches = 0;
	int loc = 0;
	fpos_t strt;
	int chr;
	fgetpos(pfile, &strt);
	while ((chr = fgetc(pfile)) != EOF)
	{
		if (chr == 10)
		{

			int cur = (loc > tsize ? loc : tsize) - matches;
			if (cur <= count)
			{
				selection(cur, count, best, strt, pfile, loc);
				if (!(count)) { break; }
			}
			loc = 0;
			matches = 0;
			fgetpos(pfile, &strt);
		}
		else
		{
			if ((loc < tsize) && (test[loc] == chr)) { matches = matches + 1; }
			loc = loc + 1;
		}

	}

	fclose(pfile);
	int vsize = static_cast<int>(best.size());
	mysort(best, vsize);
	printi(best, vsize);
	printf("\nAll of which are %d character(s) different.\n", count);

	return 0;
}

void mysort(vector <char*>& strings, int len)
{
	char* temp;
	int change = 0;
	for (int i = 0; i < len - 1; i++)
	{
		if (strncmp(strings[i], strings[i + 1], 4) > 0)
		{
			temp = (char*)malloc(12);
			strcpy(temp, strings[i]);
			strcpy(strings[i], strings[i + 1]);
			strcpy(strings[i + 1], temp);
			free(temp);
			change = change + 1;
		}

	}
	if (change) mysort(strings, len);
}

void selection(int& current, int& cnt, vector<char*>& pwords, fpos_t start, FILE* f, int mem)
{
	if (current < cnt)
	{
		pwords = {};
		cnt = current;
	}
	fsetpos(f, &start);
	char* word;
	word = (char*)malloc(mem + 1);
	fread(word, 1, mem + 1, f);
	word[mem] = 0;

	char* cp;
	cp = (char*)malloc(12);
	pwords.push_back(strcpy(cp, word));
}

template <class it>
void printi(it cont, int siz)
{
	for (int i = 0; i < siz; i++)
	{
		std::cout << cont[i] << ", ";
	}
}
