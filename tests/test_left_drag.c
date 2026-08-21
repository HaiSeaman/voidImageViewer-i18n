// Unit tests for the left-drag decision logic in src/left_drag.h.
//
// Build & run: tests\build_and_run_test.bat
// Standalone console program, no Win32 dependencies: the decision is a pure
// function of window state so it can be exhaustively tested.

#include <stdio.h>

#include "../src/left_drag.h"

static int failure_count;

static void expect(const char *name, int expected, int actual)
{
	if (expected == actual)
	{
		printf("pass %s\n", name);
	}
	else
	{
		failure_count++;
		printf("FAIL %s: expected %d, got %d\n", name, expected, actual);
	}
}

int main(void)
{
	// Exhaustive truth table: has_pan_room, is_fullscreen, show_caption,
	// is_maximized -> wanted decision.
	struct
	{
		int has_pan_room;
		int is_fullscreen;
		int show_caption;
		int is_maximized;
		int wanted;
		const char *name;
	}
	cases[] =
	{
		// Image larger than the viewport: drag always pans, whatever the
		// window state (this is the fix the feature is about).
		{1, 0, 0, 0, LEFT_DRAG_SCROLL,      "pan + borderless normal"},
		{1, 0, 0, 1, LEFT_DRAG_SCROLL,      "pan + borderless maximized"},
		{1, 0, 1, 0, LEFT_DRAG_SCROLL,      "pan + caption normal"},
		{1, 0, 1, 1, LEFT_DRAG_SCROLL,      "pan + caption maximized"},
		{1, 1, 0, 0, LEFT_DRAG_SCROLL,      "pan + fullscreen"},
		{1, 1, 0, 1, LEFT_DRAG_SCROLL,      "pan + fullscreen (max flag)"},
		{1, 1, 1, 0, LEFT_DRAG_SCROLL,      "pan + fullscreen + caption"},
		{1, 1, 1, 1, LEFT_DRAG_SCROLL,      "pan + everything"},

		// Image fully visible, fullscreen or caption shown: keep the
		// pre-existing pan path (the view clamp makes it a no-op).
		{0, 1, 0, 0, LEFT_DRAG_SCROLL,      "fit + fullscreen"},
		{0, 1, 0, 1, LEFT_DRAG_SCROLL,      "fit + fullscreen (max flag)"},
		{0, 1, 1, 0, LEFT_DRAG_SCROLL,      "fit + fullscreen + caption"},
		{0, 1, 1, 1, LEFT_DRAG_SCROLL,      "fit + fullscreen + caption (max)"},
		{0, 0, 1, 0, LEFT_DRAG_SCROLL,      "fit + caption normal"},
		{0, 0, 1, 1, LEFT_DRAG_SCROLL,      "fit + caption maximized"},

		// Image fully visible, borderless: dragging a maximized window
		// would restore and drag it away - do nothing instead.
		{0, 0, 0, 1, LEFT_DRAG_NOTHING,     "fit + borderless maximized"},

		// Image fully visible, borderless, normal window: drag moves the
		// window (pre-existing convenience, unchanged).
		{0, 0, 0, 0, LEFT_DRAG_MOVE_WINDOW, "fit + borderless normal"},
	};

	size_t i;
	size_t count = sizeof(cases) / sizeof(cases[0]);

	if (LEFT_DRAG_SCROLL != 0)
	{
		printf("FAIL enum baseline: LEFT_DRAG_SCROLL must be 0\n");
		failure_count++;
	}

	for (i = 0; i < count; i++)
	{
		int got = left_drag_decide(cases[i].has_pan_room,
			cases[i].is_fullscreen, cases[i].show_caption,
			cases[i].is_maximized);
		expect(cases[i].name, cases[i].wanted, got);
	}

	printf("%s: %d/%d cases passed\n", failure_count ? "FAILURE" : "SUCCESS",
		(int)(count - failure_count), (int)count);

	return failure_count ? 1 : 0;
}
