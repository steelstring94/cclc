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

#ifndef PARSERS
#define PARSERS

//Sort the lettered command line
//arguments into arrays in the
//appropriate relative order.
void parsePermStrs(const size_t, char**, char*, char**);

//Take the lettered permissions and
//convert them to binary representational
//form.
void processPerms(char *targets, char **perms, char **bins);

//Convert binary permissions
//representation to decimal
//integer format
void convertBinaries(char **bins, int *nums);

//Copy binary permissions from
//command line arguments into
//appropriate array.  Used
//if the user has input
//permissions in binary
//form instead of using
//lettered arguments.
void copyBins(int, char**, char**);

#endif
