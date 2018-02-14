/* Copyright (C) 2018 steelstring94@gmail.com

	This file is part of cclc.

    cclc is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    cclc is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with cclc.  If not, see <http://www.gnu.org/licenses/>.
*/

#define _XOPEN_SOURCE 500
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

void parsePermStrs(const size_t argc, char **argv, char *targets, char **perms) {
	for(int i = 0; i < argc; i++) {
		//This code is written to work with
		//the target arguments as the focus
		//of each loop, so if the current arg
		//being considered does not begin
		//with a hyphen - i.e. it is not
		//a list of targets - we skip it.
		if(argv[i][0] != '-') {
			continue;
		}

		char *targs = argv[i];

		for(int k = 1; k < strlen(targs); k++) {
			char targ = targs[k];
			//abs(i-k) gets us to the right
			//relative position in the arrays
			//that will hold the targets
			//and arguments because the
			//fractional part is dropped.

			//They must be in the same order
			//relative to each other.  So, if
			//targets[0] == 'u', then we know
			//perms[0] must contain the permission
			//string for the user target.
			targets[abs(i-k)] = targ;

			//The existence of argv[i+1]
			//is already guaranteed by
			//validatePermStrs() (validators.c)
			perms[abs(i-k)] = strdup(argv[i+1]);
		}
	}
}

void processPerms(char *targets, char **perms, char **bins) {
	for(int i = 0; i < 3; i++) {

		//binDig is the binary form of
		//the rwx style permissions
		//code.
		//We set the appropriate bits
		//to 1 if we find that permission
		//is enabled by the command line
		//arguments.
		char binDig[] = "000";

		for(int k = 0; k < strlen(perms[i]); k++) {
			switch(perms[i][k]) {
				case 'r':
					binDig[0] = '1';
					break;
				case 'w':
					binDig[1] = '1';
					break;
				case 'x':
					binDig[2] = '1';
					break;
			}
		}
		//The permission target codes
		//and permission codes themselves
		//will always be in the same order
		//in relation to each other in their
		//respective arrays.  We can use this
		//fact to know where to put
		//bitDig in the bins char array.
		switch(targets[i]) {
			case 'u':
				bins[0] = strdup(binDig);
				break;
			case 'g':
				bins[1] = strdup(binDig);
				break;
			case 'o':
				bins[2] = strdup(binDig);
				break;
		}
	}
}

void convertBinaries(char **bins, int *nums) {

	for(int i = 0; i < 3; i++) {
		int b = 0;

		//decimal = 2^(num. pos. - 1)
		//subtract 1 so rightmost number
		//pos. is 0, subtract k because
		//power increases from r-l, but
		//we are iterating from l-r
		for(int k = 0; k < strlen(bins[i]); k++) {
			if(bins[i][k] == '1') {
				const int v = pow(2, (strlen(bins[i])-1)-k);
				b += v;
			}
		}
		nums[i] = b;
	}
}

void copyBins(int argc, char **argv, char **bins) {
	for(int i = 1; i < argc; i++) {
		bins[i-1] = strdup(argv[i]);
	}
}
