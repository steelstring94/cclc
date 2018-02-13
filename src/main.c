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

#include <stdio.h>
#include <stdbool.h>
#include "headers/validators.h"
#include "headers/parsers.h"

int main(int argc, char *argv[]) {

	//Initialize targets char array
	//with nulls so that when we
	//copy in the actual target
	//arguments, the terminating
	//character will be null.

	//This is so that we can
	//check *targets == '\0'
	//below to see if lettered
	//inputs were given, and
	//interpret the input as
	//binary if they were not.
	char targets[4];
	for(int i = 0; i < 4; i++) {
		targets[i] = '\0';
	 }

	//This will hold the rwx permissions
	char *perms[] = {"", "", ""};

	//Initialize to empty string.
	//Otherwise we will get a
	//segfault in processPerms()
	//if the user enters less than
	//3 targets.
	for(int i = 0; i < 3; i++) {
		perms[i] = "";
	}

	//Validate input arguments and
	//handle response code
	switch(validateArguments(argc, argv, targets, perms)) {
		case 0:
			break;
		case 1:
			printf("ERROR: Invalid input\n");
			return 1;
		case 2:
			printHelp();
			return 0;
	}

	//Move the targets and permission
	//codes to their own respective
	//arrays.
	parsePermStrs(argc, argv, targets, perms);

	//Holds exactly 3 strings each of
	//length 3, which will represent
	//the binary form of the permissions.
	char *bins[] = {"000", "000", "000"};

	//If targets[0] is still
	//null, that means no
	//lettered arguments were
	//entered, therefore the
	//arguments should be treated
	//as binaries.
	if(targets[0] == '\0') {
		copyBins(argc, argv, bins);
	}
	else {
		//Convert lettered args
		//to binary form and
		//store the results in bins
		processPerms(targets, perms, bins);
	}

	//Convert binary strings to
	//integers and store each one
	//in nums.
	int nums[3];
	convertBinaries(bins, nums);

	//Print final numeric permissions
	//code to stdout and follow
	//with a newline.
	for(int i = 0; i < 3; i++) {
		printf("%d", nums[i]);
	}

	printf("\n");

	return 0;
}

//Printed if no command line arguments are given
//or if -h or --help were the first arguments
//to the program.
void printHelp() {
	printf("Syntax: cclc [TARGETS] PERMISSIONS\n\n");

	printf("TARGETS:\n\n");

	printf("\t[-u|-g|-o] - Specify permissions for user, group and other\n\n");
	printf("\t[rwx] - Specify read, write and execute\n\n\n");

	printf("Binary input also allowed\n\n");

	printf("EXAMPLES:\n\n");

	printf("\tcclc -u rwx -g r -OR- cclc 111 100 000\n\n");

	printf("\tRESULT: 740 (permission code for rwx r-- ---)\n\n\n");

	printf("Copyright (C) 2018 <steelstring94@gmail.com>\n\n");

	printf("This program is free software licensed under the GNU GPL v3 or later.\n\n");

	printf("See \"man cclc\" for more information\n\n");
}
