#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// compile as gcc -DKAPPA80 to obtain the implementation of S(163,37)
// compile as gcc -DKAPPA128 to obtain the implementation of S(257,59)
// compile as gcc -DKAPPA160 to obtain the implementation of S(331,71)
// compile as gcc -DKAPPA192 to obtain the implementation of S(389,87)
// compile as gcc -DKAPPA224 to obtain the implementation of S(449,101)
// compile as gcc -DKAPPA256 to obtain the implementation of S(521,115)

#ifdef KAPPA80
#define kappa 80
#define L 163
#define m 37
#define nLFSRtapPos 4
#define mu 12
unsigned char LFSRtapPos[nLFSRtapPos] = {0,3,6,7}; 
unsigned char revposX[kappa/4] = "d569a664f500763506c3";
unsigned char revposY[kappa/4] = "ff0149d4c640e9846cf2";
unsigned char b[L-2*kappa] = "101";
unsigned int dpos[mu] = {30,42,55,67,84,90,104,114,130,138,150,162};
#endif


#ifdef KAPPA128
#define kappa 128
#define L 257
#define m 59
#define nLFSRtapPos 6
#define mu 16
unsigned char LFSRtapPos[nLFSRtapPos] = {0,2,3,4,5,7}; 
unsigned char revposX[kappa/4] = "be352d9ca349432b80b38ac54e5164c9";
unsigned char revposY[kappa/4] = "d2ece08cbb5566d608a69b19e4a91418";
unsigned char b[L-2*kappa] = "1";
unsigned int dpos[mu] = {17,33,48,64,81,96,112,129,145,161,178,194,209,224,241,256};
#endif


#ifdef KAPPA160
#define kappa 160
#define L 331
#define m 71
#define nLFSRtapPos 6
#define mu 18
unsigned char LFSRtapPos[nLFSRtapPos] = {0,2,4,5,6,7}; 
unsigned char revposX[kappa/4] = "ea4308e1229305d185450cfa26b0dcac68c4ab7d";
unsigned char revposY[kappa/4] = "1dbb5a438e7e55904cc04406bf0670ad728462b0";
unsigned char b[L-2*kappa] = "10101010101";
unsigned int dpos[mu] = {25,43,61,78,98,115,134,151,168,186,206,224,242,259,277,294,312,330};
#endif

#ifdef KAPPA192
#define kappa 192
#define L 389
#define m 87
#define nLFSRtapPos 6
#define mu 19
unsigned char LFSRtapPos[nLFSRtapPos] = {0,1,2,3,6,7}; 
unsigned char revposX[kappa/4] = "a0265ea181b73a460fb50d8482590e584d15869de343957e";
unsigned char revposY[kappa/4] = "c6b218be600d6183c074d00fde24e1c308ebb06cebab0f84";
unsigned char b[L-2*kappa] = "10101";
unsigned int dpos[mu] = {46,65,84,104,123,141,160,179,203,217,236,256,274,293,314,331,350,369,388};
#endif

#ifdef KAPPA224
#define kappa 224
#define L 449
#define m 101
#define nLFSRtapPos 8
#define mu 21
unsigned char LFSRtapPos[nLFSRtapPos] = {0,1,2,3,4,5,6,9}; 
unsigned char revposX[kappa/4] = "e9507d49d4f4609a710d8d291eb466430af5668b03ec424c18417d86";
unsigned char revposY[kappa/4] = "d288451f8f0554a46615f4448afa34aab8673d0647044afcd4682ec4";
unsigned char b[L-2*kappa] = "1";
unsigned int dpos[mu] = {29,49,70,94,112,133,155,175,197,218,239,260,282,303,322,344,364,386,408,431,448};
#endif

#ifdef KAPPA256
#define kappa 256
#define L 521
#define m 115
#define nLFSRtapPos 6
#define mu 22
unsigned char LFSRtapPos[nLFSRtapPos] = {0,1,3,5,6,9}; 
unsigned char revposX[kappa/4] = "c1ec835120741f290154b122618c625f0a9e77c5172cac84ae564390b2e91fda";
unsigned char revposY[kappa/4] = "5865fda7830eca37d0c2045994e9c83b1c55e13f1966c220809bc019d37f0054";
unsigned char b[L-2*kappa] = "101010101";
unsigned int dpos[mu] = {58,80,102,125,146,169,192,212,235,256,278,301,324,344,371,388,412,433,454,479,498,520};
#endif

unsigned char c[L] = {0}; // vector of coefficients for the LFSR connection polynomial
unsigned char pos[L] = {0}; // tap positions for the filtering function
unsigned char d[L] = {0}; // positions where feedback is provided by the initialisation round function
unsigned char key[kappa], IV[kappa];
unsigned char state[L];

