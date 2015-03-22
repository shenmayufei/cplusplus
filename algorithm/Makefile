#
# main makefile
#
export BUILD_TYPE ?= release
export BUILD_HOME_DIR = $(shell pwd)
export BUILD_OUT_DIR  = $(BUILD_HOME_DIR)/bin/$(BUILD_TYPE)/
export BUILD_INCS = -I/usr/local/include  -I$(BUILD_HOME_DIR)/src/
export BUILD_LIBS =-L$(BUILD_OUT_DIR)  -lz
$(shell mkdir -p  $(BUILD_OUT_DIR))
# compiler options
ifeq ($(BUILD_TYPE), release)
        export CXX = g++ -fPIC -Wall -O2 -fno-strict-aliasing  -DTIME_OUT_INTERVAL=600 -DMAX_SEND_BUF_SIZE=1073741824 -D XT_STATIC -fexec-charset=GB2312
else
        export CXX = g++ -fPIC -Wall  -g -DDEBUG -fexec-charset=GB2312  -D XT_STATIC -D ORDER2TRADER_SERVICE 
endif

.PHONY: all
all : list stack queue


list:
	$(MAKE) -C src/list
list: 

stack:
	$(MAKE) -C src/stack
stack:

queue:
	$(MAKE) -C src/queue
queue:

.PHONY: clean
clean:
	cd src/list && $(MAKE) clean 
	cd src/stack && $(MAKE) clean
	cd src/queue && $(MAKE) clean
