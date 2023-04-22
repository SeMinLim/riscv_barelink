#include <stdint.h>

//#define SAMPLE_CNT 1
#define HIDDEN 32

uint8_t volatile * const pmodel = (uint8_t*)0x2000;
uint8_t volatile * psamples[SAMPLE_CNT];

/*
int inita = 12;

int volatile * const p_reg = (int *) 0x800;
int foo(int a, char b) {
	*p_reg = a;
	if ( a == 0 ) return b;
	return foo(a-1, b+1);
}
*/

uint32_t recognize(uint8_t volatile * sample) {
	int8_t * weights1i = (int8_t*)pmodel;
	int8_t * bias1i = (int8_t*)(pmodel+(784*HIDDEN));
	int8_t * weightsouti = (int8_t*)(pmodel+(784*HIDDEN)+HIDDEN);
	int8_t * biasouti = (int8_t*)(pmodel+(784*HIDDEN)+HIDDEN+(HIDDEN*10));

	int32_t hiddeni[HIDDEN];
	int32_t outi[10];

	for ( int i = 0; i < HIDDEN; i++ ) {
		hiddeni[i] = 0;
		for ( int j = 0; j < 784; j++ ) {
			hiddeni[i] += (((int32_t)sample[j]))*(((int32_t)weights1i[j+i*784]));
		}
		hiddeni[i] += ((int32_t)bias1i[i]);
		hiddeni[i] >>= 7;
	}
	for ( int i = 0; i < 10; i++ ) {
		outi[i] = 0;
		for ( int j = 0; j < HIDDEN; j++ ) {
			outi[i] += hiddeni[j]*((int32_t)weightsouti[j+i*HIDDEN]);
		}
		outi[i] += ((int32_t)biasouti[i]);
	}
		
	int answer = 0;
	int32_t top = 0;
	for ( int i = 0; i < 10; i++ ) {
		//printf( "%f ", outi[i] );
		if ( top < outi[i] ) {
			answer = i;
			top = outi[i];
		}
	}
	return answer;
}

int main() {
	for ( int i = 0; i < SAMPLE_CNT; i++ ){
		uint8_t volatile * psample = (uint8_t*)(0x3000 + (0x400*i));
		uint8_t volatile * answerloc = (uint8_t*)(0x5000 + i);

		uint32_t predicted = recognize(psample);
		*answerloc = predicted;
	}
	return 0;
}

