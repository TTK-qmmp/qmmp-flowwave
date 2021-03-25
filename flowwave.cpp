#include <QTimer>
#include <QPainter>
#include <QMenu>
#include <QPaintEvent>
#include <math.h>
#include <stdlib.h>
#include <qmmp/qmmp.h>

#include "inlines.h"
#include "flowwave.h"

FlowWave::FlowWave(QWidget *parent)
    : Visual(parent)
{
    setWindowTitle(tr("FlowWave Widget"));
    setMinimumSize(2 * 300 - 30, 105);

    m_timer = new QTimer(this);
    m_timer->setInterval(40);
    connect(m_timer, SIGNAL(timeout()), SLOT(updateVisual()));

    m_screenAction = new QAction(tr("Fullscreen"), this);
    m_screenAction->setCheckable(true);
    connect(m_screenAction, SIGNAL(triggered(bool)), this, SLOT(setFullScreen(bool)));
}

FlowWave::~FlowWave()
{
    if(m_intern_vis_data)
    {
        delete[] m_intern_vis_data;
    }

    if(m_x_scale)
    {
        delete[] m_x_scale;
    }
}

void FlowWave::start()
{
    if(isVisible())
        m_timer->start();
}

void FlowWave::stop()
{
    m_timer->stop();
}

void FlowWave::updateVisual()
{
    if(takeData(m_left, m_right))
    {
        process(m_left, m_right);
        update();
    }
}

void FlowWave::setFullScreen(bool yes)
{
    if(yes)
        setWindowState(windowState() | Qt::WindowFullScreen);
    else
        setWindowState(windowState() & ~Qt::WindowFullScreen);
}

void FlowWave::hideEvent(QHideEvent *)
{
    m_timer->stop();
}

void FlowWave::showEvent(QShowEvent *)
{
    m_timer->start();
}

void FlowWave::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.fillRect(e->rect(), Qt::black);
    draw(&painter);
}

void FlowWave::contextMenuEvent(QContextMenuEvent *)
{
    QMenu menu(this);
    menu.addAction(m_screenAction);
    menu.exec(QCursor::pos());
}

void FlowWave::process(float *left, float *)
{
    const int rows = (height() - 2) / m_cell_size.height();
    const int cols = (width() - 2) / m_cell_size.width();

    if(m_rows != rows || m_cols != cols)
    {
        m_rows = rows;
        m_cols = cols;

        if(m_intern_vis_data)
        {
            delete[] m_intern_vis_data;
        }

        if(m_x_scale)
        {
            delete[] m_x_scale;
        }

        m_intern_vis_data = new int[m_cols]{0};
        m_x_scale = new int[m_cols + 1]{0};

        for(int i = 0; i < m_cols + 1; ++i)
        {
            m_x_scale[i] = pow(pow(255.0, 1.0 / m_cols), i);
        }
    }

    short dest[256];
    short y;
    int k, magnitude;

    calc_freq(dest, left);
    const double y_scale = (double) 1.25 * m_rows / log(256);

    for(int i = 0; i < m_cols; i++)
    {
        y = 0;
        magnitude = 0;

        if(m_x_scale[i] == m_x_scale[i + 1])
        {
            y = dest[i];
        }

        for(k = m_x_scale[i]; k < m_x_scale[i + 1]; k++)
        {
            y = qMax(dest[k], y);
        }

        y >>= 7; //256

        if(y)
        {
            magnitude = int(log(y) * y_scale);
            magnitude = qBound(0, magnitude, m_rows);
        }

        m_intern_vis_data[i] -= m_analyzer_falloff * m_rows / 15;
        m_intern_vis_data[i] = magnitude > m_intern_vis_data[i] ? magnitude : m_intern_vis_data[i];
    }
}

void FlowWave::draw(QPainter *p)
{
    QLinearGradient line(0, 0, width(), 0);
    line.setColorAt(1.0 * 1 / 7, QColor(72, 176, 211));
    line.setColorAt(1.0 * 2 / 7, QColor(57, 255, 57));
    line.setColorAt(1.0 * 4 / 7, QColor(255, 247, 22));
    line.setColorAt(1.0 * 5 / 7, QColor(255, 64, 59));
    line.setColorAt(1.0 * 7 / 7, QColor(255, 64, 59));
    p->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    int x = 0;
    for(int i = 0; i < m_cols; ++i)
    {
        x = i * m_cell_size.width() + 1;
        for(int j = 0; j <= m_intern_vis_data[i] / 2; ++j)
        {
            p->fillRect(x, height() / 2 - j * m_cell_size.height() + 1, m_cell_size.width() - 2, m_cell_size.height() - 2, line);
            p->fillRect(x, height() / 2 + j * m_cell_size.height() + 1, m_cell_size.width() - 2, m_cell_size.height() - 2, line);
        }
    }
    p->fillRect(0, height() / 2, width(), height() / 2, QColor(0, 0, 0, 188));
}
