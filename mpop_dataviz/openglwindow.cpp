
#include "openglwindow.h"
#include <QtCore/QCoreApplication>
#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLPaintDevice>
#include <QtGui/QPainter>
#include <QDebug>

OpenGLWindow::OpenGLWindow(QWindow* parent) :
    QWindow(parent),
    _is_animating(false),
    _context(nullptr),
    _device(nullptr) {
    setSurfaceType(QWindow::OpenGLSurface);
}


OpenGLWindow::~OpenGLWindow()
{
    qDebug() << "~OpenGLWindow";
    delete _device;
}


void OpenGLWindow::render(QPainter* painter) {
    Q_UNUSED(painter);
}

void OpenGLWindow::initialize() {
}

void OpenGLWindow::render() {
    if (! _device) {
        _device = new QOpenGLPaintDevice;
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    _device->setSize(size());
    QPainter painter(_device);
    if (_context) {
        _context->makeCurrent(this);
    }
    render(&painter);
}


void OpenGLWindow::renderLater() {
    // Asks to render again the next time the hardware is ready for a new frame.
    requestUpdate();
}

bool OpenGLWindow::event(QEvent* event) {
    switch (event->type()) {
        case QEvent::UpdateRequest: {
            renderNow();
            return true;
            // break;
        }
        default: {
            return QWindow::event(event);
            // break;
        }
    }
}

void OpenGLWindow::exposeEvent(QExposeEvent* event) {
    Q_UNUSED(event);
    if (isExposed()) {
        renderNow();
    }
}


void OpenGLWindow::renderNow() {
    if (! isExposed()) {
        return;
    }

    bool needsInitialize = false;

    if (! _context) {
        _context = new QOpenGLContext(this);
        _context->setFormat(requestedFormat());
        _context->create();
        needsInitialize = true;
    }

    _context->makeCurrent(this);

    if (needsInitialize) {
        initializeOpenGLFunctions();
        initialize();
    }

    render();

    // Call this to finish a frame of OpenGL rendering,
    // and make sure to call makeCurrent() again before issuing any further OpenGL commands,
    // for example as part of a new frame.
    _context->swapBuffers(this);

    if (_is_animating) {
        // With a swap interval of 1, which is the case on most systems by default, the swapBuffers() call,
        // that is executed internally by QOpenGLWindow after each repaint, will block and wait for vsync.
        // This means that whenever the swap is done, an update can be scheduled again by calling update(),
        // without relying on timers.
        renderLater();
    }
}


void OpenGLWindow::setAnimating(bool animating) {
    _is_animating = animating;
    if (animating) {
        renderLater();
    }
}
