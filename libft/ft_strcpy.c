#include <stddef.h> // Para NULL

char	*ft_strcpy(char *dest, const char *src)
{
	int i;

	if (!dest || !src) // Verifica se os ponteiros não são nulos
		return (NULL);
	i = 0;
	while (src[i] != '\0') // Copia cada caractere da origem para o destino
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0'; // Adiciona o terminador nulo no final
	return (dest);
}
