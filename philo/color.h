#ifndef COLOR_H
#define COLOR_H

// フォアグラウンド色
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

// 背景色
#define BG_RED     "\033[41m"
#define BG_GREEN   "\033[42m"
#define BG_YELLOW  "\033[43m"
#define BG_BLUE    "\033[44m"
#define BG_MAGENTA "\033[45m"
#define BG_CYAN    "\033[46m"
#define BG_WHITE   "\033[47m"

// テキストスタイル
#define BOLD       "\033[1m"  // 太字
#define UNDERLINE  "\033[4m"  // 下線
#define BLINK      "\033[5m"  // 点滅
#define REVERSED   "\033[7m"  // 反転
#define HIDDEN     "\033[8m"  // 隠し文字

#endif
