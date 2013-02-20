#####generic conf
SRC_FILTER = .c
LIBS  = 
LIBS += 
CFLAGS = -I.
LDFLAGS =
CONF = .
SOURCES :=  $(shell find ./ -type f -name '*${SRC_FILTER}')
################

################target_specific conf

##### single target without a name - so we just call "make" without CONF=... for this target
ifeq ($(CONF),.)
#mkres := $(shell mkdir $(CONF))
CFLAGS += 
TARGET = w3d2ply
CC = gcc
LD = gcc
endif
####

################


OBJS := $(patsubst ./%${SRC_FILTER}, ${CONF}/%.o, $(SOURCES))

#all: post-build
#post-build: $(TARGET)
#   @echo post_build_step if you want to run somthing here like copy the binary to somewhere, etc.
#

all: $(TARGET)

$(TARGET): ${OBJS}
	$(LD) ${OBJS} ${LIBS} ${LDFLAGS} -o ${CONF}/"$(TARGET)"

${CONF}/%.o: %${SRC_FILTER}
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f ${CONF}/$(TARGET)
	rm -f $(OBJS)
