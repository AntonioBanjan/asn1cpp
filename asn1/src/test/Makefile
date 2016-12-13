
CPP          = g++

DEL_FILE     = rm -f

LINK         = g++

CFLAGS       = -Wall -W -funsigned-char -g -pthread -std=c++11

LIBS         = -lc -ldl 

INCPATH      = -I./include -I../../target/dev/test/dep-include -I../main/include

DEFINES      = -DLINUX -DUNIX -D__GXX_EXPERIMENTAL_CXX0X__  -D_GLIBCXX_USE_NANOSLEEP -D_GLIBCXX_USE_C99_STDINT_TR1 -D_GLIBCXX_USE_GETTIMEOFDAY

LPATH        = -L../../target/dev/test/dep-bin

SRCDIR       = c++/

OPATH        = ../../target/dev/test/bin/

OBJDIR       = ../../target/dev/test/objects/

LIB_PATH     = ../../target/dev/test/dep-bin

ARTIFACT     = asn1-test

STATIC_LIB_PATH = $(LIB_PATH)/static/

DYNAMIC_LIB_PATH = $(LIB_PATH)/dynamic/

SOURCES := $(wildcard $(SRCDIR)*.cpp)

OBJECTS := $(patsubst $(SRCDIR)%, $(OBJDIR)%, $(SOURCES:.cpp=.o))

STATIC_LIBS := $(wildcard $(STATIC_LIB_PATH)*.a)

SHARED_OBJECTS := $(wildcard $(DYNAMIC_LIB_PATH)*.so)

DYNAMIC_LIBS := $(patsubst $(DYNAMIC_LIB_PATH)lib%.so, -l%, $(SHARED_OBJECTS)) 

all: $(ARTIFACT)


$(ARTIFACT): $(OBJECTS)
	@echo $(CURDIR)
	@echo $(SOURCES)
	
	-@test -d $(OPATH) || mkdir $(OPATH)
	$(LINK) $(INCPATH) $(DEFINES) -o $(OPATH)$(ARTIFACT) $(OBJECTS) ../../target/dev/bin/libasn1.a  $(CFLAGS) $(STATIC_LIBS) -L$(DYNAMIC_LIB_PATH) $(DYNAMIC_LIBS)

clean:
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) $(OPATH)test-app
	
$(OBJDIR)%.o: $(SRCDIR)%.cpp
	-@test -d $(OBJDIR) || mkdir $(OBJDIR)
	$(CPP) -c $(CFLAGS) $(INCPATH) $(DEFINES) $< -o $@
