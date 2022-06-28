#pragma once
#include <ncurses.h>
#include <string>

class StatusBarPart
{
    std::string _text;
    attr_t _attributes;

public:
    StatusBarPart()
    {
        _text = "";
        _attributes = 0;
    }

    std::string getText()
    {
        return _text;
    }

    void setText(std::string text, attr_t attributes = -1)
    {
        _text = text;
        if (attributes != -1)
        {
            _attributes = attributes;
        }
    }

    attr_t getAttributes()
    {
        return _attributes;
    }

    void setAttributes(attr_t attributes)
    {
        _attributes = attributes;
    }
};