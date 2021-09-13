#include "tests.h"
#include "production.h"
#include "LinkedList.h"


bool tests()
{
	bool answer = false;

	//test the functions that get used
	//order the tests from simplest first -- this produces building blocks for use in more complex tests
	//check how functions are used in production code, this gives clues about how to provide the arguments for the invocation
	bool ok1 = testReadFile(); //done???
	bool ok2 = testGotAdjacencyMatrix(); // jh
	bool ok3 = testMakeLList(); // jp
	bool ok4 = testRemoveFromList();// not needed
	bool ok5 = testPrintHistory(); // g
	bool ok6 = testSavePayload(); //save payload // g
	//bool ok7 = testGetEdge(); // getedge // a
	//bool ok8 = testDequeLIFO(); // dequeLIFO // jp
	answer = ok1 && ok2 && ok3 && ok4 && ok5 && ok6;
	//answer = true;
	return answer;
}

bool testReadFile()
{
	puts("starting testReadFile"); fflush(stdout);
	bool ok = false;
	//the file tells how many rooms there are
	int answer = -1;
	int rightAnswer = 8;

	AdjMat* adjMP = (AdjMat*) malloc(sizeof(AdjMat));
	Room* theRoomPs[10];//addresses for 10 rooms

	char* fname = "houseGraph.txt";
	printf("Sizeof |%s| is %d.\n", fname, (int)strlen(fname));

	ok = readFile("houseGraph.txt", &answer, adjMP, theRoomPs); //read the file
	if(ok)
	{
		if(answer!=rightAnswer)
		{
			puts("test failed on number of rooms");
		}
		else
		{
			puts("read file succeeded on number of rooms");
		}

	}
	else
	{
		puts("test failed on finding file");
	}
	puts("The adjacency matrix");
	for(int i = 0; i<answer; i++)
	{
		for(int j = 0; j<answer; j++)
		{
			printf("%d",getEdge(adjMP, i, j));

		}
		printf("\n");
	}
	puts("The treasure values");
	for(int i = 0; i<answer; i++)
	{
		printf("%f\n", theRoomPs[i]->treasure);
	}


	return ok;
}

bool testGotAdjacencyMatrix()
{
	bool ans = true;



	return ans;
}

