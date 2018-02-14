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
#include <string.h>
#include <stdbool.h>

bool charsUnique(char *p, const size_t size) {
	//Returning false if any char equals
	//any other char in the same argument.
	for(int i = 0; i < size; i++) {
		for(int k = i+1; k < size; k++) {
			if(p[i] == p[k]) {
				return false;
			}
		}
	}
	return true;
}

bool validatePermStrs(const size_t argc, char **argv, char *targets, char **perms) {

	for(int i = 1; i < argc; i++) {
		//Check uniqueness of each character in each
		//argument.
		if(!charsUnique(argv[i], strlen(argv[i]))) {
			return false;
		}
		if(argv[i][0] == '-') {
			//Check each set of targets
			//has arguments following it
			//(which should be the
		  //permissions codes).
			if(!argv[i+1]) {
				return false;
			}
			for(int k = 1; k < strlen(argv[i]); k++) {
				//Check targets are either u, g or o
				if(argv[i][k] != 'u' && argv[i][k] != 'g' && argv[i][k] != 'o') {
					return false;
				}
			}
		}
		else {
			for(int k = 0; k < strlen(argv[i]); k++) {
				//Check perms are either r, w or x
				if(argv[i][k] != 'r' && argv[i][k] != 'w' && argv[i][k] != 'x') {
					return false;
				}
			}
			//Check uniqueness of perms.
			if(!charsUnique(argv[i], strlen(argv[i]))) {
				return false;
			}
		}
	}
	return true;
}

int validateArguments(const size_t argc, char **argv, char *targets, char **perms) {

	//Print help if no arguments.
	if(argc < 2 || strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
		return 2;
	}

	if(argc > 7) {
		return 1;
	}

	//Ensure proper individual arg length
	for(int i = 1; i < argc; i++) {
		if(strlen(argv[i]) > 4) {
			return 1;
		}
	}

	//If the first arg begins with
	//a hyphen, the letter syntax
	//has been used and we process
	//accordingly.
	if(argv[1][0] == '-') {
		//Validate each perm string
		if(!validatePermStrs(argc, argv, targets, perms)) {
			return 1;
		}
	}

	//If not, it should be binary syntax
	//so we check that all inputs are either
	//1 or 0.
	else {
		for(int i = 1; i < argc; i++) {
			for(int k = 0; k < strlen(argv[i]); k++) {
				if(argv[i][k] != '1' && argv[i][k] != '0') {
					return 1;
				}
			}
		}
	}
	return 0;
}
