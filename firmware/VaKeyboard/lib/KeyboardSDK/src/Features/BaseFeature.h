#pragma once

class BaseFeature
{
    private:
        static bool areFeaturesDisabledFlag;

    protected:
        BaseFeature();

        bool areFeaturesDisabled();
        static void enableFeatureProcessing();  // ActionEvaluator needs to be redesigned to get rid off function pointers to get rid off this static
        void blockFeatureProcessing();
};