.PHONY: lexer_tests
lexer_tests:
	@echo "--- Lexer tests ---"
	cd lexer_tests && ./run_lexer_tests.sh
	@echo "\n"

.PHONY: interface_tests
interface_tests:
	@echo "--- Inteface tests ---"
	cd interface_tests && ./run_interface_tests.sh
	@echo "\n"

.PHONY: tests
tests: lexer_tests interface_tests
	@echo "All tests finished."
