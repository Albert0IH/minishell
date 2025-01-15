#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *expand_variable(char *str) {
    char *expanded_str = malloc(strlen(str) + 1);  // Aloca espaço para a string expandida
    char *var_start = NULL;
    char *var_end = NULL;
    int i = 0, j = 0;

    while (str[i]) {
        if (str[i] == '$') { // Detecta a variável
            var_start = &str[i + 1];  // Início da variável
            var_end = var_start;

            // Encontra o fim da variável (caractere não alfanumérico ou fim da string)
            while (*var_end && ((*var_end >= 'a' && *var_end <= 'z') || (*var_end >= 'A' && *var_end <= 'Z') || (*var_end >= '0' && *var_end <= '9') || *var_end == '_')) {
                var_end++;
            }

            // Cria uma string com o nome da variável
            int var_len = var_end - var_start;
            char *var_name = malloc(var_len + 1);
            strncpy(var_name, var_start, var_len);
            var_name[var_len] = '\0';

            // Obtém o valor da variável de ambiente
            char *var_value = getenv(var_name);
            if (var_value) {
                // Se a variável de ambiente existir, copia o valor para a string expandida
                for (int k = 0; var_value[k]; k++, j++) {
                    expanded_str[j] = var_value[k];
                }
            } else {
                // Se a variável não existir, copia o nome da variável
                for (int k = 0; var_name[k]; k++, j++) {
                    expanded_str[j] = var_name[k];
                }
            }

            j--; // Decrementa para compensar o incremento no final do loop
            free(var_name); // Libera a memória da variável
            i = var_end - str; // Pula para a posição após a variável
        } else {
            expanded_str[j++] = str[i++]; // Copia o caractere para a string expandida
        }
    }

    expanded_str[j] = '\0'; // Finaliza a string expandida
    return expanded_str;
}

int main() {
    char *input = "$PATH.";
    printf("Original: %s\n", input);

    char *expanded_input = expand_variable(input);
    printf("Expanded: %s\n", expanded_input);

    free(expanded_input); // Libera a memória alocada
    return 0;
}
