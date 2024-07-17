#include<stdio.h>
#include<stdlib.h>
#define MAX 10
int buffer[MAX];
int empty=MAX;
int full=0;
int mutex=1;
int x=0;
void wait(int *s)
{
    while(*s <= 0);
    --(*s);
}

void signal(int *s)
{
    ++(*s);
}
void producer()
{
    wait(&mutex);
    wait(&empty);
    signal(&full);
    signal(&mutex);
    x++;
    buffer[full-1]=x;
    printf("Producer produced %d.\n",x);
    printf("Empty = %d\n",empty);
    printf("Buffer:\n");
    for(int i=0;i<full;i++)
    {
        printf("%d\t",buffer[i]);
    }
    printf("\n");
}
void consumer()
{
    printf("Consumer consumed %d.\n",buffer[full-1]);
    wait(&full);
    wait(&mutex);
    signal(&mutex);
    signal(&empty);
    printf("Empty = %d\n",empty);
    printf("Buffer:\n");
    for(int i=0;i<full;i++)
    {
        printf("%d\t",buffer[i]);
    }
    printf("\n");
}

void main()
{
    int ch;

    while(1)
    {
        printf("1.Produce\t2.Consumer\t3.Exit\n");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1: if(mutex==1 && empty!=0)
                    {
                        producer();
                    }
                    else
                    {
                        printf("Buffer is full\n");
                    }
                    break;
            case 2: if(mutex==1 && full!=0)
                    {
                        consumer();
                    }
                    else
                    {
                        printf("Buffer is empty\n");
                    }
                    break;
            case 3: exit(0);
        }
    }

}
