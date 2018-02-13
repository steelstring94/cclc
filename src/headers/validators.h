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

#ifndef VALIDATORS
#define VALIDATORS

//Printed if no command line arguments are given
//or if -h or --help were the first arguments
//to the program.
void printHelp();

//Used to ensure uniqueness
//of each input
bool charsUnique(char*, const size_t);

//Validate individual lettered arguments
bool validatePermStrs(const size_t, char**, char*, char**);

//Validate command line arguments as a whole.
//0 = Success
//1 = Failure
//2 = Run printHelp()
int validateArguments(const size_t, char**, char*, char**);

#endif
