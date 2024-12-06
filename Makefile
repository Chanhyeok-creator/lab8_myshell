PROJ_DIR = $(shell pwd)
SRC_DIR = $(PROJ_DIR)/src
INC_DIR = $(PROJ_DIR)/include
OBJ_DIR = $(PROJ_DIR)/obj
BIN_DIR = $(PROJ_DIR)/bin

# 최종 실행 파일
TARGET = $(BIN_DIR)/myshell

# 소스 파일 목록
SRC_FILES = $(SRC_DIR)/myshell.c $(SRC_DIR)/ls_command.c $(SRC_DIR)/hello.c
OBJ_FILES = $(OBJ_FILES:.c=.o)

# 목표: myshell 실행 파일
$(TARGET): $(OBJ_DIR)/myshell.o $(OBJ_DIR)/ls_command.o $(OBJ_DIR)/hello.o | $(BIN_DIR)
	gcc -o $@ $^ -I$(INC_DIR)

# 생성된 디렉토리
$(BIN_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	gcc -c -o $@ $< -I$(INC_DIR)

$(OBJ_DIR):
	mkdir -p $@

# clean: 빌드된 파일들 제거
clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/myshell

# distclean: 빌드 파일 및 생성된 디렉토리들 제거
distclean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/myshell
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# 실행: myshell 실행
run: $(TARGET)
	$(TARGET)

