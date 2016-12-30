#include "../include/utils.h"

void copyString(char* src, char* dest) {

	while(*src != '\0') {
		*dest = *src;
		dest++;
		src++;
	}

	*dest = '\0';
}

char** tokenize(char* toTokenize, char* delimiters, int * resultSize) {
	char* result[256];
	char* crtToken;
	int i = 0;
	char* toTokenize_safe = strdup(toTokenize);

	printf("toTokenize_safe : %s\n", toTokenize_safe);

	crtToken = strtok(toTokenize_safe, delimiters);
	//Nothing to tokenize.
	if (crtToken == NULL)
		return NULL;

	printf("malloc...\n");

	result[i] = malloc(strlen(crtToken) * sizeof(char));
	strcpy(result[i], strdup(crtToken));
	printf("loop...\n");
	while ((crtToken = strtok(NULL, delimiters)) != NULL) {
		i++;
		printf("crtToken : %s\n", crtToken);
		result[i] = (char*)malloc(strlen(crtToken) * sizeof(char));
		strcpy(result[i], strdup(crtToken));
	}

	*resultSize = i+1;

	//free(crtToken);

	return result;
}

void concatString(char* dest, char* toConcat) {
	dest += strlen(dest);

	while(*toConcat != '\0') {
		*dest = *toConcat;
		dest++;
		toConcat++;
	}

	*dest = '\0';

}

void clearArray(char* array, int size) {
	int i;

	for (i = 0; i < size; i++)
		array[i] = NULL;
}

/**
 * XXX This should use mime types.
 */
int getFileType(char* path) {
	char** tokenResult;
	int size = 0;
	char* ext;
	char* safePath = strdup(path);

	tokenResult = tokenize(safePath, ".", &size);

	if (tokenResult == NULL)
		return TYPE_UNKOWN;

	ext = tokenResult[size-1];

	if (strcmp(ext, EXT_HTML) == 0) {
		return TYPE_HTML;
	} else if (strcmp(ext, EXT_RUNNABLE) == 0) {
		return TYPE_RUNNABLE;
	} else {
		return TYPE_UNKOWN;
	}
}
