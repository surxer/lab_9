#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

// Fill out this structure
struct HashType
{

struct RecordType record;
struct HashType* next;

};

// Compute the hash function
int hash(int x)
{

int hashSz = 10; 
return x % hashSz;

}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;

	for (i=0;i<hashSz;++i)
	{
	   struct HashType *currentNode = pHashArray[i].next;
        if (currentNode)
        {
            printf("Index %d -> ", i);
            while (currentNode)
            {
                printf("%d %c %d -> ", currentNode->record.id, currentNode->record.name, currentNode->record.order);
                currentNode = currentNode->next;
            }
            printf("\n");
        }
        else
        {
            printf("Index %d -> Empty\n", i);
        }
		 printf("\n");
    }
    }


int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// Your hash implementation


int hashSz = 10; 

struct HashType hashTable[hashSz];

for (int i = 0; i < hashSz; ++i)
{
	hashTable[i].next = NULL;
}


for (int i = 0; i < recordSz; ++i)
{
        int index = hash(pRecords[i].id);
        struct HashType* newNode = (struct HashType*)malloc(sizeof(struct HashType));
        if (!newNode)
        {
            printf("Memory allocation failed for a new node.\n");
            exit(-1);
        }
        newNode->record = pRecords[i];
        newNode->next = hashTable[index].next;
        hashTable[index].next = newNode;
}

    
    displayRecordsInHash(hashTable, hashSz);

   
free(pRecords);

for (int i = 0; i < hashSz; ++i)
{
        struct HashType* currentNode = hashTable[i].next;
        while (currentNode)
        {
            struct HashType* temp = currentNode;
            currentNode = currentNode->next;
            free(temp);
        }
}

    return 0;

}