void toBin(unsigned char hchar, unsigned char *binarr) {

	switch (hchar) {
		case '0': {binarr[0]=0;binarr[1]=0;binarr[2]=0;binarr[3]=0; return;}
		case '1': {binarr[0]=0;binarr[1]=0;binarr[2]=0;binarr[3]=1; return;}
		case '2': {binarr[0]=0;binarr[1]=0;binarr[2]=1;binarr[3]=0; return;}
		case '3': {binarr[0]=0;binarr[1]=0;binarr[2]=1;binarr[3]=1; return;}
		case '4': {binarr[0]=0;binarr[1]=1;binarr[2]=0;binarr[3]=0; return;}
		case '5': {binarr[0]=0;binarr[1]=1;binarr[2]=0;binarr[3]=1; return;}
		case '6': {binarr[0]=0;binarr[1]=1;binarr[2]=1;binarr[3]=0; return;}
		case '7': {binarr[0]=0;binarr[1]=1;binarr[2]=1;binarr[3]=1; return;}
		case '8': {binarr[0]=1;binarr[1]=0;binarr[2]=0;binarr[3]=0; return;}
		case '9': {binarr[0]=1;binarr[1]=0;binarr[2]=0;binarr[3]=1; return;}
		case 'a': {binarr[0]=1;binarr[1]=0;binarr[2]=1;binarr[3]=0; return;}
		case 'b': {binarr[0]=1;binarr[1]=0;binarr[2]=1;binarr[3]=1; return;}
		case 'c': {binarr[0]=1;binarr[1]=1;binarr[2]=0;binarr[3]=0; return;}
		case 'd': {binarr[0]=1;binarr[1]=1;binarr[2]=0;binarr[3]=1; return;}
		case 'e': {binarr[0]=1;binarr[1]=1;binarr[2]=1;binarr[3]=0; return;}
		case 'f': {binarr[0]=1;binarr[1]=1;binarr[2]=1;binarr[3]=1; return;}
	}
}

void LFSRnextState(unsigned char *state) {

	unsigned int i, sum=0;

	for(i=0;i<L;i++) sum = sum + state[i]*c[i];
	for(i=0;i<L-1;i++) state[i] = state[i+1];
	state[L-1] = sum%2;
}

unsigned char f_2m_plus_1(unsigned char *state) {

	unsigned char X[m],Y[m],W,sum1=0,sum2=0,val,majval;
	unsigned int i,j,k,th;

	j = 0; k = 0;
	for(i=0;i<kappa;i++) {
		if (pos[L-1-i] == 1) {X[j] = state[L-1-i]; j++;}
		if (pos[L-kappa-1-i] == 1) {Y[k] = state[L-kappa-1-i]; k++;}
	}
	W = state[L-2*kappa];
	for(i=0;i<m;i++) {sum1 = sum1 + X[i]*Y[m-1-i]; sum2 = sum2+X[i];}

	if (m%2 == 0) th = m/2; else th = 1 + (m-1)/2;
	if (sum2 >= th) majval = 1; else majval = 0;

	val = (sum1 + majval + W + 1) %2;

	return val;
}

int main(unsigned int argc, unsigned char **argv) {

	unsigned int i,j,nbits;
	unsigned char bin[4], fname[80], ksbit, *ksbitstream;
	FILE *fp;

	if (argc != 3) {printf("Usage %s <key-IV-file> <nbits>\n",argv[0]); exit(1);}
	fp = (FILE *)fopen(argv[1],"r");
	if (fp == NULL) {printf("Cannot open %s for reading\n",argv[1]); exit(1);}
	nbits = (unsigned int) atoi(argv[2]); // number of keystream bits to be generated
	ksbitstream = (unsigned char *)calloc(nbits,sizeof(unsigned char));
	// In the key-Iv-file, the first line should have the kappa-bit key, and the second line should have the kappa-bit IV
	fscanf(fp,"%s\n",key); // read key from file as key[0..kappa-1]
	fscanf(fp,"%s\n",IV); // read IV from file as IV[0..kappa-1]

	for(i=0;i<nLFSRtapPos;i++) c[LFSRtapPos[i]] = 1; // obtain the coefficient vector for LFSR connection polynomial
	for(i=0;i<mu;i++) d[dpos[i]] = 1; // obtain the feedback positions for the initialisation round function
	// obtain tap positions for X and Y from posX and posY
	for(i=0;i<kappa/4;i++) {
		toBin(revposX[i],bin);
		pos[L-4*i-1] = bin[0]; pos[L-4*i-2] = bin[1]; pos[L-4*i-3] = bin[2]; pos[L-4*i-4] = bin[3];
		toBin(revposY[i],bin);
		pos[L-kappa-4*i-1] = bin[0]; pos[L-kappa-4*i-2] = bin[1]; pos[L-kappa-4*i-3] = bin[2]; pos[L-kappa-4*i-4] = bin[3];
	}
	pos[L-2*kappa] = 1; // obtain tap position for W

	// load key and IV into state, and pad with the string b
	for(i=0;i<kappa;i++) {state[L-1-i] = key[kappa-1-i]-'0'; state[L-kappa-1-i] = IV[kappa-1-i]-'0';}
	for(i=0;i<L-2*kappa;i++) state[L-2*kappa-1-i] = b[L-2*kappa-1-i]-'0'; 

	// initialisation phase
	for(i=0;i<2*kappa;i++) {
		ksbit = f_2m_plus_1(state);
		LFSRnextState(state);
		for(j=0;j<L;j++) state[i] = (state[i]+ksbit*d[i])%2;
	}

	// keystream generation phase
	ksbitstream[0] = f_2m_plus_1(state);
	for(i=1;i<nbits;i++) {
		LFSRnextState(state);
		ksbitstream[i] = f_2m_plus_1(state);
	}
	for(i=0;i<nbits;i++) printf("%u",ksbitstream[i]); printf("\n");

	return 0;
}

