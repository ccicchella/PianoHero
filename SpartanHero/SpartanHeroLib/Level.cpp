/**
 * @file Level.cpp
 * @author Caden McDonald, Conner Smith
 *
 * Level class, holds information unique to each level
 */

#include "pch.h"
#include "Level.h"
#include "StaticImage.h"
#include "SoundBoardDeclaration.h"
#include "MeterDeclaration.h"
#include "PuckDeclaration.h"
#include "Meter.h"
#include "Soundboard.h"
#include "PuckItem.h"
#include "PuckLongItem.h"
#include "Scoreboard.h"
#include "AddPuck.h"
#include "Sound.h"

using namespace std;

/// What is the border of the left and right
/// of the tracks? This is the percentage of
/// the space to the left of the first track line
/// and to the right of the last track line
const double Border = 0.09;

/// Top clearance so we don't draw past the cover
/// as a fraction of the soundboard height. This
/// is where the pucks come in
const double TopClearance = 0.1;

/// Percentage down on the soundboard to the keys
/// This is where the pucks go under the key and
/// disappear.
const double KeyRow = 0.85;

/**
 * Loads the level 0 xml file into the program
 * @param level0 the XML file that is being loaded
 */
class PuckItem;
class SpartanHero;
class PuckDeclaration;
class ItemDeclaration;
/**
 * Function to load level
 * @param levelName name of level
 * @param game pointer to SpartanHero
 */
void Level::LoadLevel(const wxXmlDocument& levelName, SpartanHero *game)
{
    mGame = game;

    auto level = levelName.GetRoot();
    auto size = level->GetAttribute(L"size");
    int playX = wxAtoi(size.BeforeFirst(','));
    int playY = wxAtoi(size.AfterFirst(','));
    game->SetPlayX(playX);
    game->SetPlayY(playY);


    auto audio = level->GetChildren();
    auto audioChildren = audio->GetChildren();
    for (; audioChildren; audioChildren=audioChildren->GetNext())
    {
        XmlAudio(audioChildren, game);
    }

    auto declarations = audio->GetNext();
    auto decChildren = declarations->GetChildren();
    for (; decChildren; decChildren=decChildren->GetNext())
    {
        XmlDeclaration(decChildren, game);
    }

    auto items = declarations->GetNext();
    auto itemChildren = items->GetChildren();

    for (; itemChildren; itemChildren=itemChildren->GetNext())
    {
        XmlItem(itemChildren, game);
    }

    auto music = items->GetNext();
    XmlMusic(music, game);
}

/**
 * XML declaration for Level
 * @param declaration pointer to xml node
 * @param game pointer to game class
 */
void Level::XmlDeclaration(wxXmlNode * declaration, SpartanHero *game)
{
    auto name = declaration->GetName();
    auto identifier = declaration->GetAttribute(L"id").ToStdString();
    auto imageFile = declaration->GetAttribute(L"image").ToStdString();
    auto sizes = declaration->GetAttribute(L"size");

    // Get the two sizes from the tuple
    int sizeX, sizeY;
    sizeX = wxAtoi(sizes.BeforeFirst(','));
    sizeY = wxAtoi(sizes.AfterFirst(','));

    if(name == L"image")
    {
        auto itemDec = make_shared<ItemDeclaration>(imageFile, sizeX, sizeY);

        mDeclarations[identifier]=itemDec;
    }

    else if(name == L"sound-board")
    {
        /*
         * Track declaration should be added in here somewhere -Ben
         */

        auto sizeBeats = wxAtoi(declaration->GetAttribute(L"size-beats"));
        auto topWidth = wxAtoi(declaration->GetAttribute(L"top-width"));
        auto coverImage = declaration->GetAttribute(L"cover").ToStdString();

        auto soundDec = make_shared<SoundBoardDeclaration>(imageFile, sizeX, sizeY, sizeBeats, topWidth, coverImage);

        mDeclarations[identifier]=soundDec;
    }

    else if(name == L"score-board")
    {
        auto itemDec = make_shared<ItemDeclaration>(imageFile, sizeX, sizeY);

        mDeclarations[identifier]=itemDec;
    }

    else if(name == L"meter")
    {
        auto needleImage = declaration->GetAttribute(L"needle").ToStdString();
        auto coverImage = declaration->GetAttribute(L"cover").ToStdString();

        auto meterDec = make_shared<MeterDeclaration>(imageFile, sizeX, sizeY, needleImage, coverImage);

        mDeclarations[identifier]=meterDec;
    }

    else if(name == L"note")
    {
        auto track = wxAtoi(declaration->GetAttribute(L"track"));
        auto tolerance = wxAtof(declaration->GetAttribute(L"tolerance"));

        auto noteDec = make_shared<PuckDeclaration>(imageFile, sizeX, sizeY, track, tolerance);

        mDeclarations[identifier]=noteDec;
    }

    else{
        wxMessageBox(L"Unknown declaration type.");
        return;
    }
}

/**
 * XML item information function
 * @param item pointer to xml node
 * @param game pointer to game class
 */
