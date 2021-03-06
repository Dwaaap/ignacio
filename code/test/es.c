#include "syscall.h"

#define printf(format, ...) \
	{\
		void* __args[] = { __VA_ARGS__ };\
		user_printf(format, __args);\
	}
#define scanf(format, ...) \
	{\
		void* __args[] = { __VA_ARGS__ };\
		user_scanf(format, __args);\
	}

void user_printf(const char* str, void** args);
int user_scanf(const char* str, void** args);

void user_printf(const char *str, void** args) {
	char c;
	char* s;
	int d;
	void* p;

	int arg = 0;
	int i = 0;
	while (str[i] != '\0') {
		if (str[i] != '%') {
			PutChar(str[i]);
		} else {
			i++;
			p = args[arg];
			arg++;
			switch (str[i]) {
				case '%':
					PutChar('%');
					break;
				case 'c':
					c = *(char*) p;
					PutChar((char) c);
					break;

				case 's':
					s = (char*) p;
					PutString(s);
					break;
				case 'd':
					d = *(int*) p;
					PutInt(d);
					break;
				default:
					return;
			}
		}
		i++;
	}
}

int user_scanf(const char *str, void** args) {
	char* s;
	int* d;
	void* p;

	int arg = 0;
	int i = 0;
	while (str[i] != '\0') {
		if (str[i] == '%') {
			i++;
			p = args[arg];
			arg++;
			switch (str[i]) {
				case 'c':
					s = (char*) p;
					*s = GetChar();
					break;

				case 's':
					s = (char*) p;
					GetString(s, 20); //TODO MAX_STRING_SIZE
					break;
				case 'd':
					d = (int*) p;
					GetInt(d);
					break;
				default:
					return -1;
			}
		}
		i++;
	}
	return arg;
}

int main(int argc, char* argv[]) {
	int i, j, k;
	char str[20];
	char c;
	printf("Entrez 3 nombres :\n");
	scanf("%d %d %d", &i, &j, &k);
	printf("Les nombres sont : %d %d %d %%\n", &i, &j, &k);
	printf("Entrez une chaine :\n");
	scanf("%s", str);
	printf("La chaine est : %s\n", str);
	printf("Entrez un caractere :\n");
	scanf("%c", &c);
	printf("Le caractere est : %c\n", &c);

	return 0;
}

