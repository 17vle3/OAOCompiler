
int idMain ( ) {

    int idA ;
    int idB ;
	int idC ;
	//int idG [ 10 ];

	//idG[9] = 8;
	//idA = 1 + 4 + 5 + idG[9] + 8;
	//print idA;
	
    idA = 8;
	idB = 9;

	idC = 10;
	//success !!
	//if (idA + idB )
	//{
	//	print idA;
	//}
	//else
	//{
	//	print idB;
	//}

	//success ! Yabee
	if ((idB == 9) && (idA < idB))
	{
		idB = idA + idB;
		
		if(idB == idA)
		{
			print idC;
		}
		else
		{
			print idB;//should print 17
		}
	}
	else
	{
		print idA;
	}


    return 0 ;
}
