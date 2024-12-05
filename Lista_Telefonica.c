#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

typedef struct Contact {
    char name[50];
    char phone[20];
    struct Contact* next;
} Contact;

Contact* hashTable[TABLE_SIZE];

// Função de hash simples
unsigned int hashFunction(char* str) {
    unsigned int hash = 0;
    while (*str) {
        hash = (hash << 5) + *str++;
    }
    return hash % TABLE_SIZE;
}

// Verificar se o contato já existe
int existeContato(char* name) {
    unsigned int index = hashFunction(name);
    Contact* current = hashTable[index];
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return 1; // Contato já existe
        }
        current = current->next;
    }
    return 0; // Contato não encontrado
}

// Adicionar contato
void adicionarContato() {
    char name[50], phone[20];
    printf("Nome: ");
    scanf(" %[^\n]", name); // Lê a string com espaços

    if (existeContato(name)) {
        printf("Erro: Contato com este nome já existe!\n");
        return;
    }

    printf("Telefone: ");
    scanf(" %[^\n]", phone);

    unsigned int index = hashFunction(name);
    Contact* newContact = (Contact*)malloc(sizeof(Contact));
    strcpy(newContact->name, name);
    strcpy(newContact->phone, phone);
    newContact->next = hashTable[index]; // Encadeamento
    hashTable[index] = newContact;

    printf("Contato adicionado com sucesso!\n");
}

// Buscar contato
void buscarContato() {
    char name[50];
    printf("Nome: ");
    scanf(" %[^\n]", name);

    unsigned int index = hashFunction(name);
    Contact* current = hashTable[index];
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            printf("Contato encontrado: %s, Telefone: %s\n", current->name, current->phone);
            return;
        }
        current = current->next;
    }
    printf("Contato não encontrado.\n");
}

// Remover contato
void removerContato() {
    char name[50];
    printf("Nome: ");
    scanf(" %[^\n]", name);

    unsigned int index = hashFunction(name);
    Contact* current = hashTable[index];
    Contact* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            if (prev == NULL) {
                hashTable[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Contato removido com sucesso!\n");
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Contato não encontrado.\n");
}

// Exibir todos os contatos
void exibirContatos() {
    int found = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        Contact* current = hashTable[i];
        while (current != NULL) {
            printf("Nome: %s, Telefone: %s\n", current->name, current->phone);
            current = current->next;
            found = 1;
        }
    }
    if (!found) {
        printf("Nenhum contato encontrado.\n");
    }
}

int main() {
    int opcao;

    do {
        printf("\nEscolha uma opcao:\n");
        printf("1 - Adicionar contato\n");
        printf("2 - Buscar contato por nome\n");
        printf("3 - Remover contato\n");
        printf("4 - Exibir todos os contatos\n");
        printf("0 - Sair\n");
        printf("Digite uma opcao: ");

        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarContato();
                break;
            case 2:
                buscarContato();
                break;
            case 3:
                removerContato();
                break;
            case 4:
                exibirContatos();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
