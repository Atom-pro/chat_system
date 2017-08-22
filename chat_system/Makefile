ROOT_PATH=$(shell pwd)
SERVER_PATH=$(ROOT_PATH)/server
CLIENT_PATH=$(ROOT_PATH)/client
WINDOW_PATH=$(ROOT_PATH)/window
CONF_PATH=$(ROOT_PATH)/conf
COMM_PATH=$(ROOT_PATH)/commen
LIB_PATH=$(ROOT_PATH)/lib
LOG_PATH=$(ROOT_PATH)/log
DATA_POOL_PATH=$(ROOT_PATH)/data_pool
cc=g++

FLAGS=-D_FAST_
LDFLAGS=#-static

INCLUDE_PATH=-I$(SERVER_PATH) -I$(DATA_POOL_PATH) -I$(LOG_PATH) -I$(COMM_PATH) -I$(LIB_PATH)/include -I$(WINDOW_PATH)

JSON_PATH=-L$(LIB_PATH)/lib
lib=-lpthread -ljson_linux-gcc-4.4.7_libmt

SERVER_BIN=udpServer
CLIENT_BIN=udpClient

SERVER_SRC=$(shell ls $(SERVER_PATH) $(DATA_POOL_PATH) $(LOG_PATH) $(COMM_PATH)| egrep -v '^.*\.h'|egrep '.*\.cpp')
CLIENT_SRC=$(shell ls $(CLIENT_PATH) $(LOG_PATH) $(COMM_PATH) $(WINDOW_PATH)| egrep -v '^.*\.h'|egrep '.*\.cpp')

SERVER_OBJ=$(shell echo $(SERVER_SRC) | sed 's/\.cpp/.o/g')
CLIENT_OBJ=$(shell echo $(CLIENT_SRC) | sed 's/\.cpp/.o/g')

.PHONY:all
all:$(SERVER_BIN) $(CLIENT_BIN)

$(SERVER_BIN):$(SERVER_OBJ)
	@echo "Link [$^] to [$@] ..."
	$(cc) -o $@ $^  $(JSON_PATH) $(lib) $(LDFLAGS)
	@echo "Link done ..."
%.o:$(SERVER_PATH)/%.cpp
	@echo "Compling [$<] to [$@] ..."
	$(cc) -c $< $(INCLUDE_PATH) 
$(CLIENT_BIN):$(CLIENT_OBJ)
	@echo "Link [$^] to [$@] ..."
	$(cc) -o $@ $^  $(JSON_PATH) $(lib) $(LDFLAGS) -lncurses
	@echo "Link done ..."
%.o:$(CLIENT_PATH)/%.cpp
	@echo "Compling [$<] to [$@] ..."
	$(cc) -c $< $(INCLUDE_PATH)

%.o:$(DATA_POOL_PATH)/%.cpp
	@echo "Compling [$<] to [$@] ..."
	$(cc) -c $< $(INCLUDE_PATH)

%.o:$(LOG_PATH)/%.cpp
	@echo "Compling [$<] to [$@] ..."
	$(cc) -c $< $(INCLUDE_PATH)
%.o:$(COMM_PATH)/%.cpp
	@echo "Compling [$<] to [$@] ..."
	$(cc) -c $< $(INCLUDE_PATH)
%.o:$(WINDOW_PATH)/%.cpp
	@echo "Compling [$<] to [$@] ..."
	$(cc) -c $< $(INCLUDE_PATH)
.PHONY:clean
clean:
	rm -rf $(SERVER_BIN) $(CLIENT_BIN) *.o output

.PHONY:output
output:
	mkdir -p output/log
	cp $(SERVER_BIN) output
	cp $(CLIENT_BIN) output
	cp -rf conf output
	cp server_ctl.sh output	

.PHONY:debug
debug:
	@echo $(SERVER_SRC)
	@echo $(CLIENT_SRC)
	@echo $(CLIENT_OBJ)
	@echo $(SERVER_OBJ)
