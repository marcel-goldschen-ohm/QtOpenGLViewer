# QtOpenGLViewer

Yet another simple 3D/2D OpenGL viewer with mouse rotation, pan, zoom and some object selection.

This is meant for when all you need is a simple OpenGL 3D or 2D viewer with generic mouse interaction and/or object selection or manipulaiton, and you don't really want to waste the time to roll your own for something so stupidly simple. If you need something fancy, you'll probably have to roll your own code, but using this code as a starting point might help.

**Author**: Marcel Goldschen-Ohm  
**Email**:  <marcel.goldschen@gmail.com>  
**License**: MIT  
Copyright (c) 2018 Marcel Goldschen-Ohm 

## Overview

1. Make your own custom viewer class that derives from `QtOpenGLViewer`. This will give you a widget with a 3D or 2D OpenGL scene (see `is3D()` and `setIs3D(bool)`) with mouse rotation (3D only), pan and zoom out of the box.
2. Override `drawScene()` and make it do something interesting beyond just drawing axes.
3. **[OPTIONAL]** Override `drawHud(QPainter &painter)` if you want a 2D overlay (default just prints mouse controls).
4. **[OPTIONAL]** Override `selectObject(const QPoint &mousePosition)` if you want mouse left-click selection of scene objects.
5. **[OPTIONAL]** Override any of the mouse, keyboard, or other input functions such as `mouseMoveEvent(...)` if you want to to handle those actions (i.e. drag objects with the mouse or something).

See the example in `test/` for some simple drawing and object selection/dragging using functions that come with `QtOpenGLViewer`.

## INSTALL

Everything is in:

* `QtOpenGLViewer.h`
* `QtOpenGLViewer.cpp`

### CMake:

See `CMakeLists.txt` for example build as a static library.

:point_right: **This is most likely what you want:** See `test/CMakeLists.txt` for example build of an app that uses QtOpenGLViewer. This build uses CMake to automatically download QtOpenGLViewer files directly from this GitHub repository, builds QtOpenGLViewer as a static library and links it to the app executable. This way you can use QtOpenGLViewer in your project without downloading or managing the QtOpenGLViewer repository manually.

### Requires:

* [Qt](http://www.qt.io)
