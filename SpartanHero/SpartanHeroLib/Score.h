/**
 * @file Score.h
 * @author charl
 *
 * Score of Game
 *
 * This class holds information for the score of the game
 */

#ifndef SPARTANHERO_SPARTANHEROLIB_SCORE_H
#define SPARTANHERO_SPARTANHEROLIB_SCORE_H

/**
 * This class is for the score of the game
 */
class Score
{
private:
    /// score of game
    int mScore = 0;
    /// meter score
    int mMeterScore = 0;
    /// potential total score
    int mTotalScore = 0;
public:
    /**
     * Constructor
     */
    Score() {mScore = 0;}
    /**
     * Getter for score
     * @returns score
     */
    int GetScore() const { return mScore; }
    /**
     * Getter for total score
     * @returns total score
     */
    int GetTotalScore() const { return mTotalScore; }
    /**
     * Function to increment score
     * @param amount amount added
     *
     */
    void Increment(int amount) { mScore += amount; }
    /**
     * Function to increment total score
     * @param amount amount added
     *
     */
    void IncrementTotal(int amount) { mTotalScore += amount; }
    /**
     * Function to reset score
     */
    void ResetScore() {mScore = 0;}
    /**
     * Function to reset total score
     */
    void ResetTotalScore() {mTotalScore = 0;}
    /**
    * Getter for meter score
    * @returns meter score
    */
    int GetMeterScore(){return mMeterScore;}
    /**
     * Function to increment meter score
     * @param amount amount added
     *
     */
    void IncrementMeterTotal(int amount) { mMeterScore += amount; }
    /**
     * Function to reset meter score
     */
    void ResetMeterScore() {mMeterScore = 0;}

};
#endif //SPARTANHERO_SPARTANHEROLIB_SCORE_H
