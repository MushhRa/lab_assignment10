#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{
    int count; // To count the occurrences of a word
    struct Trie* children[26]; // Pointers to child nodes
};

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie* pNode = (struct Trie*)malloc(sizeof(struct Trie));
    pNode->count = 0;

    for (int i = 0; i < 26; i++)
        pNode->children[i] = NULL;

    return pNode;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    struct Trie* pCrawl = pTrie;

    for (int i = 0; i < strlen(word); i++)
    {
        int index = word[i] - 'a';
        if (!pCrawl->children[index])
            pCrawl->children[index] = createTrie();

        pCrawl = pCrawl->children[index];
    }
    pCrawl->count++;
}

// Computes the number of occurrences of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    struct Trie* pCrawl = pTrie;

    for (int i = 0; i < strlen(word); i++)
    {
        int index = word[i] - 'a';
        if (!pCrawl->children[index])
            return 0;

        pCrawl = pCrawl->children[index];
    }
    return pCrawl->count;
}

// Deallocate the trie structure
void deallocateHelper(struct Trie* pTrie)
{
    for (int i = 0; i < 26; i++)
    {
        if (pTrie->children[i])
            deallocateHelper(pTrie->children[i]);
    }
    free(pTrie);
}

struct Trie *deallocateTrie(struct Trie *pTrie)
{
    deallocateHelper(pTrie);
    return NULL;
}

// This function will return the number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE* file = fopen(filename, "r");
    if (!file)
        return 0; 

    int numWords;
    fscanf(file, "%d", &numWords); 

    for (int i = 0; i < numWords; i++)
    {
        pInWords[i] = (char*)malloc(256 * sizeof(char)); 
        fscanf(file, "%s", pInWords[i]);
    }

    fclose(file);
    return numWords;
}


int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}