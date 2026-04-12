/**
 * @file SpartanHeroTest.cpp
 * @author charl, Conner
 */

#include <pch.h>
#include <regex>
#include <string>
#include <fstream>
#include <streambuf>
#include "gtest/gtest.h"
#include <Level.h>

using namespace std;

class SpartanHeroTest : public ::testing::Test{
protected:
    /**
    * Read a file into a wstring and return it.
    * @param filename Name of the file to read
    * @return File contents
    */
    wstring ReadFile(const wxString &filename)
    {
        ifstream t(filename.ToStdString());
        wstring str((istreambuf_iterator<char>(t)),
                    istreambuf_iterator<char>());

        return str;
    }
};

TEST_F(SpartanHeroTest, GameLoadTest)
{
    SpartanHero game;

    wxXmlDocument xmlDoc;

    auto file = L"../levels/level0.xml";
    if(!xmlDoc.Load(file))
    {
        wxMessageBox(L"Unable to load SpartanHero file.");
        return;
    }

    Level level;
    level.LoadLevel(xmlDoc, &game);

    ASSERT_EQ(game.GetPlayX(), 1304);
    ASSERT_EQ(game.GetPlayY(), 900);
}