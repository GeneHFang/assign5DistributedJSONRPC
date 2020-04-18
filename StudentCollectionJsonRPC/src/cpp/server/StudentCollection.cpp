/**
 * Copyright 2020 Tim Lindquist,
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 * Purpose: StudentCollection is a class defining the interface between clients
 * and the server. The server implementation of StudentCollection
 * provides storage for description of multiple students
 *
 * Ser321 Principles of Distributed Software Systems
 * see http://pooh.poly.asu.edu/Ser321
 * @author Tim Lindquist Tim.Lindquist@asu.edu
 *         Software Engineering, CIDSE, IAFSE, ASU Poly
 * @version April 2020
 */

#include "StudentCollection.hpp"
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <jsonrpccpp/server.h>
#include <jsonrpccpp/server/connectors/httpserver.h>

using namespace std;
StudentCollection::StudentCollection(){
   resetFromJsonFile("students.json");
}

StudentCollection::~StudentCollection() {
   //cout << "student collection destructor.\n";
   library.clear();
}

bool StudentCollection::resetFromJsonFile(string jsonFileName){
   bool ret = false;
   Json::Reader reader;
   Json::Value root;
   std::ifstream json(jsonFileName.c_str(), std::ifstream::binary);
   bool parseSuccess = reader.parse(json,root,false);
   if(parseSuccess){
      Json::Value::Members mbr = root.getMemberNames();
      for(vector<string>::const_iterator i = mbr.begin(); i!= mbr.end(); i++){
         //cout << *i << " " << endl;
        Json::Value jsonMedia = root[*i];
         Student * aStudent = new Student(jsonMedia);
         library[*i] = *aStudent;
         //cout << "adding ";
         //aStudent->print();
      }
      ret = true;
   }
   return ret;
}

bool StudentCollection::saveToJsonFile(string jsonFileName){
   bool ret = false;
   Json::Value jsonLib;
   for(std::map<string,Student>::iterator i = library.begin();
                                              i != library.end(); i++){
      string key = i->first;
      //cout << key << " " << endl;
      Student aStudent = library[key];
      Json::Value jsonStudent = aStudent.toJson();
      jsonLib[key] = jsonStudent;
   }
   ret = true;
   Json::StyledStreamWriter ssw("  ");
   std::ofstream jsonOutFile(jsonFileName.c_str(), std::ofstream::binary);
   ssw.write(jsonOutFile, jsonLib);
   return ret;
}

bool StudentCollection::add(const Json::Value& aStudentJson){
   bool ret = false;
   Student aStudent(aStudentJson);
   // The map container does not allow duplicates so adding will replace existing
   // value with new Student instance.
   //aStudent.print();
   library[aStudent.name]=aStudent;
   return true;
}

bool StudentCollection::remove(string aName){
   bool ret = false;
   // does the library contain this student? if so remove, if not return false
   if(library.count(aName)>0){
      library.erase(aName);
      ret = true;
   }
   return true;
}

Json::Value StudentCollection::get(string aName){
   Student aStudent("{\"name\":\""+aName+" Unknown\",\"studentid\":-1,\"takes\":[\"None\" ]}");
   if(library.count(aName)>0){
         aStudent = library[aName];
   }
   return aStudent.toJson();
}

Json::Value StudentCollection::getNames(){
   Json::Value ret(Json::arrayValue);
   vector<string> myVec;
   for(map<string,Student>::iterator it = library.begin();
                                     it != library.end(); ++it){
      myVec.push_back(it->first);
   }
   for(std::vector<string>::iterator it = myVec.begin(); it!=myVec.end();++it) {
      ret.append(Json::Value(*it));
   }
   return ret;
}

std::string StudentCollection::getById(int studentid){
   std::string ret="";
   for(map<string,Student>::iterator it = library.begin();
                                              it != library.end();++it){
      Student stud = library[it->first];
      if(stud.studentid == studentid){
         ret = stud.name;
      }
   }
   return ret;
}
