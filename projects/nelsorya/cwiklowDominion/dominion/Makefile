CFLAGS= -w -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
 
cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

randomtestvillage: randomtestvillage.c dominion.o rngs.o
	gcc -o randomtestvillage -g  randomtestvillage.c dominion.o rngs.o $(CFLAGS)

randomtestgreat_hall: randomtestgreat_hall.c dominion.o rngs.o
	gcc -o randomtestgreat_hall -g  randomtestgreat_hall.c dominion.o rngs.o $(CFLAGS)

unittestresults: dominion.o unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	@echo "Unit Test1 whoseTurn function" > unittestresults.out
	@echo "" >> unittestresults.out
	./unittest1 >> unittestresults.out
	@echo "" >> unittestresults.out
	@echo "Unit Test2 handCard function" >> unittestresults.out
	@echo "" >> unittestresults.out
	./unittest2 >> unittestresults.out
	@echo "" >> unittestresults.out
	@echo "Unit Test3 isGameOver function" >> unittestresults.out
	@echo "" >> unittestresults.out
	./unittest3 >> unittestresults.out
	@echo "" >> unittestresults.out
	@echo "Unit Test4 fullDeckCount function" >> unittestresults.out
	@echo "" >> unittestresults.out
	./unittest4 >> unittestresults.out
	@echo "" >> unittestresults.out
	@echo "Card Test1 smith function" >> unittestresults.out
	@echo "" >> unittestresults.out
	./cardtest1 >> unittestresults.out
	@echo "" >> unittestresults.out
	@echo "Card Test2 adventurer function" >> unittestresults.out
	@echo "" >> unittestresults.out
	./cardtest2 >> unittestresults.out
	@echo "" >> unittestresults.out
	@echo "Card Test3 village function" >> unittestresults.out
	@echo "" >> unittestresults.out
	./cardtest3 >> unittestresults.out
	@echo "" >> unittestresults.out
	@echo "Card Test4 great_hall function" >> unittestresults.out
	@echo "" >> unittestresults.out
	./cardtest4 >> unittestresults.out
	@echo "" >> unittestresults.out
	@echo "Gcov Function and Branch Summaries" >> unittestresults.out
	@echo "" >> unittestresults.out
	gcov -f -b dominion.c >> unittestresults.out
	@echo "" >> unittestresults.out
	@echo "Gcov Branch Coverage Details" >> unittestresults.out
	@echo "" >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

randomtestresults: dominion.o randomtestadventurer randomtestvillage randomtestgreat_hall
	@echo "Random Test adventurerEffect function" > randomtestadventurer.out
	@echo "" >> randomtestadventurer.out
	./randomtestadventurer >> randomtestadventurer.out
	@echo "" >> randomtestadventurer.out
	@echo "Gcov Function and Branch Summaries" >> randomtestadventurer.out
	@echo "" >> randomtestadventurer.out
	gcov -f -b dominion.c >> randomtestadventurer.out
	@echo "" >> randomtestadventurer.out
	@echo "Gcov Branch Coverage Details" >> randomtestadventurer.out
	@echo "" >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out
	@echo "Random Test villageEffect function" > randomtestvillage.out
	@echo "" >> randomtestvillage.out
	./randomtestvillage >> randomtestvillage.out
	@echo "" >> randomtestvillage.out
	@echo "Gcov Function and Branch Summaries" >> randomtestvillage.out
	@echo "" >> randomtestvillage.out
	gcov -f -b dominion.c >> randomtestvillage.out
	@echo "" >> randomtestvillage.out
	@echo "Gcov Branch Coverage Details" >> randomtestvillage.out
	@echo "" >> randomtestvillage.out
	cat dominion.c.gcov >> randomtestvillage.out
	@echo "Random Test great_hall Effect function" > randomtestgreat_hall.out
	@echo "" >> randomtestgreat_hall.out
	./randomtestgreat_hall >> randomtestgreat_hall.out
	@echo "" >> randomtestgreat_hall.out
	@echo "Gcov Function and Branch Summaries" >> randomtestgreat_hall.out
	@echo "" >> randomtestgreat_hall.out
	gcov -f -b dominion.c >> randomtestgreat_hall.out
	@echo "" >> randomtestgreat_hall.out
	@echo "Gcov Branch Coverage Details" >> randomtestgreat_hall.out
	@echo "" >> randomtestgreat_hall.out
	cat dominion.c.gcov >> randomtestgreat_hall.out

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

       

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe 
