WORKING_DIR			:= ./build

# 构建
default:
	mkdir -p $(WORKING_DIR) && pushd $(WORKING_DIR); \
	cmake ..; \
	make;

# 清空所有构建
clean:
	rm -rf $(WORKING_DIR)
