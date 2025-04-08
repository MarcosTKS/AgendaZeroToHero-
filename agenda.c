#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTATOS 50

struct Contato{
    char nome[128];
    char telefone[15];
};

void listarContatos(struct Contato agenda[], int numContatos) {
    printf("Lista de Contatos:\n");
    if (numContatos == 0) {
        printf("Agenda vazia!\n");
        return;
    }
    for (int i = 0; i < numContatos; i++) {
        printf("Contato %d: Nome: %s, Telefone: %s\n", i + 1, agenda[i].nome, agenda[i].telefone);
    }
}

void Adicionarcontato(struct Contato agenda[], int *numContatos, int *alteracoesNaoSalvas){
    if (*numContatos >= MAX_CONTATOS) {
        printf("Agenda cheia! Não é possível adicionar mais contatos.\n");
        return;
    }
    getchar();

    printf("Digite o nome do contato: ");
    fgets(agenda[*numContatos].nome, 128, stdin);
    agenda[*numContatos].nome[strcspn(agenda[*numContatos].nome, "\n")] = '\0'; 

    printf("Digite o telefone do contato (formato: 63 99999-9999): ");
    fgets(agenda[*numContatos].telefone, 15, stdin);
    agenda[*numContatos].telefone[strcspn(agenda[*numContatos].telefone, "\n")] = '\0';

    (*numContatos)++;
    (*alteracoesNaoSalvas) = 1;
    printf("Contato adicionado com sucesso!!!\n");


}

void Deletarcontato(struct Contato agenda[], int *numContatos, int *alteracoesNaoSalvas){
    char desejo;
    
    if(*numContatos == 0){
        printf("Não existe nenhum contato, favor criar contatos!!!");
        printf("Deseja criar um contato novo: S/N.");
        scanf(" %c", &desejo);
        if(desejo == 'S' || desejo == 's'){
            Adicionarcontato(agenda, numContatos, alteracoesNaoSalvas);
        }
        
        return;
    }

    char buscar_nome[128];

    printf("Digite o nome do contato a ser deletado: ");
    fgets(buscar_nome, 128, stdin);
    buscar_nome[strcspn(buscar_nome, "\n")] = '\0';

    int encontrado = -1;

    for (int i = 0; i < *numContatos; i++) {
        if (strcmp(agenda[i].nome,buscar_nome) == 0) {
            encontrado = i;
            break;
        }
    }
    if (encontrado == -1) {
        printf("Contato não encontrado.\n");
        return;
    }
    
    for (int i = encontrado; i < *numContatos - 1; i++) {
        agenda[i] = agenda[i + 1];
    }

    (*numContatos)--; 
    (*alteracoesNaoSalvas) = 1;
    printf("O contato '%s' deletado com sucesso!\n",buscar_nome);

}

void Salvar_contatosCSV( struct Contato agenda[], int numContatos){
    FILE *arquivo = fopen("agenda.csv", "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar!\n");
        return;
    }

    fprintf(arquivo, "Agenda com o Nome e telefone:\n");

    for (int i = 0; i < numContatos; i++) {
        fprintf(arquivo, "contato: %d", i);
        fprintf(arquivo, "\n%s,%s\n", agenda[i].nome, agenda[i].telefone);
    }

    fclose(arquivo);  
    printf("Agenda salva com sucesso no arquivo agenda.csv!\n");

}

int main(){
    struct Contato agenda[MAX_CONTATOS];
    int numContatos = 0;  
    int alteracoesNaoSalvas = 0;
    int opcao;

    do {
        printf("\n--------------------------------------------\n\t\tMenu de Operacoes\t\t\n--------------------------------------------\n");
        printf("1. Cadastro de novo contato\n");
        printf("2. Deletar contato\n");
        printf("3. Salvar agenda no arquivo CSV\n");
        printf("4. Sair e salvar tudo.\n");
        printf("5. Listar contatos\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); 

        switch (opcao) {
            case 1:
            Adicionarcontato(agenda, &numContatos, &alteracoesNaoSalvas);
                break;
            
            case 2:
            Deletarcontato(agenda, &numContatos, &alteracoesNaoSalvas);
            break;

            case 3:
            Salvar_contatosCSV(agenda, numContatos);
            break;

            case 4:
            if (alteracoesNaoSalvas) {
                printf("Voce tem alteracoes nao salvas. Salvando a agenda antes de sair...\n");
                Salvar_contatosCSV(agenda, numContatos);
            }
            printf("Saindo...\n");
            break;

            case 5:
            listarContatos(agenda, numContatos);
            break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }

    } while (opcao != 4);

    return 0;

}