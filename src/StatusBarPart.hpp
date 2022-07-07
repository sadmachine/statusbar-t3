#pragma once
#include <ncurses.h>
#include <string>

class StatusBarPart
{
    // Object vars
    std::string _text;
    attr_t _attributes;
    int _width;
    int _padding;

    // Static vars
    static int default_width;
    static int default_padding;

public:
    static const int WIDTH_FIT = 0;
    static const int WIDTH_GROW = -1;

    static int getDefaultWidth()
    {
        return default_width;
    }

    static void setDefaultWidth(int width)
    {
        default_width = width;
    }

    static int getDefaultPadding()
    {
        return default_padding;
    }

    static void setDefaultPadding(int padding)
    {
        default_padding = padding;
    }

    StatusBarPart()
    {
        _text = "";
        _attributes = 0;
        _width = StatusBarPart::default_width;
        _padding = StatusBarPart::default_padding;
    }

    std::string getText()
    {
        return _text;
    }

    StatusBarPart *setText(std::string text, attr_t attributes = -1)
    {
        _text = text;
        if (attributes != -1)
        {
            _attributes = attributes;
        }
        return this;
    }

    attr_t getAttributes()
    {
        return _attributes;
    }

    StatusBarPart *setAttributes(attr_t attributes)
    {
        _attributes = attributes;
        return this;
    }

    int getWidth()
    {
        return _width;
    }

    StatusBarPart *setWidth(int width)
    {
        _width = width;
        return this;
    }

    int getPadding()
    {
        return _padding;
    }

    StatusBarPart *setPadding(int padding)
    {
        _padding = padding;
        return this;
    }
};

int StatusBarPart::default_width = StatusBarPart::WIDTH_FIT;
int StatusBarPart::default_padding = 1;