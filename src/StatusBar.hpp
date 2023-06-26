#pragma once
#include <ncurses.h>
#include <string>
#include <vector>
#include "StatusBarPart.hpp"

class StatusBar
{
    WINDOW *_parent;
    std::vector<StatusBarPart> _parts;
    std::vector<int> _draw_widths;

    void calculateDrawWidths()
    {
        std::vector<int> grow_indexes;
        int remaining_width = _parent->_maxx;
        for (int i = 0; i < _parts.size(); i++)
        {
            StatusBarPart part = _parts[i];
            switch (part.getWidth())
            {
            case StatusBarPart::WIDTH_FIT:
                _draw_widths[i] = part.getText().length() + (part.getPadding() * 2);
                remaining_width -= _draw_widths[i];
                // Width should match content width + padding
                break;
            case StatusBarPart::WIDTH_GROW:
                // Width should grow to the available space
                grow_indexes.push_back(i);
                break;
            default:
                // Use defined fixed width + padding
                _draw_widths[i] = part.getWidth() + (part.getPadding() * 2);
                remaining_width -= _draw_widths[i];
                break;
            }
        }
        if (!grow_indexes.empty())
        {
            for (int i = 0; i < grow_indexes.size(); i++)
            {
                _draw_widths[grow_indexes[i]] = remaining_width / grow_indexes.size();
            }
        }
    }

    void drawPart(int part_num)
    {
        StatusBarPart part = _parts[part_num];

        attron(part.getAttributes());
        drawPadding(part_num);
        drawText(part_num);
        drawPadding(part_num);
        attroff(part.getAttributes());
    }

    void drawPadding(int part_num)
    {
        int padding = _parts[part_num].getPadding();
        for (int i = 0; i < padding; i++)
        {
            waddch(_parent, ' ');
        }
    }

    void drawText(int part_num)
    {
        int width_no_padding = _draw_widths[part_num] - (_parts[part_num].getPadding() * 2);
        std::string text = _parts[part_num].getText();
        for (int i = 0; i < width_no_padding; i++)
        {
            if (i >= text.length())
            {
                waddch(_parent, ' ');
            }
            else
            {
                waddch(_parent, text[i]);
            }
        }
    }

public:
    StatusBar(int num_parts, WINDOW *parent = stdscr)
    {
        _parent = parent;
        _parts = std::vector<StatusBarPart>(num_parts);
        _draw_widths = std::vector<int>(num_parts);
        for (int i = 0; i < num_parts; i++)
        {
            _parts[i] = StatusBarPart();
        }
    }

    StatusBarPart &operator[](int part_num)
    {
        return _parts[part_num];
    }

    StatusBarPart &part(int part_num)
    {
        return _parts[part_num];
    }

    void setPart(int part_num, int width, int padding)
    {
        _parts[part_num].setWidth(width);
        _parts[part_num].setPadding(padding);
    }

    void setText(int part_num, std::string msg, attr_t attributes = -1)
    {
        _parts[part_num].setText(msg, attributes);
    }

    void draw()
    {
        int output_row = _parent->_maxy;
        wmove(_parent, output_row, 0);
        calculateDrawWidths();
        for (int i = 0; i < _parts.size(); i++)
        {
            drawPart(i);
        }
    }
};