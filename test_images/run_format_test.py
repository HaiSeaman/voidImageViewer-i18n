# 全格式加载测试：启动 voidImageViewer 加载每张测试图，
# 验证窗口标题含文件名（加载成功）且窗口渲染非全黑（显示成功）。
import os
import subprocess
import time
import sys
import ctypes
from ctypes import wintypes

from PIL import ImageGrab

EXE = r"D:\AI\Github\voidImageViewer-master\voidImageViewer-master\vs2026\x64\Release\voidImageViewer.exe"
TESTDIR = os.path.dirname(os.path.abspath(__file__))

FILES = [
    "test.bmp", "test.png", "test.jpg", "test.jpeg", "test.gif",
    "test.tif", "test.tiff", "test.webp", "test.ico",
    "test_alpha.png", "test_anim.gif", "test_anim.webp", "test_orient6.jpg",
    "autumn.heic", "autumn.heif", "shelf-christmas-decoration.heic",
]

user32 = ctypes.windll.user32
kernel32 = ctypes.windll.kernel32

def find_window_by_pid(pid):
    results = []

    @ctypes.WINFUNCTYPE(wintypes.BOOL, wintypes.HWND, wintypes.LPARAM)
    def cb(hwnd, lparam):
        wpid = wintypes.DWORD()
        user32.GetWindowThreadProcessId(hwnd, ctypes.byref(wpid))
        if wpid.value == pid:
            title = ctypes.create_unicode_buffer(512)
            user32.GetWindowTextW(hwnd, title, 512)
            results.append((hwnd, title.value))
        return True

    user32.EnumWindows(cb, 0)
    return results

def get_window_rect(hwnd):
    r = wintypes.RECT()
    user32.GetWindowRect(hwnd, ctypes.byref(r))
    return (r.left, r.top, r.right, r.bottom)

def count_process_windows(pid):
    """返回进程的可见顶层窗口标题列表（用于检测错误消息框）。"""
    titles = []

    @ctypes.WINFUNCTYPE(wintypes.BOOL, wintypes.HWND, wintypes.LPARAM)
    def cb(hwnd, lparam):
        wpid = wintypes.DWORD()
        user32.GetWindowThreadProcessId(hwnd, ctypes.byref(wpid))
        if wpid.value == pid and user32.IsWindowVisible(hwnd):
            title = ctypes.create_unicode_buffer(256)
            user32.GetWindowTextW(hwnd, title, 256)
            titles.append(title.value)
        return True

    user32.EnumWindows(cb, 0)
    return titles

def image_is_blank(rect):
    try:
        img = ImageGrab.grab(rect)
    except Exception:
        return True, 0.0, 0
    img = img.convert("RGB")
    w, h = img.size
    if w <= 0 or h <= 0:
        return True, 0.0, 0
    colors = img.getcolors(maxcolors=w * h)
    if not colors:
        return False, 1.0, w * h
    black = sum(c for c, _ in colors if _ == (0, 0, 0))
    total = w * h
    non_black_ratio = 1.0 - black / total
    return non_black_ratio < 0.05, non_black_ratio, total

def kill_viv():
    subprocess.run(["taskkill", "/F", "/IM", "voidImageViewer.exe"],
                   capture_output=True)
    time.sleep(0.8)

results = []

for f in FILES:
    path = os.path.join(TESTDIR, f)
    kill_viv()
    proc = subprocess.Popen([EXE, path, "/window", "/x", "40", "/y", "40"])
    time.sleep(3.0)

    # 若窗口尚未就绪，最多再等 5 秒
    hwnd = None
    title = ""
    for _ in range(10):
        wins = find_window_by_pid(proc.pid)
        if wins:
            hwnd, title = wins[0]
            if title:
                break
        time.sleep(0.5)

    loaded = f.lower().rsplit(".", 1)[0] in title.lower()

    # 等待窗口渲染出内容（HEIC 首次解码可能耗时数秒）
    blank, ratio, total = True, 0.0, 0
    error_box = False
    deadline = time.time() + 30
    while time.time() < deadline:
        if hwnd and user32.IsWindow(hwnd):
            rect = get_window_rect(hwnd)
            blank, ratio, total = image_is_blank(rect)
            # 加载失败会弹出错误消息框（额外可见顶层窗口）
            windows = count_process_windows(proc.pid)
            error_box = any(t and "void Image Viewer" not in t for t in windows)
            if (not blank) and not error_box:
                break
        time.sleep(1.0)
        wins = find_window_by_pid(proc.pid)
        if wins:
            hwnd, title = wins[0]
            loaded = f.lower().rsplit(".", 1)[0] in title.lower()

    status = "OK" if (loaded and not blank and not error_box) else "FAIL"
    results.append((f, status, title, ratio))
    print(f"{status:4s} {f:20s} title={title!r} nonblack={ratio:.2f} errbox={error_box}")
    sys.stdout.flush()
    proc.terminate()

kill_viv()
print("\n=== 汇总 ===")
ok = [r for r in results if r[1] == "OK"]
for r in results:
    print(f"{r[1]:4s} {r[0]}")
print(f"\n通过 {len(ok)}/{len(results)}")
sys.exit(0 if len(ok) == len(results) else 1)
