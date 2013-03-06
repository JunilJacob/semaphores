#include<semaphore.h>
#include<pthread.h>
#include<stdio.h>
sem_t count_mutex,thread_barrier,loop;
int count=0,n=6;
pthread_t t[7];
void* test(void* s){
	while(1){
	sem_wait(&count_mutex);
	count=count+1;
	if(count == n){
		sem_wait(&loop);	
		sem_post(&thread_barrier);
	}
	printf("%d barrier reached\n",(int)s );
	sem_post(&count_mutex);
	sem_wait(&thread_barrier);//barrier
	sem_post(&thread_barrier);
	printf("%d completed\n",(int )s);
	sem_wait(&count_mutex);
	count=count-1;
	if(count == 0){
		sem_post(&loop);	
		sem_wait(&thread_barrier);
	}
	sem_post(&count_mutex);
	sem_wait(&loop);
	printf("######################################\n");
	sem_post(&loop);
	}
}
main(){
	int i;
	sem_init(&loop,0,1);	
	sem_init(&count_mutex,0,1);
	sem_init(&thread_barrier,0,0);
	for(i=0;i<6;i++)
		pthread_create(&t[i],0,test,(void *)i);
	for(i=0;i<6;i++)
		pthread_join(t[i],0);

}
