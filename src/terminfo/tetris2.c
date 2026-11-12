#define _BSD_SOURCE
#define _DEFAULT_SOURCE
#define _POSIX_C_SOURCE

#include <sys/time.h>

#include <signal.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#if 0
/* <signal.h> has finally stopped declaring this, even as deprecated */
struct sigvec {
    void (*sv_handler)(int); /* Signal disposition */
    int    sv_mask;          /* Signals to be blocked in handler */
    int    sv_flags;         /* Flags */
};

extern int sigvec(int sig, struct sigvec *new, struct sigvec *old);
#endif

void t(int);

int Q[276];

int q[276];
int *n = q;

int z(void)
{
	unsigned char c;
	int i = read(0, &c, 1);
	if (i<=0)
		return EOF;
	return c;
}

int u(void)
{
	static int I = 0;
	int k;
	for (int i = 11; ++i < 264;)
		if ((k = q[i]) - Q[i]
		    ) {
			Q[i] = k;
			if (i - ++I || i % 12 < 1)
				printf("\033[%d;%dH", (I = i) / 12, i % 12 * 2 + 28);
			static int K = 0;
			printf("\033[%dm  " + (K - k ? 0 : 5), k);
			K = k;
		}
	return Q[263] = z();
}

bool G(int b)
{
	for (int i = 4; i--;)
		if (q[i ? b + n[i] : b])
			return 0;
	return 1;
}

void g(int b, int x)
{
	for (int i = 4; i--; q[i ? x + n[i] : x] = b) ;
}

struct itimerval h = { .it_interval = {0,0},	/* single-shot */
		       .it_value.tv_sec = 0,	/* delay is always less than one second */
		};

void t(int __attribute__((unused)))
{
	h.it_value.tv_usec -= h.it_value.tv_usec / 3000;
	setitimer(0, &h, 0);
}

int f[] = {
        7, -13, -12, 1, 8, -11, -12, -1, 9, -1, 1, 12, 3, -13, -12, -1, 12, -1,
        11, 1, 15, -1, 13, 1, 18, -1, 1, 2, 0, -12, -1, 11, 1, -12, 1, 13, 10,
        -12, 1, 12, 11, -12, -1, 1, 2, -12, -1, 12, 13, -12, 12, 13, 14, -11,
        -1, 1, 4, -13, -12, 12, 16, -11, -12, 12, 17, -13, 1, -1, 5, -12, 12,
        11, 6, -12, 12, 24,
};

void [[noreturn]] die(int ex, char *fmt, ...) {
	va_list v;
	va_start(v, fmt);
	vfprintf(stderr, fmt, v);
	va_end(v);
	exit(ex);
}

int main(int argc, char **argv)
{
	int score = 0;

	int level = argc > 1 ? atoi(argv[1]) : 2;

	h.it_value.tv_usec = 1000000 / level;


	char *a = argc > 2 ? argv[2] : "jkl pq";
	for (int i = 276; i; i--)
		*n++ = i < 25 || i % 12 < 2 ? 7 : 0;
	srand(getpid());

	struct termios OT;
	if (tcgetattr(2, &OT) < 0) die(1,"tcgetattr: %m");

	struct termios T = OT;
	//T.c_cflag &= ~0;
	T.c_iflag &= ~IXON;
	T.c_lflag &= ~(ECHO|ECHONL|ICANON);
	T.c_cc[VMIN] = 1;
	T.c_cc[VTIME] = 0;
	if (tcsetattr(2, TCSANOW, &T) < 0) die(2, "tcsetattr: %m");

	sigset_t S;
	sigemptyset(&S);
	sigaddset(&S, SIGALRM);
	sigaction(SIGALRM, (struct sigaction[1]){{ .sa_handler = t, .sa_mask = S, .sa_flags = 0 }}, NULL);

	t(0);

	puts("\033[H\033[J");
	int c = 0;
	int x = 17;
	for (n = f + rand() % 7 * 4;; g(7, x), c = u(), g(0, x)) {
		if (c < 0) {
			if (G(x + 12))
				x += 12;
			else {
				g(7, x);
				++score;
				for (int j = 0; j < 252; j = 12 * (j / 12 + 1))
					for (; q[++j];)
						if (j % 12 == 10) {
							for (; j % 12; q[j--] = 0) ;
							c = u();
							for (; --j; q[j + 12] = q[j]) ;
							c = u();
						}
				n = f + rand() % 7 * 4;
				if (!G(x = 17)) c = a[5];
			}
		}
		if (c == *a && !G(--x))
			 ++x;
		if (c == a[1]) {
			int *m;
			n = f + 4 * *(m = n);
			if (!G(x)) n = m;
		}
		if (c == a[2] && ! G(++x)) --x;
		if (c == a[3])
			for (; G(x + 12); ++score)
				x += 12;
		if (c == a[4] || c == a[5]) {
			sigset_t O;
			sigprocmask(SIG_BLOCK, &S, &O);
			printf("\033[H\033[J\033[0m%d\n", score);
			if (c == a[5])
				break;
			for (int j = 264; j--; Q[j] = 0) ;
			while (z() - a[4]) ;
			puts("\033[H\033[J\033[7m");
			//sigprocmask(SIG_SETMASK, &O, NULL);
			sigprocmask(SIG_UNBLOCK, &S, &O);
		}
	}
	if (tcsetattr(2, TCSANOW, &T) < 0) die(3,"tcsetattr: %m");
	FILE * d = popen("cat - .tetris.highscores |"
			 " tee /dev/tty |"
			 " sort -t ' ' -s -k5,5nr -k2,2nr -o .tetris.highscores",
			 "w");
	fprintf(d, "scored %u on level %u by %s\n", score, level, getlogin());
	pclose(d);
}
