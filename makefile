# $Id$


# BOOST= BOOST_HOME given on make line as BOOST
# make -k -r CXX=/home/mark/local/gcc-4.7.1/bin/g++ BOOST=/home/mark/local/boost_1_52_0

# alternative: on debian/apt stock boost install headers are in /usr/include/boost, but libs are hidden in /usr/lib/x86_64-linux-gnu.  So, need to set BOOST_LIB
# make -k -r BOOST_LIB=/usr/lib/x86_64-linux-gnu

SRCS=main.cpp
OBJS=$(SRCS:%.cpp=%.o)
#COMMON_FLAGS=-g

all : city_skyline

%.o : %.cpp
	$(CXX) $(COMMON_FLAGS) -c $< -o $@

# $(CXX) $(COMMON_FLAGS) -I$(BOOST)/include -c $< -o $@

$(OBJS) : makefile

city_skyline : $(OBJS)
	$(CXX) $(COMMON_FLAGS) -o $@  $^ -L$(BOOST_LIB) -lboost_regex -lc

# $(CXX) $(COMMON_FLAGS) -o $@  $^ -L$(BOOST)/lib -lboost_regex -lc

clean :
	rm -f city_skyline $(OBJS) *~
