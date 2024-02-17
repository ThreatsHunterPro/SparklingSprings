#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

static string GetLineByIndex(const int _index, const string& _path)
{
    ifstream _stream = ifstream(_path);
    if (!_stream)
    {
        cerr << "Le flux n'a pas été correctement construit !" << endl;
        return string();
    }

    string _line;
    int _lineIndex = 0;
    while (getline(_stream, _line))
    {
        if (_lineIndex == _index) return _line;
        _lineIndex++;
    }
}

static void ReadAllFile(const string& _path, vector<string>& _array)
{
    ifstream _stream = ifstream(_path);
    if (!_stream) 
    {
        cerr << "Le flux n'a pas été correctement construit !" << endl;
        return;
    }

    string _line;
    while (getline(_stream, _line))
    {
        _array.push_back(_line);
    }
}

static bool ContainsText(const string& _text, const string& _word)
{
    return _text.find(_word) != string::npos;
}

static vector<char> GetAllChars(const string& _text)
{
    vector<char> _chars;
    for (const char _char : _text)
    {
        _chars.push_back(_char);
    }

    return _chars;
}

static vector<char> ReadAllChars(const string& _path) 
{
    vector<string> _texts;
    ReadAllFile(_path, _texts);

    vector<char> _allChars;
    for (const string& _text : _texts) 
    {
        const vector<char>& _newChars = GetAllChars(_text);
        _allChars.insert(_allChars.end(), _newChars.begin(), _newChars.end());
    }

    return _allChars;
}