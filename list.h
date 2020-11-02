#include "glogic.h"

struct LList
{
	struct LList *next;
	struct Board *val;
};


bool freeSList(struct LList* node);

struct LList* append(struct LList* oldHead, struct LList* newHead);
struct LList* createNode(struct Board* val);
struct LList* pop(struct LList* oldHead);





