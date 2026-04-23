ifndef PRJ_DIR
	$(error [RULES] PRJ_DIR is not defined.)
endif

$(PRJ_DIR)/build/%.o: $(PRJ_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(PRJ_DIR)/build/%.o: $(PRJ_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(PRJ_DIR)/build/%.o: $(PRJ_DIR)/%.s
	@mkdir -p $(dir $@)
	$(AS) $(CFLAGS) -c $< -o $@

-include $(DEPS)
