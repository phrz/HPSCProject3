#
#  Makefile
#  HPSCProject3
#
#  Created by Paul Herz on 11/2/16.
#  Copyright © 2016 Paul Herz. All rights reserved.
#

TARGETA = newtonform
TARGETB = lagrange2d
TARGETC = runge_uniform
TARGETD = runge_chebyshev

CXX = g++
CFLAGS = -std=c++14

SRC = src/
LIB = lib/
BIN = bin/
ROOT = $(shell pwd)/
DATA = data/
NB = notebooks/
RP = reports/

AFILES = test_NewtonForm.cpp
BFILES = test_Lagrange2D.cpp
CFILES = runge_uniform.cpp
DFILES = runge_Chebyshev.cpp
LIBFILES = Vector.cpp Matrix.cpp

NOTEBOOKAB = $(NB)proj3.ipynb
NOTEBOOKCD = $(NB)Runge2D.ipynb
REPORTAB = $(RP)proj3.pdf
REPORTCD = $(RP)Runge2D.pdf



################################
# All target                   #
################################

all: all_bin all_data all_reports



################################
# Application binaries         #
################################

all_bin: $(TARGETA) $(TARGETB) $(TARGETC) $(TARGETD)

$(TARGETA):
	$(CXX) $(CFLAGS) -o $(BIN)$(TARGETA) -I $(LIB) $(addprefix $(LIB), $(LIBFILES)) $(addprefix $(SRC), $(AFILES))

$(TARGETB):
	$(CXX) $(CFLAGS) -o $(BIN)$(TARGETB) -I $(LIB) $(addprefix $(LIB), $(LIBFILES)) $(addprefix $(SRC), $(BFILES))

$(TARGETC):
	$(CXX) $(CFLAGS) -o $(BIN)$(TARGETC) -I $(LIB) $(addprefix $(LIB), $(LIBFILES)) $(addprefix $(SRC), $(CFILES))

$(TARGETD):
	$(CXX) $(CFLAGS) -o $(BIN)$(TARGETD) -I $(LIB) $(addprefix $(LIB), $(LIBFILES)) $(addprefix $(SRC), $(DFILES))


################################
# Data files                   #
################################

all_data: data_a data_b data_c data_d

data_a: $(TARGETA)
	cd $(BIN); ./$(TARGETA)

data_b: $(TARGETB)
	cd $(BIN); ./$(TARGETB)

data_c: $(TARGETC)
	cd $(BIN); ./$(TARGETC)

data_d: $(TARGETD)
	cd $(BIN); ./$(TARGETD)



################################
# Reports                      #
################################

all_reports: $(REPORTAB) $(REPORTCD)

$(REPORTAB): all_data $(NOTEBOOKAB)
	jupyter nbconvert --to pdf --execute $(NOTEBOOKAB) --output-dir $(ROOT)$(RP) --PDFExporter.latex_command="['xelatex','{filename}']"

$(REPORTCD): all_data $(NOTEBOOKCD)
jupyter nbconvert --to pdf --execute $(NOTEBOOKCD) --output-dir $(ROOT)$(RP) --PDFExporter.latex_command="['xelatex','{filename}']"

################################
# Miscellaneous                #
################################

clean:
	rm -f ./$(DATA)*/*.txt
	rm -f ./$(BIN)$(TARGETA)
	rm -f ./$(BIN)$(TARGETB)
	rm -f ./$(BIN)$(TARGETC)
	rm -f ./$(NB)*.nbconvert.ipynb

