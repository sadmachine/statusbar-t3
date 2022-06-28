#pragma once
#include <ncurses.h>
#include <string>
#include <vector>
#include "StatusBarPart.hpp"

class StatusBar
{
    WINDOW *_parent;
    std::vector<StatusBarPart> _parts;

public:
    StatusBar(int num_parts, WINDOW *parent = stdscr)
    {
        _parent = parent;
        _parts = std::vector<StatusBarPart>(num_parts);
    }

    void setText(int part_num, std::string msg, attr_t attributes = -1)
    {
        _parts[part_num].setText(msg, attributes);
    }

    void draw()
    {
        int output_row = _parent->_maxy - 1;
        wmove(_parent, output_row, 0);
        for (int i = 0; i < _parts.size(); i++)
        {
            StatusBarPart part = _parts[i];
            attron(part.getAttributes());
            wprintw(_parent, part.getText().c_str());
            attroff(part.getAttributes());
        }
    }
};