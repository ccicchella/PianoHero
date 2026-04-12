/**
 * @file Level.h
 * @author Caden McDonald
 *
 * This class helps get the xml data for the different levels
 */

#ifndef SPARTANHERO_SPARTANHEROLIB_LEVEL_H
#define SPARTANHERO_SPARTANHEROLIB_LEVEL_H

#include "Item.h"
#include "SpartanHero.h"
#include "Score.h"
#include "PuckItem.h"
#include <map>

/**
 * This class defines each level and what is in it
 */
class Level
{
private:
    /// Pointer to SpartanHero
    SpartanHero* mGame;
    /// map of declarations
    std::map<wxString, std::shared_ptr<ItemDeclaration>> mDeclarations = {};
    /// shared pointer to pucks
    std::vector<std::shared_ptr<PuckItem>> mPucks;

public:
    void LoadLevel(const wxXmlDocument& levelName, SpartanHero *game);

    void XmlDeclaration(wxXmlNode *declaration, SpartanHero *game);
    void XmlItem(wxXmlNode *item, SpartanHero *game);
    void XmlMusic(wxXmlNode *music, SpartanHero *game);
    /**
     * Getter for declaration
     * @returns declaration
     */
    std::map<wxString, std::shared_ptr<ItemDeclaration>> GetmDeclarations() {return mDeclarations;}
    /**
     * Getter for pucks
     * @returns pucks
     */
    std::vector<std::shared_ptr<PuckItem>> GetPucks() {return mPucks;}

    void XmlAudio(wxXmlNode *audio, SpartanHero *game);
};

#endif //SPARTANHERO_SPARTANHEROLIB_LEVEL_H