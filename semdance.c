#include<semaphore.h>
#include<pthread.h>
#include<stdio.h>
sem_t leader_available,follower_available,mutex,rendezvous;
int leaders=0,followers=0;
pthread_t t[8];
void* leader(void* s){
	sem_wait(&mutex);
	if(followers>0){
		followers--;
		sem_post(&leader_available);
	}
	else{
		leaders++;
		sem_post(&mutex);		
		sem_wait(&follower_available);
	}
	printf("leader dancing\n");
	sem_post(&rendezvous);
	sem_post(&mutex);		
	
}
void* follower(void* s){
	sem_wait(&mutex);
	if(leaders>0){
		leaders--;
		sem_post(&follower_available);
	}
	else{
		followers++;
		sem_post(&mutex);		
		sem_wait(&leader_available);
	}
	printf("follower dancing\n");
	sem_post(&rendezvous);
}
main(){
	int i;
	sem_init(&rendezvous,0,0);	
	sem_init(&mutex,0,1);
	sem_init(&leader_available,0,0);
	sem_init(&follower_available,0,0);
	for(i=0;i<3;i++)
		pthread_create(&t[i],0,leader,0);
	for(;i<6;i++)
		pthread_create(&t[i],0,follower,0);
	for(i=0;i<6;i++)
		pthread_join(t[i],0);

}
