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

QDialog *VisualFlowWaveFactory::createConfigDialog(QWidget *parent)
{
    Q_UNUSED(parent);
    return nullptr;
}

void VisualFlowWaveFactory::showAbout(QWidget *parent)
{
    QMessageBox::about(parent, tr("About FlowWave Visual Plugin"),
                       tr("Qmmp FlowWave Visual Plugin") + "\n" +
                       tr("This plugin adds FlowWave visualization") + "\n" +
                       tr("Written by: Greedysky <greedysky@163.com>"));
}

QString VisualFlowWaveFactory::translation() const
{
    return QString();
}
