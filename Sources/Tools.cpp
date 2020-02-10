#include "Tools.h"

bool strStartsWith(const char* haystack, const char* needle) {
	for (int i = 0; true; i++) {
		if (needle[i] == '\0')
			break;

		if (haystack[i] == '\0' || haystack[i] != needle[i])
			return false;
	}

	return true;
}
