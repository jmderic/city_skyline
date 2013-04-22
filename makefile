# $Id$

# make -k -r CXX=/home/mark/local/gcc-4.7.1/bin/g++ BOOST=/home/mark/local/boost_1_52_0

# BOOST= BOOST_HOME given on make line as BOOST

SRCS=main.cpp
OBJS=$(SRCS:%.cpp=%.o)
#COMMON_FLAGS=-g

all : city_skyline

%.o : %.cpp
	$(CXX) $(COMMON_FLAGS) -I$(BOOST)/include -c $< -o $@

$(OBJS) : makefile

city_skyline : $(OBJS)
	$(CXX) $(COMMON_FLAGS) -o $@  $^ -L$(BOOST)/lib -lboost_regex -lc

clean :
	rm -f city_skyline $(OBJS) *~
