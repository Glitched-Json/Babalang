#ifndef DICTIONARY_C
#define DICTIONARY_C

#define DICTIONARY_HASHSIZE 101
struct dictionaryList {
	struct dictionaryList* next;
	char* name;
	char* defn;
};
static struct dictionaryList *hashtab[DICTIONARY_HASHSIZE];
struct numberList {
	struct numberList* next;
	long int number;
	long int numberReplacement;
};
static struct numberList *numbertab[DICTIONARY_HASHSIZE];

unsigned dHash(char *s) {
	unsigned hashval;
	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % DICTIONARY_HASHSIZE;
}

unsigned nHash(long int n) {
	n = ((n>>16)^n)*0x45d9f3b;
	n = ((n>>16)^n)*0x45d9f3b;
	n = (n>>16)^n;
	return n;
}

struct dictionaryList *lookup(char *s) {
    struct dictionaryList *np;
    for (np = hashtab[dHash(s)]; np != NULL; np = np->next)
    	if (strcmp(s, np->name) == 0) return np;
    return NULL;
}

struct dictionaryList *install(char *name, char *defn) {
    struct dictionaryList *np;
    unsigned hashval;
    if ((np = lookup(name)) == NULL) {
        np = (struct dictionaryList *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL) return NULL;
        hashval = dHash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else free((void *) np->defn);
    if ((np->defn = strdup(defn)) == NULL) return NULL;
    return np;
}

void emptyDictionary() {
	struct dictionaryList *np, *temp;
	for (int i=0; i<DICTIONARY_HASHSIZE; i++) {
		for (np = hashtab[i]; np != NULL; np = temp) {
			temp = np->next;
			free(np);
			hashtab[i] = temp;
		}
	}
}

#endif
