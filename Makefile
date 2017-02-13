.PHONY: clean All

All:
	@echo "----------Building project:[ uppgiftKap5 - Debug ]----------"
	@cd "uppgiftKap5" && "$(MAKE)" -f  "uppgiftKap5.mk" && "$(MAKE)" -f  "uppgiftKap5.mk" PostBuild
clean:
	@echo "----------Cleaning project:[ uppgiftKap5 - Debug ]----------"
	@cd "uppgiftKap5" && "$(MAKE)" -f  "uppgiftKap5.mk" clean
