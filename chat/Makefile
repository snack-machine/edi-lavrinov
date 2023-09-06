CC = gcc
FLAGS = -g
LIBS = -pthread

BUILD_FOLDER = build/

all: server client

server:
	bash -c "if [ ! -d "$(BUILD_FOLDER)" ]; then mkdir -p $(BUILD_FOLDER); fi"
	$(CC) $(FLAGS) $(LIBS) server.c utils.c -o $(BUILD_FOLDER)server

client:
	bash -c "if [ ! -d "$(BUILD_FOLDER)" ]; then mkdir -p $(BUILD_FOLDER); fi"
	$(CC) $(FLAGS) $(LIBS) client.c utils.c -o $(BUILD_FOLDER)client

clean:
	rm -r $(BUILD_FOLDER)
