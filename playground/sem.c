#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int cnt = 0;  // カウンタ
sem_t sem;     // セマフォ

void* routine(void *p) {
    for (int i = 0; i < 1000; i++) {
        sem_wait(&sem);  // セマフォでロック（値が0なら待機）
        cnt++;           // カウンタのインクリメント
        sem_post(&sem);  // セマフォを解除（ロックを解放）
    }
    printf("%d\n", cnt);
    return NULL;
}

int main() {
    pid_t pid1, pid2;

    // セマフォの初期化（初期値は1）
    sem_init(&sem, 0, 1);

    // プロセス1の作成
    pid1 = fork();
    if (pid1 == 0) {
        // 子プロセス1の処理
        routine(NULL);
        exit(0);  // 子プロセス終了
    }

    // プロセス2の作成
    pid2 = fork();
    if (pid2 == 0) {
        // 子プロセス2の処理
        routine(NULL);
        exit(0);  // 子プロセス終了
    }

    // 親プロセスで子プロセスの終了を待機
    wait(NULL);
    wait(NULL);

    // 結果を表示
    printf("cnt -> %d\n", cnt);

    // セマフォの破棄
    sem_destroy(&sem);

    return 0;
}
