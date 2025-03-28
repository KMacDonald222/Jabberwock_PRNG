# File:		Makefile
# Author:	Keegan MacDonald
# Created:	2025.03.28
# Purpose:	Provide build directives for the four software products in the
# 			Jabberwock PRNG project

# Define compiler and archiver command constants
CPPC = g++ -Wall -Wextra -pedantic
AR = ar rcs

# Define libjabberwock project paths and commands
JLIB_TGT = bin/libjabberwock.a
JLIB_INC = -Iinclude/jabberwock/ -Ivendor/include/
JLIB_SRC = source/jabberwock/

# Define jtest project paths and commands
JTEST_TGT = bin/jtest
JTEST_INC = -Iinclude/ -Ivendor/include/
JTEST_SRC = source/jtest/
JTEST_LIB = -Lbin/ -ljabberwock -Lvendor/bin/ -lsha

# Build all software projects in the Jabberwock PRNG project
all:
	make $(JLIB_TGT)
	make $(JTEST_TGT)

# Build the libjabberwock project
$(JLIB_TGT): $(JLIB_SRC)utilities.o
	$(AR) $(JLIB_TGT) $(JLIB_SRC)utilities.o

$(JLIB_SRC)utilities.o: $(JLIB_SRC)utilities.cpp
	$(CPPC) $(JLIB_INC) -o $(JLIB_SRC)utilities.o -c $(JLIB_SRC)utilities.cpp

# Build the jtest project
$(JTEST_TGT): $(JTEST_SRC)jtest.o
	$(CPPC) -o $(JTEST_TGT) $(JTEST_SRC)jtest.o $(JTEST_LIB)

$(JTEST_SRC)jtest.o: $(JTEST_SRC)jtest.cpp
	$(CPPC) $(JTEST_INC) -o $(JTEST_SRC)jtest.o -c $(JTEST_SRC)jtest.cpp

# Remove build files
clean:
	-rm $(JLIB_TGT)
	-rm $(JLIB_SRC)*.o
	-rm $(JTEST_TGT)
	-rm $(JTEST_SRC)*.o