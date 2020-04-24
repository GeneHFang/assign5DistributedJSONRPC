#include "Episode.hpp"
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
Episode::Episode(){
    title="";
    episode=-1;
    rating="";
}

//Constructor from individual values
Episode::Episode(string ptitle, int pepisode, string prating){
    title = ptitle;
    episode = pepisode;
    rating = prating;
}

//Constructor from JSON value
Episode::Episode(const Json::Value& jsonObj){
    Json::Reader reader;
    Json::Value root;

    string jsonString = jsonObj.toStyledString();

    bool parseSuccess = reader.parse(jsonString,root,false);
    if(parseSuccess){
        //cout << "successful parse" << endl;
        Json::Value::Members mbr = root.getMemberNames();
        for(vector<string>::const_iterator i = mbr.begin(); i!= mbr.end(); i++){
            //cout << *i << " " << endl;
            Json::Value jsonM = root[*i];
            if(*i=="Title"){
            title = jsonM.asString();
            }else if(*i=="Episode"){
            episode = stoi(jsonM.asString());
            }else if(*i=="imdbRating"){
            rating = jsonM.asString();
            }
        }
    }else{
        cout << "MediaDescription constructor parse error with input: " << jsonString
            << endl;
}
}

//Constructor from json formatted string
Episode::Episode(string jsonString){
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
            } else if (*i=="Episode"){
                episode = stoi(js.asString());
            }
        } 
    }
    else{
        cout << "Constructor parse error with " << jsonString << endl;
    }
}

//Destrcutor
Episode::~Episode(){
    title="";
    episode=-1;
    rating="";
}

//Convert current object to json formatted string
string Episode::toString(){
    Json::Value jsonObj;
    string ret = "{}";
    jsonObj = toJson();
    cout << "json to string : " << jsonObj.toStyledString() << endl;
    ret = jsonObj.toStyledString();
    cout << "ret to string : " << ret << endl;
    
    return ret;
}

//Convert current object to json value
Json::Value Episode::toJson(){
    Json::Value jsonLib;
    jsonLib["Title"] = title;
    jsonLib["Episode"] = episode;
    jsonLib["imdbRating"] = rating;
    return jsonLib;
}

//Setter
void Episode::setValues(string ptitle, int pepisode, string prating){
    title = ptitle;
    episode = pepisode;
    rating = prating;
}

//Log to console
void Episode::print(){
   cout << "Title: " << title << endl;
   cout << "Episode: " << episode << endl;
   cout << "Rating: " << rating << endl;
}