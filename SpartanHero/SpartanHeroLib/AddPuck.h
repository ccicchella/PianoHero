/**
 * @file AddPuck.h
 * @author Caden McDonald
 *
 * Visitor class
 *
 * This class is a child of ItemVisitor and visits the score/soundboards
 */

#ifndef SPARTANHERO_SPARTANHEROLIB_ADDPUCK_H
#define SPARTANHERO_SPARTANHEROLIB_ADDPUCK_H

#include "ItemVisitor.h"
#include "Track.h"
/**
 * This class is a visitor to add pucks
 */
class AddPuck : public ItemVisitor
{
private:
    /// shared pointer to pucks
    std::shared_ptr<PuckItem> mPuck;
    /// shared pointer to tracks
    std::vector<std::shared_ptr<Track>> mTracks;
    /// width
    double mScoreboardW;
    /// height
    double mScoreboardH;

public:
    /**
     * Function to push puck
     * @param puck shared pointer to puck
     */
    void PuckPush(std::shared_ptr<PuckItem> puck) {mPuck = puck;}
    /**
     * Getter for tracks
     * @returns tracks
     */
    std::vector<std::shared_ptr<Track>> GetTracks() {return mTracks;}
    /**
     * Getter for scoreboard width
     * @return scoreboard width
     */
    double GetmScoreboardW() {return mScoreboardW;}
    /**
     * Getter for scoreboard height
     * @return scoreboard height
     */
    double GetmScoreboardH() {return mScoreboardH;}

    void VisitSoundboard(Soundboard* soundboard) override;
    void VisitScoreboard(Scoreboard *scoreboard) override;
};

#endif //SPARTANHERO_SPARTANHEROLIB_ADDPUCK_H
