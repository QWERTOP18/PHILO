#include <stdio.h>
#include <pthread.h>

int cnt = 0;

void *routine(void *arg) {
    pthread_mutex_t *mutex = (pthread_mutex_t *)arg;  // 引数をミューテックスとしてキャスト
    for (int i = 0; i < 10000; i++) {
        pthread_mutex_lock(mutex);  // lockして同時アクセスを防ぐ
        cnt++;
        pthread_mutex_unlock(mutex);  // unlock
    }
    return NULL;
}

int main(void) {
    pthread_t p1, p2;
    pthread_mutex_t mutex;

    pthread_mutex_init(&mutex, NULL);  // ミューテックスの初期化

    // 2つのスレッドで並列処理する
    pthread_create(&p1, NULL, &routine, (void *)&mutex);  // ミューテックスのアドレスを渡す
    pthread_create(&p2, NULL, &routine, (void *)&mutex);  // ミューテックスのアドレスを渡す

    // 終了するまで待つ
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    pthread_mutex_destroy(&mutex);  // ミューテックスの破棄

    printf("cnt -> %d\n", cnt);  // 結果表示
    return 0;
}
