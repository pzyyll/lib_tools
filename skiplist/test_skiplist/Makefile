# Version 1.0
# Author Caizhili
# A simple c++ makefile template
#
# Version 2.0
# Author Caizhili
# Add suffix SRCSUFFIXS. Example ".cpp", ".cc".

TARGET     = test
CC         = g++
CPPFLAGS   = -std=gnu++11 -Wall -g3 -fPIC
LDFLAGS    = -lgtest_main -lgtest -lpthread #-lboost_system -lboost_thread -lboost_serialization
LDPATH     = $(ROOT_PATH)/googletest/cmake-build-debug/usr/lib/
SRC_SUFFIX = .cpp
SRC_DIRS   = . #./common/ext/test/
INC_DIRS   = . $(ROOT_PATH)/googletest/cmake-build-debug/usr/include/ $(ROOT_PATH)/skiplist/ #./common/ext/test/

LIB_PATH   := $(addprefix -L,$(LDPATH))
INCFLAGS   := $(addprefix -I,$(INC_DIRS))
COMPILE.cc := $(CC) $(CPPFLAGS) $(INCFLAGS) $(LIB_PATH)

ABS_SRCDIRS := $(abspath $(SRC_DIRS))
ABS_INCDIRS := $(abspath $(INC_DIRS))

SRCS := $(foreach v,$(ABS_SRCDIRS),$(wildcard $(addprefix $(v)/*,$(SRC_SUFFIX))))
OBJS := $(SRCS:.cpp=.o)
DEPS := $(SRCS:.cpp=.d)

## TARGET
.PHONY : all
all : $(TARGET)

.PHONY : $(TARGET)
$(TARGET) : $(OBJS)
	@echo "Build target "$@
	@$(COMPILE.cc) $^ $(LDFLAGS) -o $@ 

PAT_WILDCARD = $(addprefix %,$(SRC_SUFFIX))
%.o : $(PAT_WILDCARD) %.d
	@echo "Compliling $@"
	@$(COMPILE.cc) -c $< $(LDFLAGS) -o $@ 

## DEPS
%.d : $(PAT_WILDCARD)
	@echo "Create "$@;
	@set -e; rm -f $@; \
	$(COMPILE.cc) -MT $*.d -MP -MM $< -MF $@;

sinclude $(DEPS)

.PHONY : clean
clean:
	@rm -rf $(DEPS) $(OBJS) $(TARGET)
