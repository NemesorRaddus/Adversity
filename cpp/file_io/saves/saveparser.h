#pragma once

//File generated using Raddus Binary Data Parser Generator v1.0.1 Beta

class QByteArray;

struct SaveData;

class SaveParser
{
public:
    static SaveData readData(QByteArray &array);
    static void writeData(QByteArray &array, const SaveData &data);
};
