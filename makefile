# $Id$

# make -k -r CXX=/home/mark/local/gcc-4.7.1/bin/g++ BOOST=/home/mark/local/boost_1_52_0

# BOOST= BOOST_HOME given on make line as BOOST

SRCS=main.cpp
OBJS=$(SRCS:%.cpp=%.o)

all : city_skyline

%.o : %.cpp
	$(CXX) -I$(BOOST)/include -c $< -o $@


city_skyline : $(OBJS)
	$(CXX) -o $@  $^ -L$(BOOST)/lib -lboost_regex -lc
