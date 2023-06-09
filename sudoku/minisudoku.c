#include <stdint.h>
#include <stdbool.h>

char volatile * const printchar = (char*)0x1fffffff;
char setin[16] = {0,3,0,4,0,0,2,0,4,0,3,0,0,0,0,2};


bool check(char* set, int idx) {
	int row = idx/4;
	int col = idx%4;
	int blk = ((idx/8)*8)+(col/2)*2;
	bool unique[12];
	for ( int i = 0; i < 12; i++ ) unique[i] = false;

	bool ret = true;
	for ( int i = 0; i < 4; i++ ) {
		char r = set[row*4+i];
		char c = set[i*4+col];
		char b = set[blk+(i/2)*4+(i%2)];
		//printf( "row: %d col: %d blk: %d\n", r,c,b );

		if ( r > 0 ) {
			if ( unique[r-1] ) ret = false;
			unique[r-1] = true;
		}
		if ( c > 0 ) {
			if ( unique[c+4-1] ) ret = false;
			unique[c+4-1] = true;
		}
		if ( b > 0 ) {
			if ( unique[b+8-1] ) ret = false;
			unique[b+8-1] = true;
		}
	}
	//printf( "check %s %x\n", ret?"true":"false", mask );
	return ret;
}
bool solve(char* set, int idx) {
	if ( idx >= 16 ) return true;

	if ( set[idx] > 0 ) {
		return solve(set, idx+1);
	} else {
		for ( int i = 0; i < 4; i++ ) {
			set[idx] = i+1;
			bool r = check(set, idx);

			if (r) {
				if ( solve(set, idx+1) ) return true;
			}
		}
		set[idx] = 0;
		return false;
	}
}

int 
main() {
	for ( int i = 0; i < 16; i++ ) {
		(*printchar) = (setin[i]+0x30);
		if ( i % 4 == 3 ) (*printchar) = 0xa;
	}
	(*printchar) = 0xa;
	
	if ( solve(setin, 0) ) {
		for ( int i = 0; i < 16; i++ ) {
			(*printchar) = (setin[i]+0x30);
			if ( i % 4 == 3 ) (*printchar) = 0xa;
		}
		(*printchar) = 0xa;

		uint8_t mul = 1 * 5;
		uint8_t div = 10 / 5;
		(*printchar) = mul + 0x30;
		(*printchar) = 0xa;
		(*printchar) = div + 0x30;
		(*printchar) = 0xa;
	} else {
		(*printchar) = 0x78;
		(*printchar) = 0xa;
	}

}
