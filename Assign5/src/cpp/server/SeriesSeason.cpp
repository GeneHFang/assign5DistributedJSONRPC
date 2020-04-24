#include "SeriesSeason.hpp"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

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

//Default constructor
SeriesSeason::SeriesSeason(){
    
    title="";
    titleAndSeason="";
    season=-1;
    rating="";
    genre="";
    imgURL="";
    plot="";
    //episodes=null;
}

//Constructor from individual values
SeriesSeason::SeriesSeason(string ptitle, int pseason, string prating, 
    string pgenre, string pimgurl, string pplot, vector<Episode> pepisodes){
    title=ptitle;
    titleAndSeason=ptitle+" - Season "+to_string(pseason);
    season = pseason;
    rating = prating;
    genre = pgenre;
    imgURL = pimgurl;
    plot=pplot;
    episodes = pepisodes;
}

//Constructor from jsonObj
SeriesSeason::SeriesSeason(const Json::Value& jsonObj){
    Json::Value::Members mbr = jsonObj.getMemberNames();

    for (vector<string>::const_iterator i = mbr.begin(); i != mbr.end(); i++){
        Json::Value js = jsonObj[*i];
        if (*i=="Title"){
            title = js.asString();
        } else if (*i=="imdbRating"){
            rating = js.asString();
        } else if (*i=="Genre"){
            genre = js.asString();
        } else if (*i=="Poster"){
            imgURL = js.asString();
        } else if (*i=="Season"){
            season = stoi(js.asString());
        } else if (*i=="Plot"){
            plot = js.asString();
        } else if (*i=="Episodes"){
            auto jsonEpisodes = jsonObj[*i];
            for (Json::Value::ArrayIndex i = 0 ; i != jsonEpisodes.size(); i++){
                Episode ep(jsonEpisodes[i]);
                
                /* Goes into Episode constructor
                string t = jsonEpisodes[i]["Title"].asString();
                int num = stoi(jsonEpisodes[i]["Episode"].asString());
                string rate = jsonEpisodes[i]["imdbRating"].asString();
                Episode ep(t, num, rate);
                */
                episodes.push_back(ep);
            }
        }
    }
    titleAndSeason = title + " - Season " + to_string(season);
}

//Constructor from json formatted String
SeriesSeason::SeriesSeason(string jsonString){
    Json::Reader reader;
    Json::Value jsonObj;

    bool parseSuccess = reader.parse(jsonString, jsonObj, false);
    if (parseSuccess){
        Json::Value::Members mbr = jsonObj.getMemberNames();

        for (vector<string>::const_iterator i = mbr.begin(); i != mbr.end(); i++){
            Json::Value js = jsonObj[*i];
            if (*i=="Title"){
                title = js.asString();
            } else if (*i=="imdbRating"){
                rating = js.asString();
            } else if (*i=="Genre"){
                genre = js.asString();
            } else if (*i=="Poster"){
                imgURL = js.asString();
            } else if (*i=="Season"){
                season = stoi(js.asString());
            } else if (*i=="Plot"){
                plot = js.asString();
            } else if (*i=="Episodes"){
                auto jsonEpisodes = jsonObj[*i];
                for (Json::Value::ArrayIndex i = 0 ; i != jsonEpisodes.size(); i++){
                    Episode * ep = new Episode(jsonEpisodes[i]);
                    
                    /* Goes into Episode constructor
                    string t = jsonEpisodes[i]["Title"].asString();
                    int num = stoi(jsonEpisodes[i]["Episode"].asString());
                    string rate = jsonEpisodes[i]["imdbRating"].asString();
                    Episode ep(t, num, rate);
                    */
                    episodes.push_back(*ep);
                }
            }
        }
        titleAndSeason = title + " - Season " + to_string(season);
    }
    else{
        cout << "Constructor parse error with " << jsonString << endl;
    }
}

//Destructor
SeriesSeason::~SeriesSeason(){
    
    title="";
    rating="";
    genre="";
    imgURL="";
    season=-1;
    plot="";
    //episodes = 0; 
}

//Convert current object to json formatted string
string SeriesSeason::toString(){
    string ret= "{}";

    Json::Value jsonLib;
    jsonLib = toJson();
    ret = jsonLib.toStyledString();
    return ret;
}

//Convert current object to JSON value
Json::Value SeriesSeason::toJson(){
    Json::Value jsonLib;

    jsonLib["Title"] = title;
    jsonLib["imdbRating"] = rating;
    jsonLib["Season"] = season;
    jsonLib["Poster"] = imgURL;
    jsonLib["Genre"] = genre;
    jsonLib["Plot"] = plot;
    

    Json::Value epsArr; 
   // string jsonEpisodes = "{\"Episodes\":[";
    
    for(int i = 0 ; i < episodes.size() ; i++ ){
        epsArr.append(episodes[i].toJson());
        // if (i = episodes.size()-1) {
        //     jsonEpisodes+=(episodes[i].toString()+"]}");
        // }
        // else {
        //     jsonEpisodes+=(episodes[i].toString()+",");
        // }
    }

    // Json::Reader r;
    // Json::Value epp; 
    // r.parse(jsonEpisodes, epp, false);
    // auto episodeArray = epp["Episodes"];
    jsonLib["Episodes"] = epsArr;

    return jsonLib;

}

//Setter
void SeriesSeason::setValues(string ptitle, string pseason, string prating, 
    string pgenre, string pimgurl, string pplot, vector<Episode> pepisodes){
        title=ptitle;
        titleAndSeason=ptitle+" - Season "+pseason;
        season = stoi(pseason);
        rating = prating;
        genre = pgenre;
        imgURL = pimgurl;
        plot = pplot;
        episodes = pepisodes;
}

//Log to console
void SeriesSeason::print(){
    cout << "SS printer" << endl;
    cout << toString() << endl;
    // cout << "Title: " << title << endl;
    // cout << "Season: " << season << endl;
    // cout << "Rating: " << rating << endl;
    // cout << "Genre: " << genre << endl;
    // cout << "Plot: " << plot << endl;
    // cout << "Poster: " << imgURL << endl;
    // cout << "Episodes: [" << endl;

    // for (int i = 0 ; i < episodes.size() ; i++)
    // {
    //     episodes[i].
    // }
}