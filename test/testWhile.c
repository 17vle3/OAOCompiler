int idMain ()
{
	int idA;
	int idLoop;
	int idB;
	
	idA = 10;
	idB = 20;
	idLoop = 0;
	
	//passed
	//while ( idA > 0 )
	//{
	//	idLoop = idLoop + 1;
	//	idA = idA - 1;
	//}
	
	//print idLoop;//print 10

	//EXCELLLLLLLLLLLLLENT
	while(idA > 0)
	{
		idA = idA - 1;
		
		while(idB > 0)
		{
			idB = idB - 1;
			idLoop = idLoop + 1;
		}
		idB = 20;

	}

	print idLoop ;//should print 200
}
