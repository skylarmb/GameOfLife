#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define H 1024
#define W 1024

/* world stuff */

typedef int World[H][W];

int readFile(char *filename, World w) {
	FILE *fp;
    fp = fopen(filename,"r");
    if(fp==NULL){
        printf("File not found: %s",filename);
		exit(1);
    }
	int size = -1;
	while(fgetc(fp) != '\n'){
		size++;
	}
	printf("size: %d",size);
    fclose(fp);
	for(int i = 0; i <= size; i++){
		for(int j = 0; j <= size; j++){
			w[i][j] = 0;
		}
	}
	fp = fopen(filename,"r");
	char c;
    for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			c = fgetc(fp);
			if(c == '#') w[i][j] = 1;
			else w[i][j] = 0;
		}
		c = fgetc(fp);
		c = fgetc(fp);
    }
	fclose(fp);
	return size;
}

void outWorld (World w,int size) {
	int he, wi;
	
	for (he = 0; he < size; he++){
		for (wi = 0; wi < size; wi++){
			if (w[he][wi] == 1) printf("\u2588");
			else printf(" ");
		}
		printf("\n");
	}
	printf("\n");
}

int neighbors (World w, int x, int y) {
	int count = 0;
	for (int i = x - 1; i <= x + 1; i++){
		for (int j = y - 1; j <= y + 1; j++){
			if (i < 0 || i >= W || j < 0 || j >= H
			|| w[i][j] != 1 || (i == x && j == y)) continue;
			else count++;
		}
	}
	return count;
}


void propogate (World w,int size){
	World w2;
	int n, he, wi = 0;
	
	for (he = 0; he < size; he++){
		for (wi = 0; wi < size; wi++){
			n = neighbors(w, he, wi);
			if (n == 3){ w2[he][wi] = 1; }
			else if (n == 2 &&	w[he][wi] == 1) { w2[he][wi] = 1; }
			else w2[he][wi] = 0;
		}
	}
	printf("\n");
	
	for (he = 0; he < H; he++){
		for (wi = 0; wi < W; wi++){
			w[he][wi] = w2[he][wi];
		}
	}
}

// user entry is a pain for testing
// here's some code to load test data
void loadTestData(World world) {
	// toggle
	//world[1][0] = 1;
	//world[1][1] = 1;
	//world[1][2] = 1;
	
	/*
	// glider
	world[10][4] = 1;
	world[10][5] = 1;
	world[10][6] = 1;
	world[11][6] = 1;
	world[12][5] = 1;
	*/
}

int main(int argc, char** argv) {
	World world;
	int size = readFile(argv[1],world);
	outWorld(world,size);
	int numtimes;
	if (sscanf (argv[2], "%i", &numtimes)!=1)
		printf ("arg 2 not an integer\n");
	for(int i=numtimes; i > 0; i--){
		propogate(world,size);
		outWorld(world,size);
		usleep(100000);
	}
	return 0;
}
