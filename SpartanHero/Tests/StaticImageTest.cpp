/**
 * @file StaticImageTest.cpp
 * @author charl
 */
#include <pch.h>
#include <gtest/gtest.h>
#include <StaticImage.h>


class StaticImageTest : public ::testing::Test {
protected:
    void SetUp() override {
        spartanHero = new SpartanHero();
        // StaticImage object
        staticImage = new StaticImage(spartanHero, 10, 20, 30, 40, "background1.png");
    }

    StaticImage* staticImage;
    SpartanHero* spartanHero;
};

// Test case to verify StaticImage constructor
TEST_F(StaticImageTest, ConstructorInitialization)
{
    // Check if StaticImage object is not null
    ASSERT_NE(staticImage, nullptr);
    ASSERT_TRUE(staticImage->GetSizeX());
    ASSERT_TRUE(staticImage->GetSizeY());


}

