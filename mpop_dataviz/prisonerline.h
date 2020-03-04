#pragma once

#include "sceneobject.h"
#include <QPoint>
#include <QEasingCurve>

class PrisonerLine : public SceneObject
{
    Q_OBJECT
    // properties

    Q_PROPERTY(qreal x READ getX WRITE setX NOTIFY xChanged)
    Q_PROPERTY(qreal y READ getY WRITE setY NOTIFY yChanged)
    Q_PROPERTY(qreal z READ getZ WRITE setZ NOTIFY zChanged)
    Q_PROPERTY(qreal rotation READ getRotation WRITE setRotation NOTIFY rotationChanged)
    Q_PROPERTY(qreal scale READ getScale WRITE setScale NOTIFY scaleChanged)

public:
    explicit PrisonerLine( QObject* parent = nullptr);
    ~PrisonerLine() override;
    virtual void draw(const QElapsedTimer& timer) override;
    /**
     * @brief Sets the position of the line. (x, y)
     * @param point Position
     */
    void setPosition(qreal x, qreal y);
    /**
     * @brief Sets the angle of the line to the given angle (in degrees)
     * @param degrees Angle in degrees.
     */
    void setOrientation(qreal degrees);

    qreal getX() const { return this->_x; }
    qreal getY() const { return this->_y; }
    qreal getZ() const { return this->_z; }
    qreal getRotation() const { return this->_rotation; }
    qreal getScale() const { return this->_scale; }

    void setX(qreal value);
    void setY(qreal value);
    void setZ(qreal value);
    void setRotation(qreal value);
    void setScale(qreal value);

signals:
    void xChanged(qreal);
    void yChanged(qreal);
    void zChanged(qreal);
    void scaleChanged(qreal);
    void rotationChanged(qreal);
private:
    //qreal _angleDegrees;
    qreal _x;
    qreal _y;
    qreal _z;
    qreal _rotation;
    qreal _scale;
};
