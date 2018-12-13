/* --------------------------------------------------------------------------------
 * A Qt-based 2D or 3D OpenGL viewer with mouse rotation, pan and zoom.
 *
 * Copyright 2018 Marcel Paz Goldschen-Ohm <marcel.goldschen@gmail.com>
 * -------------------------------------------------------------------------------- */

#ifndef __QtOpenGLViewer_H__
#define __QtOpenGLViewer_H__

#include <QColor>
#include <QFont>
#include <QObject>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QPainter>
#include <QVector3D>

#ifdef DEBUG
#include <iostream>
#include <QDebug>
#endif

/* --------------------------------------------------------------------------------
 * Graph viewer UI.
 * -------------------------------------------------------------------------------- */
class QtOpenGLViewer : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
    Q_PROPERTY(bool Is3D READ is3D WRITE setIs3D NOTIFY optionsChanged)
    Q_PROPERTY(float MouseWheelSensitivity READ mouseWheelSensitivity WRITE setMouseWheelSensitivity)
    Q_PROPERTY(bool SwapMouseWheelZoomDirection READ swapMouseWheelZoomDirection WRITE setSwapMouseWheelZoomDirection)
    Q_PROPERTY(QColor BackgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY optionsChanged)
    Q_PROPERTY(QFont HudFont READ hudFont WRITE setHudFont NOTIFY optionsChanged)
    
public:
    QtOpenGLViewer(QWidget *parent = NULL) : QOpenGLWidget(parent) {}
    virtual ~QtOpenGLViewer() {}
    
    struct Camera {
        QVector3D eye = QVector3D(0, 0, 10);
        QVector3D center = QVector3D(0, 0, 0);
        QVector3D up = QVector3D(0, 1, 0);
        QVector3D view() { return center - eye; }
        void zoom(float viewDistance) { eye = center - view().normalized() * viewDistance; }
    } camera;
    
    bool is3D() const { return _is3D; }
    void setIs3D(bool b) { if(_is3D && !b) goToDefaultView(); _is3D = b; }
    
    float mouseWheelSensitivity() const { return _mouseWheelSensitivity; }
    void setMouseWheelSensitivity(float f) { _mouseWheelSensitivity = f > 1e-3 ? f : 1e-3; }
    
    bool swapMouseWheelZoomDirection() const { return _swapMouseWheelZoomDirection; }
    void setSwapMouseWheelZoomDirection(bool b) { _swapMouseWheelZoomDirection = b; }
    
    QColor backgroundColor() const { return _backgroundColor; }
    void setBackgroundColor(const QColor &color) { _backgroundColor = color; }
    
    QFont hudFont() const { return _hudFont; }
    void setHudFont(const QFont &font) { _hudFont = font; }
    
    // useful stuff
    static QVector3D screen2World(QVector3D screen, int *viewport, float *projection, float *modelview);
    static QVector3D world2Screen(QVector3D world, int *viewport, float *projection, float *modelview);
    static float intersectRayAndSphere(const QVector3D &rayOrigin, const QVector3D &rayDirection, const QVector3D &sphereCenter, float sphereRadius);
    static float intersectRayAndPlane(const QVector3D &rayOrigin, const QVector3D &rayDirection, const QVector3D &pointOnPlane, const QVector3D &planeNormal);
    void goToBillboard(const QVector3D &origin, const QVector3D &right);
    bool isLeftToRight(const QVector3D &vec);
    static float luminance(const QColor &color);
    static QColor colorWithMaxContrast(const QColor &color);
    void renderText(float x, float y, const QString &text, const QColor &color, const QFont &font);
    
    // drawing
    virtual void drawScene();
    virtual void drawHud(QPainter &painter);
    void drawAxes();
    
    // mouse selection
    virtual void selectObject(const QPoint &mousePosition);
    void getPickRay(const QPoint &mousePosition, QVector3D &origin, QVector3D &ray);
    QVector3D pickPointInPlane(const QPoint &mousePosition, const QVector3D &pointOnPlane, bool snapToUnitGrid = false);
    
signals:
    void optionsChanged();
    void selectedObjectChanged(QObject*);
    
public slots:
    virtual void goToDefaultView();
    virtual void deleteSelectedObject();
    virtual void editSelectedObject(const QPoint &mousePosition);
    
protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    
    virtual void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    virtual void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
    virtual void mouseDoubleClickEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    
protected:
    bool _is3D = true;
    float _mouseWheelSensitivity = 0.2;
    bool _swapMouseWheelZoomDirection = false;
    QColor _backgroundColor = QColor(200, 200, 200);
    QFont _hudFont = QFont("Sans", 10, QFont::Normal);
    QPoint _mousePosition;
    QObject *_selectedObject = NULL;
};

#endif
