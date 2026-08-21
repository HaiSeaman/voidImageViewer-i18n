// Decision logic for dragging the image with the left mouse button.
//
// Kept as a pure function in its own header so the truth table can be unit
// tested without any Win32 state (tests/test_left_drag.c).

#ifndef VIV_LEFT_DRAG_H
#define VIV_LEFT_DRAG_H

enum
{
	LEFT_DRAG_SCROLL = 0,   // pan the image (existing _VIV_DOING_SCROLL path)
	LEFT_DRAG_MOVE_WINDOW,  // drag moves the whole window (HTCAPTION drag)
	LEFT_DRAG_NOTHING       // ignore the drag
};

// Decides what holding the left button on the image and dragging does.
//
//   has_pan_room  rendered image is larger than the viewport on some axis
//   is_fullscreen fullscreen mode is active
//   show_caption  system caption is shown (bordered window)
//   is_maximized  window is currently maximized
//
// Borderless normal windows keep the drag-to-move-window convenience; when
// the image is pannable (or fullscreen/caption already own the drag) the drag
// pans instead; a borderless maximized window is never drag-restored.
static int left_drag_decide(int has_pan_room, int is_fullscreen,
	int show_caption, int is_maximized)
{
	if (has_pan_room || is_fullscreen || show_caption)
	{
		return LEFT_DRAG_SCROLL;
	}

	if (is_maximized)
	{
		return LEFT_DRAG_NOTHING;
	}

	return LEFT_DRAG_MOVE_WINDOW;
}

#endif
