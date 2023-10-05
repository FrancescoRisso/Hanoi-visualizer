#include <stdio.h>
#include <stdlib.h>

typedef enum { left, center, right } Pos;

#define N 5
#define MOVE_ALL_TO_THE right  // Other option is center

typedef struct {
	int left[N], center[N], right[N];
} Hanoi;


/*
	initHanoi
	---------------------------------------------------------------------
	Initialises the hanoi problem
	---------------------------------------------------------------------
	OUTPUT:
		- the Hanoi object
*/
Hanoi initHanoi();


/*
	printHanoi
	---------------------------------------------------------------------
	Prints a Hanoi structure
	---------------------------------------------------------------------
	PARAMETERS:
		- h: the structure to be printed
*/
void printHanoi(Hanoi h);

/*
	move
	---------------------------------------------------------------------
	Moves some disks from a post to another
	---------------------------------------------------------------------
	PARAMETERS:
		- h: the structure to operate with
		- from: the post where to take
		- to: the post where to put
		- disks: how many disks to move
	---------------------------------------------------------------------
	OUTPUT:
		- the updated Hanoi structure
*/
Hanoi move(Hanoi h, Pos from, Pos to, int disks);

/*
	getPost
	---------------------------------------------------------------------
	Returns a post of the hanoi structure
	---------------------------------------------------------------------
	PARAMETERS:
		- h: a pointer to the structure
		- p: the position of the post
	---------------------------------------------------------------------
	OUTPUT:
		- a pointer to an N-sized array containing the post
*/
int *getPost(Hanoi *h, Pos p);


int main(int argc, char *argv[]) {
	Hanoi hanoi;

	hanoi = initHanoi();

	printHanoi(hanoi);

	hanoi = move(hanoi, left, MOVE_ALL_TO_THE, N);

	printHanoi(hanoi);

	return 0;
}

Hanoi initHanoi() {
	int i;
	Hanoi h;

	for(i = 0; i < N; i++) {
		h.left[i] = i + 1;
		h.center[i] = h.right[i] = 0;
	}

	return h;
}

void printHanoi(Hanoi h) {
	int i, r;

	// printf("\n\n\n\t");
	system("cls");
	printf("\n\t");
	for(i = 0; i < N + 1; i++) printf(" ");
	printf("%c", 179);
	for(i = 0; i < N + 2; i++) printf("  ");
	printf("%c", 179);
	for(i = 0; i < N + 2; i++) printf("  ");
	printf("%c", 179);
	for(i = 0; i < N + 1; i++) printf(" ");

	for(r = 0; r < N; r++) {
		printf("\n\t ");
		for(i = 0; i < N - h.left[r]; i++) printf(" ");
		for(; i < N; i++) printf("%c", 220);
		printf("%c", 179);
		for(i = 0; i < h.left[r]; i++) printf("%c", 220);
		for(; i < N; i++) printf(" ");

		printf("    ");

		for(i = 0; i < N - h.center[r]; i++) printf(" ");
		for(; i < N; i++) printf("%c", 220);
		printf("%c", 179);
		for(i = 0; i < h.center[r]; i++) printf("%c", 220);
		for(; i < N; i++) printf(" ");

		printf("    ");

		for(i = 0; i < N - h.right[r]; i++) printf(" ");
		for(; i < N; i++) printf("%c", 220);
		printf("%c", 179);
		for(i = 0; i < h.right[r]; i++) printf("%c", 220);
		for(; i < N; i++) printf(" ");
	}

	printf("\n\t");
	for(i = 0; i < N + 1; i++) printf("%c", 196);
	printf("%c", 193);
	for(i = 0; i < N + 2; i++) printf("%c%c", 196, 196);
	printf("%c", 193);
	for(i = 0; i < N + 2; i++) printf("%c%c", 196, 196);
	printf("%c", 193);
	for(i = 0; i < N + 1; i++) printf("%c", 196);

	printf("\n\n");
	system("pause");
}

Hanoi move(Hanoi h, Pos from, Pos to, int disks) {
	int i, *post, tmp;
	Pos tmpPos;

	if(disks < 0 || disks > N) {
		printf("\nInvalid move\n");
		exit(1);
	}

	if(disks == 0) return h;

	if(disks == 1) {
		post = getPost(&h, from);
		for(i = 0; i < N && post[i] == 0; i++) {}
		if(i == N) {
			printf("\nInvalid move\n");
			exit(1);
		}
		tmp = post[i];
		post[i] = 0;

		post = getPost(&h, to);
		for(i = 0; i < N && post[i] == 0; i++) {}
		if(i == 0) {
			printf("\nInvalid move\n");
			exit(1);
		}
		post[i - 1] = tmp;

		printHanoi(h);

		return h;
	}

	if((from == left && to == center) || (from == center && to == left)) tmpPos = right;
	if((from == right && to == center) || (from == center && to == right)) tmpPos = left;
	if((from == left && to == right) || (from == right && to == left)) tmpPos = center;

	h = move(h, from, tmpPos, disks - 1);
	h = move(h, from, to, 1);
	h = move(h, tmpPos, to, disks - 1);

	return h;
}

int *getPost(Hanoi *h, Pos p) {
	switch(p) {
		case left: return h->left;
		case center: return h->center;
		case right: return h->right;
	}
}
