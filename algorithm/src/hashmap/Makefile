PROGRAM = hashmap
LIBS    = -L$(BUILD_OUT_DIR)
SOURCE  = $(wildcard *.cpp) $(wildcard */*.cpp) $(wildcard */*/*.cpp) $(wildcard */*/*/*.cpp)
OBJS = $(patsubst %.cpp,%.o, $(SOURCE)) 

%.o: %.cpp
	$(CXX) -c $(BUILD_INCS) $(FORCE_INCLUDE) -o $@ $?

$(PROGRAM):$(OBJS)
	$(CXX) -o $(BUILD_OUT_DIR)/$@ $^ $(LIBS) $(BUILD_LIBS)

clean:
	rm -f $(OBJS) $(BUILD_OUT_DIR)/$(PROGRAM)