void Level::XmlItem(wxXmlNode * item, SpartanHero *game)
{
    std::shared_ptr<Item> ourItem;

    auto name = item->GetName();
    auto identifier = item->GetAttribute(L"id").ToStdString();
    auto pos = item->GetAttribute(L"p");

    // Get the two positions from the tuple
    int posX, posY;
    posX = wxAtoi(pos.BeforeFirst(','));
    posY = wxAtoi(pos.AfterFirst(','));

    if(name == L"image")
    {
        auto imageDec = mDeclarations[identifier];

        auto image = imageDec->getMImageFileNameDeclaration();
        auto sizeX = imageDec->getMSizeXDeclaration();
        auto sizeY = imageDec->getMSizeYDeclaration();

        ourItem = std::make_shared<StaticImage>(game, sizeX, sizeY, posX, posY, image);
    }
    else if (name == L"sound-board")
    {
        auto soundboardDec = mDeclarations[identifier];

        auto boardImage = soundboardDec->getMImageFileNameDeclaration();
        auto coverImage = soundboardDec->GetmCoverImage();
        auto sizeX = soundboardDec->getMSizeXDeclaration();
        auto sizeY = soundboardDec->getMSizeYDeclaration();
        auto topWidth = soundboardDec->GetTopWidth();
        auto sizeBeats = soundboardDec->GetSizeBeats();

        auto sbChildren = item->GetChildren();
        ourItem = std::make_shared<Soundboard>(game, sizeX, sizeY, posX, posY, boardImage, coverImage, sbChildren, topWidth, sizeBeats);

    }
    else if(name == L"score-board")
    {
        auto scoreboardDec = mDeclarations[identifier];

        auto image = scoreboardDec->getMImageFileNameDeclaration();
        auto sizeX = scoreboardDec->getMSizeXDeclaration();
        auto sizeY = scoreboardDec->getMSizeYDeclaration();

        ourItem = std::make_shared<Scoreboard>(game,sizeX,sizeY,posX,posY,image);
    }
    else if(name == L"meter")
    {
        auto meterDec = mDeclarations[identifier];

        auto image = meterDec->getMImageFileNameDeclaration();
        auto needleImage = meterDec->GetmNeedleImage();
        auto coverImage = meterDec->GetmCoverImage();
        auto sizeX = meterDec->getMSizeXDeclaration();
        auto sizeY = meterDec->getMSizeYDeclaration();

        ourItem = std::make_shared<Meter>(game, sizeX, sizeY, posX, posY, image, needleImage, coverImage);
    }
    else{
        wxMessageBox(L"Unknown item type.");
        return;
    }
    if (ourItem != nullptr)
    {
        game->Add(ourItem);
    }
}
/**
 * Function for xml music
 * @param music pointer to xml node
 * @param game pointer to SpartanHero
 */
void Level::XmlMusic(wxXmlNode *music, SpartanHero *game)
{
    int startX = 0;
    int startY = 0;

    game->SetBeatsPerMinute(wxAtoi(music->GetAttribute(L"beats-per-minute")));
    game->SetBeatsPerMeasure(wxAtoi(music->GetAttribute(L"beats-per-measure")));
    game->SetMaxMeasure(wxAtoi(music->GetAttribute(L"measures")));

    auto backing = music->GetAttribute(L"backing").ToStdString();

    auto note = music->GetChildren();
    for(; note; note = note->GetNext())
    {
        auto identifier = note->GetAttribute(L"id").ToStdString();
        auto sound = note->GetAttribute(L"sound");
        auto measure = std::stoi(note->GetAttribute(L"measure").ToStdString());
        auto beat = std::stod(note->GetAttribute(L"beat").ToStdString());
        auto duration = std::stod(note->GetAttribute(L"duration").ToStdString());

        auto puckDec = mDeclarations[identifier];

        auto image = puckDec->getMImageFileNameDeclaration();
        auto sizeX = puckDec->getMSizeXDeclaration();
        auto sizeY = puckDec->getMSizeYDeclaration();
        auto track = puckDec->GetmTrack();
        auto tolerance = puckDec->GetmTolerance();

        if (duration < 1)
        {
            shared_ptr<PuckItem> puck = std::make_shared<PuckItem>(game,sizeX, sizeY, startX, startY, image, track, tolerance, beat, measure, duration, sound);

            if (puck != nullptr)
            {
                AddPuck soundboardVisitor;
                soundboardVisitor.PuckPush(puck);
                mGame->Accept(&soundboardVisitor);
            }
        }
        else
        {
            std::shared_ptr<PuckItem> puck = std::make_shared<PuckLongItem>(game,sizeX,sizeY,startX,startY,image,track,tolerance,beat,measure,duration, sound);

            if (puck != nullptr)
            {
                AddPuck soundboardVisitor;
                soundboardVisitor.PuckPush(puck);
                mGame->Accept(&soundboardVisitor);
            }
        }
    }
}

/**
 * Function for XML audio
 * @param audio pointer to xml node
 * @param game pointer to SpartanHero
 */
void Level::XmlAudio(wxXmlNode* audio, SpartanHero *game)
{
    auto name = audio->GetAttribute(L"name");
    auto filename = audio->GetAttribute(L"audio");
    double volume2;
    auto volume = audio->GetAttribute(L"volume");
    auto sound = make_shared<Sound>();
    volume.ToDouble(&volume2);
    if (volume2>=0)
    {
        sound->SetVolume(volume2);
    }
    sound->loadAudioFile(game->GetAudioEngine(), filename);

    game->AddToSoundMap(name, sound);
}