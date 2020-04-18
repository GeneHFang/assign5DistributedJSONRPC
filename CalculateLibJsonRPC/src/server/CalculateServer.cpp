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
 * Meant to run on OSX, Cygwin, and Raspberry Pi Debian.
 * <p/>
 * Ser321 Principles of Distributed Software Systems
 * see http://pooh.poly.asu.edu/Cst420
 * @author Tim Lindquist (Tim.Lindquist@asu.edu),ASU-IAFSE,Software Engineering
 * @file    CalculateServer.cpp
 * @date    July, 2015
 * @license See above
 **/
#include <jsonrpccpp/server.h>
#include <jsonrpccpp/server/connectors/httpserver.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "calculateserverstub.h"

using namespace jsonrpc;
using namespace std;

class CalculateServer : public calculateserverstub {
public:
  CalculateServer(AbstractServerConnector &connector, int port);

  virtual void notifyServer();
  virtual std::string serviceInfo();
  virtual double plus(double param1, double param2);
  virtual double minus(double param1, double param2);
  virtual double times(double param1, double param2);
  virtual double divide(double param1, double param2);
private:
  int portNum;
};

CalculateServer::CalculateServer(AbstractServerConnector &connector,
                                 int port) :
  calculateserverstub(connector){
  portNum = port;
  cout << "server up and listening on port " << port << endl;
}

void CalculateServer::notifyServer(){
  cout << "Calculate server notified" << endl;
}

string CalculateServer::serviceInfo(){
   std::string msg =
                "Calculate service providing plus,minus,times,divide on port ";
   stringstream ss;
   ss << portNum;
   return  msg.append(ss.str());
}

double CalculateServer::plus(double param1, double param2) {
   cout << "Requested " << param1 << " + " << param2 << " returning "
        << (param1 + param2) << endl;
   return param1 + param2;
}

double CalculateServer::minus(double param1, double param2) {
   cout << "Requested " << param1 << " - " << param2 << " returning "
        << (param1 - param2) << endl;
   return param1 - param2;
}

double CalculateServer::times(double param1, double param2) {
   cout << "Requested " << param1 << " * " << param2 << " returning "
        << (param1 * param2) << endl;
   return param1 * param2;
}

double CalculateServer::divide(double param1, double param2) {
   cout << "Requested " << param1 << " / " << param2 << " returning "
        << (param1 / param2) << endl;
   return param1 / param2;
}

int main(int argc, char * argv[]) {
   int port = 8080;
   if(argc > 1){
      port = atoi(argv[1]);
   }
   //cout << port << endl;
   HttpServer httpserver(port);
   CalculateServer cs(httpserver, port);
   cs.StartListening();
   int c = getchar();
   cs.StopListening();
   return 0;
}
