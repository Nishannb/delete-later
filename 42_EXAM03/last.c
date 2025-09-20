#define _GNU_SOURCE
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// stderrに"Error: "へ続く形でエラーメッセージを出力する。
// システムコール系のmalloc, readが失敗したときは必ずエラーメッセージ出力するように明記あり。
int	put_err(const char *msg)
{
	fprintf(stderr, "Error: %s\n", msg);
	// エラーステータスを1にすることを忘れずに。
	return (1);
}

int	main(int ac, char **av)
{
	// 引数が1つ以外の場合はreturn 1
	if (ac < 2)
		return (1);
	size_t	buf_size = 4096;
	size_t	word_len = strlen(av[1]);
	// word_lenが0のときの例外処理は明記がなかった気がする。
	// よくわからないからとりあえずreturn 1
	if (word_len == 0)
		return (1);
	char	*asterisk = calloc(word_len + 1, sizeof(char));
	if (!asterisk)
		return (put_err("malloc failed"));
	for (size_t i = 0; i < word_len; i++)
		asterisk[i] = '*';
	// asteriskはコピー用に使う。
	// av[1] = "abc"のとき asterisk = "***"
	char	*buf = calloc(buf_size + 1, sizeof(char));
	// malloc errorハンドリング
	if (!buf)
		return (free(asterisk), put_err("malloc failed"));
	// メモリリークはおそらく見られてないはずだが、念の為free
	char	*str = calloc(1, sizeof(char));
	if (!str)
		return (free(asterisk), free(buf), put_err("malloc failed"));
	// 標準入力を開く。buffer_sizeは固定にした。
	ssize_t	rd;
	while ((rd = read(STDIN_FILENO, buf, buf_size)) > 0)
	{
		buf[rd] = 0;
		size_t	old_len = strlen(str);
		// reallocで動的に確保する長さを変更する。
		// strjoinみたいな感覚で使った。
		str = realloc(str, old_len + rd);
		if (!str)
			return (free(asterisk), free(buf), put_err("malloc failed"));
		// old_lenで記憶しておいた長さから先のstrでrdだけbufをコピーする。
		// memmoveは正直使っていい関数だったか覚えていない。
		memmove(str + old_len, buf, rd);
		char	*checker = str;
		// strの領域をwhileで走査
		// memmemで一致する領域を見つけたときだけ、asteriskをコピー
		while ((checker = memmem(checker, strlen(checker), av[1], word_len)) != NULL) {
			memmove(checker, asterisk, word_len);
			// checker += word_len をしないとav[1] = *aのとき str = "*aa"を操作したときに
			// 期待する結果は**aなのにcheckerが更新されていないせいで結果が***となる。
			checker += word_len;
		}
		// 一行ずつ処理するためにnext_lineに次の改行があるポインタを格納していく。
		char	*next_line;
		while ((next_line = (char *)memmem(str, strlen(str), "\n", 1)) != NULL) {
			write(STDOUT_FILENO, str, next_line - str + 1);
			// strをmemmoveで更新することで、すでに出力した行がもう一度出力することを防ぐ。
			memmove(str, next_line + 1, strlen(next_line) + 1);
		}
	}
	if (rd < 0)
		return (free(asterisk), free(str), free(buf), put_err("read failed"));
	// EOFまでの行が残っているときに忘れずに出力する。
	if (*str)
		printf("%s", str);
	return (free(asterisk), free(str), free(buf), 0);
}