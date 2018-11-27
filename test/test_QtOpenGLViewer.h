/* --------------------------------------------------------------------------------
 * Example test for QtOpenGLViewer.
 *
 * Author: Marcel Paz Goldschen-Ohm
 * Email: marcel.goldschen@gmail.com
 * -------------------------------------------------------------------------------- */

#include "QtOpenGLViewer.h"

#include <QApplication>
#include <QObject>
#include <QString>

#ifdef MACX
#   include <OpenGL/glu.h>
#else
#   include <glu.h>
#endif

class Sphere : public QObject
{
    Q_OBJECT
    
public:
    QVector3D center = QVector3D(0, 0, 0);
    float radius = 1;
    QColor color;
};

class SphereViewer : public QtOpenGLViewer
{
    Q_OBJECT
    
public:
    // add some spheres to our viewer as child objects on construction.
    SphereViewer();
    
    // draw the spheres (selected sphere is yellow)
    void drawScene() Q_DECL_OVERRIDE;
    
    // select spheres with mouse
    void selectObject(const QPoint &mousePosition) Q_DECL_OVERRIDE;
    
protected:
    // drag selected sphere in scene
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
};
