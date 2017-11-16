#include "globalutilities.h"

#include <sstream>
#include <string>

double GlobalUtilities::roundDouble(double d, unsigned prec) noexcept
{
    std::stringstream ss;
    ss << std::fixed;
    ss.precision(prec);
    ss << d;
    return QString(ss.str().data()).toDouble();
}

QString GlobalUtilities::alterNormalTextToInternal(QString normalText) noexcept
{
    normalText.remove(' ');
    normalText.remove('/');
    normalText.remove('\\');
    normalText.remove('\'');
    normalText.remove('\"');
    normalText.remove('|');

    normalText.replace('ć','c');
    normalText.replace('ę','e');
    normalText.replace('ł','l');
    normalText.replace('ń','n');
    normalText.replace('ó','o');
    normalText.replace('ś','s');
    normalText.replace('ź','z');
    normalText.replace('ż','z');

    normalText.replace('Ć','C');
    normalText.replace('Ę','E');
    normalText.replace('Ł','L');
    normalText.replace('Ń','N');
    normalText.replace('Ó','O');
    normalText.replace('Ś','S');
    normalText.replace('Ź','Z');
    normalText.replace('Ż','Z');

    return normalText;
}

QString GlobalUtilities::sanitize(QString script) noexcept
{
    script.remove(';');
    script.remove('|');
    script.remove('&');
    script.remove('\n');

    int parCnt = 0;
    for (int i=0;i<script.size();++i)
    {
        if (script[i] == '(')
            ++parCnt;
        else if (script[i] == ')')
        {
            --parCnt;
            if (parCnt == 0)
            {
                script.remove(i+1,script.size()-i-1);
                break;
            }
        }
    }

    return script;
}
