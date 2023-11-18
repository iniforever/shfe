
CXX=g++
OUT_NAME=efh3_recv_lev2

OUT_PATH=./bin/
SRC_PATH=./
OBJ_PATH=./obj/

DEBUG_PATH=debug/
RELEASE_PATH=release/

LIB_DEBUG_FILE= -lpthread -lrt -ldl -lciul1 -l onload_ext

LIB_RELEASE_FILE=-lpthread -lrt -ldl -lciul1 -l onload_ext

SRC_FILE=$(wildcard $(SRC_PATH) *.cpp)
ALL_FILE=$(notdir $(SRC_FILE))
OBJ_FILE=$(patsubst %.cpp,%.o,$(ALL_FILE))

DEBUG_CXXFLAGS=-g -ggdb3 -Wall -fPIC
RELEASE_CXXFLAGS=-O2 -fPIC -lrt

DEBUG_ARFLAGS=cqs
RELEASE_ARFLAGS=cqs

OUT_DEBUG_FILE=$(OUT_PATH)$(DEBUG_PATH)$(OUT_NAME)
OBJ_DEBUG_FILE=$(addprefix  $(OBJ_PATH)$(DEBUG_PATH),$(notdir $(OBJ_FILE)))

OUT_RELEASE_FILE=$(OUT_PATH)$(RELEASE_PATH)$(OUT_NAME)
OBJ_RELEASE_FILE=$(addprefix  $(OBJ_PATH)$(RELEASE_PATH),$(notdir $(OBJ_FILE)))

debug : pre_debug $(OUT_DEBUG_FILE)

release : per_release $(OUT_RELEASE_FILE)

all : debug release

pre_debug :
	-$(shell mkdir $(OBJ_PATH) -p)
	-$(shell mkdir $(OBJ_PATH)$(DEBUG_PATH) -p)
	-$(shell mkdir $(OUT_PATH) -p)
	-$(shell mkdir $(OUT_PATH)$(DEBUG_PATH) -p)
	-$(shell mkdir $(OUT_PATH)$(DEBUG_PATH)log/ -p)

per_release :
	-$(shell mkdir $(OBJ_PATH) -p)
	-$(shell mkdir $(OBJ_PATH)$(RELEASE_PATH) -p)
	-$(shell mkdir $(OUT_PATH) -p)
	-$(shell mkdir $(OUT_PATH)$(RELEASE_PATH) -p)

$(OUT_DEBUG_FILE) : $(OBJ_DEBUG_FILE)
	$(CXX) $(DEBUG_CXXFLAGS) $(addprefix  $(OBJ_PATH)$(DEBUG_PATH),$(notdir $^)) -o $@ $(LIB_DEBUG_FILE) 

$(OUT_RELEASE_FILE) : $(OBJ_RELEASE_FILE)
	$(CXX) $(RELEASE_CXXFLAGS) $(addprefix  $(OBJ_PATH)$(RELEASE_PATH),$(notdir $^)) -o $@ $(LIB_RELEASE_FILE)

$(OBJ_PATH)$(DEBUG_PATH)%.o : %.cpp
	$(CXX) -c $(DEBUG_CXXFLAGS) $(INC_DEBUG_PATH) $(SRC_PATH)$< -o $@
	
$(OBJ_PATH)$(RELEASE_PATH)%.o : %.cpp
	$(CXX) -c $(RELEASE_CXXFLAGS) $(INC_RELEASE_PATH) $(SRC_PATH)$< -o $@
	
clean :
	@echo  "make clean"
	$(shell rm $(OBJ_PATH) -rf)
	$(shell rm $(OUT_PATH)$(DEBUG_PATH)$(OUT_NAME) -f)
	$(shell rm $(OUT_PATH)$(RELEASE_PATH)$(OUT_NAME) -f)
