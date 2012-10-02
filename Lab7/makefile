CXX = g++
CXXFLAGS = -pedantic -Wall -Werror -Wno-sign-compare -Wno-long-long -lm

lab7: MoneyBox.o Parser.o Common.o main.o
	$(CXX) $(CXXFLAGS) -o lab7 MoneyBox.o Parser.o Common.o main.o

clean :
	rm *.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

Parser.o : Parser.cpp
	$(CXX) $(CXXFLAGS) -c Parser.cpp

Common.o : Common.cpp
	$(CXX) $(CXXFLAGS) -c Common.cpp

MoneyBox.o : MoneyBox.cpp
	$(CXX) $(CXXFLAGS) -c MoneyBox.cpp

