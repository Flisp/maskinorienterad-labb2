.PHONY: clean All

All:
	@echo "----------Building project:[ asciiDisplay - Debug ]----------"
	@cd "asciiDisplay" && "$(MAKE)" -f  "asciiDisplay.mk" && "$(MAKE)" -f  "asciiDisplay.mk" PostBuild
clean:
	@echo "----------Cleaning project:[ asciiDisplay - Debug ]----------"
	@cd "asciiDisplay" && "$(MAKE)" -f  "asciiDisplay.mk" clean
