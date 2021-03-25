/* =================================================
 * This file is part of the TTK qmmp plugin project
 * Copyright (C) 2015 - 2021 Greedysky Studio

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; If not, see <http://www.gnu.org/licenses/>.
 ================================================= */

#ifndef FLOWWAVE_H
#define FLOWWAVE_H

#include <qmmp/visual.h>

/*!
 * @author Greedysky <greedysky@163.com>
 */
class FlowWave : public Visual
{
    Q_OBJECT
public:
    explicit FlowWave(QWidget *parent = nullptr);
    virtual ~FlowWave();

public slots:
    virtual void start() override;
    virtual void stop() override;

private slots:
    void updateVisual();
    void setFullScreen(bool yes);

private:
    virtual void hideEvent(QHideEvent *e) override;
    virtual void showEvent(QShowEvent *e) override;
    virtual void paintEvent(QPaintEvent *e) override;
    virtual void contextMenuEvent(QContextMenuEvent *e) override;

    void process(float *left, float *right);
    void draw(QPainter *p);

    int *m_x_scale = nullptr;
    double m_analyzer_falloff = 2.2;
    QSize m_cell_size = QSize(15, 6);
    QTimer *m_timer = nullptr;
    int m_rows = 0, m_cols = 0;
    int *m_intern_vis_data = nullptr;
    float m_left[QMMP_VISUAL_NODE_SIZE];
    float m_right[QMMP_VISUAL_NODE_SIZE];
    QAction *m_screenAction = nullptr;

};

#endif
