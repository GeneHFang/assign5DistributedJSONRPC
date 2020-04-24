#include "Episode.hpp"
#include <string>
#include <cmath>
#include <vector>
#include <json/json.h>

using namespace std;

/**
 * Copyright 2020 Tim Lindquist, Gene Li
 *
 * This software is the intellectual property of the author, and can not be 
 * distributed, used, copied, or reproduced, in whole or in part, for any purpose, commercial or otherwise.
 * The author grants the ASU Software Engineering program the right to copy, execute, and evaluate this
 * work for the purpose of determining performance of the author in coursework,
 * and for Software Engineering program evaluation, so long as this copyright and
 * right-to-use statement is kept in-tact in such use.
 * All other uses are prohibited and reserved to the author.
 * 
 *
 * Purpose: SeriesSeason is a class whose properties describe a single SeriesSeason.
 * Ser321 Principles of Distributed Software Systems
 * see http://pooh.poly.asu.edu/Ser321
 * @author Tim Lindquist Tim.Lindquist@asu.edu
 *         Gene H Li ghli1@asu.edu
 *         Software Engineering, CIDSE, IAFSE, ASU Poly
 * @version April 2020
 */

class SeriesSeason {
    public:
        //attributes
        string title;
        string titleAndSeason;
        int season;
        string rating;
        string genre;
        string imgURL; 
        string plot;
        vector<Episode> episodes;


        //constructors/destructor
        SeriesSeason();
        SeriesSeason(string title, int season, string rating, string genre, string imgurl, string plot, vector<Episode> episodes);
        SeriesSeason(const Json::Value& jsonObj);
        SeriesSeason(string jsonString);
        ~SeriesSeason();
        
        //Returns object as string Json 
        string toString();

        //Returns object as Json::Value
        Json::Value toJson();

        //Creates object from Json::Value
        void fromJson(Json::Value json);

        //setter
        void setValues(string title, string season, string rating, string genre, string imgurl, string plot, vector<Episode> episodes);

        //log to console
        void print();
};