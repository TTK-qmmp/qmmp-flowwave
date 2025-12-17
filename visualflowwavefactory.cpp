#include "visualflowwavefactory.h"
#include "flowwave.h"

#include <QMessageBox>

VisualProperties VisualFlowWaveFactory::properties() const
{
    VisualProperties properties;
    properties.name = tr("FlowWave Plugin");
    properties.shortName = "flowwave";
    properties.hasAbout = true;
    return properties;
}

Visual *VisualFlowWaveFactory::create(QWidget *parent)
{
    return new FlowWave(parent);
}

#if (QMMP_VERSION_INT < 0x10700) || (0x20000 <= QMMP_VERSION_INT && QMMP_VERSION_INT < 0x20200)
QDialog *VisualFlowWaveFactory::createConfigDialog(QWidget *parent)
#else
QDialog *VisualFlowWaveFactory::createSettings(QWidget *parent)
#endif
{
    Q_UNUSED(parent);
    return nullptr;
}

void VisualFlowWaveFactory::showAbout(QWidget *parent)
{
    QMessageBox::about(parent, tr("About FlowWave Visual Plugin"),
                       tr("Qmmp FlowWave Visual Plugin") + "\n" +
                       tr("Written by: Greedysky <greedysky@163.com>"));
}

QString VisualFlowWaveFactory::translation() const
{
    return QString();
}

#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
#include <QtPlugin>
Q_EXPORT_PLUGIN2(flowwave, VisualFlowWaveFactory)
#endif
