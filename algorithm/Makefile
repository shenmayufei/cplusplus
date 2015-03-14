#
# main makefile
#
export BUILD_TYPE = release
export BUILD_HOME_DIR = $(shell pwd)
export BUILD_OUT_DIR  = $(BUILD_HOME_DIR)/bin/$(BUILD_TYPE)/
export BUILD_INCS = -I$(BUILD_HOME_DIR)/src/XtTraderApi/ -I$(BUILD_HOME_DIR)/include -I/usr/local/include  -I$(BUILD_HOME_DIR)/libs/src/  -I$(BUILD_HOME_DIR)/ -I$(BUILD_HOME_DIR)/src/
export BUILD_LIBS =-L$(BUILD_OUT_DIR)  -lpthread -lz
$(shell mkdir -p  $(BUILD_OUT_DIR))
# compiler options
ifeq ($(BUILD_TYPE), release)
        #export CXX = g++ -fPIC -Wall -g -O2 -fno-strict-aliasing -fexec-charset=GB2312 -D XT_STATIC
        export CXX = g++ -fPIC -Wall -O2 -fno-strict-aliasing  -DTIME_OUT_INTERVAL=600 -DMAX_SEND_BUF_SIZE=1073741824 -D XT_STATIC -fexec-charset=GB2312
else
        export CXX = g++ -fPIC -Wall  -g -DDEBUG -fexec-charset=GB2312  -D XT_STATIC -D ORDER2TRADER_SERVICE 
        #export CXX = g++ -fPIC -Wall  -g -DDEBUG -DTIME_OUT_INTERVAL=600 -DMAX_SEND_BUF_SIZE=1073741824
endif

.PHONY: all
all : traderapi test

BASE = net utils  idata
base:$(BASE)
$(BASE):
	$(MAKE) -C libs/src/$@


traderapi:
	$(MAKE) -C src/XtTraderApi
traderapi:base protocol 

protocol:
	$(MAKE) -C Protocol

test: 
	$(MAKE) -C src/TestTraderApi

.PHONY: clean
clean:
	for project in $(BASE); do $(MAKE) clean -C libs/src/$$project; done
	cd src/XtTraderApi && $(MAKE) clean 
	cd src/TestTraderApi && $(MAKE) clean 
