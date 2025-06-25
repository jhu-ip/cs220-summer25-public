CXX = g++
CXXFLAGS = -g -Wall -Wextra -pedantic -std=c++11

phone_db : phone_db.o
	$(CXX) -o phone_db phone_db.o

phone_db.o : phone_db.cpp
	$(CXX) $(CXXFLAGS) -c phone_db.cpp -o phone_db.o
