#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define TABLE_SIZE 10

struct Node {
    char key[100];
    struct Node* next;
};

struct HashTable {
    struct Node* head;
} ht[TABLE_SIZE];

// fungsi inisialisasi Hash Table
void initializationHT() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht[i].head = NULL;
    }
}

int stringtoInteger(char key[]) { // nama lain: StoI
    int sum = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        sum += key[i]; // pivot sum of ASCII values of character
    }
    return sum;
}

int DivHash(char key[]) {
    int intKey = stringtoInteger(key);
    return intKey % TABLE_SIZE;
}

int firstCharacterHash(char key[]) {
    if (key[0] == '\0') { // cek apakah ada data
        return -1;
    }
    char firstCharacter = key[0];
    if (!isalpha(firstCharacter)) { // cek apakah karakter pertama adalah huruf
        return -1;
    }
    return tolower(firstCharacter) - 'a';
}

int midSquareHash(char key[]) {
    int intKey = stringtoInteger(key);
    int square = intKey * intKey;
    int midDigits = (square / 10) % TABLE_SIZE; // rumus mengambil digit tengah
    return midDigits;
}

int foldingHash(char key[]){
	int sum = 0;
	for (int i = 0; key[i] != '\0'; i += 2){
		int part = 0;
		if (key[i] != '\0'){
			part = key[i] * 256;
		}
		if (key[i + 1] != '\0'){
			part += key[i + 1];
		}
		sum += part;
	}
	return sum % TABLE_SIZE;
}

int digitExtractionHash(char key[]) {
    int intKey = stringtoInteger(key);
    int extractedDigit = (intKey / 10) % TABLE_SIZE; // rumus sama seperti mid square
    return extractedDigit;
}

int rotatingHash(char key[]) {
    int intKey = stringtoInteger(key);
    int rotated = ((intKey << 4) | (intKey >> (sizeof(int) * 8 - 4))) & 0xFFFFFFFF; // untuk rotasi bit
    return rotated % TABLE_SIZE;
}

int linearProbing(int index) {
    return (index + 1) % TABLE_SIZE;
}

int rehash(int (*hashFunction)(char[]), char key[]) {
    return (hashFunction(key) + 1) % TABLE_SIZE;
}

// insert data ke hash table dengan linear probing
void insertWithLinearProbing(char key[], int (*hashFunction)(char[])) {
    int index = hashFunction(key);
    if (index == -1) {
        printf("Key %s tidak valid untuk hash function yang digunakan.\n", key);
        return;
    }

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->key, key);
    newNode->next = NULL;

    if (ht[index].head == NULL) {
        ht[index].head = newNode;
        printf("Key %s dimasukkan ke index %d.\n", key, index);
    } else {
        struct Node* current = ht[index].head;
        int originalIndex = index;
        while (current->next != NULL) {
            current = current->next;
        }
        // collision handling menggunakan linear probing
        while (ht[index].head != NULL) {
            index = linearProbing(index);
            if (index == originalIndex) { // jika table full
                printf("Hash table penuh, tidak dapat memasukkan key %s.\n", key);
                free(newNode);
                return;
            }
        }
        ht[index].head = newNode;
        printf("Key %s dimasukkan ke index %d dengan linear probing.\n", key, index);
    }
}

// insert data ke hash table dengan chaining
void insertWithChaining(char key[], int (*hashFunction)(char[])){
    int index = hashFunction(key);
    if (index == -1){
        printf("Key %s tidak valid untuk hash function yang digunakan.\n", key);
        return;
    }

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->key, key);
    newNode->next = NULL;

    if (ht[index].head == NULL){
        ht[index].head = newNode;
        printf("Key %s dimasukkan ke index %d.\n", key, index);
    } else {
        struct Node* current = ht[index].head;
        while (current->next != NULL){
            current = current->next;
        }
        current->next = newNode;
        printf("Key %s dimasukkan ke index %d dengan chaining.\n", key, index);
    }
}

// insert data ke hash table dengan rehashing
void insertWithRehashing(char key[], int (*hashFunction)(char[])) {
    int index = hashFunction(key);
    if (index == -1) return;

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->key, key);
    newNode->next = NULL;

    int attempt = 1;
    while (ht[index].head != NULL) {
        index = (hashFunction(key) + attempt) % TABLE_SIZE;
        attempt++;
    }
    ht[index].head = newNode;
    printf("Key %s dimasukkan ke index %d dengan rehashing.\n", key, index);
}

// fungsi untuk menampilkan hash table
void displayHT() {
    printf("\nHash Table\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Index %d: ", i);
        struct Node* current = ht[i].head;
        if (current == NULL) {
            printf("Kosong\n");
        } else {
            while (current != NULL) {
                printf("%s -> ", current->key);
                current = current->next;
            }
            printf("NULL\n");
        }
    }
}

int main() {
    initializationHT();
    char key[100];
    int choice;
    int collisionChoice;
    int (*hashFunction)(char[]) = NULL;

    // menu pilihan metode hashing
    while (1) {
        printf("\nPilih metode hashing:\n");
        printf("1. Division Hash\n");
        printf("2. First Character Hash\n");
        printf("3. Mid-Square Hash\n");
        printf("4. Folding\n");
        printf("5. Digit Extraction Hash\n");
        printf("6. Rotating Hash\n");
        printf("7. Exit\n");
        printf("Pilihan Anda: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                hashFunction = DivHash;
                break;
            case 2:
                hashFunction = firstCharacterHash;
                break;
            case 3:
                hashFunction = midSquareHash;
                break;
            case 4:
            	hashFunction = foldingHash;
            	break;
            case 5:
                hashFunction = digitExtractionHash;
                break;
            case 6:
                hashFunction = rotatingHash;
                break;
            case 7:
                return 0;
            default:
                printf("Pilihan tidak valid. Silakan pilih kembali.\n");
                continue;
        }
        
        // menu pilihan metode penanganan kolisi
        printf("\nPilih metode penanganan kolisi:\n");
        printf("1. Linear Probing\n");
        printf("2. Chaining\n");
        printf("3. Rehashing\n");
        printf("Pilihan anda: ");
        scanf("%d", &collisionChoice);
        
        void (*insertFunction)(char[], int (*)(char[])) = NULL;
        
        switch (collisionChoice){
        	case 1:
        		insertFunction = insertWithLinearProbing;
        		break;
        	case 2:
        		insertFunction = insertWithChaining;
        		break;
        	case 3:
        		insertFunction = insertWithRehashing;
        		break;
        	default:
        		printf("Pilihan tidak valid. Silahkan pilih kembali.\n");
        		continue;
		}

        // input key
        while (1) {
            printf("Masukkan key yang berupa (string) atau exit untuk kembali ke menu: ");
            scanf("%s", key);
            if (strcmp(key, "exit") == 0) break;
            insertFunction(key, hashFunction);
        }
    }

    // tampilkan hash table
    displayHT();

    return 0;
}