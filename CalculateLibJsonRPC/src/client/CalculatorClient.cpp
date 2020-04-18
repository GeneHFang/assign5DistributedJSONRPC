/**
 * Copyright (c) 2015 Tim Lindquist,
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
 * Purpose: C++ calculate server using json-rpc-cpp.
 * This class provides methods to providing remote arithmetic functions.
 * Meant to run on OSX, Debian Linux, and Raspberry Pi Debian.
 * <p/>
 * Ser321 Principles of Distributed Software Systems
 * see http://pooh.poly.asu.edu/Cst420
 * @author Tim Lindquist (Tim.Lindquist@asu.edu),ASU-IAFSE,Software Engineering
 * @file    CalculateServer.cpp
 * @date    July, 2015
 * @license See above
 **/
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <jsonrpccpp/client/connectors/httpclient.h>
#include "calculatestub.h"

using namespace jsonrpc;
using namespace std;

void split(vector<string> & aStringVector,  /* return value */
           const string & aString,
           const string & aDelimiter) {
   size_t  start = 0, end = 0;
   while ( end != string::npos) {
      end = aString.find(aDelimiter, start);
      // If at end, use length=maxLength.  Else use length=end-start.
      aStringVector.push_back(aString.substr(start,
                          (end == string::npos) ? string::npos : end - start));
      // If at end, use start=maxSize.  Else use start=end+delimiter.
      start = ((end > (string::npos - aDelimiter.size()) )
               ? string::npos : end + aDelimiter.size());
   }
}

int main(int argc, char*argv[]) {
   string host = "http://127.0.0.1:8080";
   if(argc>1){
      host = string(argv[1]);
   }
   HttpClient httpclient(host);
   calculatestub cc(httpclient);
   cout << "Connecting to host " << host << endl;
   try {
      string inLine;
      cout << "Connected to: "  << cc.serviceInfo() << endl;
      while(true){
         std::cout << "Enter end or {+|-|*|/} double double -- eg: + 5 10 >";
         std::getline (std::cin, inLine);
         vector<string> tokens;
         split(tokens, inLine, " ");
         if(tokens.size()>=3){
            double left, right;
            istringstream leftStream(tokens[1]);
            leftStream >> left;
            istringstream rightStream(tokens[2]);
            rightStream >> right;
            double result = 0.0;
            if(tokens[0]=="+"){
               result = cc.plus(left,right);
            } else if(tokens[0]=="-"){
               result = cc.minus(left,right);
            } else if(tokens[0]=="*"){
               result = cc.times(left,right);
            } else if(tokens[0]=="/"){
               result = cc.divide(left,right);
            } 
            cout << tokens[1] << " " << tokens[0] << " " << tokens[2]
                 <<   " is " << result << endl;
         } else if(tokens[0]=="end"){
            break;
         }
      }
   } catch (JsonRpcException e) {
      cerr << e.what() << endl;
   }
}

