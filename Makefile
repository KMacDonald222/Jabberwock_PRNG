# File:		Makefile
# Author:	Keegan MacDonald
# Created:	2025.03.28
# Purpose:	Provide build directives for the four software products in the
# 			Jabberwock PRNG project

# Define compiler and archiver command constants
CPPC = g++ -Wall -Wextra -pedantic -Ofast
AR = ar rcs

# Define libJabberwock project paths and commands
JLIB_TGT = Bin/libJabberwock.a
JLIB_INC = -IInclude/Jabberwock/ -IVendor/Include/
JLIB_SRC = Source/Jabberwock/

# Define JTest project paths and commands
JTEST_TGT = Bin/JTest
JTEST_INC = -IInclude/ -IVendor/Include/
JTEST_SRC = Source/JTest/
JTEST_LIB = -LBin/ -lJabberwock -LVendor/Bin/ -lsha

# Define JGen project paths and commands
JGEN_TGT = Bin/JGen
JGEN_INC = -IInclude/ -IVendor/Include
JGEN_SRC = Source/JGen/
JGEN_LIB = -LBin/ -lJabberwock -LVendor/Bin/ -lsha

# Define JOTP project paths and commands
JOTP_TGT = Bin/JOTP
JOTP_INC = -IInclude/ -IVendor/Include
JOTP_SRC = Source/JOTP/
JOTP_LIB = -LBin/ -lJabberwock -LVendor/Bin/ -lsha

# Build all software projects in the Jabberwock PRNG project
all:
	make $(JLIB_TGT)
	make $(JTEST_TGT)
	make $(JGEN_TGT)
	make $(JOTP_TGT)

# Build the libJabberwock project
$(JLIB_TGT): $(JLIB_SRC)Utilities.o $(JLIB_SRC)Abstract_Node.o \
	$(JLIB_SRC)XOR_Node.o $(JLIB_SRC)AND_Node.o $(JLIB_SRC)OR_Node.o \
	$(JLIB_SRC)LFSR_Node.o $(JLIB_SRC)Jabberwock.o
	$(AR) $(JLIB_TGT) $(JLIB_SRC)Utilities.o $(JLIB_SRC)Abstract_Node.o \
		$(JLIB_SRC)XOR_Node.o $(JLIB_SRC)AND_Node.o $(JLIB_SRC)OR_Node.o \
		$(JLIB_SRC)LFSR_Node.o $(JLIB_SRC)Jabberwock.o

$(JLIB_SRC)Utilities.o: $(JLIB_SRC)Utilities.cpp
	$(CPPC) $(JLIB_INC) -o $(JLIB_SRC)Utilities.o -c $(JLIB_SRC)Utilities.cpp

$(JLIB_SRC)Abstract_Node.o: $(JLIB_SRC)Abstract_Node.cpp
	$(CPPC) $(JLIB_INC) -o $(JLIB_SRC)Abstract_Node.o -c \
		$(JLIB_SRC)Abstract_Node.cpp

$(JLIB_SRC)XOR_Node.o: $(JLIB_SRC)XOR_Node.cpp
	$(CPPC) $(JLIB_INC) -o $(JLIB_SRC)XOR_Node.o -c $(JLIB_SRC)XOR_Node.cpp

$(JLIB_SRC)AND_Node.o: $(JLIB_SRC)AND_Node.cpp
	$(CPPC) $(JLIB_INC) -o $(JLIB_SRC)AND_Node.o -c $(JLIB_SRC)AND_Node.cpp

$(JLIB_SRC)OR_Node.o: $(JLIB_SRC)OR_Node.cpp
	$(CPPC) $(JLIB_INC) -o $(JLIB_SRC)OR_Node.o -c $(JLIB_SRC)OR_Node.cpp

$(JLIB_SRC)LFSR_Node.o: $(JLIB_SRC)LFSR_Node.cpp
	$(CPPC) $(JLIB_INC) -o $(JLIB_SRC)LFSR_Node.o -c $(JLIB_SRC)LFSR_Node.cpp

$(JLIB_SRC)Jabberwock.o: $(JLIB_SRC)Jabberwock.cpp
	$(CPPC) $(JLIB_INC) -o $(JLIB_SRC)Jabberwock.o -c $(JLIB_SRC)Jabberwock.cpp

# Build the JTest project
$(JTEST_TGT): $(JTEST_SRC)JTest.o
	$(CPPC) -o $(JTEST_TGT) $(JTEST_SRC)JTest.o $(JTEST_LIB)

$(JTEST_SRC)JTest.o: $(JTEST_SRC)JTest.cpp
	$(CPPC) $(JTEST_INC) -o $(JTEST_SRC)JTest.o -c $(JTEST_SRC)JTest.cpp

# Build the JGen project
$(JGEN_TGT): $(JGEN_SRC)JGen.o
	$(CPPC) -o $(JGEN_TGT) $(JGEN_SRC)JGen.o $(JGEN_LIB)

$(JGEN_SRC)JGen.o: $(JGEN_SRC)JGen.cpp
	$(CPPC) $(JGEN_INC) -o $(JGEN_SRC)JGen.o -c $(JGEN_SRC)JGen.cpp

# Build the JOTP project
$(JOTP_TGT): $(JOTP_SRC)JOTP.o
	$(CPPC) -o $(JOTP_TGT) $(JOTP_SRC)JOTP.o $(JOTP_LIB)

$(JOTP_SRC)JOTP.o: $(JOTP_SRC)JOTP.cpp
	$(CPPC) $(JOTP_INC) -o $(JOTP_SRC)JOTP.o -c $(JOTP_SRC)JOTP.cpp

# Remove build files
clean:
	-rm $(JLIB_TGT)
	-rm $(JLIB_SRC)*.o
	-rm $(JTEST_TGT)
	-rm $(JTEST_SRC)*.o
	-rm $(JGEN_TGT)
	-rm $(JGEN_SRC)*.o
	-rm $(JOTP_TGT)
	-rm $(JOTP_SRC)*.o