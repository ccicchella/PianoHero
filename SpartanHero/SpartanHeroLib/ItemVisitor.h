/**
 * @file ItemVisitor.h
 * @author Caden McDonald
 *
 * Item visitor class
 *
 * This class is a visitor class for the items in the game
 */

#ifndef SPARTANHERO_SPARTANHEROLIB_ITEMVISITOR_H
#define SPARTANHERO_SPARTANHEROLIB_ITEMVISITOR_H

class Meter;
class Scoreboard;
class StaticImage;
class PuckItem;
class PuckLongItem;
class Soundboard;
/**
 * This class is a visitor for items
 */
class ItemVisitor
{
private:

public:
    /**
    * Constructor
    * Ensures this is an abstract class
    */
    ItemVisitor() {}

    /**
     * Virtual Deconstructor
     */
    virtual ~ItemVisitor() {}

    /**
     * Visit an object
     * @param soundboard object we are visiting
     */
    virtual void VisitSoundboard(Soundboard* soundboard) {}

    /**
     * Visit an object
     * @param meter object we are visiting
     */
    virtual void VisitMeter(Meter* meter) {}

    /**
     * Visit an object
     * @param scoreboard object we are visiting
     */
    virtual void VisitScoreboard(Scoreboard* scoreboard) {}

    /**
     * Visit an object
     * @param staticImage object we are visiting
     */
    virtual void VisitStaticImage(StaticImage* staticImage) {}

    /**
     * Visit an object
     * @param puckItem object we are visiting
     */
    virtual void VisitPuckItem(PuckItem* puckItem) {}

    /**
     * Visit an object
     * @param puckLongItem object we are visiting
     */
    virtual void VisitPuckLongItem(PuckLongItem* puckLongItem) {}


};

#endif //SPARTANHERO_SPARTANHEROLIB_ITEMVISITOR_H