bool testMakeLList()
{
	bool ok = true;
	puts("starting testMakeLList");fflush(stdout);
	//what are the criteria for success for make LList?
	//should be able to make one, add data to it, get the data back
	//test case 1:
	LLNode* theListP = makeEmptyLinkedList();
	bool rightAnswer = true;
	bool answer = isEmpty(theListP);
	if(answer!=rightAnswer)
	{
		ok = false;
	}
	//test case 2:
	//TODO more test cases here
	if(ok)
	{
		puts("test make LList did pass");
	}
	else
	{
		puts("test make LList did not pass.");
	}

	return ok;
}
bool testRemoveFromList()
{
	bool ok = true;
	//cases:
	//1 list is empty:return same list
	//2 list is of length one, and item is present: return empty list
	//3 list is of length one, and item is not present: return same list
	//4 list is longer than one, item is present, at first location: return list starting at second element
	//5 list is longer than one, item is present, not at first location: return list with item removed
	//6 list is longer than one, item is not present: return same list
	LLNode* case1 = makeEmptyLinkedList();
	Payload* pay1 = (Payload*) malloc(sizeof(Room));
	pay1->roomNumber = 1;
	LLNode* ans = removeFromList(case1, pay1);
	if((ans != case1) || (ans->payP != (Payload*)0))
	{
		ok = false;

	}
	printf("testRemove case 1 with %d\n", ok); fflush(stdout);
	savePayload(case1, pay1);
	//this is case2
	ans = removeFromList(case1, pay1);
	if((ans != case1) || (ans->payP != (Payload*)0))
	{
		ok = false;

	}
	printf("testRemove case 2 with %d\n", ok); fflush(stdout);
	//now case 3
	Payload* pay3 = (Payload*) malloc(sizeof(Room));
	pay3->roomNumber = 3;
	ans = removeFromList(case1, pay3);
	if(ans != case1)//this is only a partial check for list unchanged
	{
		ok = false;

	}
	printf("testRemove case 3 with %d\n", ok); fflush(stdout);
	//now case 4
	case1 = makeEmptyLinkedList();
	pay1 = (Payload*) malloc(sizeof(Room));
	pay1->roomNumber = 1;
	savePayload(case1, pay1);
	pay3 = (Payload*) malloc(sizeof(Room));
	pay3->roomNumber = 3;
	savePayload(case1, pay3);
	ans = removeFromList(case1, pay1);

	if(ans == case1)
	{
		ok = false;

	}
	printf("testRemove case 4 with %d\n", ok); fflush(stdout);
	//now case 5
	case1 = makeEmptyLinkedList();
	pay1 = (Payload*) malloc(sizeof(Room));
	pay1->roomNumber = 1;
	savePayload(case1, pay1);
	pay3 = (Payload*) malloc(sizeof(Room));
	pay3->roomNumber = 3;
	savePayload(case1, pay3);
	//puts("trying case 5");fflush(stdout);
	ans = removeFromList(case1, pay3);//ans should be equal to case1
	LLNode* theNext = (LLNode*) ans->next; //this is element where pay3 got attached
	Payload* check = (Payload*) 0;
	if (theNext)
	{
		check = theNext->payP; //this should be pay3, which should have been removed
	}
	//printf("testRemove returned from case 5\n"); fflush(stdout);
	if((ans != case1) || (check != (Payload*)0))//disquiet
	{
		ok = false;

	}
	//printf("ans == case1 is %d\n", ans==case1);
	//printf("check != 0 is %d\n", check != (Payload*)0);
	printf("testRemove case 5 with %d\n", ok); fflush(stdout);
	//now case 6
	case1 = makeEmptyLinkedList();
	pay1 = (Payload*) malloc(sizeof(Room));
	pay1->roomNumber = 1;
	savePayload(case1, pay1);
	pay3 = (Payload*) malloc(sizeof(Room));
	pay3->roomNumber = 3;
	savePayload(case1, pay3);
	Payload* another = (Payload*) malloc(sizeof(Room));
	another->roomNumber=2;
	ans = removeFromList(case1, another);
	if((ans != case1))
	{
		ok = false;

	}
	printf("testRemove case 6 with %d\n", ok); fflush(stdout);
	return ok;
}
bool testPrintHistory()
{
	puts("starting testPrintHistory"); fflush(stdout);
	bool ok = true;
	LLNode2* historyP2 = makeEmptyLinkedList2();
	float treasureSubtotal = 5.1;
	int room = 0;
	int answer = -1;
	int rightAnswer = 8;

//	printHistory();
	if(ok)

	{
		puts("testPrintHistory did pass");
	}
	else
	{
		puts("testPrintHistory did not pass.");

	}
	return ok;
}

bool testGetEdge()
{
	puts("starting testReadFile"); fflush(stdout);
	bool ok = false;
	int answer = -1;
	int rightAnswer = 8;

	AdjMat* adjMP = (AdjMat*) malloc(sizeof(AdjMat));
	Room* theRoomPs[10];//addresses for 10 rooms

	char* fname = "houseGraph.txt";
	printf("Sizeof |%s| is %d.\n", fname, (int)strlen(fname));

	ok = readFile("houseGraph.txt", &answer, adjMP, theRoomPs); //read the file
	if(ok)
	{
		if(answer!=rightAnswer)
		{
			puts("test failed on number of rooms");
		}
		else
		{
			puts("read file succeeded on number of rooms");
		}

	}
	else
	{
		puts("test failed on finding file");
	}
	puts("The adjacency matrix");
	for(int i = 0; i<answer; i++)
	{
		for(int j = 0; j<answer; j++)
		{
			printf("%d",getEdge(adjMP, i, j));

		}
		printf("\n");
	}
	puts("The treasure values");
	for(int i = 0; i<answer; i++)
	{
		printf("%f\n", theRoomPs[i]->treasure);
	}


	return ok;
}

bool testSavePayload()
{
	bool ok = true;
	LLNode2* historyP = makeEmptyLinkedList2();
	SearchResults* srP = (SearchResults*) malloc(sizeof(SearchResults));
	srP->roomNumber= 0;
	srP->treasure = 13.6;
	savePayload2(historyP, srP);
	float rightAnswer = 13.6;
	//we are going to look through the list to find this value
	Payload2* payP= historyP->payP;
	float answer = payP ->treasure;
	float tol= 0.01;
	if((rightAnswer- tol<answer) && (answer<rightAnswer + tol))
	{

	}
	else
	{
		ok = false;
	}
	if(ok)
	{

		puts("test savePayload passed");
	}
	else
	{
		puts("testSavePayload failed");
	}

return ok;
}






