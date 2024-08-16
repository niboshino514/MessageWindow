#include "File.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <array>
#include <sstream>
#include <locale>
#include <codecvt>
#include <windows.h>



std::vector<std::string> EvoLib::File::Split(const std::string& input, const char& delimiter)
{
    std::istringstream stream(input);	// string��getline�Ŏg����f�[�^�ɕϊ��H
    std::string field;					// ��������������1�����i�[����H
    std::vector<std::string> result;	// ������̕�����̔z��

    while (getline(stream, field, delimiter))
    {
        result.push_back(field);
    }

    // ���������������Ԃ�
    return result;
}

bool EvoLib::File::IsFileExist(const std::string& name)
{
    return std::filesystem::is_regular_file(name);
}


std::vector<std::vector<std::string>> EvoLib::File::CsvFileLoading(const std::string& filePath, LoadType loadType)
{
    // �t�@�C�����̓ǂݍ���
    std::ifstream ifs(filePath);
    std::string line;


    // �s�J�E���g
    int lineCount = 0;

    // �ǂݍ��񂾃e�L�X�g
    std::vector<std::vector<std::string>>loadText;

    while (getline(ifs, line))
    {
        // �s�J�E���g�����Z
        lineCount++;


        // ��s�ڂ̏������΂�
        if (lineCount <= 1 && loadType == File::LoadType::SkipFirstLine ||
            lineCount <= 1 && loadType == File::LoadType::DoubleSkip)
        {
            continue;
        }



        // csv�f�[�^1�s��','�ŕ����̕�����ɕ���
        std::vector<std::string>	strvec = File::Split(line, ',');

        if (static_cast<int>(strvec.size()) == 0)
        {
            break;
        }

        // ���ڂ��X�L�b�v����
        if (loadType == File::LoadType::SkipOneColumn ||
            loadType == File::LoadType::DoubleSkip)
        {
            strvec.erase(strvec.begin());
        }

        loadText.push_back(strvec);
    }



    return loadText;
}

std::vector<std::vector<std::string>> EvoLib::File::CsvFileLoading_Revision(const std::string& filePath, const bool isSkipOneArray, const int skipColumnNum)
{
    // �t�@�C�������݂��Ȃ��ꍇ
    if (!IsFileExist(filePath))
    {
        std::string errorText = "[" + filePath + "] " +
            "�t�@�C���͑��݂��Ȃ��悤�ł��B";

        EvoLib::Assert::ErrorMessageBox(errorText);
    }

    // �ǂݍ��񂾃e�L�X�g
    std::vector<std::vector<std::wstring>> loadText;
    std::wifstream file(EvoLib::Convert::StringToWString(filePath));
    file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t>));
    std::vector<std::vector<std::wstring>> data;
    std::wstring line;

    // �s�J�E���g
    int lineCount = 0;
    bool insideQuotes = false;
    std::wstring currentCell;
    std::vector<std::wstring> row;

    while (std::getline(file, line))
    {
        // �s�J�E���g�����Z
        lineCount++;

        // ��s�ڂ̏������΂�
        if (isSkipOneArray && lineCount <= 1)
        {
            continue;
        }

        for (wchar_t ch : line)
        {
            if (ch == L'"')
            {
                insideQuotes = !insideQuotes;
            }
            else if (ch == L',' && !insideQuotes)
            {
                row.push_back(currentCell);
                currentCell.clear();
            }
            else
            {
                currentCell += ch;
            }
        }

        
        row.push_back(currentCell);
        currentCell.clear();

        // ����X�L�b�v����
        if (skipColumnNum > 0)
        {
            for (int i = 0; i < skipColumnNum; i++)
            {
                if (!row.empty())
                {
                    row.erase(row.begin());
                }
            }
        }

        data.push_back(row);
        row.clear();
    }

    std::vector<std::vector<std::string>> loadStringData;

    // �ǂݍ��񂾃f�[�^��string�^�ɕϊ�
    for (auto& row : data)
    {
        std::vector<std::string> tempRow;

        for (auto& cell : row)
        {
            tempRow.push_back(EvoLib::Convert::WStringToString(cell));
        }

        loadStringData.push_back(tempRow);
    }

    return loadStringData;
}

void EvoLib::File::SimpleCsvFileWriting(const std::string& fileName, const std::string& writingText)
{
    std::ofstream writing_file;
    writing_file.open(fileName, std::ios::out);

    writing_file << writingText << std::endl;

    writing_file.close();
}
