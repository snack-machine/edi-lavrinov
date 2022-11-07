CC = gcc

BUILD_FOLDER = build/

all: server client

server:
	bash -c "if [ ! -d "$(BUILD_FOLDER)" ]; then mkdir -p $(BUILD_FOLDER); fi"
	$(CC) server.c utils.c -o $(BUILD_FOLDER)server

client:
	bash -c "if [ ! -d "$(BUILD_FOLDER)" ]; then mkdir -p $(BUILD_FOLDER); fi"
	$(CC) client.c utils.c -o $(BUILD_FOLDER)client

clean:
	rm -r $(BUILD_FOLDER)
