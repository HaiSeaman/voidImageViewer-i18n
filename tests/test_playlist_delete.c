// Regression test for viv.c:_viv_playlist_delete shuffle branch (line ~10400).
//
// Background: the shuffle branch deletes an entry from _viv_playlist_shuffle_indexes
// (a _viv_playlist_t ** array) via os_move_memory. os_move_memory is MoveMemory,
// whose third parameter is a BYTE count. The original code passed an element
// count (missing * sizeof(_viv_playlist_t *)), which corrupted the array and
// left stale pointers to freed nodes (use-after-free on later navigation).
//
// This test models exactly that memmove with the byte-count semantics of
// MoveMemory. --show-bug runs the buggy element-count version and asserts it
// fails; the default run asserts the fixed byte-count version passes.
//
// Build & run:
//   call vcvars64.bat
//   cl /nologo /W4 /WX tests\test_playlist_delete.c /Fe:tests\test_playlist_delete.exe
//   tests\test_playlist_delete.exe            -> expects SUCCESS (fixed logic)
//   tests\test_playlist_delete.exe --show-bug -> expects FAILURE (old logic)

#include <stdio.h>
#include <string.h>

static int failure_count;

typedef struct node_s
{
	long id;
	struct node_s *next;
	struct node_s *prev;
} node_t;

static void expect(const char *name, int condition)
{
	if (condition)
	{
		printf("pass %s\n", name);
	}
	else
	{
		failure_count++;
		printf("FAIL %s\n", name);
	}
}

// delete one element from a _viv_playlist_t ** style array, shifting the tail.
// In the real code the array is a global; here we return the new logical count.
// mir: whether to mimic the buggy (element-count) memmove from viv.c:10400.
static int remove_index(node_t **arr, int count, int index, int mimic_bug)
{
	if (mimic_bug)
	{
		// BUG: passes element count where MoveMemory wants a byte count.
		memmove(arr + index, arr + index + 1, (size_t)(count - (index + 1)));
	}
	else
	{
		memmove(arr + index, arr + index + 1, (size_t)(count - (index + 1)) * sizeof(node_t *));
	}
	return count - 1;
}

static int contains(node_t **arr, int count, node_t *target)
{
	int i;
	for (i = 0; i < count; i++)
	{
		if (arr[i] == target)
		{
			return 1;
		}
	}
	return 0;
}

// count after delete must equal [0,1,3,4] pointers for N=5, delete index=2.
static int order_ok(node_t **arr)
{
	return (arr[0]->id == 0) && (arr[1]->id == 1) && (arr[2]->id == 3) && (arr[3]->id == 4);
}

static void run_case(int mimic_bug)
{
	node_t nodes[5];
	node_t *arr[5];
	int i;
	int count;

	for (i = 0; i < 5; i++)
	{
		nodes[i].id = i;
		arr[i] = &nodes[i];
	}

	count = remove_index(arr, 5, 2, mimic_bug);

	// The deleted node (id 2) must not remain reachable in the array.
	expect("deleted node no longer reachable", !contains(arr, count, &nodes[2]));
	// The tail must have shifted up: logical order is 0,1,3,4.
	expect("tail shifted up correctly", order_ok(arr));
	// The highest logical slot must now be nodes[4] (id 4).
	expect("last element is old tail", count == 4 && arr[3] == &nodes[4]);

	if (mimic_bug)
	{
		printf("(buggy element-count memmove: expected the assertions above to FAIL)\n");
	}
}

int main(int argc, char **argv)
{
	int mimic_bug = (argc > 1) && (strcmp(argv[1], "--show-bug") == 0);

	run_case(mimic_bug);

	printf("%s: %d assertion(s) failed\n", failure_count ? "FAILURE" : "SUCCESS", failure_count);
	return failure_count ? 1 : 0;
}