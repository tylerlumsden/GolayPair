inline int coprimelength[100] = {0,0,0,1,1,3,1,5,3,5,3,9,3,11,5,7,7,15,5,17,7,11,9,21,7,19,11,17,11,27,7,29,15,19,15,23,11,35,17,23,15,39,11,41,19,23,21,45,15,41,19,31,23,51,17,39,23,35,27,57,15,59,29,35,31,47,19,65,31,43,23,69,23,71,35,39,35,59,23,77,31,53,39,81,23,63,41,55,39,87,23,71,43,59,45,71,31,95,41,59};


inline int coprimelist[100][100] = {
{},
{},
{},
{2},
{3},
{2,3,4},
{5},
{2,3,4,5,6},
{3,5,7},
{2,4,5,7,8},
{3,7,9},
{2,3,4,5,6,7,8,9,10},
{5,7,11},
{2,3,4,5,6,7,8,9,10,11,12},
{3,5,9,11,13},
{2,4,7,8,11,13,14},
{3,5,7,9,11,13,15},
{2,3,4,5,6,7,8,9,10,11,12,13,14,15,16},
{5,7,11,13,17},
{2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18},
{3,7,9,11,13,17,19},
{2,4,5,8,10,11,13,16,17,19,20},
{3,5,7,9,13,15,17,19,21},
{2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22},
{5,7,11,13,17,19,23},
{2,3,4,6,7,8,9,11,12,13,14,16,17,18,19,21,22,23,24},
{3,5,7,9,11,15,17,19,21,23,25},
{2,4,5,7,8,10,11,13,14,16,17,19,20,22,23,25,26},
{3,5,9,11,13,15,17,19,23,25,27},
{2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28},
{7,11,13,17,19,23,29},
{2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30},
{3,5,7,9,11,13,15,17,19,21,23,25,27,29,31},
{2,4,5,7,8,10,13,14,16,17,19,20,23,25,26,28,29,31,32},
{3,5,7,9,11,13,15,19,21,23,25,27,29,31,33},
{2,3,4,6,8,9,11,12,13,16,17,18,19,22,23,24,26,27,29,31,32,33,34},
{5,7,11,13,17,19,23,25,29,31,35},
{2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36},
{3,5,7,9,11,13,15,17,21,23,25,27,29,31,33,35,37},
{2,4,5,7,8,10,11,14,16,17,19,20,22,23,25,28,29,31,32,34,35,37,38},
{3,7,9,11,13,17,19,21,23,27,29,31,33,37,39},
{2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40},
{5,11,13,17,19,23,25,29,31,37,41},
{2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42},
{3,5,7,9,13,15,17,19,21,23,25,27,29,31,35,37,39,41,43},
{2,4,7,8,11,13,14,16,17,19,22,23,26,28,29,31,32,34,37,38,41,43,44},
{3,5,7,9,11,13,15,17,19,21,25,27,29,31,33,35,37,39,41,43,45},
{2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46},
{5,7,11,13,17,19,23,25,29,31,35,37,41,43,47},
{2,3,4,5,6,8,9,10,11,12,13,15,16,17,18,19,20,22,23,24,25,26,27,29,30,31,32,33,34,36,37,38,39,40,41,43,44,45,46,47,48},
{3,7,9,11,13,17,19,21,23,27,29,31,33,37,39,41,43,47,49},
{2,4,5,7,8,10,11,13,14,16,19,20,22,23,25,26,28,29,31,32,35,37,38,40,41,43,44,46,47,49,50},
{3,5,7,9,11,15,17,19,21,23,25,27,29,31,33,35,37,41,43,45,47,49,51},
{2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52},
{5,7,11,13,17,19,23,25,29,31,35,37,41,43,47,49,53},
{2,3,4,6,7,8,9,12,13,14,16,17,18,19,21,23,24,26,27,28,29,31,32,34,36,37,38,39,41,42,43,46,47,48,49,51,52,53,54},
{3,5,9,11,13,15,17,19,23,25,27,29,31,33,37,39,41,43,45,47,51,53,55},
{2,4,5,7,8,10,11,13,14,16,17,20,22,23,25,26,28,29,31,32,34,35,37,40,41,43,44,46,47,49,50,52,53,55,56},
{3,5,7,9,11,13,15,17,19,21,23,25,27,31,33,35,37,39,41,43,45,47,49,51,53,55,57},
{2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58},
{7,11,13,17,19,23,29,31,37,41,43,47,49,53,59},
{2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60},
{3,5,7,9,11,13,15,17,19,21,23,25,27,29,33,35,37,39,41,43,45,47,49,51,53,55,57,59,61},
{2,4,5,8,10,11,13,16,17,19,20,22,23,25,26,29,31,32,34,37,38,40,41,43,44,46,47,50,52,53,55,58,59,61,62},
{3,5,7,9,11,13,15,17,19,21,23,25,27,29,31,33,35,37,39,41,43,45,47,49,51,53,55,57,59,61,63},
{2,3,4,6,7,8,9,11,12,14,16,17,18,19,21,22,23,24,27,28,29,31,32,33,34,36,37,38,41,42,43,44,46,47,48,49,51,53,54,56,57,58,59,61,62,63,64},
{5,7,13,17,19,23,25,29,31,35,37,41,43,47,49,53,59,61,65},
{2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66},
{3,5,7,9,11,13,15,19,21,23,25,27,29,31,33,35,37,39,41,43,45,47,49,53,55,57,59,61,63,65,67},
{2,4,5,7,8,10,11,13,14,16,17,19,20,22,25,26,28,29,31,32,34,35,37,38,40,41,43,44,47,49,50,52,53,55,56,58,59,61,62,64,65,67,68},
{3,9,11,13,17,19,23,27,29,31,33,37,39,41,43,47,51,53,57,59,61,67,69},
{2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70},
{5,7,11,13,17,19,23,25,29,31,35,37,41,43,47,49,53,55,59,61,65,67,71},
{2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72},
{3,5,7,9,11,13,15,17,19,21,23,25,27,29,31,33,35,39,41,43,45,47,49,51,53,55,57,59,61,63,65,67,69,71,73},
{2,4,7,8,11,13,14,16,17,19,22,23,26,28,29,31,32,34,37,38,41,43,44,46,47,49,52,53,56,58,59,61,62,64,67,68,71,73,74},
{3,5,7,9,11,13,15,17,21,23,25,27,29,31,33,35,37,39,41,43,45,47,49,51,53,55,59,61,63,65,67,69,71,73,75},
{2,3,4,5,6,8,9,10,12,13,15,16,17,18,19,20,23,24,25,26,27,29,30,31,32,34,36,37,38,39,40,41,43,45,46,47,48,50,51,52,53,54,57,58,59,60,61,62,64,65,67,68,69,71,72,73,74,75,76},
{5,7,11,17,19,23,25,29,31,35,37,41,43,47,49,53,55,59,61,67,71,73,77},
{2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78},
{3,7,9,11,13,17,19,21,23,27,29,31,33,37,39,41,43,47,49,51,53,57,59,61,63,67,69,71,73,77,79},
{2,4,5,7,8,10,11,13,14,16,17,19,20,22,23,25,26,28,29,31,32,34,35,37,38,40,41,43,44,46,47,49,50,52,53,55,56,58,59,61,62,64,65,67,68,70,71,73,74,76,77,79,80},
{3,5,7,9,11,13,15,17,19,21,23,25,27,29,31,33,35,37,39,43,45,47,49,51,53,55,57,59,61,63,65,67,69,71,73,75,77,79,81},
{2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82},
{5,11,13,17,19,23,25,29,31,37,41,43,47,53,55,59,61,65,67,71,73,79,83},
{2,3,4,6,7,8,9,11,12,13,14,16,18,19,21,22,23,24,26,27,28,29,31,32,33,36,37,38,39,41,42,43,44,46,47,48,49,52,53,54,56,57,58,59,61,62,63,64,66,67,69,71,72,73,74,76,77,78,79,81,82,83,84},
{3,5,7,9,11,13,15,17,19,21,23,25,27,29,31,33,35,37,39,41,45,47,49,51,53,55,57,59,61,63,65,67,69,71,73,75,77,79,81,83,85},
{2,4,5,7,8,10,11,13,14,16,17,19,20,22,23,25,26,28,31,32,34,35,37,38,40,41,43,44,46,47,49,50,52,53,55,56,59,61,62,64,65,67,68,70,71,73,74,76,77,79,80,82,83,85,86},
{3,5,7,9,13,15,17,19,21,23,25,27,29,31,35,37,39,41,43,45,47,49,51,53,57,59,61,63,65,67,69,71,73,75,79,81,83,85,87},
{2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88},
{7,11,13,17,19,23,29,31,37,41,43,47,49,53,59,61,67,71,73,77,79,83,89},
{2,3,4,5,6,8,9,10,11,12,15,16,17,18,19,20,22,23,24,25,27,29,30,31,32,33,34,36,37,38,40,41,43,44,45,46,47,48,50,51,53,54,55,57,58,59,60,61,62,64,66,67,68,69,71,72,73,74,75,76,79,80,81,82,83,85,86,87,88,89,90},
{3,5,7,9,11,13,15,17,19,21,25,27,29,31,33,35,37,39,41,43,45,47,49,51,53,55,57,59,61,63,65,67,71,73,75,77,79,81,83,85,87,89,91},
{2,4,5,7,8,10,11,13,14,16,17,19,20,22,23,25,26,28,29,32,34,35,37,38,40,41,43,44,46,47,49,50,52,53,55,56,58,59,61,64,65,67,68,70,71,73,74,76,77,79,80,82,83,85,86,88,89,91,92},
{3,5,7,9,11,13,15,17,19,21,23,25,27,29,31,33,35,37,39,41,43,45,49,51,53,55,57,59,61,63,65,67,69,71,73,75,77,79,81,83,85,87,89,91,93},
{2,3,4,6,7,8,9,11,12,13,14,16,17,18,21,22,23,24,26,27,28,29,31,32,33,34,36,37,39,41,42,43,44,46,47,48,49,51,52,53,54,56,58,59,61,62,63,64,66,67,68,69,71,72,73,74,77,78,79,81,82,83,84,86,87,88,89,91,92,93,94},
{5,7,11,13,17,19,23,25,29,31,35,37,41,43,47,49,53,55,59,61,65,67,71,73,77,79,83,85,89,91,95},
{2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96},
{3,5,9,11,13,15,17,19,23,25,27,29,31,33,37,39,41,43,45,47,51,53,55,57,59,61,65,67,69,71,73,75,79,81,83,85,87,89,93,95,97},
{2,4,5,7,8,10,13,14,16,17,19,20,23,25,26,28,29,31,32,34,35,37,38,40,41,43,46,47,49,50,52,53,56,58,59,61,62,64,65,67,68,70,71,73,74,76,79,80,82,83,85,86,89,91,92,94,95,97,98}

};