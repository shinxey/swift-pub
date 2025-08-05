#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define SP_IMPLEMENTATION
#include "../swift_pub.h"

char *token_descriptions[SP_TOK_KIND_UNKNOWN + 1] = {
	// need to update this when SpTokenKind enum changes
	"SP_TOK_KIND_EOF", // end of file

	"SP_TOK_KIND_ID",

	// keywords
	"SP_TOK_KIND_FUNC",
	"SP_TOK_KIND_PUBLIC",
	"SP_TOK_KIND_PRIVATE",
	"SP_TOK_KIND_OPEN",
	"SP_TOK_KIND_INTERNAL",
	"SP_TOK_KIND_INIT",
	"SP_TOK_KIND_CLASS",
	"SP_TOK_KIND_STRUCT",
	"SP_TOK_KIND_ACTOR",

	"SP_TOK_KIND_KEY_END",

	// single char tokens
	"SP_TOK_KIND_OPEN_BR", // '('
	"SP_TOK_KIND_CLOSING_BR", // ')'
	"SP_TOK_KIND_OPEN_CBR", // '{'
	"SP_TOK_KIND_CLOSING_CBR", // '}'
	"SP_TOK_KIND_OPEN_SBR", // '['
	"SP_TOK_KIND_CLOSING_SBR", // ']'
	"SP_TOK_KIND_LESS_THAN", // '<'
	"SP_TOK_KIND_MORE_THAN", // '>'

	"SP_TOK_KIND_UNKNOWN",
};

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Usage: lexer_test path/to/file.swift");
		return 1;
	}

	char* filename = argv[1];

	SpInputBuf *buf = sp_input_buf_create();

	if (!buf) {
		printf("out of memory\n");
		return 1;
	}

	int res = sp_input_buf_open(buf, filename);

	if (res != 0) {
		printf("encountered error while opening file\n");
		sp_input_buf_destroy(buf);
		return 1;
	}

	SpLexToken tok = {0};

	while ((res = sp_lex_next_token(buf, &tok)) == 0) {
		printf("%s %s\n", tok.buf, token_descriptions[tok.kind]);

		if (tok.kind == SP_TOK_KIND_EOF) {
			break;
		}
	}

	sp_input_buf_close(buf);
	sp_input_buf_destroy(buf);

	return 0;
}
