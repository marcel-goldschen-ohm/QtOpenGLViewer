/* --------------------------------------------------------------------------------
 * Example test for QtOpenGLViewer.
 *
 * Author: Marcel Paz Goldschen-Ohm
 * Email: marcel.goldschen@gmail.com
 * -------------------------------------------------------------------------------- */

#include "test_QtOpenGLViewer.h"

#include <QApplication>
#include <QMouseEvent>

// add some spheres to our viewer as child objects on construction.
SphereViewer::SphereViewer() : QtOpenGLViewer()
{
    Sphere *r = new Sphere();
    r->setParent(this);
    r->setObjectName("Red Sphere");
    r->color = QColor(255, 0, 0);
    r->center = QVector3D(0, 0, -2);
    r->radius = 1;
    
    Sphere *g = new Sphere();
    g->setParent(this);
    g->setObjectName("Green Sphere");
    g->color = QColor(0, 255, 0);
    g->center = QVector3D(3, 3, 3);
    g->radius = 2;
    
    Sphere *b = new Sphere();
    b->setParent(this);
    b->setObjectName("Blue Sphere");
    b->color = QColor(0, 0, 255);
    b->center = QVector3D(-3, 1, 0);
    b->radius = 0.5;
}

// draw the spheres (selected sphere is yellow)
void SphereViewer::drawScene()
{
    drawAxes();
    GLUquadric *quadric = gluNewQuadric();
    if(quadric) {
        glEnable(GL_LIGHTING);
        for(Sphere *sphere : findChildren<Sphere*>(QString(), Qt::FindDirectChildrenOnly)) {
            glPushMatrix();
            glTranslatef(sphere->center.x(), sphere->center.y(), sphere->center.z());
            if(sphere == _selectedObject)
                glColor3f(1, 1, 0);
            else
                glColor4f(sphere->color.redF(), sphere->color.greenF(), sphere->color.blueF(), sphere->color.alphaF());
            gluSphere(quadric, sphere->radius, 32, 32);
            glPopMatrix();
        }
        glDisable(GL_LIGHTING);
        gluDeleteQuadric(quadric);
    }
}

// select spheres with mouse
void SphereViewer::selectObject(const QPoint &mousePosition)
{
    QVector3D pickOrigin, pickRay;
    getPickRay(mousePosition, pickOrigin, pickRay);
    pickRay.normalize();
    float t = 0, tmin = 0;
    _selectedObject = NULL;
    for(Sphere *sphere : findChildren<Sphere*>(QString(), Qt::FindDirectChildrenOnly)) {
        t = intersectRayAndSphere(pickOrigin, pickRay, sphere->center, sphere->radius);
        // t < 0: no intersection
        // t >= 0: t is distance from origin along ray to intersection point
        if(t >= 0 && (!_selectedObject || t < tmin)) {
            _selectedObject = sphere;
            tmin = t;
        }
    }
}

// drag selected sphere in scene
void SphereViewer::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton) {
        if(_selectedObject) {
            if(Sphere *sphere = qobject_cast<Sphere*>(_selectedObject)) {
                sphere->center = pickPointInPlane(event->pos(), sphere->center);
                repaint();
                return;
            }
        }
    }
    QtOpenGLViewer::mouseMoveEvent(event);
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    
    SphereViewer viewer;
    viewer.show();
    
    return app.exec();
}
