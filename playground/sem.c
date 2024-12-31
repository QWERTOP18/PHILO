#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int cnt = 0;
sem_t sem;  // セマフォの宣言

void *routine(void *p)
{
    for (int i = 0; i < 10000; i++)
    {
        sem_wait(&sem);  // セマフォでロック（値が0であれば待機）
        cnt++;
        sem_post(&sem);  // セマフォを解除（ロックを解放）
    }
    return NULL;
}

int main(void)
{
    pthread_t p1, p2;

    // セマフォの初期化（初期値は1）
    sem_init(&sem, 0, 1);

    // 2つのスレッドで並列処理する
    pthread_create(&p1, NULL, &routine, NULL);
    pthread_create(&p2, NULL, &routine, NULL);

    // 終了するまで待つ
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    // セマフォの破棄
    sem_destroy(&sem);

    printf("cnt -> %d\n", cnt);
    return 0;
}
