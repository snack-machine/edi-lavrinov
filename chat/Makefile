CC = gcc

LIBS = -pthread

BUILD_FOLDER = build/

all: server client

server:
	bash -c "if [ ! -d "$(BUILD_FOLDER)" ]; then mkdir -p $(BUILD_FOLDER); fi"
	$(CC) $(LIBS) server.c utils.c -o $(BUILD_FOLDER)server

client:
	bash -c "if [ ! -d "$(BUILD_FOLDER)" ]; then mkdir -p $(BUILD_FOLDER); fi"
	$(CC) $(LIBS) client.c utils.c -o $(BUILD_FOLDER)client

clean:
	rm -r $(BUILD_FOLDER)
