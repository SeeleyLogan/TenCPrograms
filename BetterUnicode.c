/*
 * Unicode is dumb
 * Why? Because imagine you have a string, of 100 ANSI characters.
 * Now you want to insert a unicode character.
 * Well congrats, you just extended that 100 byte array to a 202 byte array. By adding one character
 * This program is designed to solve this problem
 * By using pointers to unicode characters
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Hahahha get it? Like vim but for wide strings (I have no life)
struct WIM
{
	char *str_ptr;  // Pointer to 
	short *wchar_indexes;
	size_t length;  // Length of string in characters (wide characters count as 1)
	size_t wchars;  // How many wide characters in string
};

// Constructor
char* createWIM(wchar_t wide_str[])
{
	// Allocate memory for struct
	struct WIM *wim = malloc(wcslen(wide_str));

	if (wim == NULL)
		// Oopsie doopsie, malloc didn't work :(
		return NULL;

	wim->length = wcslen(wide_str);
	wim->wchars = 0;

	// Assume each character is a wide character
	// Allocate enough space for each character and a pointer to said character
	// We will reallocate later
	wim->str_ptr = calloc(wim->length, 2);
	wim->wchar_indexes = calloc(wim->length, 2);

	// Free the appropriate memory for each case assuming any malloc didn't work
	if (wim->str_ptr != NULL && wim->wchar_indexes == NULL)
	{
		free(wim->str_ptr);
		free(wim);
		return NULL;
	}
	else if (wim->str_ptr == NULL && wim->wchar_indexes != NULL)
	{
		free(wim->wchar_indexes);
		free(wim);
		return NULL;
	}
	else if (wim->str_ptr == NULL && wim->wchar_indexes == NULL)
	{
		free(wim);
		return NULL;
	}

	// Iterate through each character, collecting information in preparation for allocation
	for (int i = 0; i < wim->length; i++)
	{
		wchar_t wch = wide_str[i];

		if (wch > 255)
		{
			// wch is UNICODE
			memcpy(wim->str_ptr + i + wim->wchars, &wch, 2);  // Push wch onto string
			*(wim->wchar_indexes + i) = i-wim->wchars;  // Push index of wch onto array wchar
			wim->wchars++;
		}
		else if (wch <= 255)
			// wch is ANSI (guess it ain't a wch)
			memcpy(wim->str_ptr + i + wim->wchars, (char*)&wch, 1);  // Push first byte of wch onto string

		if (wch == 0)  // wch is 0 (NULL termination)
			break;
	}

	// Realloc string to save memory
	realloc(wim->str_ptr, wim->length + wim->wchars);

	return wim;
}

// Self explainatory
void freeWIM(struct WIM *wim)
{
	free(wim->str_ptr);
	free(wim->wchar_indexes);
	free(wim);
}

int main()
{
	struct WIM *wim = createWIM(L" \x16E <- cyclops");

	if (wim != NULL)
		freeWIM(wim);
	
	return 0;
}
