CPU := $(shell uname -p)
ifeq ($(CPU),arm)
export LD_LIBRARY_PATH=/opt/homebrew/lib/:$LD_LIBRARY_PATH
INCD = -I /opt/homebrew/include/
LIBD = -L /opt/homebrew/lib/
endif

CC := gcc
SRCD := src
TSTD := tests
BLDD := build
BIND := bin
INCD += -I include

ALL_SRCF := $(shell find $(SRCD) -type f -name '*.c')
ALL_OBJF := $(patsubst $(SRCD)/%,$(BLDD)/%,$(ALL_SRCF:.c=.o))
FUNC_FILES := $(filter-out build/main.o, $(ALL_OBJF))
TEST_SRC := $(shell find $(TSTD) -type f -name '*.c')
TEST_OBJ := $(patsubst $(TSTD)/%,$(BLDD)/%,$(TEST_SRC:.c=.o))

TEST := unit_tests


CFLAGS := -Wall -Wextra -Wshadow -Wdouble-promotion -Wformat=2 -Wundef -pedantic
GCOV := -fprofile-arcs -ftest-coverage
DFLAGS := -g -DDEBUG
PRINT_STATEMENTS := -DERROR -DSUCCESS -DWARN -DINFO

STD := -std=gnu11
TEST_LIB := -lcriterion
LIBS := -lm

CFLAGS += $(STD)
CFLAGS += $(GCOV)
CFLAGS += $(DFLAGS)

TEST_RESULTS := "test_results.json"
OCLINT_REPORT := "oclint_report.html"
GCOV_REPORT := "matrix.c.gcov"

all:; @$(MAKE) _all -j
_all: setup $(BIND)/$(TEST) $(ALL_OBJF)

debug: CFLAGS += $(DFLAGS) $(PRINT_STATEMENTS) 
debug: all

setup: $(BIND) $(BLDD)
$(BIND):
	mkdir -p $(BIND)
$(BLDD):
	mkdir -p $(BLDD)

SRC_CFLAGS := $(CFLAGS) -DSTUDENT_MAIN

$(BIND)/$(TEST): $(FUNC_FILES) $(TEST_OBJ)
	$(CC) $(SRC_CFLAGS) $(INCD) $(FUNC_FILES) $(TEST_OBJ) $(TEST_LIB) $(LIBD) -o $@ $(LIBS)

$(BLDD)/%.o: $(TSTD)/%.c
	$(CC) $(CFLAGS) $(INCD) -c -o $@ $<

$(BLDD)/%.o: $(SRCD)/%.c 
	$(CC) $(SRC_CFLAGS) $(INCD) -c -o $@ $<

check:
	oclint -report-type html -o oclint_report.html -rc SHORT_VARIABLE_NAME=1 -rc LONG_LINE=120--enable-clang-static-analyzer $(ALL_SRCF) -- $(INCD) -DNDEBUG
	cppcheck $(ALL_SRCF)

test: 
	@rm -fr $(TSTD).out
	@mkdir -p $(TSTD).out
	@$(BIND)/$(TEST) -j1 --full-stats --verbose --json=$(TEST_RESULTS)

gcov:
	@gcov matrix.o -o build -s src > /dev/null 2>&1
	@echo Generated unit test coverage report for matrix.c. See $(GCOV_REPORT)
	
clean:
	rm -fr $(BLDD) $(BIND) $(TSTD).out *.out $(OCLINT_REPORT) $(GCOV_REPORT) $(TEST_RESULTS)

.PHONY: all clean debug setup test