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
 * <p/>
 * Purpose: C++ class which serves as server for a collection of SeriesSeasons, based on Prof. Lindquist's server of students. This
 * class is part of a SeriesSeason collection distributed application that uses JsonRPC.
 * Meant to run on OSX, Debian Linux, and Raspberry Pi Debian.
 * <p/>
 * Ser321 Principles of Distributed Software Systems
 * see http://pooh.poly.asu.edu/Ser321
 * @author Tim Lindquist Tim.Lindquist@asu.edu
 *         Gene H Li ghli1@asu.edu
 *         Software Engineering, CIDSE, IAFSE, ASU Poly
 * @version April 2020
 */


#include <jsonrpccpp/server.h>
#include <jsonrpccpp/server/connectors/httpserver.h>

#include <json/json.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <csignal>

#include "medialibraryserverstub.h"
#include "MediaLibrary.hpp"

using namespace jsonrpc;
using namespace std;

//server stub
class MediaLibraryServer : public medialibraryserverstub {
public:
   MediaLibraryServer(AbstractServerConnector &connector, int port); //Constructor
   virtual std::string serviceInfo(); //unused
   virtual bool toJsonFile(); //Saves library to seriesTest.json
   virtual Json::Value initLibraryFromJsonFile(); //Restores library from seriesTest.json
   virtual bool addLibrary(const Json::Value& aLibraryJson); //Appends contents of a libraryJson to server library
   virtual bool addToLibrary(const Json::Value& aSeriesSeasonJson); //Adds a SeriesSeason to server library
   virtual bool removeFromLibrary(const std::string& key); //Removes a SeriesSeason from server library
   virtual Json::Value getJson(); //Returns the server library formatted as Json
   virtual Json::Value get(const std::string& aTitle); //Returns a Json formatted SeriesSeason from server library with key
   virtual Json::Value getTitles(); //Returns a Json formatted array of all keys in server library 
   
private: 
   MediaLibrary * library; //server library
   MediaLibrary * searchLibrary; //unused
   int portNum; //port number connection is on
};

/**
 *Refer to the class declaration for medialibraryserverstub above for general purpose of functions 
 *Any comments on function implementations are additional details, if any  
*/

//Constructor creates a MediaLibrary object from seriesTest.json that rests on server 
MediaLibraryServer::MediaLibraryServer(AbstractServerConnector &connector, int port) :
                             medialibraryserverstub(connector){
   library = new MediaLibrary();
   library->initLibraryFromJsonFile("seriesTest.json");
   portNum = port;
}

//Originally copied from example, but found that I did not need to use it
string MediaLibraryServer::serviceInfo(){
   std::string msg =
                "SeriesSeason collection management service.";
   stringstream ss;
   ss << portNum;
   cout << "serviceInfo called. Returning: SeriesSeason collection management service."
        << endl;
   return  msg.append(ss.str());
}

bool MediaLibraryServer::toJsonFile(){
   cout << "saving collection to seriesTest.json" << endl;
   bool ret = library->toJsonFile("seriesTest.json");
   return ret;
}

Json::Value MediaLibraryServer::initLibraryFromJsonFile(){
   cout << "restoring collection from seriesTest.json" << endl;
   library->initLibraryFromJsonFile("seriesTest.json");
   Json::Value ret = getJson();
   return ret;
}

bool MediaLibraryServer::addLibrary(const Json::Value& aLibraryJson) {
    Json::Value::Members mbr = aLibraryJson.getMemberNames();
    std::map<std::string, SeriesSeason> mp;
    mp.clear();
    for(vector<string>::const_iterator i = mbr.begin(); i!= mbr.end(); i++){
        Json::Value jsonMedia = aLibraryJson[*i];
        SeriesSeason * aDesc = new SeriesSeason(jsonMedia);
        mp[*i] = *aDesc;
    }

   cout << "Adding Library..." << endl;
   bool ret = library->addLibrary(mp);
   return ret;
}

bool MediaLibraryServer::addToLibrary(const Json::Value& aSeriesSeasonJson) {
   SeriesSeason aSS(aSeriesSeasonJson);
   cout << "Adding " << aSS.titleAndSeason << endl;
   bool ret = library->addToLibrary(aSS);
   return ret;
}

bool MediaLibraryServer::removeFromLibrary(const string& key) {
   cout << "Removing " << key << endl;
   bool ret = library->removeFromLibrary(key);
   return ret;
}

Json::Value MediaLibraryServer::getJson(){
   cout << "Getting Json of Library" << endl;
   return library->getJson();
}


Json::Value MediaLibraryServer::get(const string& key){
    cout << "Getting SeriesSeason " << key << endl;
    return library->get(key).toJson();
}

Json::Value MediaLibraryServer::getTitles(){
   Json::FastWriter fw;
   Json::Value r(Json::arrayValue);
   std::vector<string> myVec = library->getTitles();
   for (std::vector<string>::iterator it = myVec.begin(); it!=myVec.end();++it)
   {
       r.append(Json::Value(*it));
   }
   std::string Titles = fw.write(r);
   cout << "Get Titles returning: " << Titles  << endl;
   return r;
}

void exiting(){
   std::cout << "Server has been terminated. Exiting normally" << endl;
   //ss.StopListening();
}

int main(int argc, char * argv[]) {
   // invoke with ./bin/studentRPCServer 8080
   int port = 8080;
   if(argc > 1){
      port = atoi(argv[1]);
   }
   HttpServer httpserver(port);
   MediaLibraryServer ss(httpserver, port);
   // to use tcp sockets instead of http uncomment below (comment above), and the include
   // for tcpsocketserver.h above. If not running locally, you will need to input ip & port
   // from command line for both server and client programs.
   //TcpSocketServer tcpserver("localhost",port);
   //StudentServer ss(tcpserver, port);
   std::atexit(exiting);
   auto ex = [] (int i) {cout << "server terminating with signal " << i << endl;
                         // ss.StopListening();
                         exit(0);
                         //return 0;
                        };
   // ^C
   std::signal(SIGINT, ex);
   // abort()
   std::signal(SIGABRT, ex);
   // sent by kill command
   std::signal(SIGTERM, ex);
   // ^Z
   std::signal(SIGTSTP, ex);
   cout << "Student collection server listening on port " << port
      //<< " press return/enter to quit." << endl;
        << " use ps to get pid. To quit: kill -9 pid or press CTRL+C " << endl;
   ss.StartListening();
   while(true){
      //Since all methods are called via clientside GUI, this while loop is intentionally empty to enable server to listen to client method calls
   }
   ss.StopListening();
   return 0;
}