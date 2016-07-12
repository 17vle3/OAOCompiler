
int idMain ( ) {
    int idA ;
    int idC ;
    int idB [ 10 ] ;

	// test case 1
	//idB [ 3 ] = 7;
	//idA =  idB [ 3 ];
	//print idA;//should print 7 GOOOOOOOOOOD Kappa
	
	//test case 2
	//idB [ 3 ] = 6 + 5;
	//idA = idB [ 3 ];
	//print idA;//should print 11 GOOOOOOOOOOOD

	//test case 3
	//idB[ 1 ] = 87;
	//idB[ 2 ] = 87;
	//idB[ 9 ] = idB[ 1 ] + idB[ 2 ];
	//idA = idB[9];
	//print idA;//print 174 GOOOOOOOOOOOOOOD
	
	//test case 4
	idC = 9;
	idB[3] = 19;
	idB[4] = idC + idB[3];
	
	idA = idB[4];
	print idA;//print 28 GOOOOOOOOOOOOOOOOOOOOD


    return 0 ;
}
