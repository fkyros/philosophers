#include <pthread.h>
#include <stdio.h>

void *semen()
{
	int	a = 0;

	if (!a)
		printf("no hay semen!!!\n");
	a++;
	printf("semen = %d\n", a);
	return (NULL);
}

int main(void)
{
	pthread_mutex_t	ex;
	pthread_t		t1;
	pthread_t		t2;

	pthread_mutex_init(&ex, NULL);
	if (pthread_create(&t1, NULL, &semen, NULL))
		return (1);
	if (pthread_create(&t2, NULL, &semen, NULL))
		return (1);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_mutex_destroy(&ex);
	return (0);
}
