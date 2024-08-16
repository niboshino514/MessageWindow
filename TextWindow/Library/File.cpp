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
    std::istringstream stream(input);	// stringをgetlineで使えるデータに変換？
    std::string field;					// 分割した文字列1つ文を格納する？
    std::vector<std::string> result;	// 分割後の文字列の配列

    while (getline(stream, field, delimiter))
    {
        result.push_back(field);
    }

    // 分割した文字列を返す
    return result;
}

bool EvoLib::File::IsFileExist(const std::string& name)
{
    return std::filesystem::is_regular_file(name);
}


std::vector<std::vector<std::string>> EvoLib::File::CsvFileLoading(const std::string& filePath, LoadType loadType)
{
    // ファイル情報の読み込み
    std::ifstream ifs(filePath);
    std::string line;


    // 行カウント
    int lineCount = 0;

    // 読み込んだテキスト
    std::vector<std::vector<std::string>>loadText;

    while (getline(ifs, line))
    {
        // 行カウントを加算
        lineCount++;


        // 一行目の処理を飛ばす
        if (lineCount <= 1 && loadType == File::LoadType::SkipFirstLine ||
            lineCount <= 1 && loadType == File::LoadType::DoubleSkip)
        {
            continue;
        }



        // csvデータ1行を','で複数の文字列に分割
        std::vector<std::string>	strvec = File::Split(line, ',');

        if (static_cast<int>(strvec.size()) == 0)
        {
            break;
        }

        // 一列目をスキップする
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
    // ファイルが存在しない場合
    if (!IsFileExist(filePath))
    {
        std::string errorText = "[" + filePath + "] " +
            "ファイルは存在しないようです。";

        EvoLib::Assert::ErrorMessageBox(errorText);
    }

    // 読み込んだテキスト
    std::vector<std::vector<std::wstring>> loadText;
    std::wifstream file(EvoLib::Convert::StringToWString(filePath));
    file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t>));
    std::vector<std::vector<std::wstring>> data;
    std::wstring line;

    // 行カウント
    int lineCount = 0;
    bool insideQuotes = false;
    std::wstring currentCell;
    std::vector<std::wstring> row;

    while (std::getline(file, line))
    {
        // 行カウントを加算
        lineCount++;

        // 一行目の処理を飛ばす
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

        // 列をスキップする
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

    // 読み込んだデータをstring型に変換
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
