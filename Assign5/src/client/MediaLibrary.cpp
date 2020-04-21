#include "MediaLibrary.hpp"
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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
 * Purpose: MediaLibrary is a class defining the interface between clients
 * and the server. The server implementation of MediaLibrary
 * provides storage for description of multiple media works -- SeriesSeason(s).
 * Ser321 Principles of Distributed Software Systems
 * see http://pooh.poly.asu.edu/Ser321
 * @author Tim Lindquist Tim.Lindquist@asu.edu
 *         Gene H Li ghli1@asu.edu
 *         Software Engineering, CIDSE, IAFSE, ASU Poly
 * @version April 2020
 */

//Constructor
MediaLibrary::MediaLibrary(){
   initLibraryFromJsonFile("seriesTest.json");
}

//Destructor
MediaLibrary::~MediaLibrary() {
   media.clear();
}

//Appends a map of seriesSeasons to current library
void MediaLibrary::addLibrary(std::map<std::string, SeriesSeason> lib)
{
   media.insert(lib.begin(),lib.end());
}

//Appends a single SeriesSeason instance to current library (uses C++17 syntax)
bool MediaLibrary::addToLibrary(SeriesSeason ssObj){
   bool ret; 

   auto const [position, hasBeenAdded] = media.insert({ssObj.titleAndSeason, ssObj});
   ret = hasBeenAdded;

   return ret;
}

//Removes a single SeriesSeason instance based on key
bool MediaLibrary::removeFromLibrary(std::string key){
   bool ret = false;

   ret = (media.erase(key) != 0);

   return ret;
}

//Clears library and reinitializes from json filename
bool MediaLibrary::initLibraryFromJsonFile(string jsonFileName){
   media.clear();
   bool ret = false;
   Json::Reader reader;
   Json::Value root;
   std::ifstream json(jsonFileName.c_str(), std::ifstream::binary);
   bool parseSuccess = reader.parse(json,root,false);
   if(parseSuccess){
      Json::Value::Members mbr = root.getMemberNames();
      for(vector<string>::const_iterator i = mbr.begin(); i!= mbr.end(); i++){
         Json::Value jsonMedia = root[*i];
         SeriesSeason * aDesc = new SeriesSeason(jsonMedia);
         cout << *i << endl;
         media[*i] = *aDesc;
         cout << "adding ";
         aDesc->print();
      }
      ret = true;
   }
   return ret;
}

//Creates a Json object from library
Json::Value MediaLibrary::getJson(){
   Json::Value jsonLib;
   for(std::map<string,SeriesSeason>::iterator i = media.begin();
                                                         i!= media.end(); i++){
      string key = i->first;
      cout << key << " " << endl;
      SeriesSeason aMedia = media[key];
      Json::Value jsonMedia = aMedia.toJson();
      jsonLib[key] = jsonMedia;
   }
   return jsonLib;
}

//Creates a json file based on library
bool MediaLibrary::toJsonFile(string jsonFileName){
   bool ret = false;
   Json::Value jsonLib = getJson();
   Json::StyledStreamWriter ssw("  ");
   std::ofstream jsonOutFile(jsonFileName.c_str(), std::ofstream::binary);
   ssw.write(jsonOutFile, jsonLib);
   return true;
}

//debugging use only, prints json formatted string to console
void MediaLibrary::printMap(){
   std::cout << getJson().toStyledString() << std::endl;
}

//Get a single instance of SeriesSeason using a key
SeriesSeason MediaLibrary::get(string aTitle){
   SeriesSeason aMedia = media[aTitle];
   return aMedia;
}

//Gets string vector of all keys in library
vector<string> MediaLibrary::getTitles(){
   vector<string> myVec;
   for(map<string,SeriesSeason>::iterator it = media.begin();
                                              it != media.end();++it){
      myVec.push_back(it->first);
   }
   return myVec;
}
