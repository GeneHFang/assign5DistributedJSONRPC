/**
 * Copyright (c) 2020 Tim Lindquist,
 * Software Engineering,
 * Arizona State University at the Polytechnic campus
 * <p/>
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation version 2
 * of the License.
 * <p/>
 * This program is distributed in the hope that it will be useful,
 * but without any warranty or fitness for a particular purpose.
 * <p/>
 * Please review the GNU General Public License at:
 * http://www.gnu.org/licenses/gpl-2.0.html
 * see also: https://www.gnu.org/licenses/gpl-faq.html
 * so you are aware of the terms and your rights with regard to this software.
 * Or, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,USA
 * <p/>
 * Purpose: C++ class to represent a student. This class is part of a
 * student collection distributed application that uses JsonRPC.
 * Meant to run on OSX, Debian Linux, and Raspberry Pi Debian.
 * <p/>
 * Ser321 Principles of Distributed Software Systems
 * see http://pooh.poly.asu.edu/Ser321
 * @author Tim Lindquist (Tim.Lindquist@asu.edu),ASU-IAFSE,Software Engineering
 * @file    Student.cpp
 * @date    April, 2020
 * @license See above
 **/

#include "Student.hpp"
#include <iostream>
#include <stdlib.h>
Student::Student(){
   name = "";
   studentid = 0;
   takes = vector<string>();
}

Student::Student(string aName, int aStudentId, vector<string> aTakes) {
   name = aName;
   studentid = aStudentId;
   takes = aTakes;
}

Student::Student(const Json::Value& jsonObj){
   string nameStr = "name";
   string studentidStr = "studentid";
   string takesStr = "takes";
   Json::Value::Members mbr = jsonObj.getMemberNames();
   for(vector<string>::const_iterator i = mbr.begin(); i!= mbr.end(); i++){
      Json::Value jsonM = jsonObj[*i];
      if(nameStr.compare(*i)==0){
         name = jsonM.asString();
      }else if(studentidStr.compare(*i)==0){
         studentid = jsonM.asInt();
      }else if(takesStr.compare(*i)==0){
         takes = vector<string>();
         for(int i=0; i<jsonM.size(); i++){
            takes.push_back(jsonM[i].asString());
         }
      }
   }
}

Student::Student(string jsonString){
   string nameStr = "name";
   string studentidStr = "studentid";
   string takesStr = "takes";
   Json::Reader reader;
   Json::Value root;
   bool parseSuccess = reader.parse(jsonString,root,false);
   if(parseSuccess){
      Json::Value::Members mbr = root.getMemberNames();
      for(vector<string>::const_iterator i = mbr.begin(); i!= mbr.end(); i++){
         Json::Value jsonM = root[*i];
         if(nameStr.compare(*i)==0){
            name = jsonM.asString();
         }else if(studentidStr.compare(*i)==0){
            studentid = jsonM.asInt();
         }else if(takesStr.compare(*i)==0){
            takes = vector<string>();
            for(int i=0; i<jsonM.size(); i++){
               takes.push_back(jsonM[i].asString());
            }
         }
      }
   }else{
      cout << "Student constructor parse error with input: " << jsonString
           << endl;
   }
}

Student::~Student() {
   name = "";
   studentid = -1;
}

string Student::toJsonString(){
   string ret = "{}";
   Json::Value jsonLib;
   jsonLib["name"] = name;
   jsonLib["studentid"] = studentid;
   Json::Value tmp(Json::arrayValue);
   for(int i=0; i<takes.size(); i++){
      tmp[i]=takes[i];
   }
   jsonLib["takes"] = tmp;
   ret = jsonLib.toStyledString();
   return ret;
}

Json::Value Student::toJson(){
   Json::Value jsonLib;
   jsonLib["name"] = name;
   jsonLib["studentid"] = studentid;
   Json::Value tmp(Json::arrayValue);
   for(int i=0; i<takes.size(); i++){
      tmp[i]=takes[i];
   }
   jsonLib["takes"] = tmp;
   return jsonLib;
}

void Student::setValues(string aName, int aStudentId, vector<string> aTakes) {
   name = aName;
   studentid = aStudentId;
   takes = aTakes;
}

void Student::print(){
   cout << "Student " << name << " with ID "
        << studentid << " takes ";
   for (int i=0; i<takes.size(); i++){
      cout << takes[i] << " ";
   }
   cout << endl;
}
